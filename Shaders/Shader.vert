#version 330 core

layout (location = 0) in vec3 l_position;

uniform mat4 u_projection = mat4(1);
uniform mat4 u_model = mat4(1);

void main() 
{
    gl_Position = u_projection *  u_model * vec4(l_position, 1);
}