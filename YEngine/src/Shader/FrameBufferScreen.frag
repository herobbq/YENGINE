#version 330 core

in vec2 texcoord;

uniform sampler2D utexture;

out vec4 framgColor;
const float offset = 1.0/300.0;
void main()
{
   //反相
  // vec3 col = vec3(1.0f - texture(utexture,texcoord));
  //灰度
  //  framgColor = texture(utexture,texcoord);
	//float average =  0.2126 * framgColor.r + 0.7152 * framgColor.g + 0.0722 * framgColor.b;
	//核效果
	vec2 offsets[9] = vec2[]
	(
	  vec2(-offset,offset),//左上
	  vec2(0.0f,offset),//正上
	  vec2(offset,offset),//右上
	  vec2(-offset,0.0f),//左
	  vec2(0.0f,0.0f),//中
	  vec2(0.0f,offset),//右
	  vec2(-offset,-offset),//左下
	  vec2(0.0,-offset),//正下
	  vec2(offset,-offset)//右下

	);

	float kernel[9] = float[]
	(
		1.0/16.0,2.0/16.0,1.0/16.0,
		2.0/16.0,4.0/16.0,2.0/16.0,
		1.0/16.0,2.0/16.0,1.0/16.0
	);

	vec3 sampleTex[9];
	for(int i = 0;i<9;i++)
	{
	  sampleTex[i] = vec3(texture(utexture,texcoord.st+offsets[i]));
	}
	vec3 color = vec3(0.0);
	for(int i = 0;i<9;i++)
	{
	  color +=sampleTex[i]*kernel[i];
	}
	framgColor = vec4(color,1.0);
	//framgColor = vec4(average,average,average,1.0);
}