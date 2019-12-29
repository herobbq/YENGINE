#ifndef YLIGHT_H_
#define YLIGHT_H_
#include "YNode.h"
#include "YType.h"
enum class LightType
{
	DIRECTIONAL = 0,
	POINT = 1,
	SPOT = 2,
	AMBIENT = 3,
};


class BaseLight : public YNode
{
public:
	BaseLight();
	virtual ~BaseLight();
	virtual LightType getLightType() const = 0;
	float getIntensity() const { return m_fintensity; }
	void setIntensity(float intensity);
protected:
	void setRotationFromDirection(const glm::vec3 &direction);
protected:
	float       m_fintensity;
	glm::vec3   m_direction;
	
};
class  DirectionLight : public BaseLight
{
	static DirectionLight* create(const glm::vec3 &direction, const  YColor&color);

	//get light type
	virtual LightType getLightType() const override { return LightType::DIRECTIONAL; }
	DirectionLight();
	void setDirection(const glm::vec3 &dir);

	/**
	* Returns the Direction in parent.
	*/
	glm::vec3 getDirection() const;

	virtual ~DirectionLight(); 
};

class  PointLight : public BaseLight
{
public:
	static PointLight* create(const glm::vec3 &position, const YColor &color, float range);

	//get light type
	virtual LightType getLightType() const override { return LightType::POINT; }

	/** get or set range */
	float getRange() const { return m_range; }
	void setRange(float range) { m_range = range; }


	PointLight();
	virtual ~PointLight();

protected:
	float m_range;
};

class  SpotLight : public BaseLight
{
public:
	static SpotLight* create(const glm::vec3 &direction, const glm::vec3 &position, const YColor &color, float innerAngle, float outerAngle, float range);

	//get light type
	virtual LightType getLightType() const override { return LightType::SPOT; }


	void setDirection(const glm::vec3 &dir);

	
	glm::vec3 getDirection() const;

	
	glm::vec3 getDirectionInWorld() const;

	
	void setRange(float range) { m_range = range; }

	
	float getRange() const { return m_range; }
	
	void setInnerAngle(float angle);

	
	float getInnerAngle() const { return m_innerAngle; }

	
	float getCosInnerAngle() const { return m_cosInnerAngle; }

	
	void setOuterAngle(float outerAngle);

	
	float getOuterAngle() const { return m_outerAngle; }

	/** get cos outAngle */
	float getCosOuterAngle() const { return m_cosOuterAngle; }


	SpotLight();
	virtual ~SpotLight();

protected:
	float m_range;
	float m_innerAngle;
	float m_cosInnerAngle;
	float m_outerAngle;
	float m_cosOuterAngle;
};
class  AmbientLight : public BaseLight
{
public:
	
	static AmbientLight* create(const YColor &color);

	//get light type
	virtual LightType getLightType() const override { return LightType::AMBIENT; }


	AmbientLight();
	virtual ~AmbientLight();
};


#endif // YLIGHT_H_
