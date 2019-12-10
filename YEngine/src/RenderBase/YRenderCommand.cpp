#include "YRenderCommand.h"
#include "YCamera.h"
YRenderCommand::YRenderCommand()
	: m_globalOrder(0)
	, m_isTransparent(true)
	, m_is3D(false)
	, m_depth(0)
{

}

YRenderCommand::~YRenderCommand()
{

}


void YRenderCommand::init(float globalZOrder, const glm::mat4& modelViewTransform, uint32_t flags)
	
{
	m_globalOrder = globalZOrder;
	if (flags == 1 )
	{
		if (YCamera::GetVisitingCamera())
			m_depth = YCamera::GetVisitingCamera()->getDepthInView(modelViewTransform);

		set3D(true);
	}
	else
	{
		set3D(false);
		m_depth = 0;
	}
}
