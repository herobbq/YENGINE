#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

varying vec3 v_lightPos;
varying vec4 v_lightColor;
varying vec3 v_normal;
varying vec3 v_fragPos;
varying vec3 v_viewPos;
varying float v_specularStrength;


uniform float u_ambientStrength;
uniform Material u_material;
uniform Light u_light;
out vec4 fargmenColor;
void main()
{
    
    vec3 ambient = u_material.ambient *u_light.ambient;


	vec3 normal = normalize(v_normal);
	vec3 LightDir = normalize(u_light.position - v_fragPos);
	float diff = max(dot(normal,LightDir),0.0);
	vec3 diffuse = u_light.diffuse *(diff * u_material.diffuse);

	vec3 viewDir = normalize(v_viewPos - v_fragPos);
	vec3 reflectDir = reflect(-LightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0), u_material.shininess);
    vec3 specular = u_light.specular * (spec * u_material.specular) ;

	vec4 result = vec4(ambient + diffuse +specular,1.0f);

    fargmenColor =  result;

}