#include "YCustomCommand.h"

YCustomCommand::YCustomCommand()
	: func(nullptr)
{

}

YCustomCommand::~YCustomCommand()
{

}

void YCustomCommand::init(float globalZOrder, const glm::mat4& modelViewTransform, uint32_t flags)
{
	YRenderCommand::init(globalZOrder, modelViewTransform, flags);
}

void YCustomCommand::init(float globalZOrder)
{
	m_globalOrder = globalZOrder;
}

void YCustomCommand::execute()
{
	if (func)
	{
		func();
	}
}

