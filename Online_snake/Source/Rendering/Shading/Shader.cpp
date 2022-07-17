#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

Shader::Shader(std::string_view frag_path, std::string_view fert_path)
    : m_frag_path(frag_path), m_fert_path(fert_path), m_shader_id(0)
{
    std::string frag_source = parse_shader(frag_path);
    std::string fert_source = parse_shader(fert_path);

    m_shader_id = create_shader(fert_source, frag_source);
    glUseProgram(m_shader_id);
}

Shader::~Shader() { glDeleteProgram(m_shader_id); }

void Shader::bind() const noexcept { glUseProgram(m_shader_id); }

void Shader::unbind() const noexcept { glUseProgram(0); }

void Shader::set_uniform4f(std::string_view name, float v1, float v2, float v3, float v4)
{
    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniform4f(location, v1, v2, v3, v4);
    unbind();
}

void Shader::set_uniform4fv(std::string_view name, int32_t count, const float* v)
{
    if (count == 0)
        return;

    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniform4fv(location, static_cast<GLsizei>(count), v);
    unbind();
}

void Shader::set_uniform3f(std::string_view name, float v1, float v2, float v3)
{
    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniform3f(location, v1, v2, v3);
    unbind();
}

void Shader::set_uniform3fv(std::string_view name, int32_t count, const float* v)
{
    if (count == 0)
        return;

    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniform3fv(location, static_cast<GLsizei>(count), v);
    unbind();
}

void Shader::set_uniform2f(std::string_view name, float v1, float v2)
{
    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniform2f(location, v1, v2);
    unbind();
}

void Shader::set_uniform1f(std::string_view name, float v1)
{
    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniform1f(location, v1);
    unbind();
}

void Shader::set_uniform1i(std::string_view name, int32_t v1)
{
    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniform1i(location, v1);
    unbind();
}

void Shader::set_uniform_mat4f(std::string_view name, const glm::mat4& matrix)
{
    const int32_t location = get_uniform_location(name);
    if (location == -1)
        return;

    bind();
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    unbind();
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
        std::cout << message;
        glDeleteShader(id);
        throw std::runtime_error(message);
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
    std::stringstream ss[1];
    std::string line;

    while (getline(stream, line))
    {
        ss[0] << line << '\n';
    }
    return ss[0].str();
}