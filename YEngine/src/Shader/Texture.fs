#version 330 core

in vec3 outColor;
in vec2 texCoord;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
out vec4 FragColor;
void main()
{
  FragColor = mix(texture(u_texture1, texCoord), texture(u_texture2, texCoord), 0.2);
}