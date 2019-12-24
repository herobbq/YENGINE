#include "LightTest.h"
#define GLEW_STATIC
#include "glew.h"
#include "YLoadShader.h"
#include "YRenderer.h"
#include "GLProgram.h"
#include "YTexture2D.h"
#include "YType.h"
#include "YDirector.h"
#include "GLView.h"
#include "YCamera.h"



LightTest::LightTest()
	:m_shader(nullptr)
	, m_Texture1(nullptr)
{

}

LightTest::~LightTest()
{

}



void LightTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&LightTest::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool LightTest::init()
{
	glfwSetCursorPosCallback(YDirector::GetInstance()->getGLwindow(), YCamera::mouse_callback);
	glfwSetScrollCallback(YDirector::GetInstance()->getGLwindow(), YCamera::scroll_callback);
	m_shader = new YShader("./src/Shader/LightTest.vs", "./src/Shader/LightTest.fs");
	initBuffers();
	return true;    
}

void LightTest::initBuffers()
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

	unsigned int pos;
	m_shader->use();
	pos = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(pos);
	 
	glm::vec3 lightcolor(1.0, 1.0, 1.0);
	glUniform3fv(glGetUniformLocation(m_shader->GetProgram(), "u_lightColor"), 1,&lightcolor[0]);

	glEnableVertexAttribArray(0);

}

void LightTest::onDraw(const glm::mat4* transform, uint32_t)
{
	glfwSetInputMode(YDirector::GetInstance()->getGLwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float curTime = glfwGetTime();
	m_deltaTime = curTime - m_lastFrame;
	m_lastFrame = curTime;
	YCamera::processInput(YDirector::GetInstance()->getGLwindow(), m_deltaTime);
	m_shader->use();
	glBindVertexArray(m_VAO);
	glm::mat4 view = YCamera::GetVisitingCamera()->getViewMatrix();
	view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
	m_shader->setMat4(GLProgram::UNIFORM_NAME_VIEW, view);
	m_shader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::GetVisitingCamera()->getProjectionMatrix());
	m_shader->setMat4(GLProgram::UNIFORM_NAME_MODEL, glm::mat4(1));

	glDrawArrays(GL_TRIANGLES, 0, 36);

}

