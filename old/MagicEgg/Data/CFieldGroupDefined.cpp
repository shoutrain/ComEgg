#include "CFieldGroupDefined.h"

size_ CFieldGroupDefined::Offset(size_ nSize,
								 size_ nBlockSize, 
								 size_ nIndex) const
{
	if (0 == nBlockSize)
		throw FIELD_DATA_NULL;

	if (nSize < nIndex)
		throw FIELD_INDEX_ERROR;

	if (nSize * m_nUnitSize > nBlockSize)
		throw FIELD_SIZE_OVERLOADED;

	if (0 == m_szSizeName[0])
		throw FIELD_TYPE_ERROR;

	size_ nOffset = 0;

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

