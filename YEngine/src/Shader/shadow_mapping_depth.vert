#version 330 core

layout (location = 0) in vec3 a_Posistion;
layout (location = 2) in vec2 a_texCoords;
uniform mat4 lightSpaceMatrix;
uniform mat4 u_model;
out vec2 TexCoords;
void main()
{
    TexCoords  = a_texCoords;
    gl_Position = lightSpaceMatrix * u_model * vec4(a_Posistion, 1.0);
}