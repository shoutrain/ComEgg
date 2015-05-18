#include "CButton.h"

#include "CContainer.h"

bool_ CButton::Create()
{
	if (m_pWindow || !Parent())
		return false_v;

	ch_1 *pValue = null_v;

	try
	{
		pValue = (ch_1 *)(const ch_1 *)m_Value;
	}
	catch (...)
	{
		pValue = null_v;
	}

	m_pWindow = new fltk::Button(m_iLeftPos, 
								 m_iTopPos, 
								 m_iWidth, 
								 m_iHeight, 
								 pValue);
	m_pWindow->callback(CContainer::OnClickCallBack, this);

	if (!m_bIsEnable)
		m_pWindow->deactivate();

	return true_v;
}

bool_ CButton::Destroy()
{
	_DEL(m_pWindow);
	m_Value = m_OrnValue;

	return true_v;
}

bool_ CButton::CheckOut()
{
	if (!m_pWindow)
		return false_v;

	try
	{
		m_pWindow->label((const ch_1 *)m_Value);
	}
	catch (...)
	{
		m_pWindow->label(null_v);
	}

	return true_v;
}

bool_ CButton::Enable(bool_ bIsEnable)
{
	if (!m_pWindow)
		return false_v;

	if (bIsEnable)
		m_pWindow->activate();
	else
		m_pWindow->deactivate();

	m_bIsEnable = bIsEnable;

	return false_v;
}
