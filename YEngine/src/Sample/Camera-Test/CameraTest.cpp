#include "CameraTest.h"

#define GLEW_STATIC
#include "glew.h"
#include "YLoadShader.h"
#include "YRenderer.h"
#include "GLProgram.h"
#include "YTexture.h"
#include "YType.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "YDirector.h"
#include "GLView.h"
#include "YCamera.h"

CameraTest::CameraTest()
	:m_shader(nullptr)
	, m_deltaTime(0.0f)
	, m_lastFrame(0.0f)
	/*, m_flastY(0.0f)
	, m_flastX(0.0f)
	,m_bfirstMouse(true)*/
{

}

CameraTest::~CameraTest()
{
	delete m_shader;
}

CameraTest* CameraTest::create()
{
	CameraTest* res = new (std::nothrow)CameraTest;
	if (res&&res->init())
	{
		return res;
	}
	delete res;
	res = nullptr;
	return nullptr;
}

void CameraTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&CameraTest::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}



bool CameraTest::init()
{
	
	glfwSetCursorPosCallback(YDirector::GetInstance()->getGLwindow(), YCamera::mouse_callback);
	glfwSetScrollCallback(YDirector::GetInstance()->getGLwindow(), YCamera::scroll_callback);
	m_shader = new YShader("./src/Shader/CameraTest.vs", "./src/Shader/CameraTest.fs");
	initBuffers();
	return true;
}

void CameraTest::initBuffers()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_shader->use();
	m_positionAttributeLocation = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(m_positionAttributeLocation, 3 , GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_positionAttributeLocation);
	m_TextureAttributeLocation = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_TEX_COORD);
	glVertexAttribPointer(m_TextureAttributeLocation, 2 , GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_TextureAttributeLocation);

	m_Texture1 = YTexture::CreateText("src/Sample/Camera-Test/Texture/container.jpg");
	m_Texture2 = YTexture::CreateText("src/Sample/Camera-Test/Texture/awesomeface.png");

	glUniform1i(glGetUniformLocation(m_shader->GetProgram(), GLProgram::UNIFORM_NAME_TEXTURE1),0);
	m_shader->SetInt(GLProgram::UNIFORM_NAME_TEXTURE2, 1);
	glBindVertexArray(0);



}

void CameraTest::onDraw(const glm::mat4* transform, uint32_t)
{
	glfwSetInputMode(YDirector::GetInstance()->getGLwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float curTime = glfwGetTime();
	m_deltaTime = curTime - m_lastFrame;
	m_lastFrame = curTime;
	YCamera::processInput(YDirector::GetInstance()->getGLwindow(),m_deltaTime);
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	m_shader->use();
	#ifdef TextureUnit
		glBindTextureUnit(0, m_Texture1);
		glBindTextureUnit(1, m_Texture2);
	#else
		glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, m_Texture1);
	    glActiveTexture(GL_TEXTURE1);
	    glBindTexture(GL_TEXTURE_2D, m_Texture2);
    #endif // DEBUG

	// pass transformation matrices to the shader
	m_shader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix()); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	m_shader->setMat4(GLProgram::UNIFORM_NAME_VIEW, YCamera::m_visitingCamera->getViewMatrix());

	// render boxes
	glBindVertexArray(m_VAO);

	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		m_shader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
}









