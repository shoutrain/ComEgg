#include "CLinuxFileImp.h"

#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

bool_ CLinuxFileImp::Open(const ch_1 *pszFullPath, bool_ bIsRead)
{
	if (!pszFullPath || null_v == pszFullPath[0])
		return false_v;

	if (0 <= m_File)
		Close();

	m_bIsRead = bIsRead;

	b_4 Flags = O_RDONLY;

	if (!bIsRead)
		Flags = O_CREAT | O_TRUNC | O_WRONLY;

	m_File = open(pszFullPath, Flags, 0644);

	if (m_File < 0)
		return false_v;

	return true_v;
}

void CLinuxFileImp::Close()
{
	if (0 <= m_File)
		close(m_File);

	m_File = -1;
}

bool_ CLinuxFileImp::Read(ub_1 *&pBuffer, size_ BufferSize, size_ &ReadSize)
{
	if (0 > m_File || !m_bIsRead)
		return false_v;

	ReadSize = read(m_File, pBuffer, BufferSize);

	if (0 > ReadSize)
		return false_v;

	return true_v;
}

bool_ CLinuxFileImp::Write(const ub_1 *pBuffer, size_ BufferSize)
{
	if (0 > m_File || m_bIsRead)
		return false_v;

	b_4 WriteSize = write(m_File, pBuffer, BufferSize);

	if (0 > WriteSize)
		return false_v;
	
	return true_v;
}

bool_ CLinuxFileImp::Delete(const ch_1 *pszFullPath)
{
	ch_1 szCommand[512];

	memset(szCommand, 0, 512);
	sprintf(szCommand, "rm -dfr %s", pszFullPath);

	b_4 Ret = system(szCommand);

	if (-1 == Ret || 127 == Ret)
		return false_v;

	return true_v;
}
