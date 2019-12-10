#ifndef YCUSTOMCOMMAND_H_
#define YCUSTOMCOMMAND_H_
#include "YRenderCommand.h"
#include <functional>
class YCustomCommand : public YRenderCommand
{
public:
	YCustomCommand();
	virtual ~YCustomCommand();
public:
	/**
	Init function.
	@param globalZOrder GlobalZOrder of the render command.
	@param modelViewTransform When in 3D mode, depth sorting needs modelViewTransform.
	@param flags Use to identify that the render command is 3D mode or not.
	*/
	void init(float globalZOrder, const glm::mat4& modelViewTransform, uint32_t flags);
	/**
	Init function. The render command will be in 2D mode.
	@param globalZOrder GlobalZOrder of the render command.
	*/
	void init(float globalZOrder);

	/**
	Execute the render command and call callback functions.
	*/
	void execute();
	//TODO: This function is not used, it should be removed.
	bool isTranslucent() { return true; }
	/**Callback function.*/
	std::function<void()> func;
};



#endif // YCUSTOMCOMMAND_H_
