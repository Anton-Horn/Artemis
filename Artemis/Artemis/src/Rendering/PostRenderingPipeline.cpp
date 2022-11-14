
#include "PostRenderingPipeline.h"

#include "RenderingPipeline.h"
#include "FrameBuffer.h"
#include "Renderer.h"



PostRenderingData PostRenderer::s_RenderingData;

void PostRenderer::Init()
{

    s_RenderingData.Vertices[0] = { -1.0f,  1.0f, 0.0f, 0.0f, 0.0f };
    s_RenderingData.Vertices[1] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f };
    s_RenderingData.Vertices[2] = {  1.0f, -1.0f, 0.0f, 1.0f, 1.0f };
    s_RenderingData.Vertices[3] = {  1.0f,  1.0f, 0.0f, 1.0f, 0.0f };

    VertexBufferSpec spec;
    spec.BufferSize = 4;
    spec.VertexSize = sizeof(PostRenderingVertex);
    spec.Attributes = { {VertexBufferDataType::FLOAT, 3}, {VertexBufferDataType::FLOAT, 2} };
   

    s_RenderingData.Vertexbuffer = VertexBuffer::Create(spec, s_RenderingData.Vertices);

    Texture2DSpecification texture_spec;
    texture_spec.Width = 0;
    texture_spec.Height = 0;
    texture_spec.LoadFile = 0;
    texture_spec.Data = nullptr;
    texture_spec.AllowTexturePointer = true;

    s_RenderingData.Texture = Texture2D::Create(texture_spec);
}

void PostRenderer::DrawFrameBufferColorAttachment(FrameBuffer* framebuffer)
{

    Renderer* renderer = RenderingPipeline::GetData().Renderer;
    renderer->SetViewport(0, 0, s_RenderingData.width, s_RenderingData.height);

    renderer->SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    renderer->Clear();

    renderer->DisableZBuffer();
    renderer->DisableAlphaBlending();

    s_RenderingData.Texture->CreateTexturePointer(framebuffer->GetColorAttachmentRendererID(0));

    s_RenderingData.Texture->BindTextureUnit(0);

    s_RenderingData.PostProcessingShader->Bind();
    s_RenderingData.PostProcessingShader->SetUniform1i(0, "u_sampler");
    renderer->DrawVertexBuffer(s_RenderingData.Vertexbuffer);
    s_RenderingData.PostProcessingShader->UnBind();

    renderer->EnableZBuffer();

}

void PostRenderer::Resize(int width, int height)
{
    s_RenderingData.width = width;
    s_RenderingData.height = height;
}

