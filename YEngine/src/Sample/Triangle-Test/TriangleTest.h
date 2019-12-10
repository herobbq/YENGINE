#ifndef YTRIANGLETEST_H_
#define YTRIANGLETEST_H_

#include "YNode.h"
#include "YCustomCommand.h"
#include "glm/glm.hpp"

class YShader;
class TriangleTest :public YNode
{
public:
	TriangleTest();
	virtual ~TriangleTest();
public:
	static TriangleTest* create();
	virtual void draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags) override;
	//virtual void onDraw();
protected:
	virtual bool init() override;
	virtual void initBuffers();
	void onDraw(const glm::mat4* transform, uint32_t);
protected:
	YCustomCommand m_customCommand;
	YShader*    m_shader;
	unsigned int m_VBO;
	unsigned int m_VAO;
};



#endif

