#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 LineColor;

void main()
{    
    FragColor = vec4(LineColor,1.0);
}