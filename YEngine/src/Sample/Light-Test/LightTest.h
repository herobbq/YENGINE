#ifndef LIGHTTEST_H_
#define LIGHTTEST_H_

#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"

class YShader;
class GLFWwindow;
class YTexture2D;
class LightTest :public YNode
{


public:
	LightTest();
	virtual ~LightTest();
public:
	Y_CREATESAMPLE(LightTest);
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;

	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);


protected:
	YCustomCommand m_customCommand;
	YShader*    m_Boxshader;
	YShader*    m_Lightshader;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_LightVAO;
	YTexture2D* m_Texture1;
	

};
#endif
