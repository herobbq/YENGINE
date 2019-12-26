#include "GLViewImpl.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define GLEW_STATIC
#include "glew.h"
#include <glfw3.h>
#include <iostream>
#include "YCamera.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
GLViewImpl* GLFWEventHandler::_view = nullptr;
GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
	return GLViewImpl::create(viewName, false);
}

GLViewImpl* GLViewImpl::create(const std::string& viewName, bool resizable)
{
	auto ret = new (std::nothrow) GLViewImpl;
	if (ret && ret->initWithRect(viewName,  960, 640, 1.0f, resizable)) {
		//ret->release();
		return ret;
	}
	delete ret ;
	ret = nullptr;
	return nullptr;
}

bool GLViewImpl::windowShouldClose()
{
	if (m_window)
		return glfwWindowShouldClose(m_window) ? true : false;
	else
		return true;
}

void GLViewImpl::pollEvents()
{
	
	glfwPollEvents();
}

GLViewImpl::GLViewImpl(bool initglfw /*= true*/)
{
	GLFWEventHandler::setGLViewImpl(this);
	if (initglfw)
	{
		//glfwSetErrorCallback(GLFWEventHandler::onGLFWError);
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
}

GLViewImpl::~GLViewImpl()
{
	GLFWEventHandler::setGLViewImpl(nullptr);
	glfwTerminate();
}

bool GLViewImpl::initWithRect(const std::string& viewName, int width , int height , float frameZoomFactor, bool resizable)
{
	//auto s = glfwInit();
	
	 m_window = glfwCreateWindow(width, height, viewName.c_str(), NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	m_size.width = width;
	m_size.height = height;
	glfwMakeContextCurrent(m_window);
	glfwSetMouseButtonCallback(m_window, GLFWEventHandler::onGLFWMouseCallBack);
	glfwSetCursorPosCallback(m_window, GLFWEventHandler::onGLFWMouseMoveCallBack);
	glfwSetScrollCallback(m_window, GLFWEventHandler::onGLFWMouseScrollCallback);
	glfwSetCharCallback(m_window, GLFWEventHandler::onGLFWCharCallback);
	glfwSetKeyCallback(m_window, GLFWEventHandler::onGLFWKeyCallback);
	glfwSetWindowPosCallback(m_window, GLFWEventHandler::onGLFWWindowPosCallback);
	glfwSetFramebufferSizeCallback(m_window, GLFWEventHandler::onGLFWframebuffersize);
	glfwSetWindowSizeCallback(m_window, GLFWEventHandler::onGLFWWindowSizeFunCallback);
	glfwSetWindowIconifyCallback(m_window, GLFWEventHandler::onGLFWWindowIconifyCallback);
	glfwSetWindowFocusCallback(m_window, GLFWEventHandler::onGLFWWindowFocusCallback);

	//imgui
	const char* glsl_version = "#version 330 core";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	if (glewInit()!=GLEW_OK)
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glViewport(0, 0, width, height);
	return true;
}

GLFWwindow* GLViewImpl::getCurWindow()
{
	return m_window;
}

void GLViewImpl::swapBuffers()
{
	if (m_window)
	{
		
		glfwSwapBuffers(m_window);
		
	}
}

void GLViewImpl::onGLFWError(int errorID, const char* errorDesc)
{
	
}

void GLViewImpl::onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{

}

void GLViewImpl::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{

}

void GLViewImpl::onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
{

}

void GLViewImpl::onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*if (YCamera* _camera = YCamera::m_visitingCamera)
	{
		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::FORWARD, m_deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::BACKWARD, m_deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::LEFT, m_deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			_camera->ProcessKeyboard(YCamera::RIGHT, m_deltaTime);
	}*/
	
}

void GLViewImpl::onGLFWCharCallback(GLFWwindow* window, unsigned int character)
{

}

void GLViewImpl::onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
{

}

void GLViewImpl::onGLFWframebuffersize(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
	m_size.width= w;
	m_size.height = h;
}

void GLViewImpl::onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
{

}

void GLViewImpl::onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
{

}

void GLViewImpl::onGLFWWindowFocusCallback(GLFWwindow* window, int focused)
{

}


