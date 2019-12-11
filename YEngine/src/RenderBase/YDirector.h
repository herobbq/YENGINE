#ifndef YDIRECTOR_H_
#define YDIRECTOR_H_
#include <stack>
class YScene;
class GLView;
class YRenderer;
class YDirector
{
private:
	YDirector();
	virtual ~YDirector();
public:
	static YDirector* GetInstance();
	void   PushScene(YScene* scene);
	void   PopScene(YScene* scene);
	void   setOpenGLView(GLView *openGLView);
	void   setNextScene();
	void   mainLoop();
	void   replaceScene(YScene *scene);
	void   runWithScene(YScene *scene);
	GLView* getOpenGLView() { return m_openGLView; }
protected:
	void   drawScene();
	
protected:
	std::stack<YScene*> m_SceneStack;
	YScene* m_NextScene;
	YScene* m_RuingScene;
	GLView *m_openGLView;
	YRenderer *m_renderer;
};







#endif
