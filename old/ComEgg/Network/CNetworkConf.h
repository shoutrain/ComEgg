#ifndef CNETWORK_CONF_H
#define CNETWORK_CONF_H

#include "NetworkCommon.h"
#include "../Protocols/ProtocolCommon.h"
#include "../Protocols/CProtocolInfo.h"
#include "../Protocols/CPDUInfo.h"
#include "../Transactions/CTransaction.h"

#include <map>

using namespace std;

typedef map<size_, const CPDUInfo *> map_pdu_table;
typedef map<const CPDUInfo *, size_> map_id_table;

class CNetworkConf: public CBaseClass
{
public:
	ret_ ConfigPDU(const v_ &ID,
				   const CPDUInfo *pPDUInfo,
				   EDirection Direction);
	ret_ IdentifyID(const v_ &ID,
					CPDUInfo *&pPDUInfo,
					EDirection Direction);
	ret_ IdentifyPDU(const CPDUInfo *pPDUInfo,
					 v_ &ID,
					 EDirection Direction);

	const CProtocolInfo *GetProtocol() const
	{
		return m_pProtocol;
	}

	const CField *GetCommandID() const
	{
		return m_pCommandID;
	}

	const CField *GetSizeID() const
	{
		return m_pSizeID;
	}

	ub_2 GetLocalPort() const
	{
		return m_nLocalPort;
	}

	void SetTransaction(const CTransaction *pTransaction)
	{
		m_pTransaction	= (CTransaction *)pTransaction;
	}

	const CTransaction *GetTransaction() const
	{
		return m_pTransaction;
	}

protected:
	CNetworkConf(const CProtocolInfo *pProtocol,
				 const CField *pCommandID,
				 const CField *pSizeID,
				 ub_2 nLocalPort,
				 class_sign ClassID)
		: CBaseClass(ClassID)
	{
		m_pProtocol		= (CProtocolInfo *)pProtocol;
		m_pCommandID	= (CField *)pCommandID;
		m_pSizeID		= (CField *)pSizeID;
		m_nLocalPort	= nLocalPort;
	}

	virtual ~CNetworkConf()
	{
		m_PDUInTableMap.clear();
		m_PDUOutTableMap.clear();
	}

private:
	bool_ FindPDU(const v_ &ID, EDirection Direction, CPDUInfo *&pPDUInfo);
	bool_ FindID(const CPDUInfo *pPDUInfo, EDirection Direction, v_ &ID);

	map_pdu_table	m_PDUInTableMap;
	map_pdu_table	m_PDUOutTableMap;

	map_id_table	m_IDInTableMap;
	map_id_table	m_IDOutTablemap;

	CProtocolInfo *m_pProtocol;
	CField *m_pCommandID;
	CField *m_pSizeID;
	ub_2 m_nLocalPort;

	CTransaction	*m_pTransaction;
};

#endif // CNETWORK_CONF_H
