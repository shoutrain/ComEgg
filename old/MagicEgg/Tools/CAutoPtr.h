#ifndef CAUTO_PTR_H
#define CAUTO_PTR_H

#include "../Common/Common.h"

template <class PtrClass>
class CAutoPtr
{
public:
	CAutoPtr()
	{
		m_Ptr = null_v;
	}

	CAutoPtr(const PtrClass *&Ptr)
	{
		m_Ptr = null_v;
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
