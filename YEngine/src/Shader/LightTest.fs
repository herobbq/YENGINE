#version 330 core

varying vec3 v_lightPos;
varying vec3 v_lightColor;

out vec4 fargmenColor;
void main()
{
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength *v_lightColor;
	vec3  result = ambient * vec3(1.0,0.0,0.0);
    fargmenColor = vec4(result,1.0);
}