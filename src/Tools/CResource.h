#ifndef CRESOURCE_H
#define CRESOURCE_H

#include "../Common/CBaseClass.h"

#include <deque>

using namespace std;

template <class UnitType>
class CResource: public CBaseClass
{
public:
	CResource(): CBaseClass(CRESOURCE) {}

	virtual ~CResource()
	{
		Stop();
	}

	ret_ Initialize(const UnitType &Unit, const size_ &nMaxNum)
	{
		_START(INITIALIZE);

#ifdef _DEBUG_
		if (0 >= nMaxNum)
			_RET(PARAMETER_SIZE_OVERFLOW | PARAMETER_1);
#endif

		m_nMaxNum	= nMaxNum;
		m_UnitGroup = new UnitType[m_nMaxNum];

		for (size_ n = 0; n < m_nMaxNum; n++)
		{
			m_UnitGroup[n] = Unit;
			m_FreeDeque.push_back((UnitType *)&m_UnitGroup[n]);
		}

		_RET(SUCCESS);
	}

	ret_ Allocate(UnitType *&pUnit)
	{
		_START(ALLOCATE);

#ifdef _DEBUG_
		if (pUnit)
			_RET(PARAMETER_NOT_NULL | PARAMETER_1);
#endif

		if (0 < m_FreeDeque.size())
		{
			pUnit = m_FreeDeque.front();
			m_FreeDeque.pop_front();
		}
		else
		{
			_RET(NO_ELEMENT_IN_CONTAINER);
		}

		_RET(SUCCESS);
	}

	ret_ Release(UnitType *&pUnit)
	{
		_START(RELEASE);

#ifdef _DEBUG_
		if (!pUnit)
			_RET(PARAMETER_NULL | PARAMETER_1);

        size_ n = 0;

		for (; n < m_nMaxNum; n++)
			if (pUnit == &m_UnitGroup[n])
				break;

		if (m_nMaxNum == n)
			return (PARAMETER_ERROR | PARAMETER_1);
#endif

		m_FreeDeque.push_back(pUnit);
		pUnit = null_v;

		_RET(SUCCESS);
	}

	size_ GetFreeSize()
	{
		return (size_)m_FreeDeque.size();
	}

public:
	ret_ Stop()
	{
		_START(STOP);

		m_FreeDeque.clear();
		_DEL_ARR(m_UnitGroup)

		_RET(SUCCESS);
	}

private:
	size_		m_nMaxNum;
	UnitType	*m_UnitGroup;

	deque<UnitType *> m_FreeDeque;
};

#endif // CRESOURCE_H
