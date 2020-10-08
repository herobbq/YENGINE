#pragma once

#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"

class YShader;
class GLFWwindow;
class YTexture2D;
class YModel;
class ShadowTest :public YNode
{


public:
	ShadowTest();
	virtual ~ShadowTest();
public:
	Y_CREATESAMPLE(ShadowTest);
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;

	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);
	void renderScene(YShader*    shader);
	void renderCube();
	void renderQuad();
protected:
	YCustomCommand m_customCommand;
	unsigned int m_planeVAO;
	unsigned int m_cubeVAO;
	YShader*    m_shader;
	YShader*    m_Depthshader;
	YShader*    m_Quadshader;
	YTexture2D* m_Texture;
	unsigned int m_depthMap;
	unsigned int m_FBO;
	const unsigned int  SHADOW_WIDTH;
	glm::vec3           m_lightPos;
	const unsigned int  SHADOW_HEIGHT;
};