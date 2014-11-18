#ifndef CSENDER_HANDLE_H
#define CSENDER_HANDLE_H

#include "CDatagramHandle.h"
#include "CSenderConf.h"

class CSenderHandle: public CDatagramHandle
{
public:
	CSenderHandle(): CDatagramHandle(CSENDERHANDLE)
	{
		m_pConf = null_v;
	}

protected:
	virtual ret_ OnOpen(const ub_1 *pObj);

	virtual const CNetworkConf *GetConf() const
	{
		return (const CNetworkConf *)m_pConf;
	}

private:
	CSenderConf *m_pConf;
};


#endif // CSENDER_HANDLE_H
