#include"Ref.h"

Ref::Ref()
	:m_iRefCount(1)
{

}

Ref::~Ref()
{

}

void Ref::AddRef()
{
	++m_iRefCount;
}

void Ref::SubRef()
{
	--m_iRefCount;
	if (m_iRefCount==0)
	{
		delete this;
	}
}

void Ref::release()
{
	delete this;
}

