#include "SeniorGLTest.h"

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
#include <map>



SeniorGLTest::SeniorGLTest()
	:m_pshader(nullptr)
	, m_pModel(nullptr)
	, m_pCubeTexture(nullptr)
	,m_pPlaneTexture(nullptr)
	,m_bDepthTest(false)
	,m_bStencilTest(false)
	, m_pOutlineShader(false)
	, m_bTransparentTest(false)
	, m_pTransparentTexture(nullptr)
	, m_bCullFace(false)
{

}

SeniorGLTest::~SeniorGLTest()
{

}



void SeniorGLTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&SeniorGLTest::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool SeniorGLTest::init()
{
	m_pshader = new YShader("./src/Shader/SeniorGLTest.vert", "./src/Shader/SeniorGLTest.frag");
	m_pOutlineShader = new YShader("./src/Shader/SeniorGLTest.vert", "./src/Shader/SeniorGLColorTest.frag");
	initBuffers();
	return true;
}

void SeniorGLTest::initBuffers()
{

	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
										  // Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		// Left face
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		// Right face
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left      
	};
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};
	float transparentVertices[] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};
	unsigned int vbo;
	glGenVertexArrays(1, &m_CubeVAO);
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_CubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_POSITION);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_TEXCOORDS);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*) (3 * sizeof(float)));

	glBindVertexArray(0);

	glGenVertexArrays(1, &m_PlaneVAO);
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_PlaneVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_POSITION);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_TEXCOORDS);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	glGenVertexArrays(1, &m_TransparentVAO);
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_TransparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_POSITION);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(GLProgram::LAYOUT_INDEX_TEXCOORDS);
	glVertexAttribPointer(GLProgram::LAYOUT_INDEX_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


	m_pPlaneTexture = YTexture2D::create("src/Sample/SeniorGL-Test/Texture/metal.png");
	m_pCubeTexture = YTexture2D::create("src/Sample/SeniorGL-Test/Texture/marble.jpg");
	m_pTransparentTexture = YTexture2D::create("src/Sample/SeniorGL-Test/Texture/window.png");
	m_pshader->use();
	m_pshader->SetInt(GLProgram::UNIFORM_NAME_TEXTURE1, 0);
}

void SeniorGLTest::onDraw(const glm::mat4* transform, uint32_t)
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();
	ImGui::Begin("SeniorGl", 0, ImGuiWindowFlags_MenuBar);
	ImGui::Checkbox("DepthTset", &m_bDepthTest);
	ImGui::Checkbox("StencilTest", &m_bStencilTest);
	ImGui::Checkbox("TransparentTest", &m_bTransparentTest);
	ImGui::Checkbox("CullFace", &m_bCullFace);
	
	ImGui::End();
	

	m_pshader->use();
	std::vector<glm::vec3> vegetation
	{
		glm::vec3(-1.5f, 0.0f, -0.48f),
		glm::vec3(1.5f, 0.0f, 0.51f),
		glm::vec3(0.0f, 0.0f, 0.7f),
		glm::vec3(-0.3f, 0.0f, -2.3f),
		glm::vec3(0.5f, 0.0f, -0.6f)
	};
	// view/projection transformations
	if (m_bDepthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	glDepthFunc(GL_LESS);
	glStencilMask(0x00);
	glm::mat4 model = glm::mat4(1.0f);
	m_pshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix());
	m_pshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, YCamera::m_visitingCamera->getViewMatrix());
	glBindTexture(GL_TEXTURE_2D, m_pPlaneTexture->GetName());
	model = glm::mat4(1.0f);
	glBindVertexArray(m_PlaneVAO);
	m_pshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(m_CubeVAO);
	if (m_bStencilTest)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
	}
	if (m_bCullFace)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pCubeTexture->GetName());
	// render the loaded model
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f)); // translate it down so it's at the center of the scene
	m_pshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	m_pshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	if (m_bStencilTest)
	{
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);

		m_pOutlineShader->use();
		m_pOutlineShader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix());
		m_pOutlineShader->setMat4(GLProgram::UNIFORM_NAME_VIEW, YCamera::m_visitingCamera->getViewMatrix());
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f));
		m_pOutlineShader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(1.1f));// translate it down so it's at the center of the scene
		m_pOutlineShader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glStencilMask(0xFF);
	}
	if (m_bTransparentTest)
	{
		glBindVertexArray(m_TransparentVAO);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, m_pTransparentTexture->GetName());
		m_pshader->use();
		m_pshader->setMat4(GLProgram::UNIFORM_NAME_PROJECTION, YCamera::m_visitingCamera->getProjectionMatrix());
		m_pshader->setMat4(GLProgram::UNIFORM_NAME_VIEW, YCamera::m_visitingCamera->getViewMatrix());
		std::map<float, glm::vec3> mapVegetation;
		for (int i =0;i<vegetation.size();++i)
		{
			float distance = glm::length(vegetation[i]);
			mapVegetation[distance] = vegetation[i];
			
		}
		for (auto it = mapVegetation.rbegin();it!=mapVegetation.rend();++it)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second);
			m_pshader->setMat4(GLProgram::UNIFORM_NAME_MODEL, model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	else
	{
		glDisable(GL_BLEND);
	}
	
	
}



