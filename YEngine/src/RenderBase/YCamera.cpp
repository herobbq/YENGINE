#include"YCamera.h"
YCamera* YCamera::m_visitingCamera = nullptr;
YCamera::YCamera()
{

}

YCamera::~YCamera()
{

}

YCamera* YCamera::GetVisitingCamera()
{
	return m_visitingCamera;
}

float YCamera::getDepthInView(const glm::mat4& transform) const
{
	//glm::mat4 camWorldMat = getNodeToWorldTransform();
	//const glm::mat4 &viewMat = camWorldMat.getInversed();
	//float depth = -(viewMat.m[2] * transform.m[12] + viewMat.m[6] * transform.m[13] + viewMat.m[10] * transform.m[14] + viewMat.m[14]);
	//return depth;
	return 1;
}

