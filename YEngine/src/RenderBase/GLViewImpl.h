#ifndef GLVIEWIMPL_H_
#define GLVIEWIMPL_H_
#include "GLView.h"
#include <string>
class GLViewImpl :public GLView
{
public:
	static GLViewImpl* create(const std::string& viewName);
	static GLViewImpl* create(const std::string& viewName, bool resizable);
public:
	virtual void pollEvents()override;
protected:
	GLViewImpl(bool initglfw = true);
	virtual ~GLViewImpl();
	bool initWithRect(const std::string& viewName, int width, int height, float frameZoomFactor, bool resizable);
	virtual GLFWwindow* getCurWindow();
	virtual void swapBuffers();
};

#endif
