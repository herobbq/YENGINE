#version 330 core

struct Material
{
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct AmbientLight
{
   vec3  color;
   bool  enable;
   float intensity;
};

struct DirectorLight
{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   bool  enable;
   float intensity;
   vec3  position;
   vec3  director;
   float rang;
};

struct PointLight
{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   bool  enable;
   float intensity;
   vec3  position;
   float rang;
   float constant;
   float linear;
   float quadratic;
};

struct SpotLight
{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   vec3  color;
   bool  enable;
   float intensity;
   vec3  director;
   vec3  position;
   float rang;
   float cosInnerAngle;
   float cosOuterAngle;
   };




#define  PointLightNum 2
#define  SpotLightNum 2

in vec2 texCoord;

out vec4 fragColor;

varying vec3 v_fargPos;
varying vec3 v_normal;
varying vec3 v_viewPos;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform Material u_material;
uniform AmbientLight u_ambientLight;
uniform DirectorLight u_directorLight;
uniform PointLight[PointLightNum] u_pointLights;
uniform SpotLight[SpotLightNum] u_spotLights;

vec3 CalcAmbientLight()
{
   if(u_ambientLight.enable)
   {
   return  vec3(vec3(texture(u_material.diffuse,texCoord)) * u_ambientLight.color * u_ambientLight.intensity );
	 
   }
   return vec3(0);
}

vec3 CalcDirectorLight(DirectorLight light,vec3 normal,vec3 viewDir)
{
   if(light.enable == true)
   {
     vec3 lightDirector = normalize(-light.director);

	 float diff = max(dot(normal,lightDirector),0.0);

	 vec3 refDir = reflect(-lightDirector,normal);
	 float spec = pow(max(dot(refDir,viewDir),0.0),u_material.shininess);


	 // vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, texCoord));
	 vec3 diffuse = light.diffuse *diff*(vec3(texture(u_material.diffuse,texCoord)));
	 vec3 specular = light.specular *spec*(vec3(texture(u_material.specular,texCoord)));

	 vec3 result = diffuse + specular;
	 return result ;
   }
    return vec3(0);
}

vec3 CalcPointLight(PointLight light,float distance,vec3 normal,vec3 viewDir,vec3 lightDirector)
{
    if(light.enable == true)
   {
      

	  float diff =max(dot(normal,lightDirector),0.0);
	  vec3 diffuse = diff * vec3(texture(u_material.diffuse,texCoord)) * light.diffuse;

	  vec3 reflecDir = reflect(-lightDirector,normal);
	  float spec = pow(max(dot(reflecDir,viewDir),0.0),u_material.shininess);
      vec3 specular =  light.specular *spec*(vec3(texture(u_material.specular,texCoord)));

	  float attenuation = 1/(light.constant + light.linear * distance + light.quadratic * distance *distance);

	  vec3 result = attenuation * (diffuse + specular);
	  return result;

    }
    return vec3(0);
}


vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 viewDir,vec3 lightDirector)
{
	 if(light.enable == true)
   {
	  

	  float diff = max(dot(lightDirector,normal),0.0);
	  vec3  diffuse = light.diffuse * vec3(texture(u_material.diffuse,texCoord)) *diff;

	  vec3 reflDir = reflect(-lightDirector,normal);
	  float spec = pow(max(dot(reflDir,viewDir),0.0),u_material.shininess);
	  vec3 specular = spec * light.specular * vec3(texture(u_material.specular,texCoord));

	  float epsion = light.cosInnerAngle - light.cosOuterAngle;
	  float theta = dot(-lightDirector,normalize(light.director));
	  float intersity = clamp((theta-light.cosOuterAngle)/epsion,0,1);
      
	  vec3 result = (specular + diffuse ) * intersity;
	  return result;

   }
    return vec3(0);
}




void main()
{
    vec3 result = CalcAmbientLight();
	vec3 normal = normalize(v_normal);
	vec3 viewDir = normalize(v_viewPos -v_fargPos );
	
	result+=CalcDirectorLight(u_directorLight,normal,viewDir);
	for(int i = 0;i<PointLightNum;++i)
	{
		float distance = length(u_pointLights[i].position-v_fargPos);
		vec3 lightDir = normalize(u_pointLights[i].position -v_fargPos );
	    result+=CalcPointLight(u_pointLights[i],distance,normal,viewDir,lightDir);
	}
	for(int i = 0;i<SpotLightNum;++i)
	{
		vec3 lightDir = normalize(u_spotLights[i].position -v_fargPos );
	    result+=CalcSpotLight(u_spotLights[i],normal,viewDir,lightDir);
	}
	

    fragColor = vec4(result ,1.0f);
	
}