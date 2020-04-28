#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoords;
layout (location = 3) in vec3 a_tangent;
layout (location = 4) in vec3 a_bittangent;

out VS_OUT
{
  vec3 normal;
  vec3 tangent;
  vec3 bittangent;
}vs_out;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
      
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(u_view * u_model)));
	vs_out.normal = normalize(vec3(u_projection * vec4(normalMatrix * a_normal,0.0)));
	vs_out.tangent = normalize(vec3(u_projection * vec4(normalMatrix * a_tangent,0.0)));
	vs_out.bittangent = normalize(vec3(u_projection * vec4(normalMatrix * a_bittangent,0.0)));
}