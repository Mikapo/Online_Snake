#pragma once

#include <array>
#include <glm/matrix.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class Shader
{
public:
    Shader(std::string_view frag_path, std::string_view fert_path);
    ~Shader();
    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;

    void operator=(const Shader&) = delete;
    void operator=(Shader&&) = delete;

    void bind() const noexcept;
    void unbind() const noexcept;

    template <typename... Types>
    void set_uniform(std::string_view name, Types... values)
    {
        const int32_t pos = get_uniform_location(name);

        if (pos != -1)
        {
            bind();
            call_gl_uniform(pos, values...);
        }
    }

private:
    void call_gl_uniform(int32_t pos, float v1, float v2, float v3, float v4) const noexcept;
    void call_gl_uniform(int32_t pos, int32_t count, const std::vector<std::array<float, 4>> v) const noexcept;
    void call_gl_uniform(int32_t pos, float v1, float v2, float v3) const noexcept;
    void call_gl_uniform(int32_t pos, int32_t count, const std::vector<std::array<float, 3>> v) const noexcept;
    void call_gl_uniform(int32_t pos, float v1, float v2) const noexcept;
    void call_gl_uniform(int32_t pos, float v1) const noexcept;
    void call_gl_uniform(int32_t pos, int32_t v1) const noexcept;
    void call_gl_uniform(int32_t pos, bool v1) const noexcept;
    void call_gl_uniform(int32_t pos, const glm::mat4& matrix) const noexcept;

    struct shader_source
    {
        std::string vertex_source;
        std::string fragment_source;
    };

    uint32_t create_shader(std::string_view vertex_shader, std::string_view fragment_shader);
    uint32_t compile_shader(uint32_t type, std::string_view source);
    std::string parse_shader(std::string_view filepath);
    int32_t get_uniform_location(std::string_view name);

    std::string m_frag_path;
    std::string m_fert_path;
    uint32_t m_shader_id;
    std::unordered_map<std::string_view, int32_t> m_uniform_location_cache;
};
