#version 330 core

in VS_OUT
{
	vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
}fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fargmenColor;
float ShadowCalculation(vec4 fragPosLightSpace ,float bias)
{
	
	 vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	 if(projCoords.z>1)
	   return 0.0;
	 projCoords = projCoords * 0.5 + 0.5;

	 float closestDepth = texture(shadowMap, projCoords.xy).r; 

	 float currentDepth = projCoords.z;

	 vec2 textsize =  1.0/textureSize(shadowMap,0);
	 float shadow  = 0.0;
	 for(int x = -1;x<=1;++x )
	 {
		for(int y = -1;y<=1;++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * textsize).r; 
		    shadow += currentDepth - bias > pcfDepth  ? 1.0 :  0.0;
		}
	 }
	 shadow /= 9.0;
	//shadow = currentDepth - bias > closestDepth  ? 1.0 :  0.0;
	 return shadow;
}
void main()
{
    
   vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);
    vec3 ambient = 0.3 *lightColor;


	
	vec3 LightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max(dot(normal,LightDir),0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-LightDir,normal);
	 vec3 halfwayDir = normalize(LightDir + viewDir);  
   float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor; 
  

    float bias = max(0.05*(1.0 - diff ),0.005);
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace,bias);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    fargmenColor = vec4(lighting, 1.0);
}
