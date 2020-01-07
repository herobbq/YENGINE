#version 330 core

in vec2 TexCoords;

out vec4 fragColor;
uniform sampler2D u_texture1;

void main()
{
	vec4 color = texture(u_texture1,TexCoords);
	 fragColor =color;
}