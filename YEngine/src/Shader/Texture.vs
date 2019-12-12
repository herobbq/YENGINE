#version 330 core

attribute vec3 a_position;
attribute vec3 a_color;
attribute vec2 a_texCoord;

out vec3 outColor;
out vec2 textCoord;

void main()
{
  gl_Position = vec4(a_position,1.0);
  outColor= a_color;
  textCoord = a_texCoord;
}