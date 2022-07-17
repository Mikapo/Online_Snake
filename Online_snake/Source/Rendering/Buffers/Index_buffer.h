#pragma once

#include "Rendering/Renderer_item.h"
#include <cstdint>

#include "GL/glew.h"

class Index_buffer : public Renderer_item
{
public:
    Index_buffer(const void* data, size_t count) noexcept;
    ~Index_buffer();
    Index_buffer(const Index_buffer&) = delete;
    Index_buffer(Index_buffer&&) = default;

    void operator=(const Index_buffer&) = delete;
    void operator=(Index_buffer&&) = delete;

    void bind() const noexcept;
    void unbind() const noexcept;
    inline size_t get_count() const noexcept { return m_count; }

private:
    size_t m_count;
};
