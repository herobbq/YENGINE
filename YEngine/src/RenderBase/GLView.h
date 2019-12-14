#ifndef YGLVIWE_H_
#define YGLVIWE_H_
#include "Ref.h"
#include "YType.h"
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
	virtual float  width() { return m_size.width; }
	virtual float  height() { return m_size.height; }
	virtual YSize& getViewSize() { return m_size; }
protected:
	GLFWwindow* m_window;
	YSize       m_size;

};
#endif // YGLVIWE_H_
