#include "YLight.h"

BaseLight::BaseLight()
	:m_fintensity(1.0f)
{

}

BaseLight::~BaseLight()
{

}

void BaseLight::setIntensity(float intensity)
{
	m_fintensity = intensity>=0? intensity:0;
}

void BaseLight::setRotationFromDirection(const glm::vec3 &direction)
{
	float projLen = std::sqrt(direction.x * direction.x + direction.z * direction.z);
	float rotY = glm::degrees(atan2f(-direction.x, -direction.z));
	float rotX = -glm::degrees(atan2f(-direction.y, projLen));
	setRotation(glm::vec3(rotX, rotY, 0.0f));
	m_direction = direction;
}


DirectionLight* DirectionLight::create(const glm::vec3 &direction, const YColor&color)
{
	auto light = new (std::nothrow) DirectionLight();
	light->setRotationFromDirection(direction);
	light->setColor(color);
	return light;
}

DirectionLight::DirectionLight()
{

}

void DirectionLight::setDirection(const glm::vec3 &dir)
{
	setRotationFromDirection(dir);
}

glm::vec3& DirectionLight::getDirection() const
{
	return m_direction;
}

DirectionLight::~DirectionLight()
{

}

PointLight* PointLight::create(const glm::vec3 &position, const YColor &color, float range)
{
	auto light = new (std::nothrow) PointLight();
	light->setPosition(position);
	light->setColor(color);
	light->m_range = range;
	return light;
}

PointLight::PointLight()
{

}

PointLight::~PointLight()
{

}

SpotLight* SpotLight::create(const glm::vec3 &direction, const glm::vec3 &position, const YColor &color, float innerAngle, float outerAngle, float range)
{
	auto light = new (std::nothrow) SpotLight();
	light->setRotationFromDirection(direction);
	light->setPosition(position);
	light->setColor(color);
	light->setInnerAngle(innerAngle);
	light->setOuterAngle(outerAngle);
	light->m_range = range;
	return light;
}

void SpotLight::setDirection(const glm::vec3 &dir)
{
	setRotationFromDirection(dir);
}

glm::vec3 SpotLight::getDirection() const
{
	return m_direction;
}

glm::vec3 SpotLight::getDirectionInWorld() const
{
	return m_direction;
}

void SpotLight::setInnerAngle(float angle)
{
	m_innerAngle = angle;
	m_cosInnerAngle = cosf(angle);
}

void SpotLight::setOuterAngle(float outerAngle)
{
	m_outerAngle = outerAngle;
	m_cosOuterAngle = cosf(outerAngle);
}

SpotLight::SpotLight()
{

}

SpotLight::~SpotLight()
{

}

AmbientLight* AmbientLight::create(const YColor &color)
{
	auto light = new (std::nothrow) AmbientLight();
	light->setColor(color);
	return light;
}

AmbientLight::AmbientLight()
{

}

AmbientLight::~AmbientLight()
{

}
