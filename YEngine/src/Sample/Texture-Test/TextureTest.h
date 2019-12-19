#ifndef YTEXTURETEST_H_
#define YTEXTURETEST_H_

#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"

class YShader;
class YTexture2D;
class TextureTest :public YNode
{
public:
	TextureTest();
	virtual ~TextureTest();
public:
	static TextureTest* create();
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;
	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);
protected:
	YCustomCommand m_customCommand;
	YShader*    m_shader;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
	YTexture2D* m_Texture1;
	YTexture2D* m_Texture2;
	int  m_positionAttributeLocation;
	int  m_ColorAttributeLocation;
	int  m_TextureAttributeLocation;
};



#endif

