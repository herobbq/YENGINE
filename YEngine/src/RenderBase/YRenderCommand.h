#ifndef YRENDERCOMMAND_H_
#define YRENDERCOMMAND_H_
#include "YType.h"

class YRenderCommand
{
public:
	void init(float globalZOrder, const glm::mat4& modelViewTransform, uint32_t flags);
	/** Get global Z order. */
	float getGlobalOrder() const { return m_globalOrder; }

	/** Returns whether is transparent. */
	bool isTransparent() const { return m_isTransparent; }

	/** Set transparent flag. */
	void setTransparent(bool isTransparent) { m_isTransparent = isTransparent; }
	/**Whether the command should be rendered at 3D mode.*/
	bool is3D() const { return m_is3D; }
	/**Set the command rendered in 3D mode or not.*/
	void set3D(bool value) { m_is3D = value; }
	/**Get the depth by current model view matrix.*/
	float getDepth() const { return m_depth; }

protected:
	/**Constructor.*/
	YRenderCommand();
	/**Destructor.*/
	virtual ~YRenderCommand();

	/** Commands are sort by global Z order. */
	float m_globalOrder;

	/** Transparent flag. */
	bool  m_isTransparent;

	/** Is the command been rendered on 3D pass. */
	bool m_is3D;

	/** Depth from the model view matrix.*/
	float m_depth;
};


#endif
