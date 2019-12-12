#version 330 core

in vec3 outColor;
in vec2 textCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
out vec4 FragColor;
void main()
{
  FragColor = mix(texture(texture1, textCoord), texture(texture2, textCoord), 0.2);
}