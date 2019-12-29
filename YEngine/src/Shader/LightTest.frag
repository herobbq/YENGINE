#version 330 core

varying vec3 v_lightPos;
varying vec4 v_lightColor;
varying vec3 v_normal;
varying vec3 v_fragPos;
varying vec3 v_viewPos;
varying float v_specularStrength;

uniform float u_ambientStrength;
out vec4 fargmenColor;
void main()
{
    
    vec4 ambient = u_ambientStrength *v_lightColor;


	vec3 normal = normalize(v_normal);
	vec3 LightDir = normalize(v_lightPos - v_fragPos);
	float diff = max(dot(normal,LightDir),0.0);
	vec4 diffuse = diff * v_lightColor;

	vec3 viewDir = normalize(v_viewPos - v_fragPos);
	vec3 reflectDir = reflect(-LightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec4 specular =spec * v_specularStrength * v_lightColor;


    fargmenColor = ( ambient + diffuse +specular) * vec4(1.0f, 0.5f, 0.31f,1.0f);

}