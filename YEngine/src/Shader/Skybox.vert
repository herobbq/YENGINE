#version 330 core

attribute vec3 a_position;

out vec3 tex_coord;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
 tex_coord = a_position;
 vec4 pos = u_projection * u_view *vec4(a_position,1.0);
 gl_Position = pos.xyww;
}