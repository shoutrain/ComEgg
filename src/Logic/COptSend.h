#ifndef COPT_SEND_H
#define COPT_SEND_H

#include "COperator.h"

#include "../Protocols/CPDUInfo.h"

class COptSend: public COperator
{
public:
    COptSend(const CPDUInfo *pPDUInfo,
			 const CVariable *pDestination = null_v);
	COptSend(b_4 nSign,
			 const CPDUInfo *pPDUInfo,
			 const CVariable *pIP = null_v,
			 const CVariable *pPort = null_v);

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

	CPDUInfo			*m_pPDUInfo;
	vector_evaluate		m_EvaluateVector;

	enum
	{
		NONE_SEND,
		TCP_SEND,
		UDP_SEND
	} m_SendType;

	CVariable *m_pDestination;
	CVariable *m_pIP;
	CVariable *m_pPort;
};

#endif // COPT_SEND_H
