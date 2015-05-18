#ifndef CXML_LOADER_ACTIONS_H
#define CXML_LOADER_ACTIONS_H

#include "CXMLLoader.h"

class CXMLLoaderActions: public CXMLLoader
{
public:
	static CXMLLoaderActions *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CXMLLoaderActions;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ Load(XercesDOMParser *pParser, const ch_1 *pszEnvironmentPath);

private:
	ret_ LoadDataBlock(CData &Data, const DOMElement *pElement);
	ret_ LoadProcessor(const DOMElement *pElement);
	ret_ LoadProgram(const CData *pParentData,
					 CProgram &Program,
					 const DOMElement *pElement,
					 const CPDUInfo *pPDU = null_v);
	ret_ LoadProcessBlock(CProgram &Program,
						  const DOMElement *pElement,
						  const CPDUInfo *pPDU = null_v);

	ret_ LoadEmpty(CProgram &Program,
				   const DOMElement *pElement, 
				   const CPDUInfo *pPDU = null_v);
	ret_ LoadUnitaryCalculate(CProgram &Program,
							  const DOMElement *pElement,
							  const CPDUInfo *pPDU = null_v);
	ret_ LoadDualityCalculate(CProgram &Program,
							  const DOMElement *pElement,
							  const CPDUInfo *pPDU = null_v);
	ret_ LoadConfigGroup(CProgram &Program,
						 const DOMElement *pElement,
						 const CPDUInfo *pPDU = null_v);
	ret_ LoadIf(CProgram &Program,
				const DOMElement *pElement,
				const CPDUInfo *pPDU = null_v);
	ret_ LoadWhile(CProgram &Program,
				   const DOMElement *pElement,
				   const CPDUInfo *pPDU = null_v);
	ret_ LoadContinue(CProgram &Program);
	ret_ LoadBlock(CProgram &Program);
	ret_ LoadBreak(CProgram &Program);
	ret_ LoadSend(CProgram &Program,
				  const DOMElement *pElement,
				  const CPDUInfo *pPDU = null_v);
	ret_ LoadReadFile(CProgram &Program,
					  const DOMElement *pElement,
					  const CPDUInfo *pPDU = null_v);
	ret_ LoadSaveFile(CProgram &Program,
					  const DOMElement *pElement,
					  const CPDUInfo *pPDU = null_v);
	ret_ LoadDeleteFile(CProgram &Program,
						const DOMElement *pElement,
						const CPDUInfo *pPDU = null_v);
	ret_ LoadSplit(CProgram &Program,
				   const DOMElement *pElement,
				   const CPDUInfo *pPDU = null_v);
	ret_ LoadDie(CProgram &Program);
	ret_ LoadShowWindow(CProgram &Program,
						const DOMElement *pElement);
	ret_ LoadWaitMessage(CProgram &Program,
						 const DOMElement *pElement);
	ret_ LoadAlert(CProgram &Program,
				   const DOMElement *pElement);
	ret_ LoadEnable(CProgram &Program,
					const DOMElement *pElement);
	ret_ LoadAddItem(CProgram &Program,
					 const DOMElement *pElement,
					 const CPDUInfo *pPDU = null_v);
	ret_ LoadVariable(const CData &Data,
					  const DOMElement *pElement,
					  CVariable *&pOV,
					  const CPDUInfo *pPDU = null_v);
	ret_ LoadSolidVariable(const CData &Data,
						   const DOMElement *pElement,
						   CVariable *&pOV);
	ret_ LoadInterfaceVariable(const CData &Data,
							   const DOMElement *pElement,
							   CVariable *&pOV);
	ret_ LoadGroupVariable(const CData &Data,
						   const DOMElement *pElement,
						   CVariable *&pOV);
	ret_ LoadNetworkVarialbe(const CData &Data,
							 const DOMElement *pElement,
							 CVariable *&pOV,
							 const CPDUInfo *pPDU);

	ret_ LoadExpression(const CData &Data,
						const DOMElement *pElement,
						CExpression *&pExpression,
						const CPDUInfo *pPDU = null_v);

	CXMLLoaderActions()
		: m_wsSolidVariable(SOLID_VARIABLE),
		  m_wsInterfaceVariable(INTERFACE_VARIABLE),
		  m_wsGroupVariable(GROUP_VARIABLE),
		  m_wsNetworkVariable(NETWORK_VARIABLE),
		  m_pTmpContainer(null_v) {}

	CXMLLoaderActions(const CXMLLoaderActions &);
	const CXMLLoaderActions &operator =(const CXMLLoaderActions &);

	static CXMLLoaderActions *m_pInstance;

	auto_xerces_str m_wsSolidVariable;
	auto_xerces_str m_wsInterfaceVariable;
	auto_xerces_str m_wsGroupVariable;
	auto_xerces_str m_wsNetworkVariable;

	CContainer *m_pTmpContainer;
};

#endif // CXML_LOADER_ACTIONS_H
