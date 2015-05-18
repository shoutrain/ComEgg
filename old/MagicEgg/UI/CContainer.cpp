#include "CContainer.h"
#include "CUIManager.h"

#include "../Protocols/CProtocolManager.h"
#include "../Protocols/CProtocolInfo.h"
#include "../Network/NetworkCommon.h"
#include "../UI/CWindow.h"

CContainer::~CContainer()
{
	for (map_windows::iterator pos = m_WindowsMap.begin();
		 pos != m_WindowsMap.end(); pos++)
	{
		_DEL(pos->second);
	}

	for (map_pdu_programs::iterator pos_ = m_MessageMap.begin();
		 pos_ != m_MessageMap.end(); pos_++)
	{
		_DEL(pos_->second);
	}

	for (map_programs::iterator pos__ = m_ProgramsMap.begin();
		 pos__ != m_ProgramsMap.end(); pos__++)
	{
		_DEL(pos__->second);
	}

	if (m_pWait)
		m_pWait->destroy();
	
	_DEL(m_pWait);

	if (m_pWindow)
		m_pWindow->destroy();
	
	_DEL(m_pWindow);

	m_WindowsMap.clear();
	m_MessageMap.clear();
	m_ProgramsMap.clear();
}

bool_ CContainer::AddChild(CWindow *pWindow)
{
	if (!pWindow)
		return false_v;

	map_windows::const_iterator pos = m_WindowsMap.find(pWindow->Name());

	// the window with same name has already exist;
	if (m_WindowsMap.end() != pos) 
		return false_v;

	m_WindowsMap.insert(map_windows::value_type(pWindow->Name(), pWindow));
	pWindow->SetParent(this);

	return true_v;
}

CWindow *CContainer::GetChild(const ch_1 *pszName) const
{
	if (!pszName)
		return null_v;
	
	map_windows::const_iterator pos = m_WindowsMap.find(pszName);

	if (m_WindowsMap.end() != pos)
		return (CWindow *)pos->second;

	return null_v;
}

bool_ CContainer::Create()
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

	m_pWindow = new fltk::Window(m_iLeftPos, 
								 m_iTopPos, 
								 m_iWidth, 
								 m_iHeight, 
								 pValue);
	m_pWindow->begin();

	for (map_windows::iterator pos = m_WindowsMap.begin();
		 pos != m_WindowsMap.end(); pos++)
	{
		if (!((CWindow *)pos->second)->Create())
			return false_v;
	}

	m_pWindow->end();
	m_pWindow->show();
	CUIManager::Instance()->SetCurContainer(this);

	opt_unit OU;

	OU.pData = &m_Data;
	OU.pParent = null_v;
	m_StartProgram.Initialize(&OU);
	m_StartProgram.Work(null_v);

	CheckOut();

	return true_v;
}

bool_ CContainer::Destroy()
{
	CheckIn();

	opt_unit OU;

	OU.pData = &m_Data;
	OU.pParent = null_v;
	m_EndProgram.Initialize(&OU);
	m_EndProgram.Work(null_v);

	for (map_windows::iterator pos = m_WindowsMap.begin();
		 pos != m_WindowsMap.end(); pos++)
	{
		if (!((CWindow *)pos->second)->Destroy())
			return false_v;
	}
	
	if (m_pWindow)
	{
		// m_pWindow->destroy();
		_DEL(m_pWindow);
	}
	
	return true_v;
}

bool_ CContainer::CheckIn()
{
	for (map_windows::iterator pos = m_WindowsMap.begin();
		 pos != m_WindowsMap.end(); pos++)
	{
		((CWindow *)pos->second)->CheckIn();
	}

	return true_v;
}

bool_ CContainer::CheckOut()
{
	for (map_windows::iterator pos = m_WindowsMap.begin();
		 pos != m_WindowsMap.end(); pos++)
	{
		((CWindow *)pos->second)->CheckOut();
	}

	return true_v;	
}

bool_ CContainer::Enable(bool_ bIsEnable)
{
	for (map_windows::iterator pos = m_WindowsMap.begin();
		 pos != m_WindowsMap.end(); pos++)
	{
		((CWindow *)pos->second)->Enable(bIsEnable);
	}

	return true_v;
}

bool_ CContainer::AddMessageProcessor(const ch_1 *pszPDUName,
									  CProgram *&pProgram)
{
	if (!pszPDUName || 0 == pszPDUName[0])
		return false_v;

	if (pProgram)
		return false_v;

	CPDUInfo *pPDUInfo = null_v;

	if (SUCCESS != CProtocolManager::Instance()->GetProtocol()->GetPDU(
			pszPDUName,
			pPDUInfo))
	{
		return false_v;
	}

	map_pdu_programs::const_iterator pos =  m_MessageMap.find(pPDUInfo);

	if (m_MessageMap.end() != pos)
		return false_v;

	pProgram = new CProgram();
	m_MessageMap.insert(map_pdu_programs::value_type(pPDUInfo, pProgram));

	return true_v;
}

bool_ CContainer::AddOnClickProcessor(const ch_1 *pszButtonName, 
									  CProgram *&pProgram)
{
	if (!pszButtonName || 0 == pszButtonName[0])
		return false_v;

	if (pProgram)
		return false_v;

	map_programs::const_iterator pos = m_ProgramsMap.find(pszButtonName);

	if (m_ProgramsMap.end() != pos)
		return false_v;

	// the button identified by name should be exist
	map_windows::const_iterator pos_ = m_WindowsMap.find(pszButtonName);

	if (m_WindowsMap.end() == pos_) 
		return false_v;

	pProgram = new CProgram();
	m_ProgramsMap.insert(map_programs::value_type(pszButtonName, pProgram));

	return true_v;
}

CProgram *CContainer::GetOnClickProcessor(const ch_1 *pszButtonName) const
{
	if (!pszButtonName || 0 == pszButtonName[0])
		return null_v;

	map_programs::const_iterator pos = m_ProgramsMap.find(pszButtonName);

	if (m_ProgramsMap.end() == pos)
		return null_v;

	return (CProgram *)pos->second;
}

void CContainer::OnMessage(TMU *pTMU)
{
	if (m_pWaittedMessage != pTMU->pPDUInfo)
		return;
	else
		WaitMessage();

	map_pdu_programs::const_iterator pos = m_MessageMap.find(pTMU->pPDUInfo);

	if (m_MessageMap.end() == pos)
	{
		printf("Received message can not be found!");

		return;
	}

	CProgram *pProgram = (CProgram *)pos->second;

	CheckIn();

	try
	{
		opt_unit OU;

		OU.pData = &m_Data;
		OU.pParent = null_v;
		pProgram->Initialize(&OU);
		pProgram->Work(pTMU);
	}
	catch (...)
	{
		printf("Exception happened while handling message!\n");

		return;
	}

	if (CUIManager::Instance()->GetCurContainer() == this)
		CheckOut();
}

void CContainer::OnClickCallBack(fltk::Widget *pControl, void *pWindow)
{
	CContainer *pParent = (CContainer *)((CWindow *)pWindow)->Parent();

	if (!pParent)
		return;

	CProgram *pProgram = pParent->GetOnClickProcessor(
		((CWindow *)pWindow)->Name());

	if (!pProgram)
		return;

	pParent->CheckIn();

	try
	{
		opt_unit OU;

		OU.pData = &pParent->Data();
		OU.pParent = null_v;
		pProgram->Initialize(&OU);
		pProgram->Work(null_v);
	}
	catch (...)
	{
		printf("Exception happened while handling click!\n");

		return;
	}

	if (CUIManager::Instance()->GetCurContainer() == pParent)
		pParent->CheckOut();
}
