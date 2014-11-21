#ifndef CAUTO_PTR_H
#define CAUTO_PTR_H

#include "../Common/Common.h"

template <class PtrClass>
class CAutoPtr
{
public:
    CAutoPtr() // init the object by null, and be initialized later
	{
		m_Ptr = null_v;
	}

    CAutoPtr(const PtrClass *&Ptr) // init the object by real object
	{
		m_Ptr = Ptr;
	}

	~CAutoPtr()
	{
		_DEL(m_Ptr);
	}

	PtrClass *&Ptr()
	{
		return m_Ptr;
	}

private:
	PtrClass *m_Ptr;
};

#endif // CAUTO_PTR_H
