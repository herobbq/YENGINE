#include"YCamera.h"
#include "YDirector.h"
#include"glfw3.h"


YCamera* YCamera::m_visitingCamera = nullptr;
float YCamera::m_flastX = 0.0f;
float YCamera::m_flastY = 0.0f;
bool YCamera::m_bfirstMouse = true;
YCamera::YCamera()
{

}

YCamera::~YCamera()
{

}

bool YCamera::initDefault()
{
	YSize windowSize = YDirector::GetInstance()->getWinsize();
	m_vPostion = glm::vec3(0.0f,0.0,3.0f);
	m_vUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_vFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vRight = glm::normalize(glm::cross(m_vFront, m_vUp));
	m_fMovementSpeed = 2.5f;
	m_fYaw = -90.0f;
	m_fPitch = 0.0f;
	m_fMouseSensitivity = 0.1f;
	m_fZoom = 45.0f;
	this->initPerspective(glm::radians(m_fZoom), windowSize.width / windowSize.height, 0.1f, 100.0f);
	this->lookAt(glm::vec3(0.0,0.0,10.0f), m_vUp);
	return true;
}

void YCamera::updateCameraParam()
{
	// Calculate the new Front vector
	glm::vec3 vfront;
	vfront.x = cos(glm::radians(m_fYaw)*cos(glm::radians(m_fPitch)));
	vfront.y = sin(glm::radians(m_fPitch));
	vfront.z = sin(glm::radians(m_fYaw)*cos(glm::radians(m_fPitch)));
	m_vFront = glm::normalize(vfront);
	m_vRight = glm::normalize(glm::cross(m_vFront, glm::vec3(0.0, 1.0, 0.0)));
	m_vUp = glm::normalize(glm::cross(m_vRight, m_vFront));
	m_ViewMatrix = glm::lookAt(m_vPostion, m_vPostion + m_vFront, m_vUp);
}

YCamera* YCamera::Create()
{
	YCamera* camera = new (std::nothrow) YCamera();
	
	camera->initDefault();
	

	return camera;
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

void YCamera::initPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_ProjectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

void YCamera::lookAt(glm::vec3 pos, glm::vec3 up)
{

	m_ViewMatrix = glm::lookAt(m_vPostion, m_vPostion+m_vFront, up);
}

void YCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = m_fMovementSpeed * deltaTime;
	if (direction == FORWARD)
		m_vPostion += m_vFront * velocity;
	if (direction == BACKWARD)
		m_vPostion -= m_vFront * velocity;
	if (direction == LEFT)
		m_vPostion -= m_vRight * velocity;
	if (direction == RIGHT)
		m_vPostion += m_vRight * velocity;
	if (direction == UP)
		m_vPostion += m_vUp * velocity;
	if (direction == DOWN)
		m_vPostion -= m_vUp * velocity;
	updateCameraParam();
}

void YCamera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= m_fMouseSensitivity;
	yoffset *= m_fMouseSensitivity;

	m_fYaw += xoffset;
	m_fPitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_fPitch > 89.0f)
		m_fPitch = 89.0f;
	if (m_fPitch < -89.0f)
		m_fPitch = -89.0f;

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraParam();
}



void YCamera::ProcessMouseScroll(float yoffset)
{
	m_vPostion += glm::vec3(0.0, 0.0, -yoffset);
	updateCameraParam();
}

void YCamera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (m_bfirstMouse)
	{
		m_flastX = xpos;
		m_flastY = ypos;
		m_bfirstMouse = false;
	}

	float xoffset = xpos - m_flastX;
	float yoffset = m_flastY - ypos; // reversed since y-coordinates go from bottom to top

	m_flastX = xpos;
	m_flastY = ypos;
	if (m_visitingCamera)
	{
		m_visitingCamera->ProcessMouseMovement(xoffset, yoffset);
	}

}

void YCamera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	if (m_visitingCamera)
	{
		m_visitingCamera->ProcessMouseScroll(yoffset);
	}

}



void YCamera::processInput(GLFWwindow *window, float deltaTime)
{
	if (YCamera* _camera = YCamera::m_visitingCamera)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::DOWN, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::UP, deltaTime);
	}
}
