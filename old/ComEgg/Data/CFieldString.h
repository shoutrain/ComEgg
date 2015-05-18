#ifndef CFIELD_STRING_H
#define CFIELD_STRING_H

#include "CField.h"

// For style of string
class CFieldString: public CField
{
public:
	CFieldString(const ch_1 *pszName,
				 size_ nSize,
				 const CField *pGroupField = null_v)
		: CField(pszName, FIELD_STR_TYPE)
	{
		m_nUnitSize = nSize;
		m_pGroupField = (CField *)pGroupField;
	}

	virtual CField *Clone(const CField *pGroupField, 
						  const CField *pFirstField) const
	{
		CFieldString *pField = new CFieldString(m_szName, 
												m_nUnitSize, 
												pGroupField);

		if (!pFirstField)
			pFirstField = pField;

		if (m_pNextField)
			pField->Attach(m_pNextField->Clone(pGroupField, pField));

		return pField;
	}

	virtual size_ Size(const ub_1 *pBlock = null_v, 
					   size_ nBlockSize = 0) const
	{
		return m_nUnitSize;
	}

	virtual size_ Offset(const ub_1 *pBlock, 
						 size_ nBlockSize, 
						 size_ nIndex = 0) const;

private:
	CFieldString();
	CFieldString(const CFieldString &);
	const CFieldString &operator =(const CFieldString &);
};

#endif // CFIELD_STRING_H
