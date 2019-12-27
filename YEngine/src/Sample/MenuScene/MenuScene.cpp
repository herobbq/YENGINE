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
	,m_pCameraTest(nullptr)
	,m_pFrameBufferTest(nullptr)
	,m_pLightTest(nullptr)
	,m_pSkyboxTest(nullptr)
	,m_pTextureTest(nullptr)
	,m_pTriangleTest(nullptr)
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
	ImGui::End();
	if (YScene* renderScene = YDirector::GetInstance()->getRenderScene())
	{
		if (m_bRenderCameraTest)
		{
			if (m_pCameraTest==nullptr)
			{
				m_pCameraTest = CameraTest::create();
			}
			else
			{
				renderScene->removeChild(m_pCameraTest);
				renderScene->addChild(m_pCameraTest,1);
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
				renderScene->removeChild(m_pTriangleTest);
				renderScene->addChild(m_pTriangleTest, 1);
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
				renderScene->removeChild(m_pTextureTest);
				renderScene->addChild(m_pTextureTest, 1);
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
				renderScene->removeChild(m_pFrameBufferTest);
				renderScene->addChild(m_pFrameBufferTest, 1);
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
				renderScene->removeChild(m_pLightTest);
				renderScene->addChild(m_pLightTest, 1);
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
				renderScene->removeChild(m_pSkyboxTest);
				renderScene->addChild(m_pSkyboxTest, 1);
			}
		}
		else
		{
			renderScene->removeChild(m_pSkyboxTest);
		}
	}
	
}



