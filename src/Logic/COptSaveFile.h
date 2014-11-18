#ifndef COPT_SAVE_FILE_H
#define COPT_SAVE_FILE_H

#include "COperator.h"

class COptSaveFile: public COperator
{
public:
	COptSaveFile(const CVariable *pFilePath,
				 const CVariable *pFileName,
				 const CVariable *pFileContent,
				 const CVariable *pResult)
		: COperator(OT_SAVE_FILE)
	{
		m_pFilePath		= pFilePath->Clone();
		m_pFileName		= pFileName->Clone();
		m_pFileContent	= pFileContent->Clone();
		m_pResult		= pResult->Clone();
	}

	virtual ~COptSaveFile()
	{
		_DEL(m_pFilePath);
		_DEL(m_pFileName);
		_DEL(m_pFileContent);
		_DEL(m_pResult);
	}

	COptSaveFile(const COptSaveFile &opt): COperator(opt)
	{
		m_pFilePath		= opt.m_pFilePath->Clone();
		m_pFileName		= opt.m_pFileName->Clone();
		m_pFileContent	= opt.m_pFileContent->Clone();
		m_pResult		= opt.m_pResult->Clone();
	}

	const COptSaveFile &operator =(const COptSaveFile &opt)
	{
		if (this != &opt)
		{
			COperator::operator =(opt);

			_DEL(m_pFilePath);
			_DEL(m_pFileName);
			_DEL(m_pFileContent);
			_DEL(m_pResult);
			m_pFilePath		= opt.m_pFilePath->Clone();
			m_pFileName		= opt.m_pFileName->Clone();
			m_pFileContent	= opt.m_pFileContent->Clone();
			m_pResult		= opt.m_pResult->Clone();
		}

		return *this;
	}

	virtual COperator *Clone() const
	{
		return (COperator *)new COptSaveFile(*this);;
	}

	virtual void Initialize(const opt_unit *pUnit)
	{
		COperator::Initialize(pUnit);

		m_pFilePath->Initialize(pUnit->pData);
		m_pFileName->Initialize(pUnit->pData);
		m_pFileContent->Initialize(pUnit->pData);
		m_pResult->Initialize(pUnit->pData);
	}

	virtual void Work(const TMU *pTMU);

private:
	CVariable *m_pFilePath;
	CVariable *m_pFileName;
	CVariable *m_pFileContent;
	CVariable *m_pResult;
};

#endif // COPT_SAVE_FILE_H

