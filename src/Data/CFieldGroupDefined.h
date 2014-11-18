#ifndef CFIELD_GROUP_DEFINED_H
#define CFIELD_GROUP_DEFINED_H

#include "CField.h"

// For style of defined group
class CFieldGroupDefined: public CField
{
public:
	CFieldGroupDefined(const ch_1 *pszName, const ch_1 *pszSizeName)
		: CField(pszName, FIELD_GROUP_TYPE)
	{
		memset(m_szSizeName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szSizeName, pszSizeName, VARIABLE_NAME_LENGTH);
	}

	virtual CField *Clone(const CField *pGroupField, 
						  const CField *pFirstField) const
	{
		CFieldGroupDefined *pField = new CFieldGroupDefined(m_szName, 
															m_szSizeName);

		if (m_pSubField)
			pField->SetSubField(m_pSubField->Clone(this, null_v));

		return pField;
	}

	virtual const ch_1 *GetSizeName() const
	{
		return m_szSizeName;
	}

	virtual size_ Offset(size_ nSize,
						 size_ nBlockSize, 
						 size_ nIndex = 0) const;
protected:
	ch_1 m_szSizeName[VARIABLE_NAME_LENGTH];

private:
	CFieldGroupDefined();
	CFieldGroupDefined(const CFieldGroupDefined &);
	const CFieldGroupDefined &operator =(const CFieldGroupDefined &);
};

#endif // CFIELD_GROUP_DEFINED_H
