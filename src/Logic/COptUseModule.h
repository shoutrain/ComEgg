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

    virtual COperator *clone() const
	{
		return (COperator *)new COptUseModule(*this);
	}
	
	virtual ~COptUseModule();

	bool_ AddInParameter(CAutoVar *pValue);
	bool_ AddOutParameter(const ch_1 *pszFieldName, CAutoVar *pValue);

    virtual void init(const optUnit *unit);

    virtual void work(const TMessageUnit *tmu);

private:
	COptUseModule();

	void Clear();

	CInterfaceInfo *m_pInterfaceInfo;

    vectorEvaluate m_InEvaluateVector;
    vectorEvaluate m_OutEvaluateVector;
};

#endif // COPT_USE_MODULE_H
