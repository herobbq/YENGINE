#ifndef YTEXTURETEST_H_
#define YTEXTURETEST_H_

#include "YNode.h"
#include "YCustomCommand.h"
#include "YType.h"

class YShader;
class YTexture2D;
class NormalMapping :public YNode
{
public:
	NormalMapping();
	virtual ~NormalMapping();
public:
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;
	//virtual void onDraw();
	Y_CREATESAMPLE(NormalMapping);
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);
protected:
	YCustomCommand m_customCommand;
};



#endif

