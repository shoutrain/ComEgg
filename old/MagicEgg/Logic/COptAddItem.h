#ifndef COPT_ADD_ITEM_H
#define COPT_ADD_ITEM_H

#include "COperator.h"

#include <string.h>

class COptAddItem: public COperator
{
public:

	COptAddItem(const ch_1 *pWindowName)
		: COperator(OT_ADD_ITEM)
	{
		memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szWindowName, pWindowName, VARIABLE_NAME_LENGTH);
	}

	virtual ~COptAddItem()
	{
		Clear();
	}

	COptAddItem(const COptAddItem &opt);
	const COptAddItem &operator =(const COptAddItem &opt);
	
	virtual COperator *Clone() const
	{
		return (COperator *)new COptAddItem(*this);
	}

	bool_ AddVariable(const CVariable *pVariable);

	virtual void Initialize(const opt_unit *pUnit);
	virtual void Work(const TMU *pTMU);

private:
	COptAddItem();

	void Clear();

	ch_1 m_szWindowName[VARIABLE_NAME_LENGTH];
	vector_var m_VariableVector;
};

#endif // COPT_ADD_ITEM_H


