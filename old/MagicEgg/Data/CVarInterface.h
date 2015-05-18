#ifndef CVAR_INTERFACE_H
#define CVAR_INTERFACE_H

#include "CVariable.h"

#include "../Protocols/ProtocolCommon.h"

class CVarInterface: public CVariable
{
public:
	CVarInterface(const ch_1 *pszName)
	{
		memset(m_szName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szName, pszName, VARIABLE_NAME_LENGTH);
	}

	virtual CVariable *Clone() const;
	virtual void Initialize(const CData *pData) {}
	virtual v_ *Value(const TMU *pTMU);

private:
	CVarInterface();
	CVarInterface(const CVarInterface &);
	const CVarInterface &operator =(const CVarInterface &);

	ch_1 m_szName[VARIABLE_NAME_LENGTH];
};

#endif // CVAR_INTERFACE_H
