#include "CWindow.h"

#include <string.h>

CWindow::CWindow(b_4 iLeftPos, 
				 b_4 iTopPos, 
				 b_4 iWidth, 
				 b_4 iHeight, 
				 const ch_1 *pszName,
				 EWindowType WindowType)
{
	m_iLeftPos = iLeftPos;
	m_iTopPos = iTopPos;
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	memset(m_szName, 0, WINDOW_NAME_LENGTH);
	strncpy(m_szName, pszName, WINDOW_NAME_LENGTH);

	m_WindowType = WindowType;
	m_pParent = null_v;
}

CWindow::~CWindow()
{

}
