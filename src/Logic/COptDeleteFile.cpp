#include "COptDeleteFile.h"

#include "../System/CFile.h"

void COptDeleteFile::Work(const TMU *pTMU)
{
	v_ Success((b_4)true_v);
	v_ Failure((b_4)false_v);

	(*m_pResult->Value(pTMU)) = Failure;

	try
	{
		CFile DelFile;

		if (!DelFile.Delete((const ch_1 *)(*m_pFilePath->Value(pTMU))))
			throw FILE_DELETE_ERROR;

		(*m_pResult->Value(pTMU)) = Success;
	}
	catch (...)
	{
		throw;
	}
}


