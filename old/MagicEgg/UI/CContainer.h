#ifndef CCONTAINER_H
#define CCONTAINER_H

#include "CWindow.h"

#include <string>
#include <map>

using namespace std;

class CPDUInfo;
struct TMU;

typedef map<string, const CWindow *> map_windows;
typedef map<string, const CProgram *> map_programs;
typedef map<const CPDUInfo *, const CProgram *> map_pdu_programs;

class CContainer: public CWindow
{
public:
	CContainer(b_4 iLeftPos, 
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
				  WINDOW_CONTAINER), 
		  m_pWindow(null_v)
	{
		try
		{
			m_Value = pszValue;
		}
		catch (...)
		{
		}
		
		// For wait
		m_pWait = new fltk::Window(0, 0, 100, 50, "Wait...");

		m_pWait->callback();
		m_pWait->begin();

		fltk::Widget *pLabel = new fltk::Widget(0, 0, 80, 30, "Pleast Wait...");

		pLabel->box(fltk::FLAT_BOX);
		pLabel->labelfont(fltk::HELVETICA_ITALIC);

		m_pWait->end();
		m_pWait->set_modal();

		m_pWaittedMessage = null_v;
	}

	virtual ~CContainer();

	void WaitMessage(const CPDUInfo *pPDUInfo = null_v)
	{
		m_pWaittedMessage = (CPDUInfo *)pPDUInfo;

		if (m_pWaittedMessage)
			m_pWait->show();
		else
			m_pWait->hide();
	}

	bool_ AddChild(CWindow *pWindow);
	CWindow *GetChild(const ch_1 *pszName) const;

	// For show the window, instead of the class
	virtual bool_ Create();
	// For destory the window, instead of the class
	virtual bool_ Destroy();

	virtual bool_ CheckIn();
	virtual bool_ CheckOut();

	virtual bool_ Enable(bool_ bIsEnable = true_v);

	CData &Data()
	{
		return m_Data;
	}

	CProgram &StartProgram()
	{
		return m_StartProgram;
	}

	CProgram &EndProgram()
	{
		return m_EndProgram;
	}
	
	bool_ AddMessageProcessor(const ch_1 *pszPDUName, CProgram *&pProgram);
	bool_ AddOnClickProcessor(const ch_1 *pszButtonName, CProgram *&pProgram);
	CProgram *GetOnClickProcessor(const ch_1 *pszButtonName) const;

	void OnMessage(TMU *pTMU);

	static void OnClickCallBack(fltk::Widget *pControl, void *pWindow);

private:
	fltk::Window *m_pWait;
	fltk::Window *m_pWindow;

	CPDUInfo *m_pWaittedMessage;

	map_windows m_WindowsMap;
	map_pdu_programs m_MessageMap; // For message processors
	map_programs m_ProgramsMap; // For button click processors

	CData m_Data;

	CProgram m_StartProgram;
	CProgram m_EndProgram;

	v_ m_Value;
};

#endif // CCONTAINER_H
