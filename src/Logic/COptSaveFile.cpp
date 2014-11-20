#include "COptSaveFile.h"

#include "../System/CFile.h"

void COptSaveFile::Work(const TMessageUnit *pTMU)
{
	v_ Success((b_4)true_v);
	v_ Failure((b_4)false_v);

	(*m_pResult->Value(pTMU)) = Failure;

	try
	{
		v_ DstFileName = (*m_pFilePath->Value(pTMU)) 
			+ (*m_pFileName->Value(pTMU));
		CFile WriteFile;

		if (!WriteFile.Write((const ch_1 *)DstFileName, 
							 (const ub_1 *)
							 (const obj_)(*m_pFileContent->Value(pTMU)), 
							 REV_BUFFER_MAX_SIZE))
		{
			throw FILE_WRITE_ERROR;				
		}

		(*m_pResult->Value(pTMU)) = Success;
	}
	catch (...)
	{
		throw;
	}
}


