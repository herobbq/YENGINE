#version 330 core
layout(location =  0) in vec3 a_Position;
layout(location =  1) in vec3 a_Noraml;
layout(location =  2) in vec2 a_Texcoord;

out VS_OUT
{
	vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
}vs_out;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_lightSpaceMatrix ;


void main()
{
   gl_Position = u_projection * u_view * u_model * vec4(a_Position,1.0);
   vs_out.Normal = mat3(transpose(inverse(u_model))) * a_Noraml;
   vs_out.TexCoords = a_Texcoord;
   vs_out.FragPos =  vec3(u_model * vec4(a_Position,1.0));
   vs_out.FragPosLightSpace = u_lightSpaceMatrix * vec4(vs_out.FragPos,1.0);
}
