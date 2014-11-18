#include "CFieldString.h"

size_ CFieldString::Offset(const ub_1 *pBlock, 
						   size_ nBlockSize, 
						   size_ nIndex) const
{
	if (!pBlock || 0 == nBlockSize)
		throw FIELD_DATA_NULL;

	size_ nOffset = 0;

	if (m_pPrevField)
	{
		try
		{
			nOffset += m_pPrevField->Offset(pBlock, nBlockSize)	
				+ m_pPrevField->Size(pBlock, nBlockSize);
		}
		catch (...)
		{
			throw;
		}
	}

	if (nIndex && m_pGroupField)
		nOffset += m_pGroupField->Offset(pBlock, nBlockSize, nIndex);

	try
	{
		if (nBlockSize < nOffset + Size(pBlock, nBlockSize))
			throw FIELD_SIZE_OVERLOADED;
	}
	catch (...)
	{
		throw;
	}

	return nOffset;
}

