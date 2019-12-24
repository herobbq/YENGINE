#version 330 core
attribute vec3 a_position;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;

uniform vec3 u_lightColor;

varying vec3 v_lightPos;
varying vec3 v_lightColor;

void main()
{
   gl_Position = u_projection * u_view * u_model * vec4(a_position,1.0);
   v_lightColor= u_lightColor;
}
