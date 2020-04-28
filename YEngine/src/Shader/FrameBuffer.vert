#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;
uniform vec4 u_objectColor;

out vec2 TexCoords;

void main()
{
  gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);
  TexCoords = texCoords;
}