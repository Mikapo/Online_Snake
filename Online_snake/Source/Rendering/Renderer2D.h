#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

class Shader;
struct Buffers;
class Renderer2D
{
public:
    Renderer2D();
    ~Renderer2D();

    Renderer2D(const Renderer2D&) = delete;
    Renderer2D(Renderer2D&&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;
    Renderer2D& operator=(Renderer2D&&) = delete;

    void init();
    void change_coordinate_system(glm::vec2 min, glm::vec2 max);
    void draw_square(glm::vec2 pos, glm::vec2 scale, glm::vec4 color) const;

private:
    Shader* m_shader = nullptr;
    Buffers* m_square_buffers = nullptr;
    glm::mat4 m_projection;
};
