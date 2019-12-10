#ifndef YGLVIWE_H_
#define YGLVIWE_H_
#include "Ref.h"
#include "glm/glm.hpp"
class GLFWwindow;
class YScene;
class YRenderer;
class GLView :public Ref
{
public:
	GLView();
	
	virtual ~GLView();
public:
	virtual void pollEvents();
	void renderScene(YScene* scene, YRenderer* renderer);
	virtual bool windowShouldClose() { return false; };
	virtual GLFWwindow* getCurWindow() = 0;
	virtual void swapBuffers() = 0;
protected:
	GLFWwindow* m_window;
};
#endif // YGLVIWE_H_
