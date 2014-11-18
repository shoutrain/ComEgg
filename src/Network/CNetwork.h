#ifndef CNETWORK_H
#define CNETWORK_H

#include "NetworkCommon.h"

class CNetworkConf;

class CNetwork: public CBaseClass
{
public:
	CNetwork(bool_ IsAutoStart,
			 ENetworkType Type,
			 class_sign ClassID)
		: CBaseClass(ClassID)
	{
		m_IsAutoStart = IsAutoStart;
		m_Type = Type;
	}

	virtual void Work() = 0;
	virtual void Sleep() = 0;

	virtual const CNetworkConf *GetConf() const = 0;

	bool_ IsAutoStart() const
	{
		return m_IsAutoStart;
	}

	ENetworkType GetType() const
	{
		return m_Type;
	}

private:
	bool_ m_IsAutoStart;
	ENetworkType m_Type;
};

#endif // CNETWORK_H

