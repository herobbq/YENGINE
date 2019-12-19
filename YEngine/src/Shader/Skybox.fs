#version 330 core

in vec3 tex_coord;

uniform samplerCube u_cubetexture;

out vec4 Fragmcolor ;

void main()
{
   Fragmcolor = texture(u_cubetexture,tex_coord);
}
