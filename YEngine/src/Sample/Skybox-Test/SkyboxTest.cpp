#include "SkyboxTest.h"
#define GLEW_STATIC
#include "glew.h"
#include "YLoadShader.h"
#include "YRenderer.h"
#include "GLProgram.h"
#include "YTextureCube.h"
#include "YType.h"
#include "YDirector.h"
#include "GLView.h"
#include "YCamera.h"
SkyBoxTest::SkyBoxTest()
	:m_Texture1(nullptr)
	,m_shader(nullptr)
{

}

SkyBoxTest::~SkyBoxTest()
{

}

SkyBoxTest* SkyBoxTest::create()
{
	SkyBoxTest* _sky = new (std::nothrow)SkyBoxTest;
	if (_sky&&_sky->init())
	{
		return _sky;
	}
	delete _sky;
	_sky = nullptr;
	return nullptr;
}

void SkyBoxTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&SkyBoxTest::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool SkyBoxTest::init()
{
	glfwSetCursorPosCallback(YDirector::GetInstance()->getGLwindow(), YCamera::mouse_callback);
	glfwSetScrollCallback(YDirector::GetInstance()->getGLwindow(), YCamera::scroll_callback);
	m_shader = new YShader("./src/Shader/Skybox.vert", "./src/Shader/Skybox.frag");
	initBuffers();
	return true;
}

void SkyBoxTest::initBuffers()
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	m_shader->use();
	m_positionAttributeLocation =  glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glEnableVertexAttribArray(m_positionAttributeLocation);
	glVertexAttribPointer(m_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	m_Texture1 = YTextureCube::create("src/Sample/Skybox-Test/Texture/right.jpg", "src/Sample/Skybox-Test/Texture/left.jpg",
		"src/Sample/Skybox-Test/Texture/top.jpg", "src/Sample/Skybox-Test/Texture/bottom.jpg", "src/Sample/Skybox-Test/Texture/front.jpg",
		"src/Sample/Skybox-Test/Texture/back.jpg");
	glUniform1i(glGetUniformLocation(m_shader->GetProgram(), GLProgram::UNIFORM_NAME_CUBETEXTURE), 0);
	glBindVertexArray(0);

}

void SkyBoxTest::onDraw(const glm::mat4* transform, uint32_t)
{
	glfwSetInputMode(YDirector::GetInstance()->getGLwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glDepthFunc(GL_LEQUAL);
	float curTime = glfwGetTime();
	m_deltaTime = curTime - m_lastFrame;
	m_lastFrame = curTime;
	YCamera::processInput(YDirector::GetInstance()->getGLwindow(), m_deltaTime);
	glBindVertexArray(m_VAO);
	m_shader->use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture1->GetName());
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//glUniformMatrix4fv(glGetUniformLocation(m_shader->GetProgram(), GLProgram::UNIFORM_NAME_VIEW),1,GL_FALSE,&YCamera::m_visitingCamera->getViewMatrix()[0][0]);
	m_shader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix());
	m_shader->setMat4(GLProgram::UNIFORM_NAME_VIEW, YCamera::m_visitingCamera->getViewMatrix());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}

