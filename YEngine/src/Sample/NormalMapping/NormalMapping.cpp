#include "NormalMapping.h"
#include "YRenderer.h"
NormalMapping::NormalMapping()
	:YNode()
{

}

NormalMapping::~NormalMapping()
{

}

void NormalMapping::draw(YRenderer* renderer, const glm::mat4& transform, uint32_t flags)
{
	glm::mat4 value = transform;
	m_customCommand.init(1);
	m_customCommand.func = std::bind(&NormalMapping::onDraw, this, &transform, flags);
	m_customCommand.setTransparent(false);
	m_customCommand.set3D(true);
	renderer->addCommand(&m_customCommand);
}

bool NormalMapping::init()
{
	initBuffers();
	return true;
}

void NormalMapping::initBuffers()
{

}

void NormalMapping::onDraw(const glm::mat4* transform, uint32_t)
{
	
}

