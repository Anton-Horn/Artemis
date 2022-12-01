#include "VertexBuffer.h"
#include "Rendering/OpenGL/OpenGLVertexBuffer.h"


std::shared_ptr<VertexBuffer> VertexBuffer::Create(const VertexBufferSpec& spec, RenderingAPI api)
{
    if (api == RenderingAPI::OpenGL) {
        return std::make_shared<OpenGLVertexBuffer>(spec);
    }
    return nullptr;
}

std::shared_ptr<VertexBuffer>VertexBuffer::Create(const VertexBufferSpec& spec, void* data, RenderingAPI api)
{
    if (api == RenderingAPI::OpenGL) {
        return std::make_shared<OpenGLVertexBuffer>(spec, data);
    }
    return nullptr;
}


