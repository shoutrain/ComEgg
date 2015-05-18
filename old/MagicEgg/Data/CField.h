#ifndef CFIELD_H
#define CFIELD_H

#include "DataCommon.h"

#include <set>

using namespace std;

class CField;
typedef set<const CField *> set_field;

class CField
{
public:
	virtual CField *Clone(const CField *pGroupField, 
						  const CField *pFirstField) const 
	{ 
		return null_v; 
	}

	virtual ~CField() {}

	EFieldType Type() const
	{
		return m_Type;
	}
	
	const ch_1 *Name() const
	{
		return m_szName;
	}

	void Attach(const CField *pField)
	{
		((CField *)pField)->SetPrevField(this);
		SetNextField(pField);
	}

	// For field in group
	const CField *GetGroupField() const
	{
		return m_pGroupField;
	}

	// for group
	void SetSubField(const CField *pField)
	{
		CField *pRollField = (CField *)pField;
		size_ nSize = 0;

		while (pRollField)
		{
			nSize += pRollField->GetUnitSize();
			pRollField = (CField *)pRollField->GetNextField();
		}

		if (!m_pSubField)
		{
			m_pSubField = (CField *)pField;
			m_nUnitSize = nSize;
		}
		else
		{
			CField *pRollField = (CField *)m_pSubField;

			while (pRollField->GetNextField())
				pRollField = (CField *)pRollField->GetNextField();

			pRollField->Attach((CField *)pField);
			m_nUnitSize += nSize;
		}
	}

	// for group
	const CField *GetSubField() const
	{
		return m_pSubField;
	}

	void SetPrevField(const CField *pField)
	{
		m_pPrevField = (CField *)pField;
	}

	void SetNextField(const CField *pField)
	{
		m_pNextField = (CField *)pField;
	}

	const CField *GetNextField() const
	{
		return m_pNextField;
	}

	size_ GetUnitSize() const
	{
		return m_nUnitSize;
	}

	// For network
	virtual size_ Size(const ub_1 *pBlock = null_v, 
					   size_ nBlockSize = 0) const { return 0; }

	// For network
	virtual size_ Offset(const ub_1 *pBlock, 
						 size_ nBlockSize, 
						 size_ nIndex = 0) const { return 0; }

	// For defined
	virtual const ch_1 *GetSizeName() const { return null_v; }

	// For defined
	virtual size_ Offset(size_ nSize,
						 size_ nBlockSize, 
						 size_ nIndex = 0) const { return 0; }

	static void Load();

protected:
	CField(const ch_1 *pszName, EFieldType Type)
	{
		strncpy(m_szName, pszName, VARIABLE_NAME_LENGTH);
		m_Type = Type;
		m_nUnitSize = 0;
		m_pGroupField = null_v;
		m_pSubField = null_v;
		m_pPrevField = null_v;
		m_pNextField = null_v;
	}

	ch_1 m_szName[VARIABLE_NAME_LENGTH];
	EFieldType m_Type;

	size_ m_nUnitSize;

	// If it's independent field, this variable is null_v;	
	// If it's field in group, this variable indicates the parent group.
	CField *m_pGroupField;

	// If it's independent field, this variable is null_v;	
	// If it's group field, this variable is the first children field;
	CField *m_pSubField;

	CField *m_pPrevField;
	CField *m_pNextField;

private:
	CField();
	CField(const CField &);
	const CField &operator =(const CField &);
};

#endif // CFIELD_H
