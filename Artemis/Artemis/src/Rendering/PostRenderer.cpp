#include "PostRenderer.h"

#include "Renderer2d.h"
#include "FrameBuffer.h"
#include "RendererImpl.h"

#include "Core/Application.h"

void PostRenderer::Init(RenderingAPI api)
{
    m_api = api;

    s_rendering_data.vertices[0] = { -1.0f,  1.0f, 0.0f, 0.0f, 0.0f };
    s_rendering_data.vertices[1] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f };
    s_rendering_data.vertices[2] = {  1.0f, -1.0f, 0.0f, 1.0f, 1.0f };
    s_rendering_data.vertices[3] = {  1.0f,  1.0f, 0.0f, 1.0f, 0.0f };

    VertexBufferSpec spec;
    spec.buffer_size = 4;
    spec.vertex_size = sizeof(PostRenderingVertex);
    spec.attributes = { {VertexBufferDataType::FLOAT, 3}, {VertexBufferDataType::FLOAT, 2} };
   
    s_rendering_data.vertex_buffer = VertexBuffer::Create(spec, s_rendering_data.vertices, m_api);

    Texture2DSpecification texture_spec;
    texture_spec.width = 0;
    texture_spec.height = 0;
    texture_spec.load_file = 0;
    texture_spec.data = nullptr;
    texture_spec.allow_texture_pointer = true;

    s_rendering_data.texture = Texture2D::Create(texture_spec, m_api);

    s_rendering_data.post_processing_shader = Shader::Create(Shader::LoadShaderSource("Assets/Shaders/PostRenderingShader.vert"), Shader::LoadShaderSource("Assets/Shaders/PostRenderingShader.frag") , RenderingAPI::OpenGL);

    uint32_t indices[] = {0, 1, 2, 2, 3, 0};
    s_rendering_data.index_buffer.SetData(IndexBufferType::UNSIGNED_INT, indices, sizeof(indices));


}

void PostRenderer::Terminate()
{
    delete s_rendering_data.texture;
    delete s_rendering_data.vertex_buffer;
    delete s_rendering_data.post_processing_shader;
}

void PostRenderer::DrawFrameBufferColorAttachment(FrameBuffer* framebuffer)
{

    RendererImpl* renderer = Application::GetRenderer2d().GetRendererImpl();
    renderer->SetViewport(0, 0, framebuffer->GetSpec().width, framebuffer->GetSpec().height);

    renderer->SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    renderer->Clear();

    renderer->DisableZBuffer();
    renderer->DisableAlphaBlending();

    s_rendering_data.texture->CreateTexturePointer(framebuffer->GetColorAttachmentRendererID(0));

    s_rendering_data.texture->BindTextureUnit(0);

    s_rendering_data.post_processing_shader->Bind();
    s_rendering_data.post_processing_shader->SetUniform1i(0, "u_sampler");
    renderer->DrawVertexBuffer(s_rendering_data.vertex_buffer, s_rendering_data.index_buffer);
    s_rendering_data.post_processing_shader->UnBind();

    renderer->EnableZBuffer();

}


