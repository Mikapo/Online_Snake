#pragma once

#include "Application.h"
#include "Rendering/Renderer2D.h"
#include <thread>

class Snake_game
{
public:
	Snake_game();

	void start();

private:
	void render_thread();
	void logic_thread();
	void on_window_open();
	void on_input(Input_key key, Input_action action);
	void cleanup();

	Application m_application;
	Renderer2D m_renderer;

	std::thread m_logic_thread;
	bool m_logic_thread_stop_flag = false;

};

