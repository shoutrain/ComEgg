#include "CTable.h"

CColumnName::~CColumnName()
{
	TColumn *pColumn = m_pFirstColumn;
	TColumn *pNextColumn = null_v;

	while (pColumn)
	{
		pNextColumn = pColumn->pNextColumn;

		_DEL_ARR(pColumn->pszLabel);
		_DEL(pColumn);

		pColumn = pNextColumn;
	}
}

bool_ CColumnName::AddColumn(const ch_1 *pszColumnName, ub_2 uiWidth)
{
	if (!pszColumnName || 0 == pszColumnName[0])
		return false_v;

	ub_4 uiLength = strlen(pszColumnName) + 1;
	TColumn *pColumn = new TColumn;

	pColumn->pszLabel = new ch_1[uiLength];
	strncpy(pColumn->pszLabel, pszColumnName, uiLength);
	pColumn->uiWidth = uiWidth;

	if (!m_pFirstColumn)
	{
		m_pFirstColumn = m_pLastColumn = pColumn;
	}
	else
	{
		m_pLastColumn->pNextColumn = pColumn;
		m_pLastColumn = pColumn;
	}

	m_nNum++;

	return true_v;
}

const ch_1 **CColumnName::GetLabels()
{
	if (!m_nNum)
		return null_v;

	ch_1 **ppszColumns = new ch_1 *[m_nNum + 1];
	TColumn *pColumn = m_pFirstColumn;
	size_ n = 0;

	for (; n < m_nNum; n++)
	{
		ppszColumns[n] = pColumn->pszLabel;
		pColumn = pColumn->pNextColumn;
	}

	ppszColumns[n] = 0;

	return (const ch_1 **)ppszColumns;
}

const b_4 *CColumnName::GetWidths()
{
	if (!m_nNum)
		return null_v;

	b_4 *piWidths = new b_4[m_nNum + 1];
	TColumn *pColumn = m_pFirstColumn;
	size_ n = 0;

	for (; n < m_nNum; n++)
	{
		piWidths[n] = (b_4)pColumn->uiWidth;
		pColumn = pColumn->pNextColumn;
	}

	piWidths[n] = 0;

	return piWidths;
}

bool_ CTable::AddColumn(const ch_1 *pszColumnName, ub_2 uiWidth)
{
	return m_ColumnName.AddColumn(pszColumnName, uiWidth);
}

bool_ CTable::AddItem(const v_ &Index, ch_1 **ppszItem, size_ nNum)
{
	if (!ppszItem || m_ColumnName.GetNum() != nNum)
		return false_v;

	char szItem[1024];
	size_ nSize = 0;

	memset(szItem, 0, 1024);

	for (size_ n = 0; n < nNum; n++)
	{
		if (!ppszItem[n])
			return false_v;

		size_ l = strlen(ppszItem[n]);

		strncat(szItem, ppszItem[n], l);
		nSize += l;

		if (nNum - 1 != n)
		{
			strncat(szItem, "\t", 1);
			nSize++;
		}

		if (nSize >= 1024)
			return false_v;
	}

	m_pWindow->add_group(szItem, m_pWindow);
	
	v_ *pIndex = new v_(Index);

	m_IndexVector.push_back(pIndex);

	return true_v;
}

bool_ CTable::Create()
{
	if (m_pWindow)
		return false_v;

	m_pWindow = new fltk::Browser(m_iLeftPos,
								  m_iTopPos,
								  m_iWidth,
								  m_iHeight);

	const b_4 *piWidths = m_ColumnName.GetWidths();
	const ch_1 **ppszLabels = m_ColumnName.GetLabels();

	if (!ppszLabels || !piWidths)
	{
		_DEL_ARR(piWidths);
		_DEL_ARR(ppszLabels);

		return false_v;
	}
	
	m_pWindow->column_widths(piWidths);
	m_pWindow->column_labels(ppszLabels);

	_DEL_ARR(piWidths);
	_DEL_ARR(ppszLabels);

	v_ *pIndex = new v_((b_4)-1);

	m_IndexVector.push_back(pIndex);
	
	return true_v;
}

bool_ CTable::Destroy()
{
	_DEL(m_pWindow);

	for (vector_variable::const_iterator pos = m_IndexVector.begin();
		 pos != m_IndexVector.end(); pos++)
	{
		v_ *pIndex = (v_ *)*pos;
		_DEL(pIndex);
	}

	m_IndexVector.clear();

	return true_v;
}

bool_ CTable::CheckIn()
{
	if (!m_pWindow)
		return false_v;

	m_iIndex = m_pWindow->value();

	if (m_iIndex >= 0)
		m_iIndex++;
	else
		m_iIndex = 0;

	return true_v;
}

v_ *CTable::Value()
{
	if (!m_pWindow)
		return null_v;

	return (v_ *)m_IndexVector[m_iIndex];
}

