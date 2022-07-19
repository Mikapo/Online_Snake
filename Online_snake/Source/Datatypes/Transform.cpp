#include "Transform.h"

float Transform2D::get_dist(glm::vec2 other_loc)
{
    return (other_loc - m_location).length();
}