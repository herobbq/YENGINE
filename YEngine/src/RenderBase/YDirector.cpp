#include "YDirector.h"
#include "GLView.h"
#include "YScene.h"
#include "YRenderer.h"
#include "YCamera.h"
float     m_deltaTime = 0.0f;	// time between current frame and last frame
float     m_lastFrame = 0.0f;
YDirector::YDirector()
	:m_openGLView(nullptr)
	, m_renderer(nullptr)
	, m_RuingScene(nullptr)
	,m_NextScene(nullptr)
{
	m_renderer = new YRenderer;
}

YDirector::~YDirector()
{

}

YDirector* YDirector::GetInstance()
{
	static YDirector director;
	return &director;
}

void YDirector::PushScene(YScene* scene)
{
	m_SceneStack.push(scene);
	m_NextScene = scene;
}

void YDirector::PopScene(YScene* scene)
{
	m_SceneStack.pop();
	size_t c = m_SceneStack.size();

	if (c == 0)
	{
		//end();
	}
	else
	{
		//_sendCleanupToScene = true;
		m_NextScene = m_SceneStack.top();
	}
}

void YDirector::setOpenGLView(GLView *openGLView)
{
	if (openGLView)
	{
		m_openGLView = openGLView;
	}
}

void YDirector::setNextScene()
{
	if (m_RuingScene)
	{
		m_RuingScene->release();
	}
	m_RuingScene = m_NextScene;
	m_NextScene->AddRef();
	m_NextScene = nullptr;

}

void YDirector::mainLoop()
{
	float curTime = glfwGetTime();
	m_deltaTime = curTime - m_lastFrame;
	m_lastFrame = curTime;
	drawScene();
}

void YDirector::replaceScene(YScene *scene)
{
	if (m_RuingScene == nullptr)
	{
		runWithScene(scene);
		return;
	}
	if (scene == m_NextScene)
	{
		return;
	}
	if (m_NextScene)
	{
		
		m_NextScene = nullptr;
	}

	size_t index = m_SceneStack.size() - 1;


	m_SceneStack.pop();
	m_SceneStack.push(scene);

	m_NextScene = scene;
}

void YDirector::runWithScene(YScene *scene)
{
	
	PushScene(scene);
}

YSize& YDirector::getWinsize()
{
	return m_openGLView->getViewSize();
}



GLFWwindow* YDirector::getGLwindow()
{
	if(m_openGLView)
	{
		return m_openGLView->getCurWindow();
	}
	return nullptr;
}

void YDirector::drawScene()
{
	
	if (m_openGLView)
	{
		m_openGLView->pollEvents();
	}
	m_renderer->clean();
	m_renderer->clear();
	if (m_NextScene)
	{
		setNextScene();
	}

	if (m_RuingScene)
	{
		if (m_openGLView)
			m_openGLView->renderScene(m_RuingScene, m_renderer);
		
	}
	if (m_openGLView)
	{
		m_openGLView->swapBuffers();
	}
	
}

