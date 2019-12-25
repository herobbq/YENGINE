#version 330 core

varying vec4 v_objectColor;

out vec4 fragColor;

void main()
{
	fragColor = v_objectColor;
}