#include "CText.h"

bool_ CText::Create()
{
	if (m_pWindow)
		return false_v;

	if (!m_bIsMultiLine && !m_bIsSecret) // Normal Input Box
	{
		m_pWindow = new fltk::Input(m_iLeftPos,
									m_iTopPos,
									m_iWidth,
									m_iHeight);
	}
	else if (m_bIsMultiLine && !m_bIsSecret) // Multiline Input Box
	{
		m_pWindow = new fltk::MultiLineInput(m_iLeftPos,
											 m_iTopPos,
											 m_iWidth,
											 m_iHeight);
	}
	else if (!m_bIsMultiLine && m_bIsSecret) // Normal Password Box
	{
		m_pWindow = new fltk::SecretInput(m_iLeftPos,
										  m_iTopPos,
										  m_iWidth,
										  m_iHeight);
	}
	else // No other type
	{
		return false_v;
	}

	try
	{
		m_pWindow->value((const ch_1 *)m_Value);
	}
	catch (...)
	{
	}

	if (m_bIsReadOnly)
		m_pWindow->deactivate();

	return true_v;
}

bool_ CText::Destroy()
{
	_DEL(m_pWindow);
	m_Value = m_OrnValue;
	
	return true_v;
}

bool_ CText::CheckIn()
{
	if (!m_pWindow)
		return false_v;

	try
	{
		m_Value = m_pWindow->value();
	}
	catch (...)
	{
		m_Value.clear();
	}

	return true_v;
}

bool_ CText::CheckOut()
{
	if (!m_pWindow)
		return false_v;

	try
	{
		m_pWindow->value((const ch_1 *)m_Value);
	}
	catch (...)
	{
		m_pWindow->value(null_v);
	}

	return true_v;
}

bool_ CText::Enable(bool_ bIsEnable)
{
	if (!m_pWindow)
		return false_v;

	if (bIsEnable)
	{
		m_bIsReadOnly = false_v;
		m_pWindow->activate();
	}
	else
	{
		m_bIsReadOnly = true_v;
		m_pWindow->deactivate();
	}

	return false_v;
}

