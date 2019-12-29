#version 330 core

struct Material
{
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct Light
{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   vec3 position;
};

in vec2 texCoord;

out vec4 fragColor;

varying vec3 v_fargPos;
varying vec3 v_normal;
varying vec3 v_viewPos;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform Material u_material;
uniform Light u_light;
void main()
{
	vec3 ambinet = vec3(texture(u_material.diffuse,texCoord)) * u_light.ambient;

	vec3 normal = normalize(v_normal);
	vec3 LightDir = normalize(u_light.position - v_fargPos);
	float diff = max(dot(normal,LightDir),0.0);
	vec3 diffuse = diff * vec3(texture(u_material.diffuse,texCoord)) * u_light.diffuse;

	vec3 viewDir =  normalize(v_viewPos - v_fargPos);
	vec3 reflectDir = reflect(-LightDir,normal);
	float specu = pow(max(dot(viewDir,reflectDir),0.0),u_material.shininess);
	vec3  specular = specu *vec3(texture( u_material.specular,texCoord)) * u_light.specular; 

	vec3 result =  ambinet + diffuse +specular;

    fragColor = vec4(result ,1.0f);
	
}