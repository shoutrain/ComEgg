#ifndef CLINUX_FILE_IMP_H
#define CLINUX_FILE_IMP_H

#include "CFileImp.h"

class CLinuxFileImp: CFileImp
{
public:
	CLinuxFileImp(): m_File(-1) {}

	virtual ~CLinuxFileImp()
	{
		Close();
	}

	virtual bool_ Open(const ch_1 *pszFullPath, bool_ bIsRead);
	virtual void Close();

	virtual bool_ Read(ub_1 *&pBuffer, size_ BufferSize, size_ &ReadSize);
	virtual bool_ Write(const ub_1 *pBuffer, size_ BufferSize);

	virtual bool_ Delete(const ch_1 *pszFullPath);

private:
	b_4		m_File;
	bool_	m_bIsRead;
};

#endif // CLINUX_FILE_IMP_H
