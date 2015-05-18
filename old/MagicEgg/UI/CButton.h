#ifndef CBUTTON_H
#define CBUTTON_H

#include "CWindow.h"

class CButton: public CWindow
{
public:
	CButton(b_4 iLeftPos, 
			b_4 iTopPos, 
			b_4 iWidth, 
			b_4 iHeight, 
			const ch_1 *pszName,
			bool_ bIsEnable,
			const ch_1 *pszValue = null_v)
		: CWindow(iLeftPos, 
				  iTopPos, 
				  iWidth, 
				  iHeight, 
				  pszName, 
				  WINDOW_BUTTON),
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

		m_bIsEnable = bIsEnable;
	}

	virtual ~CButton()
	{
		Destroy();
	}

	virtual bool_ Create();
	virtual bool_ Destroy();

	virtual bool_ CheckOut();

	virtual bool_ Enable(bool_ bIsEnable = true_v);

	virtual v_ *Value()
	{
		return &m_Value;
	}

private:
	fltk::Button *m_pWindow;
	v_ m_Value;
	v_ m_OrnValue;
	bool_ m_bIsEnable;
};

#endif // CBUTTON_H
