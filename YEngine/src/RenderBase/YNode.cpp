#include "YNode.h"
#include "YScene.h"
YNode::YNode()
	:m_pParent(nullptr)
	, m_iTag(-1)
	, m_position(0.0, 0.0,0.0)
	, m_scaleX(1)
	, m_scaleY(1)
	, m_scaleZ(1)
	, m_rotationX(0)
	, m_rotationY(0)
	, m_rotationZ_X(0)
	,m_rotationZ_Y(0)
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

void YNode::removeChild(YNode* child)
{
	if (child == nullptr)
	{
		return;
	}
	for (auto it = m_vChildrens.begin(); it!=m_vChildrens.end();++it)
	{
		if (*it==child)
		{
			child->setParent(nullptr);
			m_vChildrens.erase(it);
			break;
		}
	}
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

YScene* YNode::getScene() const
{
	if (!m_pParent)
		return nullptr;

	auto sceneNode = m_pParent;
	while (sceneNode->m_pParent)
	{
		sceneNode = sceneNode->m_pParent;
	}

	return dynamic_cast<YScene*>(sceneNode);
}

void YNode::setPosition(const glm::vec3 &position)
{
	m_position = position;
}


glm::vec3& YNode::getPosition() 
{
		return m_position;

}

void YNode::setRotation(float rotation)
{
	m_rotationX = m_rotationZ_Y = m_rotationZ_X = m_rotationZ_Y = rotation;
	updateRotationQuat();
}

void YNode::setRotation(const glm::vec3& rotation)
{
	if (m_rotationX == rotation.x&&m_rotationY == rotation.y&&m_rotationZ_X == m_rotationZ_Y == rotation.z)
	{
		return;
	}
	m_rotationX = rotation.x;
	m_rotationY = rotation.y;
	m_rotationZ_X = m_rotationZ_Y = rotation.z;
	updateRotationQuat();
}

glm::vec3& YNode::getRotation3D() 
{
	assert(m_rotationZ_X == m_rotationZ_Y);
	return glm::vec3(m_rotationX, m_rotationY, m_rotationZ_X);

}

void YNode::setRotationQuat(const glm::fquat& quat)
{
	m_rotationQuat = quat;
	updateRotation3D();
}

glm::fquat YNode::getRotationQuat() const
{
	return m_rotationQuat;
}

void YNode::setScaleX(float scaleX)
{
	m_scaleX = scaleX;
}

float YNode::getScaleX() const
{
	return m_scaleX;
}

void YNode::setScaleY(float scaleY)
{
	m_scaleY = scaleY;
}

float YNode::getScaleY() const
{
	return m_scaleY;
}

void YNode::setScaleZ(float scaleZ)
{
	m_scaleZ = scaleZ;
}

float YNode::getScaleZ() const
{
	return m_scaleZ;
}

void YNode::setScale(float scale)
{
	setScaleX(scale);
	setScaleY(scale);
	setScaleZ(scale);
}

void YNode::setScale(float scaleX, float scaleY, float scaleZ)
{
	setScaleX(scaleX);
	setScaleY(scaleY);
	setScaleZ(scaleZ);
}

void YNode::updateRotationQuat()
{
	// convert Euler angle to quaternion
	// when _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX
	// when _rotationZ_X != _rotationZ_Y, _rotationQuat = RotationY * RotationX
	float halfRadx = glm::radians(m_rotationX / 2.f), halfRady = glm::radians(m_rotationY / 2.f), halfRadz = m_rotationZ_X == m_rotationZ_Y ? -glm::radians(m_rotationZ_X / 2.f) : 0;
	float coshalfRadx = cosf(halfRadx), sinhalfRadx = sinf(halfRadx), coshalfRady = cosf(halfRady), sinhalfRady = sinf(halfRady), coshalfRadz = cosf(halfRadz), sinhalfRadz = sinf(halfRadz);
	m_rotationQuat.x = sinhalfRadx * coshalfRady * coshalfRadz - coshalfRadx * sinhalfRady * sinhalfRadz;
	m_rotationQuat.y = coshalfRadx * sinhalfRady * coshalfRadz + sinhalfRadx * coshalfRady * sinhalfRadz;
	m_rotationQuat.z = coshalfRadx * coshalfRady * sinhalfRadz - sinhalfRadx * sinhalfRady * coshalfRadz;
	m_rotationQuat.w = coshalfRadx * coshalfRady * coshalfRadz + sinhalfRadx * sinhalfRady * sinhalfRadz;

	
}

void YNode::updateRotation3D()
{
	float x = m_rotationQuat.x, y = m_rotationQuat.y, z = m_rotationQuat.z, w = m_rotationQuat.w;
	m_rotationX = atan2f(2.f * (w * x + y * z), 1.f - 2.f * (x * x + y * y));
	float sy = 2.f * (w * y - z * x);
	sy = glm::clamp<float>(sy, -1, 1);
	m_rotationY = asinf(sy);
	m_rotationZ_X = atan2f(2.f * (w * z + x * y), 1.f - 2.f * (y * y + z * z));

	m_rotationX = glm::degrees(m_rotationX);
	m_rotationY = glm::degrees(m_rotationY);
	m_rotationZ_X = m_rotationZ_Y = -glm::degrees(m_rotationZ_X);
}

void YNode::setColor(const YColor& color)
{
	m_displayedColor = color;
}

float YNode::getScale() const
{
	assert(m_scaleX == m_scaleY == m_scaleZ);
	return m_scaleX;
}

float YNode::getRotation() const
{
	assert(m_rotationZ_X == m_rotationZ_Y==m_rotationX==m_rotationY);
	return m_rotationX;
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

