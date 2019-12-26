#include "SampleInclude.h"
#include "Application.h"
#include "YDirector.h"
#include "GLView.h"
#include "GLViewImpl.h"

#include "YScene.h"


Application::Application()
{

}

Application::~Application()
{

}

int Application::run()
{
	auto director = YDirector::GetInstance();
	GLView* _glview = director->getOpenGLView();
	if (_glview == nullptr)
	{
		_glview = GLViewImpl::create("Cpp Tests");
		director->setOpenGLView(_glview);
	}
	YScene* s = YScene::create();
	auto test = SkyBoxTest::create();
//	auto test1 = CameraTest::create();
  // auto test2 = FrameBufferTest::create();
   //auto test3 = LightTest::create();
	s->addChild(test, 1);
	//s->addChild(test1, 1);
	//s->addChild(test2, 1);
	//s->addChild(test3, 1);
	director->replaceScene(s);
	
	while (!_glview->windowShouldClose())
	{
		director->mainLoop();
	   _glview->pollEvents();
	}
	return 0;
}

Application* Application::getInstance()
{
	static Application app;
	return &app;
}

