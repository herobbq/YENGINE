#ifndef YGLPROGRAM_H_ 
#define YGLPROGRAM_H_
class GLProgram
{
public:
	static const char* UNIFORM_NAME_MODEL;
	static const char* UNIFORM_NAME_VIEW;
	static const char* UNIFORM_NAME_PROJECTION;
	static const char* UNIFORM_NAME_TEXTURE1;
	static const char* UNIFORM_NAME_TEXTURE2;
	static const char* UNIFORM_NAME_CUBETEXTURE;
public:
	static const char* ATTRIBUTE_NAME_COLOR;
	/**Attribute position.*/
	static const char* ATTRIBUTE_NAME_POSITION;
	/**@{ Attribute Texcoord 0-3.*/
	static const char* ATTRIBUTE_NAME_TEX_COORD;
	static const char* ATTRIBUTE_NAME_TEX_COORD1;
	static const char* ATTRIBUTE_NAME_TEX_COORD2;
	static const char* ATTRIBUTE_NAME_TEX_COORD3;
	/**@}*/
	/**Attribute normal.*/
	static const char* ATTRIBUTE_NAME_NORMAL;
	/**Attribute blend weight.*/
	static const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
	/**Attribute blend index.*/
	static const char* ATTRIBUTE_NAME_BLEND_INDEX;
	/**Attribute blend tangent.*/
	static const char* ATTRIBUTE_NAME_TANGENT;
	/**Attribute blend binormal.*/
	static const char* ATTRIBUTE_NAME_BINORMAL;
};
#endif // 
