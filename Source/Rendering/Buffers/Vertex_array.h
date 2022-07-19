#pragma once

#include "Rendering/Renderer_item.h"

#include "Vertex_buffer_layout.h"
#include <utility>

class Vertex_array : public Renderer_item
{
public:

    Vertex_array() noexcept;
    ~Vertex_array();
    Vertex_array(const Vertex_array&) = delete;
    Vertex_array(Vertex_array&&) = default;

    void operator=(const Vertex_array&) = delete;
    void operator=(Vertex_array&&) = delete;

    void add_buffer(const class Vertex_buffer& vb, const Vertex_buffer_layout& layout) const;
    void bind() const noexcept;
    void unbind() noexcept;
};