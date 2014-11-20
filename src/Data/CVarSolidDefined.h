#ifndef CVAR_SOLID_DEFINED_H
#define CVAR_SOLID_DEFINED_H

#include "CVariable.h"

#include "../Protocols/ProtocolCommon.h"

class CVarSolidDefined: public CAutoVar
{
public:
	CVarSolidDefined(const ch_1 *pszName)
	{
		memset(m_szName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szName, pszName, VARIABLE_NAME_LENGTH);
		m_pValue = null_v;
	}

	virtual CAutoVar *Clone() const;
	virtual void Initialize(const CData *pData);
	virtual v_ *Value(const TMessageUnit *pTMU);

private:
	CVarSolidDefined();
	CVarSolidDefined(const CVarSolidDefined &);
	const CVarSolidDefined &operator =(const CVarSolidDefined &);

	ch_1 m_szName[VARIABLE_NAME_LENGTH];
	v_ *m_pValue;
};

#endif // CVAR_SOLID_DEFINED_H
