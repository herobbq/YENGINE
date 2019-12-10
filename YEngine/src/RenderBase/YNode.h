#ifndef YENGINE_YNODE_H_
#define YENGINE_YNODE_H_
#include "Ref.h"
#include <string>
#include "glm/glm.hpp"
#include <vector>
class YRenderer;
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
};















#endif
