#include "CFieldGroup.h"

size_ CFieldGroup::Size(const ub_1 *pBlock, size_ nBlockSize) const
{
	if (!pBlock || 0 == nBlockSize)
		throw FIELD_DATA_NULL;

	if (null_v == m_pSizeField)
		throw FIELD_TYPE_ERROR;
	
	size_ nUnitNum = 0;

	if (m_pSizeField)
	{
		try
		{
			nUnitNum = (size_)*(pBlock + m_pSizeField->Offset(pBlock, 
															  nBlockSize));
		}
		catch (...)
		{
			throw;
		}
	}
	else
	{
		throw FIELD_TYPE_ERROR;
	}

	return m_nUnitSize * nUnitNum;
}

size_ CFieldGroup::Offset(const ub_1 *pBlock, 
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

	if (nIndex)
		nOffset += (nIndex - 1) * m_nUnitSize;

	try
	{
		if (nBlockSize <= nOffset)
			throw FIELD_SIZE_OVERLOADED;
	}
	catch (...)
	{
		throw;
	}

	return nOffset;
}

