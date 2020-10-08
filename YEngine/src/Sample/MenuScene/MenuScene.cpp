#include "MenuScene.h"
#include "YCamera.h"
#include "YRenderer.h"
#include "YDirector.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "SampleInclude.h"
#include "YScene.h"

MenuScene::MenuScene()
	:m_bRenderCameraTest(false)
	,m_bRenderFrameBufferTest(false)
	,m_bRenderLightTest(false)
	,m_bRenderSkyboxTest(false)
	,m_bRenderTextureTest(false)
	,m_bRenderTriangleTest(false)
	,m_bRenderModelTest(false)
	, m_bRenderSeniorGLTest(false)
	, m_bRenderAdvanceTest(false)
	, m_bRenderShadowTest(false)
	,m_pCameraTest(nullptr)
	,m_pFrameBufferTest(nullptr)
	,m_pLightTest(nullptr)
	,m_pSkyboxTest(nullptr)
	,m_pTextureTest(nullptr)
	,m_pTriangleTest(nullptr)
	,m_pModelTest(nullptr)
	, m_pSeniorGLTest(nullptr)
	,m_pShadowTest(nullptr)
	,m_pAdvanceGLTest(nullptr)
	,m_deltaTime(0)
	,m_lastFrame(0)
{

}

MenuScene::~MenuScene()
{

}


void MenuScene::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&MenuScene::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool MenuScene::init()
{
	glfwSetCursorPosCallback(YDirector::GetInstance()->getGLwindow(), YCamera::mouse_callback);
	glfwSetScrollCallback(YDirector::GetInstance()->getGLwindow(), YCamera::scroll_callback);
	return true;
}

void MenuScene::onDraw(const glm::mat4* transform, uint32_t)
{
	float curTime = glfwGetTime();
	m_deltaTime = curTime - m_lastFrame;
	m_lastFrame = curTime;
	YCamera::processInput(YDirector::GetInstance()->getGLwindow(), m_deltaTime);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Menu Test", 0, ImGuiWindowFlags_MenuBar);
	ImGui::Text("This is some useful text.");
	ImGui::Checkbox("CameraText", &m_bRenderCameraTest);
	ImGui::Checkbox("TriangleText", &m_bRenderTriangleTest);
	ImGui::Checkbox("TextureText", &m_bRenderTextureTest);
	ImGui::Checkbox("SkyboxText", &m_bRenderSkyboxTest);
	ImGui::Checkbox("FrameBufferText", &m_bRenderFrameBufferTest);
	ImGui::Checkbox("LightText", &m_bRenderLightTest);
	ImGui::Checkbox("ModelText", &m_bRenderModelTest);
	ImGui::Checkbox("SeniorGLTest", &m_bRenderSeniorGLTest);
	ImGui::Checkbox("AdvanceLightTest", &m_bRenderAdvanceTest);
	ImGui::Checkbox("ShadowTest", &m_bRenderShadowTest);
	ImGui::End();
	if (YScene* renderScene = getScene())
	{
		if (m_bRenderCameraTest)
		{
			if (m_pCameraTest==nullptr)
			{
				m_pCameraTest = CameraTest::create();
			}
			else
			{
				if (m_pCameraTest->getParent()==nullptr)
				{
					renderScene->addChild(m_pCameraTest, 1);
				}
				
			}
		}
		else
		{
			renderScene->removeChild(m_pCameraTest);
		}
		/////////////////////////////////
		if (m_bRenderTriangleTest)
		{
			if (m_pTriangleTest == nullptr)
			{
				m_pTriangleTest = TriangleTest::create();
			}
			else
			{
				if (m_pTriangleTest->getParent()==nullptr)
				{
					renderScene->addChild(m_pTriangleTest, 1);
				}
				
			}
		}
		else
		{
			renderScene->removeChild(m_pTriangleTest);
		}
		///////////////////////////////////////
		if (m_bRenderTextureTest)
		{
			if (m_pTextureTest == nullptr)
			{
				m_pTextureTest = TextureTest::create();
			}
			else
			{
				if (m_pTextureTest->getParent()==nullptr)
				{
					renderScene->addChild(m_pTextureTest, 1);
				}
				
			}
		}
		else
		{
			renderScene->removeChild(m_pTextureTest);
		}
		///////////////////////////////////////////////
		if (m_bRenderFrameBufferTest)
		{
			if (m_pFrameBufferTest == nullptr)
			{
				m_pFrameBufferTest = FrameBufferTest::create();
			}
			else
			{
				if (m_pFrameBufferTest->getParent()==nullptr)
				{
					renderScene->addChild(m_pFrameBufferTest, 1);
				}
				
			}
		}
		else
		{
			renderScene->removeChild(m_pFrameBufferTest);
		}
		///////////////////////////////////////////
		if (m_bRenderLightTest)
		{
			if (m_pLightTest == nullptr)
			{
				m_pLightTest = LightTest::create();
			}
			else
			{
				if (m_pLightTest->getParent()==nullptr)
				{
					renderScene->addChild(m_pLightTest, 1);
				}
				
			}
		}
		else
		{
			renderScene->removeChild(m_pLightTest);
		}
		////////////////////////////////////////////////////////////////
		if (m_bRenderSkyboxTest)
		{
			if (m_pSkyboxTest == nullptr)
			{
				m_pSkyboxTest = SkyBoxTest::create();
			}
			else
			{
				if (m_pSkyboxTest->getParent()==nullptr)
				{
					renderScene->addChild(m_pSkyboxTest, 1);
				}
				
			}
		}
		else
		{
			renderScene->removeChild(m_pSkyboxTest);
		}
		if (m_bRenderModelTest)
		{
			if (m_pModelTest == nullptr)
			{
				m_pModelTest = ModelTest::create();
			}
			else
			{
				if (m_pModelTest->getParent() == nullptr)
				{
					renderScene->addChild(m_pModelTest, 1);
				}

			}
		}
		else
		{
			renderScene->removeChild(m_pModelTest);
		}
		if (m_bRenderSeniorGLTest)
		{
			if (m_pSeniorGLTest == nullptr)
			{
				m_pSeniorGLTest = SeniorGLTest::create();
			}
			else
			{
				if (m_pSeniorGLTest->getParent() == nullptr)
				{
					renderScene->addChild(m_pSeniorGLTest, 1);
				}

			}
		}
		else
		{
			renderScene->removeChild(m_pSeniorGLTest);
		}
		if (m_bRenderAdvanceTest)
		{
			if (m_pAdvanceGLTest == nullptr)
			{
				m_pAdvanceGLTest = AdvanceLight::create();
			}
			else
			{
				if (m_pAdvanceGLTest->getParent() == nullptr)
				{
					renderScene->addChild(m_pAdvanceGLTest, 1);
				}

			}
		}
		else
		{
			renderScene->removeChild(m_pAdvanceGLTest);
		}
		if (m_bRenderShadowTest)
		{
			if (m_pShadowTest == nullptr)
			{
				m_pShadowTest = ShadowTest::create();
			}
			else
			{
				if (m_pShadowTest->getParent() == nullptr)
				{
					renderScene->addChild(m_pShadowTest, 1);
				}

			}
		}
		else
		{
			renderScene->removeChild(m_pShadowTest);
		}
	}
	
}



