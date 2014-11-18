#ifndef COPT_USE_MODULE_H
#define COPT_USE_MODULE_H

#include "COperator.h"

#include "../Modules/CInterfaceInfo.h"

class COptUseModule: public COperator
{
public:
    COptUseModule(const CInterfaceInfo *pInterfaceInfo);

	COptUseModule(const COptUseModule &opt);
	const COptUseModule &operator =(const COptUseModule &opt);

	virtual COperator *Clone() const
	{
		return (COperator *)new COptUseModule(*this);
	}
	
	virtual ~COptUseModule();

	bool_ AddInParameter(CVariable *pValue);
	bool_ AddOutParameter(const ch_1 *pszFieldName, CVariable *pValue);

	virtual void Initialize(const opt_unit *pUnit);
	virtual void Work(const TMU *pTMU);

private:
	COptUseModule();

	void Clear();

	CInterfaceInfo *m_pInterfaceInfo;

	vector_evaluate	m_InEvaluateVector;
	vector_evaluate m_OutEvaluateVector;
};

#endif // COPT_USE_MODULE_H
