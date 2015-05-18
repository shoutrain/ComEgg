#ifndef CFILE_H
#define CFILE_H

#include "CSysFactory.h"

class CFile
{
public:
	CFile()
	{
		m_pFile = CSysFactory::Instance()->MakeFile();
	}

	virtual ~CFile()
	{
		_DEL(m_pFile);
	}

	bool_ Read(const ch_1 *pszFullPath, 
				ub_1 *&pBuffer, 
				size_ BufferSize, 
				size_ &ReadSize)
	{
		if (!m_pFile->Open(pszFullPath, true_v))
			return false_v;

		if (!m_pFile->Read(pBuffer, BufferSize, ReadSize))
			return false_v;

		m_pFile->Close();

		return true_v;
	}


	bool_ Write(const ch_1 *pszFullPath, 
				const ub_1 *pBuffer, 
				size_ BufferSize)
	{
		if (!m_pFile->Open(pszFullPath, false_v))
			return false_v;

		if (!m_pFile->Write(pBuffer, BufferSize))
			return false_v;

		m_pFile->Close();

		return true_v;		
	}

	bool_ Delete(const ch_1 *pszFullPath)
	{
		return m_pFile->Delete(pszFullPath);
	}

private:
	CFileImp *m_pFile;
};

#endif // CFILE_H
