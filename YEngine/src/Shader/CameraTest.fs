#version 330 core

in vec2 texCoord;

out vec4 fragColor;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
    fragColor = mix(texture(u_texture1,1.0-texCoord),texture(u_texture2,1.0-texCoord),0.2);
	
}