#ifndef CPROTOCOL_MANAGER_H
#define CPROTOCOL_MANAGER_H

#include "ProtocolCommon.h"

#include <string>
#include <map>

using namespace std;

class CProtocolInfo;

typedef map<string, const CProtocolInfo *> map_protocol;

class CProtocolManager: public CBaseClass
{
public:
	static CProtocolManager *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CProtocolManager;

		return m_pInstance;
	}

    static none_ Destory()
	{
		_DEL(m_pInstance);
	}

	//ret_ InitProtocol(CProtocolInfo *&pProtocol);
	ret_ AddProtocol(const ch_1 *pszName, CProtocolInfo *&pProtocol);
	ret_ GetProtocol(const ch_1 *pszName, CProtocolInfo *&pProtocol);

	bool_ IsProtocolReady(const ch_1 *pszName)
	{
		if (!pszName)
			return false_v;

		if (m_ProtocolMap.end() != m_ProtocolMap.find(pszName))
			return true_v;

		return false_v;
	}

protected:
	ret_ Stop();

private:
	CProtocolManager(): CBaseClass(CPROTOCOLMANAGER) {}

	CProtocolManager(const CProtocolManager &);
	const CProtocolManager &operator =(const CProtocolManager &);

	virtual ~CProtocolManager()
	{
		Stop();
	}

	map_protocol m_ProtocolMap;

	static CProtocolManager *m_pInstance;
};

#endif // CPROTOCOL_MANAGER_H
