#include "Snake_game.h"
#include "Debug/Debug_logger.h"

Snake_game::Snake_game()
{
    m_application.set_render_callback(this, &Snake_game::render_thread);
    m_application.set_on_window_open_callback(this, &Snake_game::on_window_open);
    m_application.set_on_key_event_callback(this, &Snake_game::on_input);
    m_application.set_cleanup_callback(this, &Snake_game::cleanup);
    m_application.set_window_title("Snake Game");
}

void Snake_game::start()
{
    LOG(notification, game, "Starting snake game");

    m_logic_thread_stop_flag = false;
    m_logic_thread = std::thread([this] { logic_thread(); });
    m_application.start();
}

void Snake_game::render_thread()
{
    Transform2D transform({10.0f, 10.0f}, 0.0f, {8.0f, 8.0f});

    m_renderer.draw_square(transform, {0.8f, 0.0f, 0.0f, 1.0f});

    transform.m_location = {20.0f, 20.0f};
    transform.m_angle = 45.0f;
    m_renderer.draw_square(transform, {0.0f, 0.8f, 0.0f, 1.0f});
}

void Snake_game::logic_thread()
{
    while (!m_logic_thread_stop_flag)
    {
    }
}

void Snake_game::on_window_open()
{
    m_renderer.init();
    m_renderer.change_coordinate_system({0.0f, 0.0f}, {30.0f, 30.0f});
}

void Snake_game::on_input(Input_key key, Input_action action)
{
    if (key == Input_key::A && action == Input_action::press)
        LOG(notification, other, "player pressed A");
}

void Snake_game::cleanup()
{
    LOG(notification, game, "Cleaning up and exiting snake game");

    m_logic_thread_stop_flag = true;
    m_logic_thread.join();
}
