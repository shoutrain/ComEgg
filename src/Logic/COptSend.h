#ifndef COPT_SEND_H
#define COPT_SEND_H

#include "COperator.h"

#include "CPduInfo.h"

class COptSend: public COperator
{
public:
    COptSend(const CPduInfo *pPDUInfo,
			 const CAutoVar *pDestination = null_v);
	COptSend(b_4 nSign,
            const CPduInfo *pPDUInfo,
			 const CAutoVar *pIP = null_v,
			 const CAutoVar *pPort = null_v);

	COptSend(const COptSend &opt);
	const COptSend &operator =(const COptSend &opt);

	virtual COperator *Clone() const
	{
		return (COperator *)new COptSend(*this);
	}

	virtual ~COptSend();

	bool_ AddEvaluate(const ch_1 *pszFieldName, const CAutoVar *pValue);

	virtual void Initialize(const opt_unit *pUnit);
	virtual void Work(const TMessageUnit *pTMU);

private:
	COptSend();

	void Clear();

    CPduInfo *m_pPDUInfo;
	vector_evaluate		m_EvaluateVector;

	enum
	{
		NONE_SEND,
		TCP_SEND,
		UDP_SEND
	} m_SendType;

	CAutoVar *m_pDestination;
	CAutoVar *m_pIP;
	CAutoVar *m_pPort;
};

#endif // COPT_SEND_H
