#include "Renderer_item.h"

#include <utility>

Renderer_item::Renderer_item(Renderer_item&& other) noexcept
{
	*this = std::move(other);
}

void Renderer_item::operator=(Renderer_item&& other) noexcept
{
	m_id = other.m_id;
	m_is_valid = other.m_is_valid;

	other.m_id = 0;
	other.m_is_valid = false;
}
