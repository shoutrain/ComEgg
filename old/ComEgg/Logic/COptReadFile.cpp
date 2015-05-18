#include "COptReadFile.h"

#include "../System/CFile.h"

void COptReadFile::Work(const TMU *pTMU)
{
	try
	{
		v_ OrnFileName = (*m_pFilePath->Value(pTMU))
			+ (*m_pFileName->Value(pTMU));
		ub_1 *pBuffer = new ub_1[REV_BUFFER_MAX_SIZE];
		CFile ReadFile;
		size_ ReadSize;

		if (!ReadFile.Read((const ch_1 *)OrnFileName, pBuffer,
						   REV_BUFFER_MAX_SIZE, ReadSize))
		{
			throw FILE_READ_ERROR;
		}

		(*m_pResult->Value(pTMU)) = v_((ub_1 *)pBuffer);
	}
	catch (...)
	{
		throw;
	}
}

