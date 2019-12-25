#version 330 core

in vec2 texcoord;

uniform sampler2D utexture;

out vec4 framgColor;
void main()
{
   vec3 col = texture(utexture,texcoord).rgb;
	framgColor = vec4(col,1.0);
}