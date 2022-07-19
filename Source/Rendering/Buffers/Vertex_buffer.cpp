#include "Vertex_buffer.h"

#include "GL/Glew.h"

Vertex_buffer::Vertex_buffer(const void* data, GLsizeiptr size) noexcept
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Vertex_buffer::~Vertex_buffer()
{
    if(is_valid())
        glDeleteBuffers(1, &m_id);
}

void Vertex_buffer::bind() const noexcept
{
    if(is_valid())
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void Vertex_buffer::unbind() noexcept 
{ 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
