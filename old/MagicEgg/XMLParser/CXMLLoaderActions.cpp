#include "CXMLLoaderActions.h"

#include "../UI/CContainer.h"
#include "../Tools/CAutoPtr.h"

CXMLLoaderActions *CXMLLoaderActions::m_pInstance = null_v;

ret_ CXMLLoaderActions::Load(XercesDOMParser *pParser,
							 const ch_1 *pszEnvironmentPath)
{
#ifdef _DEBUG_
	if (!pParser)
		return PARAMETER_NULL | PARAMETER_1;

	if (!pszEnvironmentPath)
		return PARAMETER_NULL | PARAMETER_2;

	if (null_v == pszEnvironmentPath[0])
		return PARAMETER_EMPTY | PARAMETER_2;
#endif

	SetParser(pParser);

	ch_1 sActions[ENVIRONMENT_PATH_LENGTH];

	memset(sActions, 0, ENVIRONMENT_PATH_LENGTH);
	sprintf(sActions, "%s%s", pszEnvironmentPath, ACTIONS_XML_FILE);

	DOMDocument *pActionsDoc = null_v;

	try
	{
		GetParser()->parse(sActions);
        pActionsDoc = GetParser()->getDocument();
	}
    catch (const OutOfMemoryException &err)
    {
		auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

 		return XML_LOADER_ERROR;
    }
	catch (const XMLException &err)
    {
		auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

 		return XML_LOADER_ERROR;
	}
    catch (const DOMException &err)
    {
		auto_xerces_str sErr(err.msg);

		printf("%s\n", (const ch_1 *)sErr);

 		return XML_LOADER_ERROR;
	}
	catch (...)
    {
		printf("Unexpected error during parsing.\n");

		return XML_LOADER_ERROR;
    }

	if (!pActionsDoc)
		return XML_LOADER_ERROR;
	
	DOMElement *pRoot = pActionsDoc->getDocumentElement();

	if (!pRoot)
		return XML_LOADER_ERROR;

	DOMElement *pChild = (DOMElement *)pRoot->getFirstChild();

	if (!pChild)
		return XML_LOADER_ERROR;

	auto_xerces_str wsDataBlock("data_block");
	auto_xerces_str wsStart("start");
	auto_xerces_str wsProcessor("processor");
	auto_xerces_str wsEnd("end");

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsDataBlock))
		{
			if (SUCCESS != LoadDataBlock(CUIManager::Instance()->Data(),
										 pChild))
			{
				return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsStart))
		{
			if (SUCCESS != LoadProgram(&CUIManager::Instance()->Data(),
									   CUIManager::Instance()->StartProgram(),
									   pChild))
			{
				return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsProcessor))
		{
			if (SUCCESS != LoadProcessor(pChild))
				return XML_LOADER_ERROR;

			m_pTmpContainer = null_v;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsEnd))
		{
			if (SUCCESS != LoadProgram(&CUIManager::Instance()->Data(),
									   CUIManager::Instance()->EndProgram(),
									   pChild))
			{
				return XML_LOADER_ERROR;
			}
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadDataBlock(CData &Data,
									  const DOMElement *pElement)
{
#ifdef _DEBUG_
	if (!pElement)
		return PARAMETER_NULL | PARAMETER_2;
#endif

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		return XML_LOADER_ERROR;

	auto_xerces_str	wsObject	("v_object");
	auto_xerces_str wsB1		("v_b_1");
	auto_xerces_str wsUB1		("v_ub_1");
	auto_xerces_str wsB2		("v_b_2");
	auto_xerces_str wsUB2		("v_ub_2");
	auto_xerces_str wsB4		("v_b_4");
	auto_xerces_str wsUB4		("v_ub_4");
	auto_xerces_str wsB8		("v_b_8");
	auto_xerces_str wsUB8		("v_ub_8");
	auto_xerces_str wsFB4		("v_fb_4");
	auto_xerces_str wsFB8		("v_fb_8");
	auto_xerces_str	wsString	("v_string");
	auto_xerces_str wsGroup		("v_group");

	auto_xerces_str	wsName		("name");
	auto_xerces_str	wsValue		("value");

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(), wsObject))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (false_v == Data.Define(sName, (obj_)null_v))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB1))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_1))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, B_1, (b_4)atoi(sValue)))
					return XML_LOADER_ERROR;
			}

		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB1))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_1))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, UB_1, (b_4)atoi(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB2))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_2))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, B_2, (b_4)atoi(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB2))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_2))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, UB_2, (b_4)atoi(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB4))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_4))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, B_4, (b_4)atoi(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB4))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_4))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, UB_4, (b_4)atoi(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB8))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_8))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, B_8, (b_8)atoll(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB8))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_8))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, UB_8, (ub_8)atoll(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsFB4))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, FB_4))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, (fb_4)atof(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsFB8))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, FB_8))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, (fb_8)atof(sValue)))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsString))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, (ch_1 *)""))
					return XML_LOADER_ERROR;
			}
			else
			{
				if (false_v == Data.Define(sName, sValue))
					return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsGroup))
		{
			auto_xerces_str wsNormal("normal");
			auto_xerces_str wsFloat	("float");
			auto_xerces_str wsString("string");

			auto_xerces_str	wsName	("name");
			auto_xerces_str	wsLength("length");
			auto_xerces_str	wsSigned("signed");
			auto_xerces_str	wsSize	("size");

			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sSize	(pChild->getAttribute(wsSize));

			CFieldGroupDefined *pGroupField = new CFieldGroupDefined(
				sName, 
				sSize);

			DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

			if (!pSub)
				return XML_LOADER_ERROR;

			while (pSub)
			{
				if (0 == XMLString::compareString(pSub->getNodeName(),
												  wsNormal))
				{
					auto_xerces_str sName (pElement->getAttribute(wsName));
					auto_xerces_str	sLength(pElement->getAttribute(wsLength));
					auto_xerces_str	sSigned(pElement->getAttribute(wsSigned));

					EFieldType Type;

					GetFieldType(
						FIELD_NORMAL_STYLE, 
						atoi(sLength), 
						0 == strcmp(sSigned, "true") ? true_v : false_v,
						Type);
					
					CFieldNumber *pField = new CFieldNumber(sName, 
															Type, 
															pGroupField);

					pGroupField->SetSubField(pField);
				}
				else if (0 == XMLString::compareString(pSub->getNodeName(),
													   wsFloat))
				{
					auto_xerces_str sName (pElement->getAttribute(wsName));
					auto_xerces_str	sLength(pElement->getAttribute(wsLength));

					EFieldType Type;

					GetFieldType(FIELD_FLOAT_STYLE, 
								 atoi(sLength), 
								 false_v, 
								 Type);
					
					CFieldNumber *pField = new CFieldNumber(sName, 
															Type, 
															pGroupField);

					pGroupField->SetSubField(pField);
				}
				else if (0 == XMLString::compareString(pSub->getNodeName(),
													   wsString))
				{
					auto_xerces_str sName (pElement->getAttribute(wsName));
					auto_xerces_str	sLength(pElement->getAttribute(wsLength));
					auto_xerces_str	sSize(pElement->getAttribute(wsSize));
					
					CFieldString *pField = new CFieldString(sName, 
															atoi(sSize), 
															pGroupField);

					pGroupField->SetSubField(pField);
				}

				pSub = (DOMElement *)pSub->getNextSibling();
			}
			
			if (false_v == Data.Define(pGroupField))
				return XML_LOADER_ERROR;
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadProcessor(const DOMElement *pElement)
{
#ifdef _DEBUG_
	if (!pElement)
		return PARAMETER_NULL | PARAMETER_2;
#endif

	//
	auto_xerces_str	wsName("name");
	auto_xerces_str wsPDU("pdu");
	auto_xerces_str sName(pElement->getAttribute(wsName));

	auto_xerces_str wsDataBlock("data_block");
	auto_xerces_str wsStart("start");
	auto_xerces_str wsOnClick("on_click");
	auto_xerces_str wsOnMessage("on_message");
	auto_xerces_str wsEnd("end");

	m_pTmpContainer = CUIManager::Instance()->GetContainer(sName);
	
	// Check if there is corresponding container, it should be exist
	if (!m_pTmpContainer)
		return XML_LOADER_ERROR;

	CProtocolInfo *pProtocol = CProtocolManager::Instance()->GetProtocol();

	// Protocol should be loaded
	if (!pProtocol)
		return XML_LOADER_ERROR;

	//
	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		return XML_LOADER_ERROR;

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsDataBlock))
		{
			if (SUCCESS != LoadDataBlock(m_pTmpContainer->Data(), pChild))
				return XML_LOADER_ERROR;

			m_pTmpContainer->Data().SetParent(&CUIManager::Instance()->Data());
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsStart))
		{
			if (SUCCESS != LoadProgram(&m_pTmpContainer->Data(),
									   m_pTmpContainer->StartProgram(),
									   pChild))
			{
				return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsOnClick))
		{
			auto_xerces_str sName(pChild->getAttribute(wsName));

			CProgram *pProgram = null_v;

			if (!m_pTmpContainer->AddOnClickProcessor(sName, pProgram))
				return XML_LOADER_ERROR;

			if (SUCCESS != LoadProgram(&m_pTmpContainer->Data(),
									   *pProgram,
									   pChild))
			{
				return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsOnMessage))
		{
			auto_xerces_str sPDU(pChild->getAttribute(wsPDU));

			CPDUInfo *pPDUInfo = null_v;

			if (SUCCESS != pProtocol->GetPDU(sPDU, pPDUInfo))
				return XML_LOADER_ERROR;

			CProgram *pProgram = null_v;

			if (!m_pTmpContainer->AddMessageProcessor(sPDU, pProgram))
				return XML_LOADER_ERROR;

			if (SUCCESS != LoadProgram(&m_pTmpContainer->Data(),
									   *pProgram,
									   pChild,
									   pPDUInfo))
			{
				return XML_LOADER_ERROR;
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsEnd))
		{
			if (SUCCESS != LoadProgram(&m_pTmpContainer->Data(),
									   m_pTmpContainer->EndProgram(),
									   pChild))
			{
				return XML_LOADER_ERROR;
			}
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadProgram(const CData *pParentData,
									CProgram &Program,
									const DOMElement *pElement,
									const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pParentData)
		return PARAMETER_NULL | PARAMETER_1;

	if (!pElement)
		return PARAMETER_NULL | PARAMETER_3;
#endif

	auto_xerces_str wsDataBlock("data_block");
	auto_xerces_str wsProcessBlock("process_block");

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		return XML_LOADER_ERROR;

	Program.Data().SetParent(pParentData);

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsDataBlock))
		{
			CData Data;

			if (SUCCESS != (LoadDataBlock(Data,  pChild)))
				return XML_LOADER_ERROR;

			Program.SetData(Data);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsProcessBlock))
		{
			if (SUCCESS != LoadProcessBlock(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadProcessBlock(CProgram &Program,
										 const DOMElement *pElement,
										 const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		return XML_LOADER_ERROR;

	auto_xerces_str wsEmpty				("empty");
	auto_xerces_str	wsUnitaryCalculate	("unitary_calculate");
	auto_xerces_str	wsDualityCalculate	("duality_calculate");
	auto_xerces_str wsConfigGroup		("config_group");
	auto_xerces_str	wsIf				("if");
	auto_xerces_str	wsWhile				("while");
	auto_xerces_str wsContinue			("continue");
	auto_xerces_str wsBlock				("block");
	auto_xerces_str wsBreak				("break");
	auto_xerces_str	wsSend				("send");
	auto_xerces_str wsReadFile			("read_file");
	auto_xerces_str wsSaveFile			("save_file");
	auto_xerces_str wsDeleteFile		("delete_file");
	auto_xerces_str wsSplit				("split");
	auto_xerces_str	wsDie				("die");
	auto_xerces_str wsShowWindow		("show_window");
	auto_xerces_str wsWaitMessage		("wait_message");
	auto_xerces_str wsAlert				("alert");
	auto_xerces_str wsEnable			("enable");
	auto_xerces_str wsAddItem			("add_item");
	auto_xerces_str wsProgram			("program");

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsEmpty))
		{
			if (SUCCESS != LoadEmpty(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsUnitaryCalculate))
		{
			if (SUCCESS != LoadUnitaryCalculate(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsDualityCalculate))
		{
			if (SUCCESS != LoadDualityCalculate(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsConfigGroup))
		{
			if (SUCCESS != LoadConfigGroup(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsIf))
		{
			if (SUCCESS != LoadIf(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsWhile))
		{
			if (SUCCESS != LoadWhile(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsContinue))
		{
			if (SUCCESS != LoadContinue(Program))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsBlock))
		{
			if (SUCCESS != LoadBlock(Program))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsBreak))
		{
			if (SUCCESS != LoadBreak(Program))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSend))
		{
			if (SUCCESS != LoadSend(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsReadFile))
		{
			if (SUCCESS != LoadReadFile(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSaveFile))
		{
			if (SUCCESS != LoadSaveFile(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsDeleteFile))
		{
			if (SUCCESS != LoadDeleteFile(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSplit))
		{
			if (SUCCESS != LoadSplit(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsDie))
		{
			if (SUCCESS != LoadDie(Program))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsShowWindow))
		{
			if (SUCCESS != LoadShowWindow(Program, pChild))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsWaitMessage))
		{
			if (SUCCESS != LoadWaitMessage(Program, pChild))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsAlert))
		{
			if (SUCCESS != LoadAlert(Program, pChild))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsEnable))
		{
			if (SUCCESS != LoadEnable(Program, pChild))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsAddItem))
		{
			if (SUCCESS != LoadAddItem(Program, pChild, pPDU))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsProgram))
		{
			CProgram *pSubProgram = new CProgram();

			if (SUCCESS != LoadProgram(&Program.Data(),
										*pSubProgram,
										pChild,
										pPDU))
            {
				return XML_LOADER_ERROR;
            }

			if (false_v == Program.AddOperator(pSubProgram))
				return XML_LOADER_ERROR;
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadEmpty(CProgram &Program,
								  const DOMElement *pElement, 
								  const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV;

	while (pSub)
	{
		ret_ Ret = LoadVariable(Program.Data(), pSub, OV.Ptr(), pPDU);
		
		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptEmpty *pOperator = new COptEmpty(OV.Ptr());

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadUnitaryCalculate(CProgram &Program,
											 const DOMElement *pElement,
											 const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	auto_xerces_str wsOperator	("operator");
	auto_xerces_str	sOperator	(pElement->getAttribute(wsOperator));

	EUnitaryCalculate Calculate;

	if (SUCCESS != GetUnitaryOperator(sOperator, Calculate))
		return XML_LOADER_ERROR;

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(Program.Data(), pSub, OV[n].Ptr(), pPDU);
		
		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptUnitaryCalculate *pOUC = new COptUnitaryCalculate(Calculate,
														  OV[0].Ptr(),
														  OV[1].Ptr());

	if (false_v == Program.AddOperator(pOUC))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadDualityCalculate(CProgram &Program,
											 const DOMElement *pElement,
											 const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	//
	auto_xerces_str wsOperator	("operator");
	auto_xerces_str	sOperator	(pElement->getAttribute(wsOperator));

	EDualityCalculate Calculate;

	if (SUCCESS != GetDualityOperator(sOperator, Calculate))
		return XML_LOADER_ERROR;

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV[3];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(Program.Data(), pSub, OV[n].Ptr(), pPDU);

		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			if (3 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptDualityCalculate *pODC = new COptDualityCalculate(
		OV[0].Ptr(),
		Calculate,
		OV[1].Ptr(),
		OV[2].Ptr());

	if (false_v == Program.AddOperator(pODC))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadConfigGroup(CProgram &Program,
										const DOMElement *pElement,
										const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		if (0 == XMLString::compareString(pSub->getNodeName(),
										  m_wsGroupVariable))
		{
			if (SUCCESS != LoadGroupVariable(Program.Data(),
											 pElement,
											 OV[0].Ptr()))
			{
				return XML_LOADER_ERROR;
			}

			n++;
			break;
		}

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	pSub = (DOMElement *)pSub->getNextSibling();

	while (pSub)
	{
		if (0 == XMLString::compareString(pSub->getNodeName(),
										  m_wsSolidVariable))
		{
			if (SUCCESS != LoadSolidVariable(Program.Data(), 
											 pElement, 
											 OV[1].Ptr()))
			{
				return XML_LOADER_ERROR;
			}

			n++;
			break;
		}

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (2 != n)
		return XML_LOADER_ERROR;

	COptConfigGroup *pOperator = new COptConfigGroup(OV[0].Ptr(), OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadIf(CProgram &Program,
							   const DOMElement *pElement,
							   const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	auto_xerces_str wsDataBlock			("data_block");
	auto_xerces_str wsExpressionUnitary	("expression_unitary");
	auto_xerces_str wsExpressionDuality	("expression_duality");
	auto_xerces_str wsConditionUnitary	("condition_unitary");
	auto_xerces_str wsConditionDuality	("condition_duality");
	auto_xerces_str wsProgram			("program");

	CProgramIf *pPI = new CProgramIf();

	pPI->Data().SetParent(&Program.Data());
	
	while (pSub)
	{
		if (0 == XMLString::compareString(pSub->getNodeName(),
										  wsDataBlock))
		{
			CData Data;

			if (SUCCESS != (LoadDataBlock(Data, pSub)))
				return XML_LOADER_ERROR;

			pPI->SetData(Data);
		}
		else if (0 == XMLString::compareString(pSub->getNodeName(),
											   wsExpressionUnitary)
				 || 0 == XMLString::compareString(pSub->getNodeName(),
												  wsExpressionDuality)
				 || 0 == XMLString::compareString(pSub->getNodeName(),
												  wsConditionUnitary)
				 || 0 == XMLString::compareString(pSub->getNodeName(),
												  wsConditionDuality))
		{
			CExpression *pExpression = null_v;

			if (SUCCESS != LoadExpression(pPI->Data(),
										  pSub,
										  pExpression,
										  pPDU))
			{
				return XML_LOADER_ERROR;
			}

			if (false_v == pPI->AddExpression(pExpression))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pSub->getNodeName(),
											   wsProgram))
		{
			CProgram *pProgram = new CProgram();

			if (SUCCESS != LoadProgram(&pPI->Data(),
									   *pProgram,
									   pSub,
									   pPDU))
			{
				return XML_LOADER_ERROR;
			}

			if (false_v == pPI->AddOperator(pProgram))
				return XML_LOADER_ERROR;
		}

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (false_v == Program.AddOperator(pPI))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadWhile(CProgram &Program,
								  const DOMElement *pElement,
								  const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_3);
#endif

	auto_xerces_str	wsPosition	("position");
	auto_xerces_str	sPosition	(pElement->getAttribute(wsPosition));
	bool_			b = true_v;

	if (0 == strcmp(sPosition, "head"))
		b = true_v;
	else if (0 == strcmp(sPosition, "foot"))
		b = false_v;

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	auto_xerces_str wsDataBlock			("data_block");
	auto_xerces_str wsExpressionUnitary	("expression_unitary");
	auto_xerces_str wsExpressionDuality	("expression_duality");
	auto_xerces_str wsConditionUnitary	("condition_unitary");
	auto_xerces_str wsConditionDuality	("condition_duality");
	auto_xerces_str wsProcessBlock		("process_block");

	CData Data;
	CExpression *pExpression = null_v;
	CProgramWhile *pPW = null_v;

	Data.SetParent(&Program.Data());

	while (pSub)
	{
		if (0 == XMLString::compareString(pSub->getNodeName(),
										  wsDataBlock))
		{
			if (SUCCESS != (LoadDataBlock(Data, pSub)))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pSub->getNodeName(),
											   wsExpressionUnitary)
				 || 0 == XMLString::compareString(pSub->getNodeName(),
												  wsExpressionDuality)
				 || 0 == XMLString::compareString(pSub->getNodeName(),
												  wsConditionUnitary)
				 || 0 == XMLString::compareString(pSub->getNodeName(),
												  wsConditionDuality))
		{
			if (SUCCESS != LoadExpression(Data, pSub, pExpression, pPDU))
				return XML_LOADER_ERROR;
			
			pPW = new CProgramWhile(b, pExpression, &Data);
			pPW->Data().SetParent(&Program.Data());
		}
		else if (0 == XMLString::compareString(pSub->getNodeName(),
											   wsProcessBlock))
		{
			if (!pPW)
				return XML_LOADER_ERROR;
			
			if (SUCCESS != LoadProcessBlock(*pPW, pSub, pPDU))
				return XML_LOADER_ERROR;
		}

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (false_v == Program.AddOperator(pPW))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadContinue(CProgram &Program)
{
	COptContinue *pOperator = new COptContinue();

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadBlock(CProgram &Program)
{
	COptContinue *pOperator = new COptContinue();

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadBreak(CProgram &Program)
{
	COptContinue *pOperator = new COptContinue();

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadSend(CProgram &Program,
								 const DOMElement *pElement,
								 const CPDUInfo *pPDU)

{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	//
	CProtocolInfo *pProtocol = CProtocolManager::Instance()->GetProtocol();

	//
	auto_xerces_str	wsPDU	("pdu");
	auto_xerces_str	sPDU	(pElement->getAttribute(wsPDU));

	CPDUInfo *pPDUInfo = null_v;

	if (SUCCESS != (pProtocol->GetPDU(sPDU, pPDUInfo)))
		return XML_LOADER_ERROR;

	COptSend *pOperator = new COptSend(pPDUInfo);
	
	// For send operation, sub elements are not necessary.
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (pSub)
	{
		auto_xerces_str wsFieldVariable("field_variable");
		auto_xerces_str	wsFieldName("field_name");

		while (pSub)
		{
			if (0 == XMLString::compareString(pSub->getNodeName(), wsFieldVariable))
			{
				//
				DOMElement	*pVariable = (DOMElement *)pSub->getFirstChild();
				CAutoPtr<CVariable> OV_;

				if (!pVariable)
					return XML_LOADER_ERROR;

				while (pVariable)
				{
					ret_ Ret = LoadVariable(Program.Data(), 
											pVariable, 
											OV_.Ptr(),
											pPDU);

					if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
						return Ret;

					if (SUCCESS == Ret)
						break;

					pVariable = (DOMElement *)pVariable->getNextSibling();
				}

				//
				auto_xerces_str	sFieldName(pSub->getAttribute(wsFieldName));
				CField *pField = null_v;
			
				if (SUCCESS != pPDUInfo->GetField(sFieldName, pField))
					return XML_LOADER_ERROR;
			
				//
				if (false_v == pOperator->AddEvaluate(sFieldName, OV_.Ptr()))
					return XML_LOADER_ERROR;
			}

			pSub = (DOMElement *)pSub->getNextSibling();
		}
	}

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadReadFile(CProgram &Program,
									 const DOMElement *pElement,
									 const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV[3];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(Program.Data(), pSub, OV[n].Ptr(), pPDU);

		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			if (3 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (n != 3)
		return XML_LOADER_ERROR;

	COptReadFile *pOperator = new COptReadFile(OV[0].Ptr(),
											   OV[1].Ptr(),
											   OV[2].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadSaveFile(CProgram &Program,
									 const DOMElement *pElement,
									 const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV[4];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(Program.Data(), pSub, OV[n].Ptr(), pPDU);

		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			if (4 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptSaveFile *pOperator = new COptSaveFile(OV[0].Ptr(),
											   OV[1].Ptr(),
											   OV[2].Ptr(),
											   OV[3].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadDeleteFile(CProgram &Program,
									   const DOMElement *pElement,
									   const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(Program.Data(), pSub, OV[n].Ptr(), pPDU);

		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptDeleteFile *pOperator = new COptDeleteFile(OV[0].Ptr(),
												   OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadSplit(CProgram &Program,
								  const DOMElement *pElement,
								  const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(Program.Data(), pSub, OV[n].Ptr(), pPDU);

		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptSplit *pOperator = new COptSplit(OV[0].Ptr(),
										 OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadDie(CProgram &Program)
{
	COptDie *pOperator = new COptDie();

	if (false_v == Program.AddOperator(pOperator))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadShowWindow(CProgram &Program,
									   const DOMElement *pElement)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	auto_xerces_str wsName("name");
	auto_xerces_str sName(pElement->getAttribute(wsName));
	
	// Check if there is the container identified by the attribute
	if (!CUIManager::Instance()->GetContainer(sName))
		return XML_LOADER_ERROR;
	
	COptShowWindow *pOpt = new COptShowWindow(sName);

	if (false_v == Program.AddOperator(pOpt))
		return XML_LOADER_ERROR;
	
	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadWaitMessage(CProgram &Program,
										const DOMElement *pElement)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif
	
	auto_xerces_str wsPDU("pdu");
	auto_xerces_str sPDU(pElement->getAttribute(wsPDU));
	CPDUInfo *pPDUInfo = null_v;

	// Check if there is the pdu identified by the attribute
	if (SUCCESS != CProtocolManager::Instance()->GetProtocol()->GetPDU(
			sPDU, pPDUInfo))
	{
		return XML_LOADER_ERROR;
	}
	
	COptWaitMessage *pOpt = new COptWaitMessage(sPDU);
	
	if (false_v == Program.AddOperator(pOpt))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadAlert(CProgram &Program,
								  const DOMElement *pElement)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif
	
	auto_xerces_str wsMessage("message");
	auto_xerces_str sMessage(pElement->getAttribute(wsMessage));
	COptAlert *pOpt = new COptAlert(sMessage);

	if (false_v == Program.AddOperator(pOpt))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadEnable(CProgram &Program,
								   const DOMElement *pElement)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif
	auto_xerces_str wsName("name");
	auto_xerces_str sName(pElement->getAttribute(wsName));
	
	// Check if there is the container
	if (!m_pTmpContainer)
		return XML_LOADER_ERROR;

	// Check if there is the button identified by the attribute
	CWindow *pWindow = m_pTmpContainer->GetChild(sName);

	if (!pWindow || WINDOW_BUTTON != pWindow->Type())
		return XML_LOADER_ERROR;

	auto_xerces_str wsEnable("enable");
	auto_xerces_str sEnable(pElement->getAttribute(wsEnable));
	bool_ bEnble = (0 == strcmp(sEnable, "true")) ? true_v : false_v;
	
	COptEnable *pOpt = new COptEnable(sName, bEnble);

	if (false_v == Program.AddOperator(pOpt))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadAddItem(CProgram &Program,
									const DOMElement *pElement,
									const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	auto_xerces_str wsName("name");
	auto_xerces_str sName(pElement->getAttribute(wsName));
	
	// Check if there is the container
	if (!m_pTmpContainer)
		return XML_LOADER_ERROR;

	// Check if there is the table identified by the attribute
	CWindow *pWindow = m_pTmpContainer->GetChild(sName);

	if (!pWindow || WINDOW_TABLE != pWindow->Type())
		return XML_LOADER_ERROR;

	COptAddItem *pOpt = new COptAddItem(sName);

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		return XML_LOADER_ERROR;

	while (pSub)
	{
		CVariable *pV = null_v;
		ret_ Ret = LoadVariable(Program.Data(),
								pSub,
								pV,
								pPDU);

		if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
			return Ret;

		if (SUCCESS == Ret)
			pOpt->AddVariable(pV);
		
		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (false_v == Program.AddOperator(pOpt))
		return XML_LOADER_ERROR;

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadVariable(const CData &Data,
									 const DOMElement *pElement,
									 CVariable *&pOV,
									 const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return PARAMETER_NULL | PARAMETER_2;

	if (pOV)
		return PARAMETER_NOT_NULL | PARAMETER_3;
#endif

	if (0 == XMLString::compareString(pElement->getNodeName(),
									  m_wsSolidVariable))
	{
		if (SUCCESS != LoadSolidVariable(Data, pElement, pOV))
			return XML_LOADER_ERROR;
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   m_wsInterfaceVariable))
	{
		if (!m_pTmpContainer)
			return XML_LOADER_ERROR;
		
		if (SUCCESS != LoadInterfaceVariable(Data, pElement, pOV))
			return XML_LOADER_ERROR;
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   m_wsGroupVariable))
	{
		if (SUCCESS != LoadGroupVariable(Data, pElement, pOV))
			return XML_LOADER_ERROR;
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   m_wsNetworkVariable))
	{
		if (!pPDU)
			return XML_LOADER_ERROR;
		
		if (SUCCESS != LoadNetworkVarialbe(Data, pElement, pOV, pPDU))
			return XML_LOADER_ERROR;
	}
	else
	{
		return XML_INVALID_ELEMENT;
	}

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadSolidVariable(const CData &Data,
										  const DOMElement *pElement,
										  CVariable *&pOV)
{
#ifdef _DEBUG_
	if (!pElement)
		return PARAMETER_NULL | PARAMETER_2;

	if (pOV)
		return PARAMETER_NOT_NULL | PARAMETER_3;
#endif

	auto_xerces_str	wsName("name");
	auto_xerces_str	sName(pElement->getAttribute(wsName));

	v_ *pV = Data.Value(sName);

	if (!pV)
		return XML_LOADER_ERROR;

	pOV = new CVarSolidDefined((const ch_1 *)sName);

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadInterfaceVariable(const CData &Data,
											  const DOMElement *pElement,
											  CVariable *&pOV)
{
#ifdef _DEBUG_
	if (!pElement)
		return PARAMETER_NULL | PARAMETER_2;

	if (pOV)
		return PARAMETER_NOT_NULL | PARAMETER_3;
#endif

	auto_xerces_str	wsName("name");
	auto_xerces_str	sName(pElement->getAttribute(wsName));

	// The corresponding widnow should be loaded already
	if (!m_pTmpContainer->GetChild(sName))
		return XML_LOADER_ERROR;

	pOV = new CVarInterface((const ch_1 *)sName);
	
	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadGroupVariable(const CData &Data,
										  const DOMElement *pElement,
										  CVariable *&pOV)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);

	if (pOV)
		return (PARAMETER_NOT_NULL | PARAMETER_3);
#endif
	auto_xerces_str wsGroupName	("group_name");
	auto_xerces_str wsFieldName	("field_name");
	auto_xerces_str wsIndex		("index");

	auto_xerces_str sGroupName	(pElement->getAttribute(wsGroupName));
	auto_xerces_str	sFieldName	(pElement->getAttribute(wsFieldName));
	auto_xerces_str sIndex		(pElement->getAttribute(wsIndex));

	ch_1 szName[VARIABLE_NAME_LENGTH * 2];
	const char *pszSubName = null_v;
	const char *pszIndexName = null_v;

	memset(szName, 0, VARIABLE_NAME_LENGTH * 2);

	if (0 < strlen(sFieldName))
	{
		sprintf(szName, 
				"%s.%s", 
				(const ch_1 *)sGroupName, 
				(const ch_1 *)sFieldName);
		pszSubName = sFieldName;
	}
	else
	{
		sprintf(szName, "%s", (const ch_1 *)sGroupName);
	}

	v_ *pV = Data.Value(szName);

	if (!pV)
		return XML_LOADER_ERROR; // There is no variable defined above

	if (0 != strcmp(sIndex, SIGN_UNBOUNDED))
		pszIndexName = sIndex;

	pOV = new CVarGroupDefined(sGroupName, pszSubName, pszIndexName);

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadNetworkVarialbe(const CData &Data,
											const DOMElement *pElement,
											CVariable *&pOV,
											const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return PARAMETER_NULL | PARAMETER_2;

	if (pOV)
		return PARAMETER_NOT_NULL | PARAMETER_3;
	
	if (!pPDU)
		return PARAMETER_NULL | PARAMETER_4;
#endif

	//
	auto_xerces_str wsGroupName	("group_name");
	auto_xerces_str wsFieldName	("field_name");
	auto_xerces_str wsIndex		("index");

	auto_xerces_str sGroupName	(pElement->getAttribute(wsGroupName));
	auto_xerces_str	sFieldName	(pElement->getAttribute(wsFieldName));
	auto_xerces_str sIndex		(pElement->getAttribute(wsIndex));

	ch_1 szName[VARIABLE_NAME_LENGTH * 2];

	memset(szName, 0, VARIABLE_NAME_LENGTH * 2);

	if (0 < strlen(sGroupName))
	{
		
		sprintf(szName, 
				"%s.%s", 
				(const ch_1 *)sGroupName, 
				(const ch_1 *)sFieldName);
	}
	else
	{
		sprintf(szName, "%s", (const ch_1 *)sFieldName);
	}

	CField *pField = null_v;

	if (SUCCESS != (((CPDUInfo *)pPDU)->GetField(szName, pField)))
		return XML_LOADER_ERROR;

	if (0 == strcmp(sIndex, SIGN_UNBOUNDED))
		pOV = new CVarNetwork(pField);
	else
		pOV = new CVarNetwork(pField, sIndex);

	return SUCCESS;
}

ret_ CXMLLoaderActions::LoadExpression(const CData &Data,
									   const DOMElement *pElement,
									   CExpression *&pExpression,
									   const CPDUInfo *pPDU)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_2);

	if (pExpression)
		return (PARAMETER_NOT_NULL | PARAMETER_3);
#endif

	auto_xerces_str wsExpressionUnitary	("expression_unitary");
	auto_xerces_str wsExpressionDuality	("expression_duality");
	auto_xerces_str wsConditionUnitary	("condition_unitary");
	auto_xerces_str wsConditionDuality	("condition_duality");
	auto_xerces_str wsCalculate			("calculate");
	auto_xerces_str wsRelation			("relation");

	if (0 == XMLString::compareString(pElement->getNodeName(),
									  wsExpressionUnitary))
	{
		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			return XML_LOADER_ERROR;

		CExpression *pExp = null_v;

		while (pChild)
		{
			if (0 == XMLString::compareString(pChild->getNodeName(),
											  wsExpressionUnitary)
				|| 0 == XMLString::compareString(pChild->getNodeName(),
												 wsExpressionDuality)
				|| 0 == XMLString::compareString(pChild->getNodeName(),
												 wsConditionUnitary)
				|| 0 == XMLString::compareString(pChild->getNodeName(),
												 wsConditionDuality))
			{
				if (SUCCESS != LoadExpression(Data, pChild, pExp, pPDU))
					return XML_LOADER_ERROR;

				break;
			}

			pChild = (DOMElement *)pChild->getNextSibling();
		}

		if (!pExp)
			return XML_LOADER_ERROR;

		pExpression = (CExpression *)new CExpNot(pExp);
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   wsExpressionDuality))
	{
		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			return XML_LOADER_ERROR;

		size_ n = 0;
		CExpression *pExp[2] = {null_v, null_v};

		while (pChild)
		{
			if (2 <= n)
				break;

			if (0 == XMLString::compareString(pChild->getNodeName(),
											  wsExpressionUnitary)
				|| 0 == XMLString::compareString(pChild->getNodeName(),
												 wsExpressionDuality)
				|| 0 == XMLString::compareString(pChild->getNodeName(),
												 wsConditionUnitary)
				|| 0 == XMLString::compareString(pChild->getNodeName(),
												 wsConditionDuality))
			{
				if (SUCCESS != LoadExpression(Data, pChild, pExp[n++], pPDU))
					return XML_LOADER_ERROR;
			}

			pChild = (DOMElement *)pChild->getNextSibling();
		}

		if (2 != n)
			return XML_LOADER_ERROR;

		auto_xerces_str sRelation(pElement->getAttribute(wsRelation));

		if (0 == strcmp((const ch_1 *)sRelation, "and"))
			pExpression = (CExpression *)new CExpAnd(pExp[0], pExp[1]);
		else if (0 == strcmp((const ch_1 *)sRelation, "or"))
			pExpression = (CExpression *)new CExpOr(pExp[0], pExp[1]);
		else
			return XML_LOADER_ERROR;
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   wsConditionUnitary))
	{
		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			return XML_LOADER_ERROR;

		CAutoPtr<CVariable> v;

		while (pChild)
		{
			ret_ Ret = LoadVariable(Data, pChild, v.Ptr(), pPDU);
		
			if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
				return Ret;

			if (SUCCESS == Ret)
				break;

			pChild = (DOMElement *)pChild->getNextSibling();
		}

		pExpression = new CExpVarUnitary(v.Ptr());
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   wsConditionDuality))
	{
		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			return XML_LOADER_ERROR;

		CAutoPtr<CVariable> v[2];
		size_ n = 0;

		while (pChild)
		{
			ret_ Ret = LoadVariable(Data, pChild, v[n].Ptr(), pPDU);
		
			if (SUCCESS != Ret && XML_INVALID_ELEMENT != Ret)
				return Ret;

			if (SUCCESS == Ret)
				if (2 <= ++n)
					break;

			pChild = (DOMElement *)pChild->getNextSibling();
		}

		auto_xerces_str sOperator(pElement->getAttribute(wsCalculate));
		ECompareCalculate Calculate;

		if (SUCCESS != GetCompareOperator((const ch_1 *)sOperator, Calculate))
			return XML_LOADER_ERROR;

		pExpression = new CExpVarDuality(v[0].Ptr(), Calculate, v[1].Ptr());
	}

	return SUCCESS;
}
