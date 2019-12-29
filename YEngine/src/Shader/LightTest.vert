#version 330 core
attribute vec3 a_position;
attribute vec3 a_normal;


uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform vec3 u_lightPos;
uniform vec4 u_lightColor;
uniform vec3 u_viewPos;
uniform float u_specularStrength; 

varying vec3 v_lightPos;
varying vec4 v_lightColor;
varying vec3 v_normal;
varying vec3 v_fragPos;
varying vec3 v_viewPos;
varying float v_specularStrength;

void main()
{
   gl_Position = u_projection * u_view * u_model * vec4(a_position,1.0);
   v_lightColor = u_lightColor;
   v_normal = mat3(transpose(inverse(u_model))) * a_normal;
   v_fragPos =  vec3(u_model * vec4(a_position,1.0));
   v_lightPos = u_lightPos;
   v_viewPos = u_viewPos;
   v_specularStrength = u_specularStrength;
}
