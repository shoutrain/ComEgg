#ifndef CVAR_MODULE_H
#define CVAR_MODULE_H

#include "CVariable.h"

#include "CField.h"
#include "../Protocols/CPDUInfo.h"

class CVarModule: public CVariable
{
public:
	CVarModule(const CField *pField)
	{
		m_pField = (CField *)pField;
	}

	virtual CVariable *Clone() const;
	virtual void Initialize(const CData *pData);
	virtual v_ *Value(const TMU *pTMU);

private:
	CVarModule();
	CVarModule(const CVarModule &);
	const CVarModule &operator =(const CVarModule &);

	CField *m_pField;

	v_ m_Value;
};

#endif // CVAR_MODULE_H
