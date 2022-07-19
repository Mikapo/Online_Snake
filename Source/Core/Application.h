#pragma once

#include "Key.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <chrono>
#include <glm/vec4.hpp>
#include <memory>
#include <string>

template <typename... Argtypes>
class Application_delegate
{
public:
    virtual ~Application_delegate() = default;

    virtual void call(Argtypes... args) = 0;
};

template <typename T, typename... Argtypes>
class Application_delegate_obj : public Application_delegate<Argtypes...>
{
public:
    Application_delegate_obj(T* obj, void (T::*f)(Argtypes...)) noexcept : m_obj(obj), m_f(f)
    {
    }

    void call(Argtypes... args) noexcept override
    {
        (m_obj->*m_f)(std::forward<Argtypes>(args)...);
    };

private:
    T* m_obj;
    void (T::*m_f)(Argtypes...);
};

struct GLFWwindow;
class Application
{
public:
    Application() = default;

    Application(Application&&) = delete;
    Application(const Application&) = delete;
    Application& operator=(Application&&) = delete;
    Application& operator=(const Application&) = delete;

    void start();

    template <typename T>
    void set_on_window_open_callback(T* obj, void (T::*f)())
    {
        on_window_open_callback = std::make_unique<Application_delegate_obj<T>>(obj, f);
    }

    template <typename T>
    void set_render_callback(T* obj, void (T::*f)())
    {
        m_render_callback = std::make_unique<Application_delegate_obj<T>>(obj, f);
    }

    template <typename T>
    void set_cleanup_callback(T* obj, void (T::*f)())
    {
        m_cleanup_callback = std::make_unique<Application_delegate_obj<T>>(obj, f);
    }

    template <typename T, typename... argtypes>
    void set_on_key_event_callback(T* obj, void (T::*f)(argtypes...))
    {
        m_on_key_event_callback = std::make_unique<Application_delegate_obj<T, Input_key, Input_action>>(obj, f);
    }

    template <typename T, typename... argtypes>
    void set_window_resize_callback(T* obj, void (T::*f)(argtypes...))
    {
        m_window_resize_callback = std::make_unique<Application_delegate_obj<T, int32_t, int32_t>>(obj, f);
    }

    inline GLFWwindow* get_window() const noexcept
    {
        return m_window;
    }

    void get_window_dimensions(int32_t& out_width, int32_t& out_height) const noexcept;
    void on_window_resize(GLFWwindow* window, int32_t new_width, int32_t new_height);
    void on_key_event(int32_t key, int32_t scancode, int32_t action, int32_t mods);
    void set_window_dimensions(int32_t width, int32_t height) noexcept;
    void set_window_title(std::string_view name);

private:
    void setup_callbacks() const noexcept;
    void init();
    void cleanup();
    void render_loop();

    std::string m_name = "Window";
    int32_t m_width = 1000, m_height = 1000;
    GLFWwindow* m_window = nullptr;
    bool m_has_started = false;
    glm::vec4 m_background_color = {0.0f, 0.0f, 0.0f, 0.0f};
    std::unique_ptr<Application_delegate<>> on_window_open_callback;
    std::unique_ptr<Application_delegate<>> m_render_callback;
    std::unique_ptr<Application_delegate<>> m_cleanup_callback;
    std::unique_ptr<Application_delegate<int32_t, int32_t>> m_window_resize_callback;
    std::unique_ptr<Application_delegate<Input_key, Input_action>> m_on_key_event_callback;
};
