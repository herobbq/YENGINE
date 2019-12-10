#ifndef YRENDERER_H_
#define YRENDERER_H_
#include <vector>
#include <glfw3.h>
class YRenderCommand;
class RenderQueue
{
	public:
	enum  QUEUE_GROUP
	{
		/**Objects with globalZ smaller than 0.*/
		//GLOBALZ_NEG = 0,
		/**Opaque 3D objects with 0 globalZ.*/
		OPAQUE_3D = 0,
		/**Transparent 3D objects with 0 globalZ.*/
	//	TRANSPARENT_3D = 2,
		/**2D objects with 0 globalZ.*/
	//	GLOBALZ_ZERO = 3,
		/**Objects with globalZ bigger than 0.*/
	//	GLOBALZ_POS = 4,
		QUEUE_COUNT = 1,
	};
public:
	/**Constructor.*/
	RenderQueue();
	/**Push a renderCommand into current renderqueue.*/
	void push_back(YRenderCommand* command);
	/**Return the number of render commands.*/
	size_t size() const;
	/**Treat sorted commands as an array, access them one by one.*/
	YRenderCommand* operator[](size_t index) const;
	/**Clear all rendered commands.*/
	void clear();
	/**Realloc command queues and reserve with given size. Note: this clears any existing commands.*/
	void realloc(size_t reserveSize);

	/**Save the current DepthState, CullState, DepthWriteState render state.*/
	void saveRenderState();
	/**Restore the saved DepthState, CullState, DepthWriteState render state.*/
	void restoreRenderState();
	std::vector<YRenderCommand*>& getSubQueue(QUEUE_GROUP group) { return m_commands[group]; }
protected:
	/**The commands in the render queue.*/
	std::vector<YRenderCommand*> m_commands[QUEUE_COUNT];

	/**Cull state.*/
	bool m_isCullEnabled;
	/**Depth test enable state.*/
	bool m_isDepthEnabled;
	GLboolean m_isDepthWrite;
};
class YRenderer
{
public:
	YRenderer();
	virtual ~YRenderer();
public:
	void addCommand(YRenderCommand* command);
	void clean();
protected:
	void processRenderCommand(YRenderCommand* command);
	void visitRenderQueue(RenderQueue& queue);
public:
	void render();
	std::vector<RenderQueue> m_renderGroups;
};




#endif
