#pragma once

#include "glm/vec2.hpp"

struct Transform2D
{
    Transform2D() = default;
    Transform2D(glm::vec2 location, float angle, glm::vec2 scale) : m_location(location), m_angle(angle), m_scale(scale)
    {
    }

    glm::vec2 m_location = {0.0f, 0.0f};
    float m_angle = 0.0f;
    glm::vec2 m_scale = {1.0f, 1.0f};
};
