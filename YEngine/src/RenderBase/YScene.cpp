#include "YScene.h"
#include "YRenderer.h"
YScene::YScene()
{

}

YScene::~YScene()
{

}

YScene* YScene::create()
{
	YScene * ret = new (std::nothrow) YScene();
	if (ret && ret->init())
	{
		//ret->SubRef();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}
	return ret;
}

void YScene::render(YRenderer* renderer, const glm::mat4& eyeTransform, const glm::mat4* eyeProjection /*= nullptr*/)
{
	render(renderer, &eyeTransform, eyeProjection, 1);
}

void YScene::render(YRenderer* renderer, const glm::mat4* eyeTransforms, const glm::mat4* eyeProjections, unsigned int multiViewCount)
{
	visit(renderer, m_transform, 0);
	renderer->render();
}

