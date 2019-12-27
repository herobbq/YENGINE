#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"

class YShader;
class MenuScene :public YNode
{
public:
	MenuScene();
	virtual ~MenuScene();
public:
	Y_CREATESAMPLE(MenuScene);
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;
protected:
	virtual bool init() override;
	void onDraw(const glm::mat4* transform, uint32_t);
protected:
	YCustomCommand m_customCommand;
	bool           m_bRenderCameraTest;
	bool           m_bRenderTriangleTest;
	bool           m_bRenderSkyboxTest;
	bool           m_bRenderLightTest;
	bool           m_bRenderFrameBufferTest;
	bool           m_bRenderTextureTest;
	float         m_deltaTime;	// time between current frame and last frame
	float        m_lastFrame;
protected:
	YNode*         m_pCameraTest;
	YNode*         m_pTriangleTest;
	YNode*         m_pSkyboxTest;
	YNode*         m_pLightTest;
	YNode*         m_pFrameBufferTest;
	YNode*         m_pTextureTest;

	
};



#endif

