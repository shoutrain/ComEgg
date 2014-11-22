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

    virtual COperator *clone() const
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

    virtual void reset();

    virtual void init(const optUnit *unit);

    virtual void work(const TMessageUnit *tmu);

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

    vectorOpt m_OptVector;

	CData m_OrnData;
	CData m_Data;
};

#endif // CPROGRAM_H

