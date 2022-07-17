#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Debug/Debug_logger.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>

Shader::Shader(std::string_view frag_path, std::string_view fert_path)
    : m_frag_path(frag_path), m_fert_path(fert_path), m_shader_id(0)
{
    LOG(notification, render, "Compiling shaders {} and {}", frag_path, fert_path);

    std::string frag_source = parse_shader(frag_path);
    std::string fert_source = parse_shader(fert_path);

    m_shader_id = create_shader(fert_source, frag_source);
    glUseProgram(m_shader_id);
}

Shader::~Shader()
{
    glDeleteProgram(m_shader_id);
}

void Shader::bind() const noexcept
{
    glUseProgram(m_shader_id);
}

void Shader::unbind() const noexcept
{
    glUseProgram(0);
}

void Shader::call_gl_uniform(int32_t pos, float v1, float v2, float v3, float v4) const noexcept
{
    glUniform4f(pos, v1, v2, v3, v4);
}

void Shader::call_gl_uniform(int32_t pos, int32_t count, const std::vector<std::array<float, 4>> v) const noexcept
{
    glUniform4fv(pos, static_cast<GLsizei>(count), v.data()->data());
}

void Shader::call_gl_uniform(int32_t pos, float v1, float v2, float v3) const noexcept
{
    glUniform3f(pos, v1, v2, v3);
}

void Shader::call_gl_uniform(int32_t pos, int32_t count, const std::vector<std::array<float, 3>> v) const noexcept
{
    glUniform3fv(pos, static_cast<GLsizei>(count), v.data()->data());
}

void Shader::call_gl_uniform(int32_t pos, float v1, float v2) const noexcept
{
    glUniform2f(pos, v1, v2);
}

void Shader::call_gl_uniform(int32_t pos, float v1) const noexcept
{
    glUniform1f(pos, v1);
}

void Shader::call_gl_uniform(int32_t pos, int32_t v1) const noexcept
{
    glUniform1i(pos, v1);
}

void Shader::call_gl_uniform(int32_t pos, const glm::mat4& matrix) const noexcept
{
    glUniformMatrix4fv(pos, 1, GL_FALSE, &matrix[0][0]);
}

int32_t Shader::get_uniform_location(std::string_view name)
{
    if (m_uniform_location_cache.contains(name))
        return m_uniform_location_cache[name];

    int32_t location = glGetUniformLocation(m_shader_id, name.data());
    m_uniform_location_cache[name] = location;
    return location;
}

uint32_t Shader::compile_shader(uint32_t type, std::string_view source)
{
    const uint32_t id = glCreateShader(type);
    const char* src = source.data();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int32_t result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int32_t lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = new char[lenght];
        glGetShaderInfoLog(id, lenght, &lenght, message);
        LOG(error, render, "{}", message);
        glDeleteShader(id);
        delete message;
    }

    return id;
}

uint32_t Shader::create_shader(std::string_view vertex_shader, std::string_view fragment_shader)
{
    const uint32_t program = glCreateProgram();
    const uint32_t vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    const uint32_t fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

std::string Shader::parse_shader(std::string_view filepath)
{
    std::ifstream stream(filepath.data());
    std::stringstream ss;
    std::string line;

    while (getline(stream, line))
    {
        ss << line << '\n';
    }

    return ss.str();
}
