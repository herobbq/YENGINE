#ifndef GLVIEWIMPL_H_
#define GLVIEWIMPL_H_
#include "GLView.h"
#include <string>
class GLViewImpl :public GLView
{
	friend class GLFWEventHandler;
public:
	static GLViewImpl* create(const std::string& viewName);
	static GLViewImpl* create(const std::string& viewName, bool resizable);
public:
	bool windowShouldClose() override;
	virtual void pollEvents()override;
protected:
	GLViewImpl(bool initglfw = true);
	virtual ~GLViewImpl();
	bool initWithRect(const std::string& viewName, int width, int height, float frameZoomFactor, bool resizable);
	virtual GLFWwindow* getCurWindow();
	virtual void swapBuffers();
	void onGLFWError(int errorID, const char* errorDesc);
	void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
	void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
	void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
	void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
	void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
	void onGLFWframebuffersize(GLFWwindow* window, int w, int h);
	void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);
	void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified);
	void onGLFWWindowFocusCallback(GLFWwindow* window, int focused);
protected:
	std::string _glfwError;
};
class  GLFWEventHandler
{
public:
	static void onGLFWError(int errorID, const char* errorDesc)
	{
		if (_view)
			_view->onGLFWError(errorID, errorDesc);
	}

	static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
	{
		if (_view)
			_view->onGLFWMouseCallBack(window, button, action, modify);
	}

	static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
	{
		if (_view)
			_view->onGLFWMouseMoveCallBack(window, x, y);
	}

	static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
	{
		if (_view)
			_view->onGLFWMouseScrollCallback(window, x, y);
	}

	static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (_view)
			_view->onGLFWKeyCallback(window, key, scancode, action, mods);
	}

	static void onGLFWCharCallback(GLFWwindow* window, unsigned int character)
	{
		if (_view)
			_view->onGLFWCharCallback(window, character);
	}

	static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
	{
		if (_view)
			_view->onGLFWWindowPosCallback(windows, x, y);
	}

	static void onGLFWframebuffersize(GLFWwindow* window, int w, int h)
	{
		if (_view)
			_view->onGLFWframebuffersize(window, w, h);
	}

	static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
	{
		if (_view)
			_view->onGLFWWindowSizeFunCallback(window, width, height);
	}

	static void setGLViewImpl(GLViewImpl* view)
	{
		_view = view;
	}

	static void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
	{
		if (_view)
		{
			_view->onGLFWWindowIconifyCallback(window, iconified);
		}
	}

	static void onGLFWWindowFocusCallback(GLFWwindow* window, int focused)
	{
		if (_view)
		{
			_view->onGLFWWindowFocusCallback(window, focused);
		}
	}

private:
	static GLViewImpl* _view;
};
#endif
