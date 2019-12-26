#version 330 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
out vec4 vertexColor;
void main()
{
	gl_Position = vec4 (a_position,1.0);
	vertexColor = vec4(a_color,1.0);
}