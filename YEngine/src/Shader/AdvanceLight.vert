#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoords;


uniform mat4 u_view;

uniform mat4 u_projection;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;


out vec3 v_lightPos;
out vec3 v_normal;
out vec3 v_fragPos;
out vec3 v_viewPos;
out vec2 v_texCoords;

void main()
{
   gl_Position = u_projection * u_view  * vec4(a_position,1.0);
   v_normal =  a_normal;
   v_fragPos =  a_position;
   v_lightPos = u_lightPos;
   v_viewPos = u_viewPos;
   v_texCoords = a_texCoords;
  
}
