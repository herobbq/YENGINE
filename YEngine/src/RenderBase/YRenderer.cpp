#include"YRenderer.h"
#include "YCustomCommand.h"
YRenderer::YRenderer()
{

}

YRenderer::~YRenderer()
{

}

void YRenderer::addCommand(YRenderCommand* command)
{
	RenderQueue* queue = new RenderQueue;
	queue->push_back(command);
	m_renderGroups.push_back(*queue);
	//m_renderGroups[0].push_back(command);
}

void YRenderer::clean()
{
	for (int i =0;i<m_renderGroups.size();++i)
	{
		delete &m_renderGroups[i];
	}
	m_renderGroups.clear();
}

void YRenderer::clear()
{
	glDepthMask(true);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthMask(false);
}

void YRenderer::processRenderCommand(YRenderCommand* command)
{
	auto cmd = static_cast<YCustomCommand*>(command);
	cmd->execute();

}

void YRenderer::visitRenderQueue(RenderQueue& queue)
{
	const auto& opaqueQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::OPAQUE_3D);
	if (!opaqueQueue.empty())
	{
		//Clear depth to achieve layered rendering
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		//glDisable(GL_BLEND);
		//glEnable(GL_CULL_FACE);

		for (const auto& opaqueNext : opaqueQueue)
		{
			processRenderCommand(opaqueNext);
		}
	}
}

void YRenderer::render()
{
	for (auto &renderqueue : m_renderGroups)
	{
		//renderqueue.sort();
	}
	visitRenderQueue(m_renderGroups[0]);
}

RenderQueue::RenderQueue()
{

}

void RenderQueue::push_back(YRenderCommand* command)
{
	m_commands[0].push_back(command);
}

size_t RenderQueue::size() const
{
	return m_commands[0].size();
}

YRenderCommand* RenderQueue::operator[](size_t index) const
{
	return m_commands[0][index];
}

void RenderQueue::clear()
{
	m_commands[0].clear();
}

void RenderQueue::realloc(size_t reserveSize)
{
	m_commands[0].resize(reserveSize);
}

void RenderQueue::saveRenderState()
{
	m_isDepthEnabled = glIsEnabled(GL_DEPTH_TEST) != GL_FALSE;
	m_isCullEnabled = glIsEnabled(GL_CULL_FACE) != GL_FALSE;
	glGetBooleanv(GL_DEPTH_WRITEMASK, &m_isDepthWrite );
}

void RenderQueue::restoreRenderState()
{
	if (m_isCullEnabled)
	{
		glEnable(GL_CULL_FACE);
		//RenderState::StateBlock::_defaultState->setCullFace(true);
	}
	else
	{
		glDisable(GL_CULL_FACE);
		//RenderState::StateBlock::_defaultState->setCullFace(false);
	}

	if (m_isDepthEnabled)
	{
		glEnable(GL_DEPTH_TEST);
		//RenderState::StateBlock::_defaultState->setDepthTest(true);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		//RenderState::StateBlock::_defaultState->setDepthTest(false);
	}

	glDepthMask(m_isDepthWrite);
	//RenderState::StateBlock::_defaultState->setDepthWrite(_isDepthEnabled);
}

