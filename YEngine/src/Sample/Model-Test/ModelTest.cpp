#include "ModelTest.h"

#include "hfileinclude.h"
#include"YModel.h"
#include "YLoadShader.h"
#include "YRenderer.h"
#include "GLProgram.h"
#include "YTexture2D.h"
#include "YType.h"
#include "YDirector.h"
#include "GLView.h"
#include "YCamera.h"
#include "SampleInclude.h"




ModelTest::ModelTest()
	:m_Modelshader(nullptr)
	, m_pModel(nullptr)
{

}

ModelTest::~ModelTest()
{

}



void ModelTest::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&ModelTest::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool ModelTest::init()
{
	m_Modelshader = new YShader("./src/Shader/ModelTest.vert", "./src/Shader/ModelTest.frag");
	m_pModel = new YModel("./src/sample/Model-Test/Model/nanosuit.obj");
	initBuffers();
	return true;
}

void ModelTest::initBuffers()
{
	


}

void ModelTest::onDraw(const glm::mat4* transform, uint32_t)
{
	m_Modelshader->use();

	// view/projection transformations
	
	
	m_Modelshader->setMat4("u_projection", YCamera::m_visitingCamera->getProjectionMatrix());
	m_Modelshader->setMat4("u_view", YCamera::m_visitingCamera->getViewMatrix());

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	m_Modelshader->setMat4("u_model", model);
	m_pModel->Draw(*m_Modelshader);
}



