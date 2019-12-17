#ifndef CAMERATEST_H_
#define CAMERATEST_H_



#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"


class YShader;
class GLFWwindow;
class CameraTest :public YNode
{

	
public:
	CameraTest();
	virtual ~CameraTest();
public:
	static CameraTest* create();
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;

	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);
	void   processInput(GLFWwindow *window);
	
protected:
	YCustomCommand m_customCommand;
	YShader*    m_shader;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
	unsigned int m_Texture1;
	unsigned int m_Texture2;
	float     m_deltaTime;	// time between current frame and last frame
	float     m_lastFrame;
	
	int  m_positionAttributeLocation;
	int  m_ColorAttributeLocation;
	int  m_TextureAttributeLocation;
};
#pragma once
#endif // CAMERATEST_H_
