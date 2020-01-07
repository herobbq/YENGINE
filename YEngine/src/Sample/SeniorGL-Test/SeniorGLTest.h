#ifndef SENIORGLTEST_H_
#define SENIORGLTEST_H_

#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"

class YShader;
class GLFWwindow;
class YTexture2D;
class YModel;
class SeniorGLTest :public YNode
{


public:
	SeniorGLTest();
	virtual ~SeniorGLTest();
public:
	Y_CREATESAMPLE(SeniorGLTest);
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;

	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);


protected:
	YCustomCommand m_customCommand;
	YShader*    m_pshader;
	YShader*    m_pOutlineShader;
	unsigned int m_CubeVAO;
	unsigned int m_PlaneVAO;
	unsigned int m_TransparentVAO;
	YModel*      m_pModel;
	YTexture2D*  m_pCubeTexture;
	YTexture2D*  m_pPlaneTexture;
	YTexture2D*  m_pTransparentTexture;
	bool         m_bDepthTest;
	bool         m_bStencilTest;
	bool         m_bTransparentTest;

};
#endif

