#ifndef CFILE_IMP_H
#define CFILE_IMP_H

#include "../Common/Common.h"

class CFileImp
{
public:
	virtual bool_ Open(const ch_1 *pszFullPath, bool_ bIsRead) = 0;
	virtual void Close() = 0;

	virtual bool_ Read(ub_1 *&pBuffer, size_ BufferSize, size_ &ReadSize) = 0;
	virtual bool_ Write(const ub_1 *pBuffer, size_ BufferSize) = 0;

	virtual bool_ Delete(const ch_1 *pszFullPath) = 0;
};

#endif // CFILE_IMP_H
