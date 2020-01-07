#ifndef YTYPE_H_
#define YTYPE_H_

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct YSize
{
	float width;
	float height;
};

struct YColor 
{
	YColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) :R(r), G(g), B(b), A(a) {}
	float R;
	float G;
	float B;
	float A;
	glm::vec3 toVec3() { return glm::vec3(R, G, B); }
};



#endif
