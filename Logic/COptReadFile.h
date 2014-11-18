#ifndef COPT_READ_FILE_H
#define COPT_READ_FILE_H

#include "COperator.h"

class COptReadFile: public COperator
{
public:
	COptReadFile(const CVariable *pFilePath,
				 const CVariable *pFileName,
				 const CVariable *pResult)
		: COperator(OT_READ_FILE)
	{
		m_pFilePath		= pFilePath->Clone();
		m_pFileName		= pFileName->Clone();
		m_pResult		= pResult->Clone();
	}

	virtual ~COptReadFile()
	{
		_DEL(m_pFilePath);
		_DEL(m_pFileName);
		_DEL(m_pResult);
	}

	COptReadFile(const COptReadFile &opt): COperator(opt)
	{
		m_pFilePath		= opt.m_pFilePath->Clone();
		m_pFileName		= opt.m_pFileName->Clone();
		m_pResult		= opt.m_pResult->Clone();;
	}

	const COptReadFile &operator =(const COptReadFile &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pFilePath);
			_DEL(m_pFileName);
			_DEL(m_pResult);
			m_pFilePath		= opt.m_pFilePath->Clone();
			m_pFileName		= opt.m_pFileName->Clone();
			m_pResult		= opt.m_pResult->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptReadFile(*this);
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pFilePath->Initialize(pUnit->pData);
		m_pFileName->Initialize(pUnit->pData);
		m_pResult->Initialize(pUnit->pData);
	}

	virtual void Work(const TMU *pTMU);

private:
	CVariable *m_pFilePath;
	CVariable *m_pFileName;
	CVariable *m_pResult;
};

#endif // COPT_READ_FILE_H
