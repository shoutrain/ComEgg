#ifndef COPT_DELETE_FILE_H
#define COPT_DELETE_FILE_H

#include "COperator.h"

class COptDeleteFile: public COperator
{
public:
	COptDeleteFile(const CAutoVar *pFilePath,
				   const CAutoVar *pResult)
		: COperator(OT_DELETE_FILE)
	{
		m_pFilePath		= pFilePath->Clone();
		m_pResult		= pResult->Clone();
	}

	virtual ~COptDeleteFile()
	{
		_DEL(m_pFilePath);
		_DEL(m_pResult);
	}

	COptDeleteFile(const COptDeleteFile &opt): COperator(opt)
	{
		m_pFilePath		= opt.m_pFilePath->Clone();
		m_pResult		= opt.m_pResult->Clone();
	}

	const COptDeleteFile &operator =(const COptDeleteFile &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pFilePath);
			_DEL(m_pResult);

			m_pFilePath		= opt.m_pFilePath->Clone();
			m_pResult		= opt.m_pResult->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptDeleteFile(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pFilePath->Initialize(pUnit->pData);
		m_pResult->Initialize(pUnit->pData);
	}

	virtual void Work(const TMessageUnit *pTMU);

private:
	CAutoVar *m_pFilePath;
	CAutoVar *m_pResult;
};

#endif // COPT_DELETE_FILE_H

