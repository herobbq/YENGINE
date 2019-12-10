#ifndef YSCENE_H_
#define YSCENE_H_
#include "YNode.h"
#include <glm/glm.hpp>
class YRenderer;
class YScene :public YNode
{
public:
	YScene();
	virtual ~YScene();
	static YScene* create();
public:
	virtual void render(YRenderer* renderer, const glm::mat4& eyeTransform, const glm::mat4* eyeProjection = nullptr);

	virtual void render(YRenderer* renderer, const glm::mat4* eyeTransforms, const glm::mat4* eyeProjections, unsigned int multiViewCount);
};



#endif
