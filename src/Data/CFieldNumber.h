#ifndef CFIELD_NUMBER_H
#define CFIELD_NUMBER_H

#include "CField.h"

// For style of normal and float
class CFieldNumber: public CField
{
public:
	CFieldNumber(const ch_1 *pszName,
				 EFieldType Type,
				 const CField *pGroupField = null_v)
		: CField(pszName, Type)
	{
		m_pGroupField = (CField *)pGroupField;
		m_nUnitSize = _LEN(m_Type);
	}

	virtual CField *Clone(const CField *pGroupField,
						  const CField *pFirstField) const
	{
		CFieldNumber *pField = new CFieldNumber(m_szName, 
												m_Type, 
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
	CFieldNumber();
	CFieldNumber(const CFieldNumber &);
	const CFieldNumber &operator =(const CFieldNumber &);
};

#endif // CFIELD_NUMBER_H
