#include "LightTest.h"
#include "hfileinclude.h"
#include "YLoadShader.h"
#include "YRenderer.h"
#include "GLProgram.h"
#include "YTexture2D.h"
#include "YType.h"
#include "YDirector.h"
#include "GLView.h"
#include "YCamera.h"
#include "SampleInclude.h"

#define MaterialTest
glm::vec4 LightTest::lightColor = glm::vec4(1.0, 1.0, 1.0,1.0f);

float LightTest::m_specularStrength = 0.5;

float LightTest::m_ambientStrength = 0.1;

glm::vec3 LightTest::lightPos = glm::vec3(1.2f, 1.0f, 2.0f); ;

LightTest::LightTest()
	:m_Boxshader(nullptr)
	, m_Texture1(nullptr)
	,m_Lightshader(nullptr)
	,m_MaterialAmbient(1.0f, 0.5f, 0.31f)
	, m_MaterialDiffuse(1.0f, 0.5f, 0.31f)
	,m_MaterialSpecular(0.5f, 0.5f, 0.5f)
	, m_LightAmbient(0.2f, 0.2f, 0.2f)
	, m_LightDiffuse(0.5f, 0.5f, 0.5f)
	, m_LightSpecular(1.0f, 1.0f, 1.0f)
	,m_uShininess(32.0f)
    , bAutoChangeColor(false)
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
	
#ifndef MaterialTest
	m_Boxshader = new YShader("./src/Shader/LightTest.vert", "./src/Shader/LightTest.frag");
#else
	m_Boxshader = new YShader("./src/Shader/LightTest.vert", "./src/Shader/LightTextMaterial.frag");
#endif
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

	//glUniform4fv(glGetUniformLocation(m_Boxshader->GetProgram(), "u_lightColor"), 1,&lightColor[0]);
	//glUniform1f(glGetUniformLocation(m_Boxshader->GetProgram(), "u_specularStrength"),m_specularStrength);
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

	glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &lightColor[0]);

	glBindVertexArray(0);


}

void LightTest::onDraw(const glm::mat4* transform, uint32_t)
{
	//glfwSetInputMode(YDirector::GetInstance()->getGLwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::Begin("LightParam", 0, ImGuiWindowFlags_MenuBar);
#ifndef MaterialTest
	ImGui::ColorEdit4("LightColor", &lightColor[0]);
	ImGui::DragFloat3("LightPos", &lightPos[0],0.01);
	ImGui::DragFloat("specularStrength", &m_specularStrength,0.01,0.0,1.0);
	ImGui::DragFloat("ambientStrength", &m_ambientStrength, 0.01, 0.0, 1.0);
#else
	ImGui::ColorEdit3("LightAmbient", &m_LightAmbient[0]);
	ImGui::ColorEdit3("LightDiffuse", &m_LightDiffuse[0]);
	ImGui::ColorEdit3("LightSpecular", &m_LightSpecular[0]);
	ImGui::ColorEdit3("MaterialAmbient", &m_MaterialAmbient[0]);
	ImGui::ColorEdit3("MaterialDiffuse", &m_MaterialDiffuse[0]);
	ImGui::ColorEdit3("MaterialSpecular", &m_MaterialSpecular[0]);
	ImGui::DragFloat3("LightPos", &lightPos[0], 0.01);
	ImGui::DragFloat("LightShininess", &m_uShininess, 1.0f, 0.0, 256);
	ImGui::Checkbox("autoColor",&bAutoChangeColor);
#endif
	ImGui::End();

	m_Boxshader->use();
	
	glBindVertexArray(m_VAO);
	glm::mat4 view = YCamera::GetVisitingCamera()->getViewMatrix();
	auto s = YCamera::GetVisitingCamera()->getProjectionMatrix();
	
	glm::mat4 lightModel(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	m_Boxshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, view);
	m_Boxshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::GetVisitingCamera()->getProjectionMatrix());
	m_Boxshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, glm::mat4(1.0f));
	auto pp = YCamera::GetVisitingCamera()->getCameraPos();
	m_Boxshader->SetVec3(GLProgram::UNIFORM_NAME_VIEWPOS, YCamera::GetVisitingCamera()->getCameraPos());
#ifndef MaterialTest
	glUniform4fv(glGetUniformLocation(m_Boxshader->GetProgram(), "u_lightColor"), 1, &lightColor[0]);
	glUniform1f(glGetUniformLocation(m_Boxshader->GetProgram(), "u_specularStrength"), m_specularStrength);
	glUniform1f(glGetUniformLocation(m_Boxshader->GetProgram(), "u_ambientStrength"), m_ambientStrength);
	m_Boxshader->SetVec3("u_lightPos", lightPos);
#else
	m_Boxshader->SetVec3("u_material.ambient", m_MaterialAmbient);
	m_Boxshader->SetVec3("u_material.diffuse", m_MaterialDiffuse);
	m_Boxshader->SetVec3("u_material.specular", m_MaterialSpecular);
	m_Boxshader->SetVec3("u_light.ambient", m_LightAmbient);
	m_Boxshader->SetVec3("u_light.diffuse", m_LightDiffuse);
	m_Boxshader->SetVec3("u_light.specular", m_LightSpecular);
	m_Boxshader->SetVec3("u_light.position", lightPos);
	glUniform1f(glGetUniformLocation(m_Boxshader->GetProgram(), "u_material.shininess"), m_uShininess);
#endif
	if (bAutoChangeColor)
	{
		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		m_LightDiffuse = lightColor   * glm::vec3(0.5f); // decrease the influence
		m_LightAmbient = m_LightDiffuse * glm::vec3(0.2f); // low influence
		m_Boxshader->SetVec3("u_light.ambient", m_LightAmbient);
		m_Boxshader->SetVec3("u_light.diffuse", m_LightDiffuse);
		m_Boxshader->SetVec3("u_light.specular", m_LightSpecular);
		
		
	}

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(m_LightVAO);
	m_Lightshader->use();
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, view);
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::GetVisitingCamera()->getProjectionMatrix());
#ifndef MaterialTest
	glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &lightColor[0]);
#else
	glm::vec4 color(m_LightDiffuse, 1.0f);
	glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &color[0]);
#endif
	lightModel = glm::scale(lightModel, glm::vec3(0.2));
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, lightModel);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}



