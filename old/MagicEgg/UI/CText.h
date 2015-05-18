#ifndef CTEXT_H
#define CTEXT_H

#include "CWindow.h"

class CText: public CWindow
{
public:
	CText(b_4 iLeftPos, 
		  b_4 iTopPos, 
		  b_4 iWidth, 
		  b_4 iHeight, 
		  const ch_1 *pszName,
		  ub_2 uiMaxLength = 0,
		  bool_ bIsReadOnly = false_v,
		  bool_ bIsMultiLine = false_v,
		  bool_ bIsSecret = false_v,
		  const ch_1 *pszValue = null_v)
		: CWindow(iLeftPos, 
				  iTopPos, 
				  iWidth, 
				  iHeight, 
				  pszName, 
				  WINDOW_TEXT),
		  m_pWindow(null_v)
	{
		m_uiMaxLength = uiMaxLength;
		m_bIsReadOnly = bIsReadOnly;
		m_bIsMultiLine = bIsMultiLine;
		m_bIsSecret = bIsSecret;

		try
		{
			m_Value = pszValue;
			m_OrnValue = pszValue;
		}
		catch (...)
		{
		}
	}

	virtual ~CText()
	{
		Destroy();
	}

	virtual bool_ Create();
	virtual bool_ Destroy();

	virtual bool_ CheckIn();
	virtual bool_ CheckOut();

	virtual bool_ Enable(bool_ bIsEnable = true_v);

	virtual v_ *Value()
	{
		return &m_Value;
	}

private:
	fltk::Input *m_pWindow;
	ub_2 m_uiMaxLength;
	bool_ m_bIsReadOnly;
	bool_ m_bIsMultiLine;
	bool_ m_bIsSecret;
	v_ m_Value;
	v_ m_OrnValue;
};

#endif // CTEXT_H
