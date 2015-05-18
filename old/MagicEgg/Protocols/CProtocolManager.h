#ifndef CPROTOCOL_MANAGER_H
#define CPROTOCOL_MANAGER_H

#include "ProtocolCommon.h"

#include "CProtocolInfo.h"

class CProtocolManager
{
public:
	static CProtocolManager *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CProtocolManager;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	CProtocolInfo *GetProtocol()
	{
		if (!m_pProtocol)
			m_pProtocol = new CProtocolInfo();

		return m_pProtocol;
	}

private:
	CProtocolManager() {}
	CProtocolManager(const CProtocolManager &);
	const CProtocolManager &operator =(const CProtocolManager &);

	virtual ~CProtocolManager()
	{
		_DEL(m_pProtocol);
	}

	static CProtocolManager *m_pInstance;

	CProtocolInfo *m_pProtocol;
};

#endif // CPROTOCOL_MANAGER_H
