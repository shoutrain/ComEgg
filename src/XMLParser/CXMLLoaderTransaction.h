#ifndef CXML_LOADER_TRANSACTION_H
#define CXML_LOADER_TRANSACTION_H

#include "CXMLLoader.h"

class CXMLLoaderTransaction: public CXMLLoader
{
public:
	static CXMLLoaderTransaction *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CXMLLoaderTransaction;

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
					 const CPDUInfo *pPDU);
	ret_ LoadProcessBlock(CProgram &Program,
						  const DOMElement *pElement,
						  const CPDUInfo *pPDU);

	ret_ LoadEmpty(CProgram &Program,
				   const DOMElement *pElement, 
				   const CPDUInfo *pPDU);
	ret_ LoadUnitaryCalculate(CProgram &Program,
							  const DOMElement *pElement,
							  const CPDUInfo *pPDU);
	ret_ LoadDualityCalculate(CProgram &Program,
							  const DOMElement *pElement,
							  const CPDUInfo *pPDU);
	ret_ LoadConfigGroup(CProgram &Program,
						 const DOMElement *pElement,
						 const CPDUInfo *pPDU);
	ret_ LoadIf(CProgram &Program,
				const DOMElement *pElement,
				const CPDUInfo *pPDU);
	ret_ LoadWhile(CProgram &Program,
				   const DOMElement *pElement,
				   const CPDUInfo *pPDU);
	ret_ LoadContinue(CProgram &Program);
	ret_ LoadBlock(CProgram &Program);
	ret_ LoadBreak(CProgram &Program);
	ret_ LoadSend(CProgram &Program,
				  const DOMElement *pElement,
				  const CPDUInfo *pPDU);
	ret_ LoadForward(CProgram &Program,
					 const DOMElement *pElement,
					 const CPDUInfo *pPDU);
	ret_ LoadGetAddress(CProgram &Program,
						const DOMElement *pElement,
						const CPDUInfo *pPDU);
	ret_ LoadRegister(CProgram &Program,
					  const DOMElement *pElement,
					  const CPDUInfo *pPDU);
	ret_ LoadUnregister(CProgram &Program,
						const DOMElement *pElement,
						const CPDUInfo *pPDU);
	ret_ LoadSearch(CProgram &Program,
					const DOMElement *pElement,
					const CPDUInfo *pPDU);
	ret_ LoadGetUsage(CProgram &Program,
					  const DOMElement *pElement,
					  const CPDUInfo *pPDU);
	ret_ LoadNetworkWakeUp(CProgram &Program,
						   const DOMElement *pElement,
						   const CPDUInfo *pPDU);
	ret_ LoadNetworkSleep(CProgram &Program,
						  const DOMElement *pElement,
						  const CPDUInfo *pPDU);
	ret_ LoadReadFile(CProgram &Program,
					  const DOMElement *pElement,
					  const CPDUInfo *pPDU);
	ret_ LoadSaveFile(CProgram &Program,
					  const DOMElement *pElement,
					  const CPDUInfo *pPDU);
	ret_ LoadDeleteFile(CProgram &Program,
						const DOMElement *pElement,
						const CPDUInfo *pPDU);
	ret_ LoadUseModule(CProgram &Program,
					   const DOMElement *pElement,
					   const CPDUInfo *pPDU);
	ret_ LoadSplit(CProgram &Program,
				   const DOMElement *pElement,
				   const CPDUInfo *pPDU);
	ret_ LoadDie(CProgram &Program);


	ret_ LoadVariable(const CPDUInfo *pPDU,
					  const CData &Data,
					  const DOMElement *pElement,
					  CVariable *&pOV);
	ret_ LoadSolidVariable(const CData &Data,
						   const DOMElement *pElement,
						   CVariable *&pOV);
	ret_ LoadGroupVariable(const CData &Data,
						   const DOMElement *pElement,
						   CVariable *&pOV);
	ret_ LoadNetworkVarialbe(const CPDUInfo *pPDU,
							 const CData &Data,
							 const DOMElement *pElement,
							 CVariable *&pOV);

	ret_ LoadExpression(const CData &Data,
						const DOMElement *pElement,
						const CPDUInfo *pPDU, 
						CExpression *&pExpression);

	CXMLLoaderTransaction()
		: CXMLLoader(CXMLLOADERTRANSACCTION),
		  m_wsSolidVariable(SOLID_VARIABLE),
		  m_wsGroupVariable(GROUP_VARIABLE),
		  m_wsNetworkVariable(NETWORK_VARIABLE),
		  m_tmpNetworkType(NETWORK_NONE)
	{
	}

	CXMLLoaderTransaction(const CXMLLoaderTransaction &);
	const CXMLLoaderTransaction &operator =(const CXMLLoaderTransaction &);

	static CXMLLoaderTransaction *m_pInstance;

	auto_xerces_str m_wsSolidVariable;
	auto_xerces_str m_wsGroupVariable;
	auto_xerces_str m_wsNetworkVariable;

	ENetworkType m_tmpNetworkType;
};

#endif // CXML_LOADER_TRANSACTION_H
