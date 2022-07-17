#define GLEW_STATIC

#include "Renderer2D.h"

#include "GL/glew.h"
#include "Shading/Shader.h"
#include "Buffers/Buffers.h"

#include "Debug/Debug_logger.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void GLAPIENTRY opengl_debug(
    GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​,
    const void* userParam​)
{
    std::string_view source_string;
    Log_severity log_severity;

    switch (source​)
    {
    case GL_DEBUG_SOURCE_API:
        source_string = "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source_string = "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source_string = "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source_string = "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        source_string = "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        source_string = "Source: Other";
        break;
    default:
        source_string = "Source: Unknown";
    }

    switch (severity​)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        log_severity = Log_severity::error;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        log_severity = Log_severity::warning;
        break;
    case GL_DEBUG_SEVERITY_LOW:
        log_severity = Log_severity::warning;
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        log_severity = Log_severity::notification;
        break;
    default:
        log_severity = Log_severity::notification;
        break;
    }

    Debug_logger::get().log(log_severity, Log_type::opengl, std::format("{}: {}", source_string, message​));
}

Renderer2D::~Renderer2D()
{
    if (m_shader)
        delete m_shader;

    if (m_square_buffers)
        delete m_square_buffers;
}

void Renderer2D::init()
{
    glewInit();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(opengl_debug, NULL);
#endif

    Vertex_buffer_layout Layout;
    Layout.push<float>(2);

    std::vector<float> square_vertices
    {
        -0.5,  -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    std::vector<uint32_t> square_indices
    {
        0, 1, 2,
        0, 2, 3
    };

    m_square_buffers = new Buffers(std::move(square_vertices), std::move(square_indices), Layout);
    m_shader = new Shader("Shaders/Shader.frag", "Shaders/Shader.vert");
}

void Renderer2D::change_coordinate_system(glm::vec2 min, glm::vec2 max) const
{
    if (m_shader)
    {
        const glm::mat4 projection = glm::ortho(min.x, max.x, min.y, max.y);
        m_shader->set_uniform_mat4f("u_projection", projection);
    }
}

void Renderer2D::draw_square(glm::vec2 pos, glm::vec2 scale, glm::vec4 color) const
{
    if (!m_shader && !m_square_buffers)
        return;

    const glm::mat4 identity = glm::mat4(1);
    const glm::mat4 translate = glm::translate(identity, glm::vec3(pos, 0));
    const glm::mat4 scale_mat = glm::scale(identity, glm::vec3(scale.x, scale.y, 1));
    const glm::mat4 model = translate * scale_mat;

    m_shader->set_uniform_mat4f("u_model", model);
    m_shader->set_uniform4f("u_color", color.r, color.g, color.b, color.a);
    m_shader->bind();
    m_square_buffers->bind();

    GLsizei IndicesCount = static_cast<GLsizei>(m_square_buffers->get_indices_count());
    glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, nullptr);
}
