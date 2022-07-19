#pragma once

#include <memory>

#include "Vertex_buffer.h"
#include "Vertex_array.h"
#include "Index_buffer.h"


struct Buffers
{
public:
	Buffers(std::vector<float>&& vertices, std::vector<uint32_t>&& indices, Vertex_buffer_layout layout)
		: m_vertices(vertices),
		  m_indices(indices),
		  m_layout(layout)
	{
		m_indices_amount = indices.size();
	}

	void bind()
	{
		if (!m_has_been_initialized)
			initialize();

		m_va->bind();
		m_ib->bind();
	}
	void unbind() noexcept
	{
		if (!m_has_been_initialized)
			return;

		m_va->unbind();
		m_ib->unbind();
	}

	size_t get_indices_count() noexcept
	{
		return m_indices_amount;
	}

private:
	void initialize()
	{
		if (m_has_been_initialized)
			return;

		m_vb = std::make_unique<Vertex_buffer>(m_vertices.data(), sizeof(float) * m_vertices.size());
		m_va = std::make_unique<Vertex_array>();
		m_va->add_buffer(*m_vb, m_layout);
		m_ib = std::make_unique<Index_buffer>(m_indices.data(), m_indices.size());

		m_vertices.clear();
		m_indices.clear();

		m_has_been_initialized = true;
	}

	bool m_has_been_initialized = false;
	std::vector<float> m_vertices;
	std::vector<uint32_t> m_indices;
	Vertex_buffer_layout m_layout;
	size_t m_indices_amount = 0;

	std::unique_ptr<Vertex_buffer> m_vb;
	std::unique_ptr <Vertex_array> m_va;
	std::unique_ptr<Index_buffer> m_ib;
};

