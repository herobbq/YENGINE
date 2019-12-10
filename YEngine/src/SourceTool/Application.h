#ifndef APPLICATION_H_
#define APPLICATION_H_
class  Application
{
public:
	/**
	* @js ctor
	*/
	Application();
	/**
	* @js NA
	* @lua NA
	*/
	virtual ~Application();

	/**
	@brief    Run the message loop.
	*/
	int run();

	/**
	@brief    Get current application instance.
	@return Current application instance pointer.
	*/
	static Application* getInstance();
};

#endif // APPLICATION_H_
