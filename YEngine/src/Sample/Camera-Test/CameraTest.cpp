#include "CameraTest.h"

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
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
glm::vec3 CameraTest::lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
CameraTest::CameraTest()
	:m_shader(nullptr)
	, m_Texture1(nullptr)
	, m_Texture2(nullptr)
	, m_LightAmbient(0.2f, 0.2f, 0.2f)
	, m_LightDiffuse(0.2f, 0.2f, 0.2f)
	, m_LightSpecular(1.0f, 1.0f, 1.0f)
	, m_uShininess(64.0f)
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
	m_shader = new YShader("./src/Shader/CameraTest.vert", "./src/Shader/CameraTest.frag");
	m_Lightshader = new YShader("./src/Shader/normalBox.vert", "./src/Shader/normalBox.frag");
	initBuffers();
	return true;
}

void CameraTest::initBuffers()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_shader->use();
	m_positionAttributeLocation = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(m_positionAttributeLocation, 3 , GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(m_positionAttributeLocation);
	m_TextureAttributeLocation = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_TEX_COORD);
	glVertexAttribPointer(m_TextureAttributeLocation, 2 , GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(m_TextureAttributeLocation);
	unsigned int normal = glGetAttribLocation(m_shader->GetProgram(), GLProgram::ATTRIBUTE_NAME_NORMAL);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(normal);

	m_Texture1 = YTexture2D::create("src/Sample/Camera-Test/Texture/container2.png");
	m_Texture2 = YTexture2D::create("src/Sample/Camera-Test/Texture/container2_specular.png");

	glUniform1i(glGetUniformLocation(m_shader->GetProgram(), "u_material.diffuse"),0);
	m_shader->SetInt("u_material.specular", 1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unsigned int vbo, pos;
	glGenVertexArrays(1, &m_LightVAO);
	glGenBuffers(1, &vbo);

	glBindVertexArray(m_LightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_Lightshader->use();
	pos = glGetAttribLocation(m_Lightshader->GetProgram(), GLProgram::ATTRIBUTE_NAME_POSITION);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(pos);

	//glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &lightColor[0]);

	glBindVertexArray(0);

}

void CameraTest::onDraw(const glm::mat4* transform, uint32_t)
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::Begin("LightParam1", 0, ImGuiWindowFlags_MenuBar);
	ImGui::ColorEdit3("LightAmbient", &m_LightAmbient[0]);
	ImGui::ColorEdit3("LightDiffuse", &m_LightDiffuse[0]);
	ImGui::ColorEdit3("LightSpecular", &m_LightSpecular[0]);
	ImGui::DragFloat3("LightPos", &lightPos[0], 0.01);
	ImGui::DragFloat("LightShininess", &m_uShininess, 1.0f, 0.0, 256);
	ImGui::End();

	//glfwSetInputMode(YDirector::GetInstance()->getGLwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
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
	    glBindTexture(GL_TEXTURE_2D, m_Texture1->GetName());
	    glActiveTexture(GL_TEXTURE1);
	    glBindTexture(GL_TEXTURE_2D, m_Texture2->GetName());
    #endif // DEBUG

	// pass transformation matrices to the shader
	m_shader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix()); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	m_shader->setMat4(GLProgram::UNIFORM_NAME_VIEW,YCamera::m_visitingCamera->getViewMatrix());
	m_shader->SetVec3(GLProgram::UNIFORM_NAME_VIEWPOS, YCamera::m_visitingCamera->getCameraPos());
	auto s = YCamera::m_visitingCamera->getCameraPos();
	auto ss = YCamera::m_visitingCamera->getViewMatrix();
	// render boxes
	glBindVertexArray(m_VAO);
	m_shader->SetVec3("u_light.ambient", m_LightAmbient);
	m_shader->SetVec3("u_light.diffuse", m_LightDiffuse);
	m_shader->SetVec3("u_light.specular", m_LightSpecular);
	m_shader->SetVec3("u_light.position", lightPos);
	glUniform1f(glGetUniformLocation(m_shader->GetProgram(), "u_material.shininess"), m_uShininess);
	for (unsigned int i = 0; i < 1; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		m_shader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(m_LightVAO);
	m_Lightshader->use();
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, YCamera::m_visitingCamera->getViewMatrix());
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::GetVisitingCamera()->getProjectionMatrix());
	glm::mat4 lightModel(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	glm::vec4 color(1.0f);
	glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &color[0]);

	lightModel = glm::scale(lightModel, glm::vec3(0.2));
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, lightModel);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	
}









