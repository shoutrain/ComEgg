#ifndef CPROGRAM_H
#define CPROGRAM_H

#include "COperator.h"

class CProgram: public COperator
{
public:
	CProgram(const CData *pData = null_v): COperator(OT_PROGRAM)
	{
		if (pData)
		{
			m_OrnData	= *pData;
			m_Data		= *pData;
		}
	}

	CProgram(const CProgram &opt);
	const CProgram &operator =(const CProgram &opt);
	
	virtual COperator *Clone() const
	{
		return (COperator *)new CProgram(*this);
	}
	
	virtual bool_ AddOperator(const COperator *pOperator);

	virtual void SetData(const CData &Data)
	{
		m_OrnData	= Data;
		m_Data		= Data;
	}

	virtual CData &Data()
	{
		return m_Data;
	}

	virtual void Reset();
	virtual void Initialize(const opt_unit *pUnit);
	virtual void Work(const TMU *pTMU);

protected:
	CProgram(const EOperatorType Type, const CData *pData = null_v)
		: COperator(Type)
	{
		if (pData)
		{
			m_OrnData	= *pData;
			m_Data		= *pData;
		}
	}
	
	virtual 

	void Clear();

	vector_opt m_OptVector;

	CData m_OrnData;
	CData m_Data;
};

#endif // CPROGRAM_H

