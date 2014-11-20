#ifndef CVAR_NETWORK_H
#define CVAR_NETWORK_H

#include "CVariable.h"

#include "CField.h"
#include "../Protocols/CPDUInfo.h"

class CVarNetwork: public CAutoVar
{
public:
	CVarNetwork(const CField *pField, const ch_1 *pszIndexName = null_v)
	{
		m_pField = (CField *)pField;
		memset(m_szIndexName, 0, VARIABLE_NAME_LENGTH);

		if (pszIndexName)
			strncpy(m_szIndexName, pszIndexName, VARIABLE_NAME_LENGTH);

		m_pIndex = null_v;
	}

	virtual CAutoVar *Clone() const;
	virtual void Initialize(const CData *pData);
	virtual v_ *Value(const TMessageUnit *pTMU);

private:
	CVarNetwork();
	CVarNetwork(const CVarNetwork &);
	const CVarNetwork &operator =(const CVarNetwork &);

	CField *m_pField;
	ch_1 m_szIndexName[VARIABLE_NAME_LENGTH];
	v_ *m_pIndex;

	v_ m_Value;
};

#endif // CVAR_NETWORK_H
