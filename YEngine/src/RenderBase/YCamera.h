#ifndef YCAMERA_H_
#define YCAMERA_H_
#include "YNode.h"
#include "glm/glm.hpp"
class YCamera : public YNode
{

	friend class YScene;
	friend class YDirector;
public:
	YCamera();
	virtual ~YCamera();
public:
	static YCamera* GetVisitingCamera();
	float getDepthInView(const glm::mat4& transform) const;
public:
	static YCamera* m_visitingCamera;
};






#endif
