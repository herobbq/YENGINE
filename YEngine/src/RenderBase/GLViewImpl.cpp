#include "GLViewImpl.h"
#include <glad/glad.h> 
#include <glfw3.h>
#include <iostream>
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

void GLViewImpl::pollEvents()
{
	glfwPollEvents();
}

GLViewImpl::GLViewImpl(bool initglfw /*= true*/)
{
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
	glfwMakeContextCurrent(m_window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
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

