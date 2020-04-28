#version 330 core

in vec2 TexCoords;

out vec4 fragColor;
uniform sampler2D u_texture1;

void main()
{
	vec3 color = vec3(texture(u_texture1,TexCoords));
	 fragColor = vec4(color,1.0);
}