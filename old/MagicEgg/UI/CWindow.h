#ifndef CWINDOW_H
#define CWINDOW_H

#include "UICommon.h"

class CWindow
{
public:
	CWindow(b_4 iLeftPos, 
			b_4 iTopPos, 
			b_4 iWidth, 
			b_4 iHeight, 
			const ch_1 *pszName,
			EWindowType WindowType);
	virtual ~CWindow();

	virtual bool_ Create() = 0;
	virtual bool_ Destroy() = 0;

	virtual bool_ CheckIn()
	{
		return false_v;
	}

	virtual bool_ CheckOut()
	{
		return false_v;
	}

	virtual bool_ Enable(bool_ bIsEnable = true_v)
	{
		return false_v;
	}

	virtual v_ *Value()
	{
		return null_v;
	}

	const ch_1 *Name() const
	{
		return m_szName;
	}

	EWindowType Type() const
	{
		return m_WindowType;
	}

	bool_ SetParent(const CWindow *pParent)
	{
		m_pParent = (CWindow *)pParent;

		return true_v;
	}

	CWindow *Parent() const
	{
		return m_pParent;
	}

protected:
	b_4 m_iLeftPos;
	b_4 m_iTopPos;
	b_4 m_iWidth;
	b_4 m_iHeight;

private:
	ch_1 m_szName[WINDOW_NAME_LENGTH];
	EWindowType m_WindowType;
	CWindow *m_pParent;
};

#endif // CWINDOW_H
