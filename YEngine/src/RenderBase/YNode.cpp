#include "YNode.h"
YNode::YNode()
	:m_pParent(nullptr)
	, m_iTag(-1)
{

}

YNode::~YNode()
{

}

YNode * YNode::create()
{
	YNode * ret = new (std::nothrow) YNode();
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

void YNode::addChild(YNode * child, int localZOrder)
{
	assert(child != nullptr, "Argument must be non-nil");
	this->addChild(child, localZOrder, child->m_strName);
}

void YNode::addChild(YNode* child, int localZOrder, int tag)
{
	assert(child != nullptr, "Argument must be non-nil");
	assert(child->m_pParent == nullptr, "child already added. It can't be added again");

	addChildHelper(child, localZOrder, tag, "", true);
}

void YNode::addChild(YNode* child, int localZOrder, const std::string &name)
{
	assert(child != nullptr, "Argument must be non-nil");
	assert(child->m_pParent == nullptr, "child already added. It can't be added again");

	addChildHelper(child, localZOrder, -1, name, true);
}

void YNode::draw(YRenderer *renderer, const glm::mat4& transform, uint32_t flags)
{

}

void YNode::visit(YRenderer *renderer, const glm::mat4& parentTransform, uint32_t parentFlags)
{
	int i = 0;
	uint32_t flags = -1;
	if (!m_vChildrens.empty())
	{
		//sortAllChildren();
		// draw children zOrder < 0
		for (auto size = m_vChildrens.size(); i < size; ++i)
		{
			auto node = m_vChildrens.at(i);

			if (node && node->m_ilocalZOrder < 0)
				node->visit(renderer, m_modelViewTransform, flags);
			else
				break;
		}
		// self draw
		//if (visibleByCamera)
		this->draw(renderer, m_modelViewTransform, flags);

		for (auto it = m_vChildrens.cbegin() + i, itCend = m_vChildrens.cend(); it != itCend; ++it)
			(*it)->visit(renderer, m_modelViewTransform, flags);
	}
	else
	{
		this->draw(renderer, m_modelViewTransform, flags);
	}
}

int YNode::getTag() const
{
	return m_iTag;
}

void YNode::setTag(int tag)
{
	m_iTag = tag;
}

const std::string& YNode::getName() const
{
	return m_strName;
}

void YNode::setNodeToParentTransform(const glm::mat4& transform)
{
	m_transform = transform;
}

void YNode::setName(const std::string& name)
{
	m_strName = name;
}

void YNode::setParent(YNode* parent)
{
	m_pParent = parent;
}

bool YNode::init()
{
	return true;
}

void YNode::insertChild(YNode* child, int z)
{
	m_vChildrens.push_back(child);
	child->setLocalZOrder(z);
}

void YNode::setLocalZOrder(std::int32_t z)
{
	m_ilocalZOrder = z;
}

void YNode::addChildHelper(YNode* child, int localZOrder, int tag, const std::string &name, bool setTag)
{
	auto assertNotSelfChild
	([this, child]() -> bool
	{
		for (YNode* parent(getParent()); parent != nullptr;
			parent = parent->getParent())
			if (parent == child)
				return false;

		return true;
	});
	(void)assertNotSelfChild;

	assert(assertNotSelfChild(),
		"A node cannot be the child of his own children");


	this->insertChild(child, localZOrder);

	if (setTag)
		child->setTag(tag);
	else
		child->setName(name);

	child->setParent(this);
}

