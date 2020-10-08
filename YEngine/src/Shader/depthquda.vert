#version 330 core
layout(location = 0) in vec3 a_position;
layout (location = 2) in vec2 a_texCoords;

out vec2 TexCoords;
void main()
{
  TexCoords = a_texCoords;
  gl_Position = vec4(a_position,1.0);
}