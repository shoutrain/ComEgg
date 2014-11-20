#ifndef CVAR_GROUP_DEFINED_H
#define CVAR_GROUP_DEFINED_H

#include "CVariable.h"

#include "../Protocols/ProtocolCommon.h"

class CVarGroupDefined: public CAutoVar
{
public:
	CVarGroupDefined(const ch_1 *pszGroupName, 
					 const ch_1 *pszSubName = null_v, 
					 const ch_1 *pszIndexName = null_v)
	{
		memset(m_szGroupName, 0, VARIABLE_NAME_LENGTH);
		memset(m_szIndexName, 0, VARIABLE_NAME_LENGTH);
		memset(m_szSubName, 0, VARIABLE_NAME_LENGTH);

		strncpy(m_szGroupName, pszGroupName, VARIABLE_NAME_LENGTH);

		if (pszSubName)
			strncpy(m_szSubName, pszSubName, VARIABLE_NAME_LENGTH);

		if (pszIndexName)
			strncpy(m_szIndexName, pszIndexName, VARIABLE_NAME_LENGTH);

		m_pField = null_v;
		m_pSize = null_v;
		m_pIndex = null_v;
		m_pGroupData = null_v;
	}

	virtual CAutoVar *Clone() const;
	virtual void Initialize(const CData *pData);
	virtual v_ *Value(const TMessageUnit *pTMU);
	virtual v_ *Value(obj_ &);

private:
	CVarGroupDefined();
	CVarGroupDefined(const CVarGroupDefined &);
	const CVarGroupDefined &operator =(const CVarGroupDefined &);

	ch_1 m_szGroupName[VARIABLE_NAME_LENGTH];
	ch_1 m_szSubName[VARIABLE_NAME_LENGTH];

	ch_1 m_szIndexName[VARIABLE_NAME_LENGTH];
	CField *m_pField;
	v_ *m_pSize;
	v_ *m_pIndex;

	v_ m_Value;

	TFieldGroup *m_pGroupData;
};

#endif // CVAR_GROUP_DEFINED_H
