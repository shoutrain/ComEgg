#ifndef COPT_SEND_H
#define COPT_SEND_H

#include "COperator.h"

#include "../Protocols/CPDUInfo.h"

class COptSend: public COperator
{
public:
    COptSend(const CPDUInfo *pPDUInfo);
	COptSend(const COptSend &opt);
	const COptSend &operator =(const COptSend &opt);

	virtual COperator *Clone() const
	{
		return (COperator *)new COptSend(*this);
	}
	
	virtual ~COptSend();

	bool_ AddEvaluate(const ch_1 *pszFieldName, const CVariable *pValue);

	virtual void Initialize(const opt_unit *pUnit);
	virtual void Work(const TMU *pTMU);

private:
	COptSend();

	void Clear();

	CPDUInfo *m_pPDUInfo;
	vector_evaluate m_EvaluateVector;
};

#endif // COPT_SEND_H
