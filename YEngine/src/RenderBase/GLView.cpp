#include "GLView.h"
#include "YScene.h"
GLView::GLView()
	:m_window(nullptr)
{

}

GLView::~GLView()
{

}

void GLView::pollEvents()
{

}

void GLView::renderScene(YScene* scene, YRenderer* renderer)
{
	scene->render(renderer, glm::mat4(1), nullptr);
}

