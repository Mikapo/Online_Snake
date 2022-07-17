#pragma once

#include "Rendering/Renderer_item.h"

#include "GL/glew.h"
#include <utility>

class Vertex_buffer : public Renderer_item
{
public:
    Vertex_buffer(const void* data, GLsizeiptr size) noexcept;
    ~Vertex_buffer();
    Vertex_buffer(const Vertex_buffer&) = delete;
    Vertex_buffer(Vertex_buffer&&) = default;
    
    void operator=(const Vertex_buffer&) = delete;
    void operator=(Vertex_buffer&&) = delete;

    void bind() const noexcept;
    static void unbind() noexcept;
};
