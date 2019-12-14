#version 330 core

attribute vec3 a_position;
attribute vec3 a_color;
attribute vec2 a_texCoord;
 uniform mat4 u_model;
 uniform mat4 u_view;
 uniform mat4 u_projection;
 
 out vec2 texCoord;
 void main()
 {
   gl_Position = u_projection * u_view * u_model * vec4(a_position,1.0);
   texCoord = vec2(a_texCoord.x, 1.0 - a_texCoord.y);
 }