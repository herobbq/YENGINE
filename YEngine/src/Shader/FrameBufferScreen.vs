#version 330 core

attribute vec2 a_position;
attribute vec2 a_texCoord;

out vec2 texcoord;

void main()
{
  gl_Position = vec4(a_position.x,a_position.y,0.0,1.0);
  texcoord = a_texCoord;

}