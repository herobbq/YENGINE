#ifndef YCAMERA_H_
#define YCAMERA_H_
#include "YNode.h"
#include "YType.h"
class GLFWwindow;
class YCamera : public YNode
{
public:
enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	friend class YScene;
	friend class YDirector;
protected:
	YCamera();
	virtual ~YCamera();
	bool initDefault();
	void updateCameraParam();
public:
	static YCamera* Create();
	static YCamera* GetVisitingCamera();
	float getDepthInView(const glm::mat4& transform) const;
	void initPerspective(float fov,float aspectRatio,float nearPlane,float farPlane);
	void lookAt(glm::vec3 pos,glm::vec3 up);
	glm::mat4& getProjectionMatrix() { return m_ProjectionMatrix; }
	glm::mat4& getViewMatrix() { return m_ViewMatrix; }
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
public:
	static YCamera* m_visitingCamera;
protected:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::vec3 m_vPostion;
	glm::vec3 m_vFront;
	glm::vec3 m_vUp;
	glm::vec3 m_vRight;
	float m_fMovementSpeed;
	float m_fYaw;
	float m_fPitch;
	static float m_flastX;
	static float m_flastY;
	static bool m_bfirstMouse;
	// Camera options
	float m_fMouseSensitivity;
	float m_fZoom;
		
};






#endif
