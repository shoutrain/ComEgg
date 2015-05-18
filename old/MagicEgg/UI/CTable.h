#ifndef CTABLE_H
#define CTABLE_H

#include "CWindow.h"

struct TColumn
{
	TColumn *pNextColumn;

	ch_1 *pszLabel;
	ub_2 uiWidth;
};

class CColumnName
{
public:
	CColumnName()
		: m_pFirstColumn(null_v),
		  m_pLastColumn(null_v),
		  m_nNum(0)
	{}

	~CColumnName();

	bool_ AddColumn(const ch_1 *pszColumnName, ub_2 uiWidth);
	const ch_1 **GetLabels();
	const b_4 *GetWidths();

	size_ GetNum() const
	{
		return m_nNum;
	}

private:
	TColumn *m_pFirstColumn;
	TColumn *m_pLastColumn;
	size_ m_nNum;
};

#include <vector>

typedef vector<const v_ *> vector_variable;

class CTable: public CWindow
{
public:
	CTable(b_4 iLeftPos, 
		   b_4 iTopPos, 
		   b_4 iWidth, 
		   b_4 iHeight, 
		   const ch_1 *pszName)
		: CWindow(iLeftPos, 
				  iTopPos, 
				  iWidth, 
				  iHeight, 
				  pszName, 
				  WINDOW_TABLE),
		  m_pWindow(null_v), m_iIndex(-1)
	{
	}

	virtual ~CTable()
	{
		Destroy();
	}

	bool_ AddColumn(const ch_1 *pszColumnName, ub_2 uiWidth);
	bool_ AddItem(const v_ &Index, ch_1 **ppszItem, size_ nNum);

	size_ GetNum() const 
	{
		return m_ColumnName.GetNum();
	}

	virtual bool_ Create();
	virtual bool_ Destroy();

	virtual bool_ CheckIn();

	virtual v_ *Value();

private:
	fltk::Browser *m_pWindow;
	CColumnName m_ColumnName;
	vector_variable m_IndexVector;
	b_4 m_iIndex;
};

#endif // CTABLE_H
