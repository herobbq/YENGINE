#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_



#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"


class YShader;
class GLFWwindow;
class YTexture2D;
class FrameBufferTest :public YNode
{


public:
	FrameBufferTest();
	virtual ~FrameBufferTest();
public:
	static FrameBufferTest* create();
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;

	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);


protected:
	YCustomCommand m_customCommand;
	YShader*    m_shader;
	YShader*    m_shader1;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_BUF;
	unsigned int m_FarmeTexture;
	unsigned int m_quardVAO;
	YTexture2D* m_Texture1;
	YTexture2D* m_Texture2;
	static  float  m_fWindowWidth;
	static  float  m_fWindowHeight;
	int  m_positionAttributeLocation;
	int  m_ColorAttributeLocation;
	int  m_TextureAttributeLocation;
};
#pragma once
#endif // CAMERATEST_H_
