#ifndef CLABEL_H
#define CLABEL_H

#include "CWindow.h"

class CLabel: public CWindow
{
public:
	CLabel(b_4 iLeftPos, 
		   b_4 iTopPos, 
		   b_4 iWidth, 
		   b_4 iHeight, 
		   const ch_1 *pszName,
		   const ch_1 *pszValue = null_v)
		: CWindow(iLeftPos, 
				  iTopPos, 
				  iWidth, 
				  iHeight, 
				  pszName, 
				  WINDOW_LABEL),
		  m_pWindow(null_v)
	{
		try
		{
			m_Value = pszValue;
			m_OrnValue = pszValue;
		}
		catch (...)
		{
		}
	}

	virtual ~CLabel()
	{
		Destroy();
	}

	virtual bool_ Create();
	virtual bool_ Destroy();

	virtual bool_ CheckOut();

	virtual v_ *Value()
	{
		return &m_Value;
	}
private:
	fltk::Widget *m_pWindow;
	v_ m_Value;
	v_ m_OrnValue;
};

#endif // CLABEL_H
