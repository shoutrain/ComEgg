#include "CLabel.h"

bool_ CLabel::Create()
{
	if (m_pWindow)
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

	m_pWindow = new fltk::Widget(m_iLeftPos, 
								 m_iTopPos, 
								 m_iWidth, 
								 m_iHeight, 
								 pValue);
	m_pWindow->box(fltk::FLAT_BOX);
	m_pWindow->labelfont(fltk::HELVETICA_ITALIC);

	return true_v;
}

bool_ CLabel::Destroy()
{
	_DEL(m_pWindow);
	m_Value = m_OrnValue;

	return true_v;
}

bool_ CLabel::CheckOut()
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
