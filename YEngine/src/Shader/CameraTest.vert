#version 330 core

attribute vec3 a_position;
attribute vec3 a_color;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
uniform vec3 u_viewPos;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
varying vec3 v_fargPos;
varying vec3 v_normal;
varying vec3 v_viewPos;
 out vec2 texCoord;
 void main()
 {
   gl_Position = u_projection * u_view * u_model * vec4(a_position,1.0);
   texCoord = a_texCoord;
   v_normal = mat3(transpose(inverse(u_model))) * a_normal;
   v_fargPos =  vec3(u_model * vec4(a_position,1.0));
   v_viewPos = u_viewPos;
 }