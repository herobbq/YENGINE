#version 330 core

in vec3 v_lightPos;
in vec3 v_normal;
in vec3 v_fragPos;
in vec3 v_viewPos;
in vec2 v_texCoords;

uniform bool isBiln;
uniform sampler2D  floorTexture;
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];
uniform bool gamma;
uniform bool bPowdis;
out vec4 fargmenColor;

vec3 LightCalc(vec3 lightPos,vec3 lightColor)
{
    vec3 LightDir = normalize( lightPos - v_fragPos);
	vec3 normal = normalize(v_normal);
    float diff = max(dot(LightDir,normal),0.0);
	vec3 diffuse = diff *lightColor;

	vec3 viewDir = normalize( v_viewPos - v_fragPos);
	float spec;
   if(isBiln)
   {
      vec3 halfwayDir =  normalize(viewDir + LightDir);
	   spec = pow(max(dot(halfwayDir,normal),0.0),64);
   }else
   {
      vec3 reflectDir = reflect(-LightDir,normal);
	  spec = pow(max(dot(reflectDir,normal),0.0),8);
   }
   vec3 specular = spec* lightColor;

   float distance = length(lightPos - v_fragPos);
   float attenuation = 1.0/(bPowdis ? distance * distance:distance);

   diffuse*=attenuation;
   specular*= attenuation;
   return diffuse+specular;
   
}


void main()
{
    
   
   vec3 color = texture(floorTexture,v_texCoords).rgb;
   
	vec3 light = vec3(0.0);
	for(int i =0;i<4;++i)
	  light +=LightCalc(lightPositions[i],lightColors[i]);

    color *=light;
	if(gamma)
	  color = pow(color,vec3(1.0/2.2));

    fargmenColor = vec4(color,1.0);

}