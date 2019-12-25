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
	:m_Boxshader(nullptr)
	, m_Texture1(nullptr)
	,m_Lightshader(nullptr)
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
	m_Boxshader = new YShader("./src/Shader/LightTest.vert", "./src/Shader/LightTest.frag");
	m_Lightshader = new YShader("./src/Shader/normalBox.vert", "./src/Shader/normalBox.frag");
	initBuffers();
	return true;    
}

void LightTest::initBuffers()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int pos,normal;
	m_Boxshader->use();
	pos = glGetAttribLocation(m_Boxshader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(pos);
	normal = glGetAttribLocation(m_Boxshader->GetProgram(), GLProgram::ATTRIBUTE_NAME_NORMAL);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(normal);
	glm::vec3 lightcolor(1.0, 1.0, 1.0);
	glUniform3fv(glGetUniformLocation(m_Boxshader->GetProgram(), "u_lightColor"), 1,&lightcolor[0]);

	glBindVertexArray(0);
	unsigned int vbo;
	glGenVertexArrays(1, &m_LightVAO);
	glGenBuffers(1, &vbo);

	glBindVertexArray(m_LightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_Lightshader->use();
	pos = glGetAttribLocation(m_Lightshader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(pos);

	glm::vec4 objectColor(1.0);
	glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &objectColor[0]);

	glBindVertexArray(0);


}

void LightTest::onDraw(const glm::mat4* transform, uint32_t)
{
	glfwSetInputMode(YDirector::GetInstance()->getGLwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float curTime = glfwGetTime();
	m_deltaTime = curTime - m_lastFrame;
	m_lastFrame = curTime;
	YCamera::processInput(YDirector::GetInstance()->getGLwindow(), m_deltaTime);
	m_Boxshader->use();
	
	glBindVertexArray(m_VAO);
	glm::mat4 view = YCamera::GetVisitingCamera()->getViewMatrix();
	view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
	glm::vec3 lightPos(0.3f, 0.8f, -0.55f);
	glm::mat4 lightModel(1);
	lightModel = glm::translate(lightModel, lightPos);
	m_Boxshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, view);
	m_Boxshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::GetVisitingCamera()->getProjectionMatrix());
	m_Boxshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, glm::mat4(1));
	m_Boxshader->SetVec3("u_lightPos", lightPos);
	m_Boxshader->SetVec3(GLProgram::UNIFORM_NAME_VIEWPOS, YCamera::GetVisitingCamera()->getCameraPos());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(m_LightVAO);
	m_Lightshader->use();
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, view);
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::GetVisitingCamera()->getProjectionMatrix());
	
	lightModel = glm::scale(lightModel, glm::vec3(0.2));
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, lightModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

