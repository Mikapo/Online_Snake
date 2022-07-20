#pragma once

#include <deque>
#include <mutex>

namespace Networking
{
	template<typename T>
	class Thread_safe_queue
	{
	public:
		Thread_safe_queue() = default;
		Thread_safe_queue(const Thread_safe_queue&) = delete;
		Thread_safe_queue(Thread_safe_queue&&) = delete;
		~Thread_safe_queue() { clear(); }

		Thread_safe_queue& operator=(const Thread_safe_queue&) = delete;
		Thread_safe_queue& operator=(Thread_safe_queue&&) = delete;

		const T& front() const
		{
			std::scoped_lock lock(m_mutex);
			return m_queue.front();
		}

		const T& back() const
		{
			std::scoped_lock lock(m_mutex);
			return m_queue.back();
		}

		void push_front(const T& item)
		{
			std::scoped_lock lock(m_mutex);
			return m_queue.push_front(std::move(item));
		}

		void push_back(const T& item)
		{
			std::scoped_lock lock(m_mutex);
			return m_queue.push_back(std::move(item));
		}

		bool empty() const noexcept
		{
			std::scoped_lock lock(m_mutex);
			return m_queue.empty();
		}

		size_t count() const noexcept
		{
			std::scoped_lock lock(m_mutex);
			return m_queue.count();
		}

		void clear()
		{
			std::scoped_lock lock(m_mutex);
			return m_queue.clear();
		}

		T pop_front()
		{
			std::scoped_lock lock(m_mutex);
			auto temp = std::move(m_queue.front());
			m_queue.pop_front();
			return temp;
		}

		T pop_back()
		{
			std::scoped_lock lock(m_mutex);
			auto temp = std::move(m_queue.back());
			m_queue.pop_back();
			return temp;
		}

	private:
		std::mutex m_mutex;
		std::deque<T> m_queue;
	};
}

