#include "AdvanceLight.h"
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

AdvanceLight::AdvanceLight()
	:m_Texture(NULL)
	, m_shader(NULL)
	,m_bUseBlinn(false)
	,m_bUseGamma(false)
	,m_bUseDistance(false)
	,m_LastStatus(false)
{

}

AdvanceLight::~AdvanceLight()
{

}

void AdvanceLight::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&AdvanceLight::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool AdvanceLight::init()
{
	m_shader = new YShader("./src/Shader/AdvanceLight.vert", "./src/Shader/AdvanceLight.frag");
	
	m_arrLightPositions[0] = glm::vec3(-3.0f, 0.0f, 0.0f);
	m_arrLightPositions[1] = glm::vec3(-1.0f, 0.0f, 0.0f);
	m_arrLightPositions[2] = glm::vec3(1.0f, 0.0f, 0.0f);
	m_arrLightPositions[3] = glm::vec3(3.0f, 0.0f, 0.0f);
	
	m_arrLightColors[0] = glm::vec3(0.25);
	m_arrLightColors[1] = glm::vec3(0.50);
	m_arrLightColors[2] = glm::vec3(0.75);
	m_arrLightColors[3] = glm::vec3(1.00);
	initBuffers();
	return true;
}

void AdvanceLight::initBuffers()
{
	float planeVertices[] = {
		// positions            // normals         // texcoords
		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
	};
	unsigned int vbo;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_POSITION);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);

	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_NORMAL);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_TEXCOORDS);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	glBindVertexArray(0);

	m_Texture = YTexture2D::create("src/Sample/AdvanceLight/Texture/wood.png");

	m_shader->SetInt(GLProgram::UNIFORM_NAME_TEXTURE1, 0);
}

void AdvanceLight::onDraw(const glm::mat4* transform, uint32_t)
{

	ImGui::Begin("Advance Light", 0, ImGuiWindowFlags_MenuBar);
	ImGui::Checkbox("Blinn -Phong", &m_bUseBlinn);
	ImGui::Checkbox("Gamma", &m_bUseGamma);
	ImGui::Checkbox("distance", &m_bUseDistance);
	ImGui::End();
	ChangeTexture();
	
	m_shader->use();
	glUniform3fv(glGetUniformLocation(m_shader->GetProgram(), "lightPositions"), 4, &m_arrLightPositions[0][0]);
	glUniform3fv(glGetUniformLocation(m_shader->GetProgram(), "lightColors"), 4, &m_arrLightColors[0][0]);
	m_shader->setMat4("u_projection", YCamera::m_visitingCamera->getProjectionMatrix());
	m_shader->setMat4("u_view", YCamera::m_visitingCamera->getViewMatrix());
	m_shader->SetBool("isBiln", m_bUseBlinn);
	m_shader->SetBool("gamma", m_bUseGamma);
	m_shader->SetBool("bPowdis", m_bUseDistance);
	m_shader->SetVec3("u_viewPos", YCamera::m_visitingCamera->getPosition());
	m_shader->SetVec3("u_lightPos", glm::vec3(0.0));
	glBindVertexArray(m_VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->GetName());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void AdvanceLight::ChangeTexture()
{
	if (m_LastStatus==m_bUseGamma)
	{
		return;
	}
	if (m_bUseGamma)
	{
		m_Texture = YTexture2D::create("src/Sample/AdvanceLight/Texture/wood.png",true);
	}
	else
	{
		m_Texture = YTexture2D::create("src/Sample/AdvanceLight/Texture/wood.png");
	}
	m_LastStatus = m_bUseGamma;
}

