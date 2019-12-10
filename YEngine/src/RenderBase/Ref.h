#ifndef YENGINE_REF_H_
#define YENGINE_REF_H_

class Ref
{
public:
	Ref();
	virtual ~Ref();
public:
	void AddRef();
	void SubRef();
	void release();
private:
	int m_iRefCount;


};










#endif
