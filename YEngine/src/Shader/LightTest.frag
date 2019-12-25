#version 330 core

varying vec3 v_lightPos;
varying vec3 v_lightColor;
varying vec3 v_normal;
varying vec3 v_fragPos;
varying vec3 v_viewPos;

out vec4 fargmenColor;
void main()
{
    float ambientStrength = 0.1;
	float specularStrength = 0.5;
    vec3 ambient = ambientStrength *v_lightColor;


	vec3 normal = normalize(v_normal);
	vec3 LightDir = normalize(v_lightPos - v_fragPos);
	float diff = max(dot(normal,LightDir),0.0);
	vec3 diffuse = diff * v_lightColor;

	vec3 viewDir = normalize(v_viewPos - v_fragPos);
	vec3 reflectDir = reflect(-LightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = spec * specularStrength * v_lightColor;


    vec3  result = ( ambient + diffuse +specular) * vec3(1.0f, 0.5f, 0.31f);
    fargmenColor = vec4(result,1.0);
}