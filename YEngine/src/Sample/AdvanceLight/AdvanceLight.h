#pragma once

#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"

class YShader;
class GLFWwindow;
class YTexture2D;
class YModel;
class AdvanceLight :public YNode
{


public:
	AdvanceLight();
	virtual ~AdvanceLight();
public:
	Y_CREATESAMPLE(AdvanceLight);
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;

	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);
	void ChangeTexture();

protected:
	YCustomCommand m_customCommand;
	unsigned int m_VAO;
	YShader*    m_shader;
	bool         m_bUseBlinn;
	bool         m_bUseGamma;
	bool         m_bUseDistance;
	bool         m_LastStatus;
	glm::vec3 m_arrLightPositions[4];
	glm::vec3 m_arrLightColors[4];
	YTexture2D* m_Texture;
	

};