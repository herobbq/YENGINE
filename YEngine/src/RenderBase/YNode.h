#ifndef YENGINE_YNODE_H_
#define YENGINE_YNODE_H_
#include "Ref.h"
#include <string>
#include "YType.h"
#include <vector>
#include "PlatformMacros.h"
class YRenderer;
class YScene;
class YNode :public Ref
{
public:
	YNode();
	virtual ~YNode();
public:
	static YNode * create();
	virtual void addChild(YNode * child, int localZOrder);
	virtual void addChild(YNode* child, int localZOrder, int tag);
	
	virtual void addChild(YNode* child, int localZOrder, const std::string &name);
	virtual void removeChild(YNode* child);
	virtual void draw(YRenderer *renderer, const glm::mat4& transform, uint32_t flags);
	virtual void visit(YRenderer *renderer, const glm::mat4& parentTransform, uint32_t parentFlags);
	virtual YNode* getParent() { return m_pParent; }
	virtual const YNode* getParent() const { return m_pParent; }
	virtual int getTag() const;
	virtual void setTag(int tag);
	virtual const std::string& getName() const;
	virtual void setNodeToParentTransform(const glm::mat4& transform);
	virtual void setName(const std::string& name);
	virtual void setParent(YNode* parent);
	virtual YScene* getScene() const;
	virtual void setPosition(const glm::vec3 &position);
	virtual glm::vec3& getPosition() ;
	virtual void setRotation(float rotation);
	virtual float getRotation() const;
	virtual void setRotation(const glm::vec3& rotation);
	virtual glm::vec3& getRotation3D() ;
	virtual void setRotationQuat(const glm::fquat& quat);
	virtual glm::fquat getRotationQuat() const;
	virtual void setScaleX(float scaleX);
	virtual float getScaleX() const;
	virtual void setScaleY(float scaleY);
	virtual float getScaleY() const;
	virtual void setScaleZ(float scaleZ);
	virtual float getScaleZ() const;
	virtual void setScale(float scale);
	virtual float getScale() const;
	virtual void setScale(float scaleX, float scaleY, float scaleZ);
	void updateRotationQuat();
	void updateRotation3D();
	virtual void setColor(const YColor& color);
	virtual YColor& getColor() { return m_displayedColor; }
protected:
	virtual bool init();
	void insertChild(YNode* child, int z);
	virtual void setLocalZOrder(std::int32_t z);
private:
	void addChildHelper(YNode* child, int localZOrder, int tag, const std::string &name, bool setTag);
protected:
	std::string  m_strName;
	YNode*       m_pParent;
	std::vector<YNode*> m_vChildrens;
	std::int32_t m_ilocalZOrder;
	int          m_iTag;
	glm::mat4    m_modelViewTransform;       ///< ModelView transform of the Node.
	mutable glm::mat4 m_transform;
	glm::vec3    m_position;
	float         m_rotationX;               ///< rotation on the X-axis
	float         m_rotationY;               ///< rotation on the Y-axis

									// rotation Z is decomposed in 2 to simulate Skew for Flash animations
	float         m_rotationZ_X;             ///< rotation angle on Z-axis, component X
	float         m_rotationZ_Y;             ///< rotation angle on Z-axis, component Y

	glm::fquat m_rotationQuat;       ///rotation using quaternion, if _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX, else _rotationQuat = RotationY * RotationX

	float         m_scaleX;                  ///< scaling factor on x-axis
	float         m_scaleY;                  ///< scaling factor on y-axis
	float         m_scaleZ;                  ///< scaling factor on z-axis

	YColor     m_displayedColor;
};















#endif
