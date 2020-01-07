#include "CameraTest.h"

#include "hfileinclude.h"
#include "YLoadShader.h"
#include "YRenderer.h"
#include "GLProgram.h"
#include "YTexture2D.h"
#include "YType.h"
#include "YDirector.h"
#include "GLView.h"
#include "YCamera.h"
#include "YLight.h"
glm::vec3 CameraTest::lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
static bool  AmbinetLightEnable = false;
static bool  DirectorLightEnable = false;
static bool  PointLightEnable1 = false;
static bool  PointLightEnable2 = false;
static bool  SpotLightEnable1 = false;
static bool  SpotLightEnable2 = false;
static float innerAngle = 15.0f;
static float outerAngle = 17.5f;
CameraTest::CameraTest()
	:m_shader(nullptr)
	, m_Texture1(nullptr)
	, m_Texture2(nullptr)
	, m_LightAmbient(0.2f, 0.2f, 0.2f)
	, m_LightDiffuse(0.5f, 0.5f, 0.5f)
	, m_LightSpecular(1.0f, 1.0f, 1.0f)
	, m_uShininess(32.0f)
	, m_pDirectionLight(nullptr)
	, m_pSpotLight1(nullptr)
	, m_pAmbientLight(nullptr)
	,m_pPointLight1(nullptr)
	,m_pPointLight2(nullptr)
	, m_pSpotLight2(nullptr)
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
	m_pDirectionLight = DirectionLight::create(glm::vec3(-0.2f, -1.0f, -0.3f), YColor());
	m_pPointLight1 = PointLight::create(glm::vec3(0.7f, 0.2f, 2.0f), YColor(), 10);
	m_pPointLight2 = PointLight::create(glm::vec3(2.3f, -3.3f, -4.0f), YColor(), 10);
	m_pSpotLight1 = SpotLight::create(glm::vec3(0.0,0.0,-1.0f), glm::vec3(0.0, 0.0, 4.0f),YColor(), innerAngle, outerAngle, 30);
	m_pSpotLight2 = SpotLight::create(glm::vec3(-0.5f, 1.0f, 1.0f), glm::vec3(0.5f, -1.0f, -3.0f), YColor(), 10, 17, 30);
	m_pAmbientLight = AmbientLight::create(YColor());
	
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
	ImGui::Checkbox("AmbientEnable", &AmbinetLightEnable);
	ImGui::Checkbox("DirectorLightEnable", &DirectorLightEnable);
	ImGui::Checkbox("PointLightEnable1", &PointLightEnable1);
	ImGui::Checkbox("PointLightEnable2", &PointLightEnable2);
	ImGui::Checkbox("SpotLightEnable1", &SpotLightEnable1);
	ImGui::Checkbox("SpotLightEnable2", &SpotLightEnable2);
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
	
	// render boxes
	glBindVertexArray(m_VAO);
	if (m_pAmbientLight)
	{
		m_pAmbientLight->setEnable(AmbinetLightEnable);
		m_pAmbientLight->setIntensity(0.1f);
		m_shader->SetVec3("u_ambientLight.color", m_pAmbientLight->getColor().toVec3());
		m_shader->SetFloat("u_ambientLight.intensity", m_pAmbientLight->getIntensity());
		m_shader->SetFloat("u_ambientLight.enable", m_pAmbientLight->getEnable());
	}
	if (m_pDirectionLight)
	{
		m_pDirectionLight->setEnable(DirectorLightEnable);
		m_shader->SetFloat("u_directorLight.enable", m_pDirectionLight->getEnable());
		m_shader->SetVec3("u_directorLight.director", m_pDirectionLight->getDirection());
		//m_shader->SetVec3("u_directorLight.ambient",glm::vec3( 0.2f, 0.2f, 0.2f));
		m_shader->SetVec3("u_directorLight.diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
		m_shader->SetVec3("u_directorLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	}
	if (m_pPointLight1)
	{
		m_pPointLight1->setEnable(PointLightEnable1);
		m_shader->SetFloat("u_pointLights[0].enable", m_pPointLight1->getEnable());
		m_shader->SetVec3("u_pointLights[0].diffuse", glm::vec3(0.1f, 0.3f, 0.7f));
		m_shader->SetVec3("u_pointLights[0].position", m_pPointLight1->getPosition());
		m_shader->SetVec3("u_pointLights[0].specular", glm::vec3(1.0));
		m_shader->SetFloat("u_pointLights[0].constant", 1.0f);
		m_shader->SetFloat("u_pointLights[0].linear", 0.09);
		m_shader->SetFloat("u_pointLights[0].quadratic", 0.032);
	}
	if (m_pPointLight2)
	{
		m_pPointLight2->setEnable(PointLightEnable2);
		m_shader->SetFloat("u_pointLights[1].enable", m_pPointLight2->getEnable());
		m_shader->SetVec3("u_pointLights[1].position", m_pPointLight2->getPosition());
		m_shader->SetVec3("u_pointLights[1].diffuse", glm::vec3(0.3f, 0.0f, 0.4f));
		m_shader->SetVec3("u_pointLights[1].specular", glm::vec3(1.0));
		m_shader->SetFloat("u_pointLights[1].constant", 1.0f);
		m_shader->SetFloat("u_pointLights[1].linear", 0.09);
		m_shader->SetFloat("u_pointLights[1].quadratic", 0.032);
	}

	if (m_pSpotLight1)
	{
		m_pSpotLight1->setEnable(SpotLightEnable1);
		m_pSpotLight1->setInnerAngle(innerAngle);
		m_pSpotLight1->setOuterAngle(outerAngle);
		m_shader->SetFloat("u_spotLights[0].enable", m_pSpotLight1->getEnable());
		m_shader->SetVec3("u_spotLights[0].position", m_pSpotLight1->getPosition());
		m_shader->SetVec3("u_spotLights[0].director", m_pSpotLight1->getDirection());
		m_shader->SetVec3("u_spotLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		m_shader->SetVec3("u_spotLights[0].specular", glm::vec3(1.0));
		m_shader->SetFloat("u_spotLights[0].cosInnerAngle", m_pSpotLight1->getCosInnerAngle());
		m_shader->SetFloat("u_spotLights[0].cosOuterAngle", m_pSpotLight1->getCosOuterAngle());
	}
	if (m_pSpotLight2)
	{
		m_pSpotLight2->setEnable(SpotLightEnable2);
		m_shader->SetFloat("u_spotLights[1].enable", m_pSpotLight2->getEnable());
		m_shader->SetVec3("u_spotLights[1].position", m_pSpotLight2->getPosition());
		m_shader->SetVec3("u_spotLights[1].director", m_pSpotLight2->getDirection());
		m_shader->SetVec3("u_spotLights[1].diffuse", glm::vec3(0.8f, 0.2f, 0.1f));
		m_shader->SetVec3("u_spotLights[1].specular", glm::vec3(1.0));
		m_shader->SetFloat("u_spotLights[1].cosInnerAngle", m_pSpotLight2->getCosInnerAngle());
		m_shader->SetFloat("u_spotLights[1].cosOuterAngle", m_pSpotLight2->getCosOuterAngle());
	}
	glUniform1f(glGetUniformLocation(m_shader->GetProgram(), "u_material.shininess"), m_uShininess);
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

	glBindVertexArray(m_LightVAO);
	m_Lightshader->use();
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, YCamera::m_visitingCamera->getViewMatrix());
	m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::GetVisitingCamera()->getProjectionMatrix());
	if (m_pPointLight1&&PointLightEnable1)
	{
		glm::mat4 lightModel(1.0f);
		lightModel = glm::translate(lightModel, m_pPointLight1->getPosition());
		glm::vec4 color(1.0f);
		glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &color[0]);
		lightModel = glm::scale(lightModel, glm::vec3(0.2));
		m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, lightModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	if (m_pPointLight2&&PointLightEnable2)
	{
		glm::mat4 lightModel(1.0f);
		lightModel = glm::translate(lightModel, m_pPointLight2->getPosition());
		glm::vec4 color(1.0f);
		glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &color[0]);
		lightModel = glm::scale(lightModel, glm::vec3(0.2));
		m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, lightModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (m_pSpotLight1&&SpotLightEnable1)
	{
		glm::mat4 lightModel(1.0f);
		lightModel = glm::translate(lightModel, m_pSpotLight1->getPosition());
		glm::vec4 color(1.0f);
		glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &color[0]);
		lightModel = glm::scale(lightModel, glm::vec3(0.4));
		m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, lightModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	if (m_pSpotLight2&&SpotLightEnable2)
	{
		glm::mat4 lightModel(1.0f);
		lightModel = glm::translate(lightModel, m_pSpotLight2->getPosition());
		glm::vec4 color(0.8f, 0.0f, 0.0f,1.0f);
		glUniform4fv(glGetUniformLocation(m_Lightshader->GetProgram(), "u_objectColor"), 1, &color[0]);
		lightModel = glm::scale(lightModel, glm::vec3(0.4));
		m_Lightshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, lightModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	
	glBindVertexArray(0);
	
}









