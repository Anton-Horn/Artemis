#include "VertexBuffer.h"
#include "Rendering/OpenGL/OpenGLVertexBuffer.h"


VertexBuffer* VertexBuffer::Create(const VertexBufferSpec& spec, RenderingAPI api)
{
    if (api == RenderingAPI::OpenGL) {
        return new OpenGLVertexBuffer(spec);
    }
    return nullptr;
}

VertexBuffer* VertexBuffer::Create(const VertexBufferSpec& spec, void* data, RenderingAPI api)
{
    if (api == RenderingAPI::OpenGL) {
        return new OpenGLVertexBuffer(spec, data);
    }
    return nullptr;
}


