
#include "VertexBuffer.h"

#include "Rendering/OpenGL/OpenGLVertexBuffer.h"

#include "RenderingPipeline.h"



VertexBuffer* VertexBuffer::Create(const VertexBufferSpec& spec)
{
    if (RenderingPipeline::GetData().API == RenderingAPI::OpenGL) {
        return new OpenGLVertexBuffer(spec);
    }
    return nullptr;
}

VertexBuffer* VertexBuffer::Create(const VertexBufferSpec& spec, void* data)
{
    if (RenderingPipeline::GetData().API == RenderingAPI::OpenGL) {
        return new OpenGLVertexBuffer(spec, data);
    }
    return nullptr;
}


