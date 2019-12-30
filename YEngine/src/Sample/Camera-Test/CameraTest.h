#ifndef CAMERATEST_H_
#define CAMERATEST_H_



#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"


class YShader;
class GLFWwindow;
class YTexture2D;
class DirectionLight;
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
	
	
protected:
	YCustomCommand m_customCommand;
	YShader*    m_shader;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
	unsigned int m_LightVAO;
	YShader*    m_Lightshader;
	YTexture2D* m_Texture1;
	YTexture2D* m_Texture2;
	static glm::vec3 lightPos;
	glm::vec3    m_LightAmbient;
	glm::vec3   m_LightDiffuse;
	glm::vec3    m_LightSpecular;
	int  m_positionAttributeLocation;
	int  m_ColorAttributeLocation;
	int  m_TextureAttributeLocation;
	float m_uShininess;
	DirectionLight*    m_pDirectionLight;
};

#endif // CAMERATEST_H_
