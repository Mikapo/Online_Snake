
#version 330 core

layout(location = 0) out vec4 out_frag_color;

uniform vec4 u_color = vec4(0.9f, 0.9f, 0.9f, 1.0f);

void main() 
{     
   out_frag_color = u_color;
}