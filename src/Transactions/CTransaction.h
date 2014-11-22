#ifndef CTRANSACTION_H
#define CTRANSACTION_H

#include "CProcessor.h"

#include "../Tools/CResource.h"

class CTransaction: public CBaseClass
{
public:
	CTransaction(const CProcessor &Processor, const size_ &nSize)
		: CBaseClass(CTRANSACTION) 
	{
		m_Resource.Initialize(Processor, nSize);
	}

	virtual ~CTransaction() {}

    ret_ Allocate(CProcessor *&unit);

    ret_ Release(CProcessor *&unit);

	size_ GetFreeSize()
	{	
		return m_Resource.GetFreeSize();
	}

private:
	CTransaction();
	CTransaction(const CTransaction &);
	const CTransaction &operator =(const CTransaction &);

	CResource<CProcessor> m_Resource;
};

#endif // CTRANSACTION_H
