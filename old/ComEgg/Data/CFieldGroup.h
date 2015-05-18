#ifndef CFIELD_GROUP_H
#define CFIELD_GROUP_H

#include "CField.h"

// For style of group on network
class CFieldGroup: public CField
{
public:
	CFieldGroup(const ch_1 *pszName, const CField *pSizeField)
		: CField(pszName, FIELD_GROUP_TYPE)
	{
		m_pSizeField = (CField *)pSizeField;
	}

	virtual CField *Clone(const CField *pGroupField, 
						  const CField *pFirstField) const
	{
		if (!pFirstField || !m_pSizeField)
			return null_v;

		CField *pSizeField = (CField *)pFirstField;

		while (pSizeField)
		{
			if (strncmp(pSizeField->Name(), 
						m_pSizeField->Name(), 
						VARIABLE_NAME_LENGTH))
			{
				break;
			}

			pSizeField = (CField *)pSizeField->GetNextField();
		}

		CFieldGroup *pField = new CFieldGroup(m_szName, pSizeField);

		if (m_pNextField)
			pField->Attach(m_pNextField->Clone(null_v, pFirstField));

		if (m_pSubField)
			pField->SetSubField(m_pSubField->Clone(pField, null_v));

		return pField;
	}

	virtual size_ Size(const ub_1 *pBlock = null_v, 
					   size_ nBlockSize = 0) const;
	virtual size_ Offset(const ub_1 *pBlock, 
						 size_ nBlockSize, 
						 size_ nIndex = 0) const;

protected:
	CField *m_pSizeField;

private:
	CFieldGroup();
	CFieldGroup(const CFieldGroup &);
	const CFieldGroup &operator =(const CFieldGroup &);
};

#endif // CFIELD_GROUP_H
