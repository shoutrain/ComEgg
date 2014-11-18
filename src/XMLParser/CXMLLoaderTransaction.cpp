#include "CXMLLoaderTransaction.h"

#include "../Tools/CAutoPtr.h"

CXMLLoaderTransaction *CXMLLoaderTransaction::m_pInstance = null_v;

ret_ CXMLLoaderTransaction::Load(XercesDOMParser *pParser,
								 const ch_1 *pszEnvironmentPath)
{
	_START(LOAD);

#ifdef _DEBUG_
	if (!pParser)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pszEnvironmentPath)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (null_v == pszEnvironmentPath[0])
		_RET(PARAMETER_EMPTY | PARAMETER_2);
#endif

	SetParser(pParser);

	ch_1 sTransaction[ENVIRONMENT_PATH_LENGTH];

	memset(sTransaction, 0, ENVIRONMENT_PATH_LENGTH);
	strncpy(sTransaction, pszEnvironmentPath, ENVIRONMENT_PATH_LENGTH);
	strncat(sTransaction, TRANSACION_XML_FILE, ENVIRONMENT_PATH_LENGTH);

	DOMDocument *pTransactionDoc = null_v;

	try
	{
		GetParser()->parse(sTransaction);
        pTransactionDoc = GetParser()->getDocument();
	}
    catch (const OutOfMemoryException &err)
    {
		auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

 		_RET(XML_LOADER_ERROR);
    }
	catch (const XMLException &err)
    {
		auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

 		_RET(XML_LOADER_ERROR);
	}
    catch (const DOMException &err)
    {
		auto_xerces_str sErr(err.msg);

		printf("%s\n", (const ch_1 *)sErr);

 		_RET(XML_LOADER_ERROR);
	}
	catch (...)
    {
		printf("Unexpected error during parsing.\n");

		_RET(XML_LOADER_ERROR);
    }

	DOMElement *pRoot = pTransactionDoc->getDocumentElement();

	if (!pRoot)
		_RET(XML_LOADER_ERROR);

	DOMElement *pChild = (DOMElement *)pRoot->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

	auto_xerces_str wsDataBlock("data_block");
	auto_xerces_str wsProcessor("processor");

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsDataBlock))
		{
			if (SUCCESS != _ERR(LoadDataBlock(
									CTransactionManager::Instance()->Data(),
									pChild)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsProcessor))
		{
			if (SUCCESS != _ERR(LoadProcessor(pChild)))
				_RET(XML_LOADER_ERROR);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}


	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadDataBlock(CData &Data,
										  const DOMElement *pElement)
{
	_START(LOAD_DATA_BLOCK);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);
#endif

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

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
				_RET(XML_LOADER_ERROR);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB1))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_1))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, B_1, (b_4)atoi(sValue)))
					_RET(XML_LOADER_ERROR);
			}

		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB1))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_1))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, UB_1, (b_4)atoi(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB2))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_2))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, B_2, (b_4)atoi(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB2))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_2))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, UB_2, (b_4)atoi(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB4))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_4))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, B_4, (b_4)atoi(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB4))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_4))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, UB_4, (b_4)atoi(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsB8))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, B_8))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, B_8, (b_8)atoll(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsUB8))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, UB_8))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, UB_8, (ub_8)atoll(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsFB4))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, FB_4))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, (fb_4)atof(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsFB8))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, FB_8))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, (fb_8)atof(sValue)))
					_RET(XML_LOADER_ERROR);
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsString))
		{
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sValue	(pChild->getAttribute(wsValue));

			if (0 == strcmp(sValue, SIGN_UNBOUNDED))
			{
				if (false_v == Data.Define(sName, (ch_1 *)""))
					_RET(XML_LOADER_ERROR);
			}
			else
			{
				if (false_v == Data.Define(sName, sValue))
					_RET(XML_LOADER_ERROR);
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
				sName, sSize);

			DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

			if (!pSub)
				_RET(XML_LOADER_ERROR);

			while (pSub)
			{
				if (0 == XMLString::compareString(pSub->getNodeName(),
												  wsNormal))
				{
					auto_xerces_str sName(pSub->getAttribute(wsName));
					auto_xerces_str	sLength(pSub->getAttribute(wsLength));
					auto_xerces_str	sSigned(pSub->getAttribute(wsSigned));

					bool_ bSigned = 
						(0 == strcmp(sSigned, "true") ? true_v : false_v);
					EFieldType Type;

					GetFieldType(FIELD_NORMAL_STYLE, 
								 atoi(sLength), 
								 bSigned, 
								 Type);
					
					CFieldNumber *pField = new CFieldNumber(sName, 
															Type, 
															pGroupField);

					pGroupField->SetSubField(pField);
				}
				else if (0 == XMLString::compareString(pSub->getNodeName(),
													   wsFloat))
				{
					auto_xerces_str sName (pSub->getAttribute(wsName));
					auto_xerces_str	sLength(pSub->getAttribute(wsLength));

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
					auto_xerces_str sName (pSub->getAttribute(wsName));
					auto_xerces_str	sLength(pSub->getAttribute(wsLength));
					auto_xerces_str	sSize(pSub->getAttribute(wsSize));
					
					CFieldString *pField = new CFieldString(sName, 
															atoi(sSize), 
															pGroupField);

					pGroupField->SetSubField(pField);
				}

				pSub = (DOMElement *)pSub->getNextSibling();
			}
			
			if (false_v == Data.Define(pGroupField))
				_RET(XML_LOADER_ERROR);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadProcessor(const DOMElement *pElement)
{
	_START(LOAD_PROCESSOR);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);
#endif

	//
	CProcessor Processor;

	Processor.Data().SetParent(&CTransactionManager::Instance()->Data());
	
	auto_xerces_str	wsName	("name");
	auto_xerces_str sName	(pElement->getAttribute(wsName));

	auto_xerces_str wsDataBlock		("data_block");
	auto_xerces_str wsStartHandle	("start_handle");
	auto_xerces_str wsOverHandle	("over_handle");
	auto_xerces_str wsHandle		("handle");
	auto_xerces_str wsElseInHandle	("else_in_handle");
	auto_xerces_str wsElseOutHandle	("else_out_handle");

	if (true_v == CTransactionManager::Instance()->IsTransactionReady(sName))
		_RET(XML_LOADER_ERROR);

	CNetwork *pNetwork =
		(CNetwork *)CNetworkManager::Instance()->GetNetwork(sName);

#ifdef _DEBUG_
	if (!pNetwork)
		_RET(XML_LOADER_ERROR);

	if (NETWORK_NONE == (m_tmpNetworkType = pNetwork->GetType()))
		_RET(XML_LOADER_ERROR);
#endif

	CNetworkConf *pConf = (CNetworkConf *)pNetwork->GetConf();

#ifdef _DEBUG_
	if (!pConf)
		_RET(XML_LOADER_ERROR);
#endif

	CProtocolInfo *pProtocol = (CProtocolInfo *)pConf->GetProtocol();

#ifdef _DEBUG_
	if (!pProtocol)
		_RET(XML_LOADER_ERROR);
#endif

	//
	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsDataBlock))
		{
			CData Data;

			if (SUCCESS != _ERR(LoadDataBlock(Data,
											  pChild)))
			{
				_RET(XML_LOADER_ERROR);
			}

			Processor.SetData(Data);
			Processor.Data().SetParent(
				&CTransactionManager::Instance()->Data());
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsStartHandle))
		{
			CProgram Program;

			if (SUCCESS != _ERR(LoadProgram(&Processor.Data(),
											Program,
											pChild,
											null_v)))
			{
				_RET(XML_LOADER_ERROR);
			}

			Processor.SetNormalHandle(Program, START_HANDLE);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsOverHandle))
		{
			CProgram Program;

			if (SUCCESS != _ERR(LoadProgram(&Processor.Data(),
											Program,
											pChild,
											null_v)))
			{
				_RET(XML_LOADER_ERROR);
			}

			Processor.SetNormalHandle(Program, OVER_HANDLE);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsHandle))
		{
			//
			auto_xerces_str wsIdentity	("identity");
			auto_xerces_str sIdentity 	(pChild->getAttribute(wsIdentity));
			ch_1 			*sLastName = null_v;

			if (SUCCESS != _ERR(GetLastName(sIdentity, sLastName)))
				_RET(XML_LOADER_ERROR);

			CPDUInfo *pPDUInfo = null_v;

			if (SUCCESS != _ERR(pProtocol->GetPDU(sLastName, pPDUInfo)))
				_RET(XML_LOADER_ERROR);

			CProgram Program;

			if (SUCCESS != _ERR(LoadProgram(&Processor.Data(),
											Program,
											pChild,
											pPDUInfo)))
			{
				_RET(XML_LOADER_ERROR);
			}

			//
			auto_xerces_str wsDirection	("direction");
			auto_xerces_str	sDirection 	(pChild->getAttribute(wsDirection));

			EDirection Direction;

			if (SUCCESS != _ERR(GetDirection(sDirection, Direction)))
				_RET(XML_LOADER_ERROR);

			//
			if (SUCCESS != _ERR(Processor.SetMsgHandle(Program,
													   Direction,
													   pPDUInfo)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsElseInHandle))
		{
			CProgram Program;

			if (SUCCESS != _ERR(LoadProgram(&Processor.Data(),
											Program,
											pChild,
											null_v)))
			{
				_RET(XML_LOADER_ERROR);
			}

			Processor.SetNormalHandle(Program, DEFAULT_IN_HANDLE);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsElseOutHandle))
		{
			CProgram Program;

			if (SUCCESS != _ERR(LoadProgram(&Processor.Data(),
											Program,
											pChild,
											null_v)))
			{
				_RET(XML_LOADER_ERROR);
			}

			Processor.SetNormalHandle(Program, DEFAULT_OUT_HANDLE);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	switch (pNetwork->GetType())
	{
	case NETWORK_ACCEPTOR:
		if (SUCCESS != _ERR(CTransactionManager::Instance()->AddTransaction(
								sName,
								Processor,
								((CAcceptorConf *)pConf)->GetMaxConnection())))
		{
			_RET(XML_LOADER_ERROR);
		}

		break;

	case NETWORK_CONNECTOR:
	case NETWORK_RECEIVER:
	case NETWORK_SENDER:
		if (SUCCESS != _ERR(CTransactionManager::Instance()->AddTransaction(
								sName,
								Processor,
								1)))
		{
			_RET(XML_LOADER_ERROR);
		}

		break;

#ifdef _DEBUG_
	default:
		_RET(XML_LOADER_ERROR);
#endif
	}

	CTransaction *pTransaction = null_v;

	if (SUCCESS != _ERR(CTransactionManager::Instance()->GetTransaction(
							sName,
							pTransaction)))
	{
		_RET(XML_LOADER_ERROR);
	}

	pConf->SetTransaction(pTransaction);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadProgram(const CData *pParentData,
										CProgram &Program,
										const DOMElement *pElement,
										const CPDUInfo *pPDU)
{
	_START(LOAD_PROGRAM);

#ifdef _DEBUG_
	if (!pParentData)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_3);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_4);
#endif

	auto_xerces_str wsDataBlock		("data_block");
	auto_xerces_str wsProcessBlock	("process_block");

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

	Program.Data().SetParent(pParentData);
	
	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(), wsDataBlock))
		{
			CData Data;

			if (SUCCESS != _ERR(LoadDataBlock(Data,  pChild)))
				_RET(XML_LOADER_ERROR);

			Program.SetData(Data);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsProcessBlock))
		{
			if (SUCCESS != _ERR(LoadProcessBlock(Program,
												 pChild,
												 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadProcessBlock(CProgram &Program,
											 const DOMElement *pElement,
											 const CPDUInfo *pPDU)
{
	_START(LOAD_PROCESS_BLOCK);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

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
	auto_xerces_str	wsForward			("forward");
	auto_xerces_str	wsGetAddress		("get_address");
	auto_xerces_str	wsRegister			("register");
	auto_xerces_str	wsUnregister		("unregister");
	auto_xerces_str	wsSearch			("search");
	auto_xerces_str wsGetUsage			("get_usage");
	auto_xerces_str wsNetworkWakeUp		("network_wake_up");
	auto_xerces_str wsNetworkSleep		("network_sleep");
	auto_xerces_str wsReadFile			("read_file");
	auto_xerces_str wsSaveFile			("save_file");
	auto_xerces_str wsDeleteFile		("delete_file");
	auto_xerces_str wsUseModule			("use_module");
	auto_xerces_str wsSplit				("split");
	auto_xerces_str	wsDie				("die");
	auto_xerces_str wsProgram			("program");

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsEmpty))
		{
			if (SUCCESS != _ERR(LoadEmpty(Program,
										  pChild,
										  pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsUnitaryCalculate))
		{
			if (SUCCESS != _ERR(LoadUnitaryCalculate(Program,
													 pChild,
													 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsDualityCalculate))
		{
			if (SUCCESS != _ERR(LoadDualityCalculate(Program,
													 pChild,
													 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsConfigGroup))
		{
			if (SUCCESS != _ERR(LoadConfigGroup(Program,
												pChild,
												pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsIf))
		{
			if (SUCCESS != _ERR(LoadIf(Program,
									   pChild,
									   pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsWhile))
		{
			if (SUCCESS != _ERR(LoadWhile(Program,
										  pChild,
										  pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsContinue))
		{
			if (SUCCESS != _ERR(LoadContinue(Program)))
				_RET(XML_LOADER_ERROR);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsBlock))
		{
			if (SUCCESS != _ERR(LoadBlock(Program)))
				_RET(XML_LOADER_ERROR);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsBreak))
		{
			if (SUCCESS != _ERR(LoadBreak(Program)))
				_RET(XML_LOADER_ERROR);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSend))
		{
			if (SUCCESS != _ERR(LoadSend(Program,
										 pChild,
										 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsForward))
		{
			if (SUCCESS != _ERR(LoadForward(Program,
											pChild,
											pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsGetAddress))
		{
			if (SUCCESS != _ERR(LoadGetAddress(Program,
											   pChild,
											   pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsRegister))
		{
			if (SUCCESS != _ERR(LoadRegister(Program,
											 pChild,
											 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsUnregister))
		{
			if (SUCCESS != _ERR(LoadUnregister(Program,
											   pChild,
											   pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSearch))
		{
			if (SUCCESS != _ERR(LoadSearch(Program,
										   pChild,
										   pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsGetUsage))
		{
			if (SUCCESS != _ERR(LoadGetUsage(Program,
											 pChild,
											 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsNetworkWakeUp))
		{
			if (SUCCESS != _ERR(LoadNetworkWakeUp(Program,
												  pChild,
												  pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsNetworkSleep))
		{
			if (SUCCESS != _ERR(LoadNetworkSleep(Program,
												 pChild,
												 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsReadFile))
		{
			if (SUCCESS != _ERR(LoadReadFile(Program,
											 pChild,
											 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSaveFile))
		{
			if (SUCCESS != _ERR(LoadSaveFile(Program,
											 pChild,
											 pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsDeleteFile))
		{
			if (SUCCESS != _ERR(LoadDeleteFile(Program,
											   pChild,
											   pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsUseModule))
		{
			if (SUCCESS != _ERR(LoadUseModule(Program,
											  pChild,
											  pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSplit))
		{
			if (SUCCESS != _ERR(LoadSplit(Program,
										  pChild,
										  pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsDie))
		{
			if (SUCCESS != _ERR(LoadDie(Program)))
				_RET(XML_LOADER_ERROR);
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsProgram))
		{
			CProgram *pSubProgram = new CProgram();

			if (SUCCESS != _ERR(LoadProgram(&Program.Data(),
											*pSubProgram,
											pChild,
											pPDU)))
            {
				_RET(XML_LOADER_ERROR);
            }

			if (false_v == Program.AddOperator(pSubProgram))
				_RET(XML_LOADER_ERROR);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadEmpty(CProgram &Program,
									  const DOMElement *pElement, 
									  const CPDUInfo *pPDU)
{
	_START(LOAD_EMPTY);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV.Ptr());
		
		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptEmpty *pOperator = new COptEmpty(OV.Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadUnitaryCalculate(CProgram &Program,
												 const DOMElement *pElement,
												 const CPDUInfo *pPDU)
{
	_START(LOAD_UNITARY_CALCULATE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	auto_xerces_str wsOperator	("operator");
	auto_xerces_str	sOperator	(pElement->getAttribute(wsOperator));

	EUnitaryCalculate Calculate;

	if (SUCCESS != _ERR(GetUnitaryOperator(sOperator, Calculate)))
		_RET(XML_LOADER_ERROR);

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());
		
		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptUnitaryCalculate *pOUC = new COptUnitaryCalculate(Calculate,
														  OV[0].Ptr(),
														  OV[1].Ptr());

	if (false_v == Program.AddOperator(pOUC))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadDualityCalculate(CProgram &Program,
												 const DOMElement *pElement,
												 const CPDUInfo *pPDU)
{
	_START(LOAD_DUALITY_CALCULATE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	//
	auto_xerces_str wsOperator	("operator");
	auto_xerces_str	sOperator	(pElement->getAttribute(wsOperator));

	EDualityCalculate Calculate;

	if (SUCCESS != _ERR(GetDualityOperator(sOperator, Calculate)))
		_RET(XML_LOADER_ERROR);

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[3];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
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
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadConfigGroup(CProgram &Program,
											const DOMElement *pElement,
											const CPDUInfo *pPDU)
{
	_START(LOAD_CONFIG_GROUP);

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		if (0 == XMLString::compareString(pSub->getNodeName(),
										  m_wsGroupVariable))
		{
			if (SUCCESS != _ERR(LoadGroupVariable(Program.Data(), 
												  pElement, 
												  OV[0].Ptr())))
			{
				_RET(XML_LOADER_ERROR);
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
			if (SUCCESS != _ERR(LoadSolidVariable(Program.Data(), 
												  pElement, 
												  OV[1].Ptr())))
			{
				_RET(XML_LOADER_ERROR);
			}

			n++;
			break;
		}

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (2 != n)
		_RET(XML_LOADER_ERROR);

	COptConfigGroup *pOperator = new COptConfigGroup(OV[0].Ptr(), OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadIf(CProgram &Program,
								   const DOMElement *pElement,
								   const CPDUInfo *pPDU)
{
	_START(LOAD_IF);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_3);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_4);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

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

			if (SUCCESS != _ERR(LoadDataBlock(Data, pSub)))
				_RET(XML_LOADER_ERROR);

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

			if (SUCCESS != _ERR(LoadExpression(pPI->Data(),
											   pSub,
											   pPDU,
											   pExpression)))
			{
				_RET(XML_LOADER_ERROR);
			}

			if (false_v == pPI->AddExpression(pExpression))
				_RET(XML_LOADER_ERROR);
		}
		else if (0 == XMLString::compareString(pSub->getNodeName(),
											   wsProgram))
		{
			CProgram *pProgram = new CProgram();

			if (SUCCESS != _ERR(LoadProgram(&pPI->Data(),
											*pProgram,
											pSub,
											pPDU)))
			{
				_RET(XML_LOADER_ERROR);
			}

			if (false_v == pPI->AddOperator(pProgram))
				_RET(XML_LOADER_ERROR);
		}

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (false_v == Program.AddOperator(pPI))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadWhile(CProgram &Program,
									  const DOMElement *pElement,
									  const CPDUInfo *pPDU)
{
	_START(LOAD_WHILE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_3);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_4);
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
		_RET(XML_LOADER_ERROR);

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
			if (SUCCESS != _ERR(LoadDataBlock(Data, pSub)))
				_RET(XML_LOADER_ERROR);
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
			if (SUCCESS != _ERR(LoadExpression(Data, pSub, pPDU, pExpression)))
				_RET(XML_LOADER_ERROR);

			pPW = new CProgramWhile(b, pExpression, &Data);
			pPW->Data().SetParent(&Program.Data());
		}
		else if (0 == XMLString::compareString(pSub->getNodeName(),
											   wsProcessBlock))
		{
			if (!pPW)
				_RET(XML_LOADER_ERROR);
			
			if (SUCCESS != _ERR(LoadProcessBlock(*pPW, pSub, pPDU)))
				_RET(XML_LOADER_ERROR);
		}

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (false_v == Program.AddOperator(pPW))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadContinue(CProgram &Program)
{
	_START(LOAD_CONTINUE);

	COptContinue *pOperator = new COptContinue();

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadBlock(CProgram &Program)
{
	_START(LOAD_BLOCK);

	COptContinue *pOperator = new COptContinue();

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadBreak(CProgram &Program)
{
	_START(LOAD_BREAK);

	COptContinue *pOperator = new COptContinue();

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadSend(CProgram &Program,
									 const DOMElement *pElement,
									 const CPDUInfo *pPDU)

{
	_START(LOAD_SEND);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	//
	auto_xerces_str	wsProtocolName	("protocol");
	auto_xerces_str	sProtocolName	(pElement->getAttribute(wsProtocolName));

	CProtocolInfo *pProtocol = null_v;

	if (SUCCESS != _ERR(CProtocolManager::Instance()->GetProtocol(
							sProtocolName, pProtocol)))
	{
		_RET(XML_LOADER_ERROR);
	}

	//
	auto_xerces_str	wsPDU	("pdu");
	auto_xerces_str	sPDU	(pElement->getAttribute(wsPDU));

	CPDUInfo *pPDUInfo = null_v;

	if (SUCCESS != _ERR(pProtocol->GetPDU(sPDU, pPDUInfo)))
		_RET(XML_LOADER_ERROR);

	// For send operation, sub elements is not necessary.
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();
	size_ n = 0;
	CAutoPtr<CVariable> OV[2];
	COptSend *pOperator = null_v;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (0 == n)
	{
		switch (m_tmpNetworkType)
		{
		case NETWORK_ACCEPTOR:
		case NETWORK_CONNECTOR:
			pOperator = new COptSend(pPDUInfo);			
			break;
		case NETWORK_RECEIVER:
		case NETWORK_SENDER:
			pOperator = new COptSend(0, pPDUInfo);
			break;
		default:
			_RET(XML_LOADER_ERROR);
		}
	}
	else if (1 == n)
	{
		if (NETWORK_ACCEPTOR != m_tmpNetworkType
			&& NETWORK_CONNECTOR != m_tmpNetworkType)
		{
			_RET(XML_LOADER_ERROR);
		}

		pOperator = new COptSend(pPDUInfo, OV[0].Ptr());
	}
	else if (2 == n)
	{
		if (NETWORK_RECEIVER != m_tmpNetworkType
			&& NETWORK_SENDER != m_tmpNetworkType)
		{
			_RET(XML_LOADER_ERROR);
		}

		pOperator = new COptSend(0, pPDUInfo, OV[0].Ptr(), OV[1].Ptr());
	}
	else
	{
		_RET(XML_LOADER_ERROR);
	}

	pSub = (DOMElement *)pElement->getFirstChild();

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
					_RET(XML_LOADER_ERROR);

				while (pVariable)
				{
					ret_ Ret = LoadVariable(pPDU, 
											Program.Data(), 
											pVariable, 
											OV_.Ptr());

					if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
						_RET_BY(Ret);

					if (SUCCESS == _ERR(Ret))
						break;

					pVariable = (DOMElement *)pVariable->getNextSibling();
				}

				//
				auto_xerces_str	sFieldName(pSub->getAttribute(wsFieldName));
				CField *pField = null_v;
				
				if (SUCCESS != _ERR(pPDUInfo->GetField(sFieldName, pField)))
					return XML_LOADER_ERROR;

				//
				if (false_v == pOperator->AddEvaluate(sFieldName, OV_.Ptr()))
					_RET(XML_LOADER_ERROR);
			}

			pSub = (DOMElement *)pSub->getNextSibling();
		}
	}

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadForward(CProgram &Program,
										const DOMElement *pElement,
										const CPDUInfo *pPDU)

{
	_START(LOAD_FORWARD);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	// For forward operation, sub elements is not necessary.
	CAutoPtr<CVariable> OV[2];
	size_ n = 0;
	COptForward *pOperator = null_v;
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (0 == n)
	{
		switch (m_tmpNetworkType)
		{
		case NETWORK_ACCEPTOR:
		case NETWORK_CONNECTOR:
			pOperator = new COptForward();
			break;
		case NETWORK_RECEIVER:
		case NETWORK_SENDER:
			pOperator = new COptForward(0);
			break;
		default:
			_RET(XML_LOADER_ERROR);
		}
	}
	else if (1 == n)
	{
		if (NETWORK_ACCEPTOR != m_tmpNetworkType
			&& NETWORK_CONNECTOR != m_tmpNetworkType)
		{
			_RET(XML_LOADER_ERROR);
		}

		pOperator = new COptForward(OV[0].Ptr());
	}
	else if (2 == n)
	{
		if (NETWORK_RECEIVER != m_tmpNetworkType
			&& NETWORK_SENDER != m_tmpNetworkType)
		{
			_RET(XML_LOADER_ERROR);
		}

		pOperator = new COptForward(0, OV[0].Ptr(), OV[1].Ptr());
	}
	else
	{
		_RET(XML_LOADER_ERROR);
	}

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadGetAddress(CProgram &Program,
										   const DOMElement *pElement,
										   const CPDUInfo *pPDU)

{
	_START(LOAD_GET_ADDRESS);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	//
	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	//
	auto_xerces_str wsType	("type");
	auto_xerces_str	sType	(pElement->getAttribute(wsType));
	bool_			bIsRemote = true_v;

	if (0 == strcmp(sType, "local"))
		bIsRemote = false_v;
	else
		bIsRemote = true_v;

	COptGetAddress *pOperator = new COptGetAddress(OV[0].Ptr(),
												   OV[1].Ptr(),
												   bIsRemote);

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadRegister(CProgram &Program,
										 const DOMElement *pElement,
										 const CPDUInfo *pPDU)
{
	_START(LOAD_REGISTER);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[3];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (3 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	auto_xerces_str	wsRecovered	("recovered");
	auto_xerces_str	sRecovered	(pElement->getAttribute(wsRecovered));
	bool_			bRecovered = false_v;

	if (0 == strcmp(sRecovered, "true"))
		bRecovered = true_v;
	else
		bRecovered = false_v;

	COptRegister *pOperator = new COptRegister(OV[0].Ptr(),
											   OV[1].Ptr(),
											   OV[2].Ptr(),
											   bRecovered);

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadUnregister(CProgram &Program,
										   const DOMElement *pElement,
										   const CPDUInfo *pPDU)
{
	_START(LOAD_UNREGISTER);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptUnregister *pOperator = new COptUnregister(OV[0].Ptr(),
												   OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadSearch(CProgram &Program,
									   const DOMElement *pElement,
									   const CPDUInfo *pPDU)
{
	_START(LOAD_SEARCH);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[3];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (3 <= ++n)
				break;
		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptSearch *pOperator = new COptSearch(OV[0].Ptr(),
										   OV[1].Ptr(),
										   OV[2].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadGetUsage(CProgram &Program,
										 const DOMElement *pElement,
										 const CPDUInfo *pPDU)
{
	_START(LOAD_GET_USAGE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV.Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptGetUsage *pOperator = new COptGetUsage(OV.Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadNetworkWakeUp(CProgram &Program,
											  const DOMElement *pElement,
											  const CPDUInfo *pPDU)
{
	_START(LOAD_NETWORK_WAKE_UP);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptNetworkWakeUp *pOperator = new COptNetworkWakeUp(OV[0].Ptr(),
														 OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadNetworkSleep(CProgram &Program,
											 const DOMElement *pElement,
											 const CPDUInfo *pPDU)
{
	_START(LOAD_NETWORK_SLEEP);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (n != 2)
		_RET(XML_LOADER_ERROR);

	COptNetworkSleep *pOperator = new COptNetworkSleep(OV[0].Ptr(),
													   OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadReadFile(CProgram &Program,
										 const DOMElement *pElement,
										 const CPDUInfo *pPDU)
{
	_START(LOAD_READ_FILE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[3];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (3 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	if (n != 3)
		_RET(XML_LOADER_ERROR);

	COptReadFile *pOperator = new COptReadFile(OV[0].Ptr(),
											   OV[1].Ptr(),
											   OV[2].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadSaveFile(CProgram &Program,
										 const DOMElement *pElement,
										 const CPDUInfo *pPDU)
{
	_START(LOAD_SAVE_FILE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[4];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (4 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptSaveFile *pOperator = new COptSaveFile(OV[0].Ptr(),
											   OV[1].Ptr(),
											   OV[2].Ptr(),
											   OV[3].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadDeleteFile(CProgram &Program,
										   const DOMElement *pElement,
										   const CPDUInfo *pPDU)
{
	_START(LOAD_DELETE_FILE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptDeleteFile *pOperator = new COptDeleteFile(OV[0].Ptr(),
												   OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadUseModule(CProgram &Program,
										  const DOMElement *pElement,
										  const CPDUInfo *pPDU)
{
	_START(LOAD_USE_MODULE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	//
	auto_xerces_str	wsModuleName	("module");
	auto_xerces_str	sModuleName		(pElement->getAttribute(wsModuleName));

	CModuleInfo *pModule = null_v;

	if (SUCCESS != _ERR(CModuleManager::Instance()->GetModule(sModuleName, 
															  pModule)))
	{
		_RET(XML_LOADER_ERROR);
	}

	//
	auto_xerces_str	wsInterface	("interface");
	auto_xerces_str	sInterface	(pElement->getAttribute(wsInterface));

	CInterfaceInfo *pInterface = null_v;

	if (SUCCESS != _ERR(pModule->GetInterface(sInterface, pInterface)))
		_RET(XML_LOADER_ERROR);

	COptUseModule *pOperator = new COptUseModule(pInterface);

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

	auto_xerces_str wsParameterIn	("parameter_in");
	auto_xerces_str	wsParameterOut	("parameter_out");

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(), 
										  wsParameterIn))
		{
			DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

			if (!pSub)
				_RET(XML_LOADER_ERROR);

			while (pSub)
			{
				CAutoPtr<CVariable> OV;

				ret_ Ret = LoadVariable(pPDU, 
										Program.Data(), 
										pSub, 
										OV.Ptr());

				if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
					_RET_BY(Ret);

				if (SUCCESS == _ERR(Ret))
					if (!pOperator->AddInParameter(OV.Ptr()))
						_RET(XML_LOADER_ERROR);

				pSub = (DOMElement *)pSub->getNextSibling();
			}
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), 
											   wsParameterOut))
		{
			//  
			auto_xerces_str wsFieldName	("field_name");
			auto_xerces_str sFieldName	(pChild->getAttribute(wsFieldName));

			CField *pField = null_v;

			if (SUCCESS != _ERR(pInterface->GetOutField(sFieldName, pField)))
				_RET(XML_LOADER_ERROR);

			//
			DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

			if (!pSub)
				_RET(XML_LOADER_ERROR);

			CAutoPtr<CVariable> OV;

			while (pSub)
			{
				ret_ Ret = LoadVariable(pPDU, 
										Program.Data(), 
										pSub, 
										OV.Ptr());

				if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
					_RET_BY(Ret);

				if (SUCCESS == _ERR(Ret))
					break;

				pSub = (DOMElement *)pSub->getNextSibling();
			}

			if (!pOperator->AddOutParameter(sFieldName, OV.Ptr()))
				_RET(XML_LOADER_ERROR);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadSplit(CProgram &Program,
									  const DOMElement *pElement,
									  const CPDUInfo *pPDU)
{
	_START(LOAD_SPLIT);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_3);
#endif

	DOMElement *pSub = (DOMElement *)pElement->getFirstChild();

	if (!pSub)
		_RET(XML_LOADER_ERROR);

	CAutoPtr<CVariable> OV[2];
	size_ n = 0;

	while (pSub)
	{
		ret_ Ret = LoadVariable(pPDU, Program.Data(), pSub, OV[n].Ptr());

		if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
			_RET_BY(Ret);

		if (SUCCESS == _ERR(Ret))
			if (2 <= ++n)
				break;

		pSub = (DOMElement *)pSub->getNextSibling();
	}

	COptSplit *pOperator = new COptSplit(OV[0].Ptr(),
										 OV[1].Ptr());

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadDie(CProgram &Program)
{
	_START(LOAD_DIE);

	COptDie *pOperator = new COptDie();

	if (false_v == Program.AddOperator(pOperator))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadVariable(const CPDUInfo *pPDU,
										 const CData &Data,
										 const DOMElement *pElement,
										 CVariable *&pOV)
{
	_START(LOAD_VARIABLE);

#ifdef _DEBUG_
	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_3);

	if (pOV)
		_RET(PARAMETER_NOT_NULL | PARAMETER_4);
#endif

	if (0 == XMLString::compareString(pElement->getNodeName(),
									  m_wsSolidVariable))
	{
		if (SUCCESS != _ERR(LoadSolidVariable(Data, pElement, pOV)))
			_RET(XML_LOADER_ERROR);
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   m_wsGroupVariable))
	{
		if (SUCCESS != _ERR(LoadGroupVariable(Data, pElement, pOV)))
			_RET(XML_LOADER_ERROR);
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   m_wsNetworkVariable))
	{
		if (SUCCESS != _ERR(LoadNetworkVarialbe(pPDU, Data, pElement, pOV)))
			_RET(XML_LOADER_ERROR);
	}
	else
	{
		_RET(XML_INVALID_ELEMENT);
	}

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadSolidVariable(const CData &Data,
											  const DOMElement *pElement,
											  CVariable *&pOV)
{
	_START(LOAD_SOLID_VARIABLE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (pOV)
		_RET(PARAMETER_NOT_NULL | PARAMETER_3);
#endif

	auto_xerces_str	wsName	("name");
	auto_xerces_str	sName	(pElement->getAttribute(wsName));

	v_ *pV = Data.Value(sName);

	if (!pV)
		_RET(XML_LOADER_ERROR);

	pOV = new CVarSolidDefined((const ch_1 *)sName);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadGroupVariable(const CData &Data,
											  const DOMElement *pElement,
											  CVariable *&pOV)
{
	_START(LOAD_GROUP_VARIABLE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (pOV)
		_RET(PARAMETER_NOT_NULL | PARAMETER_3);
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
		_RET(XML_LOADER_ERROR); // There is no variable defined above

	if (0 != strcmp(sIndex, SIGN_UNBOUNDED))
		pszIndexName = sIndex;

	pOV = new CVarGroupDefined(sGroupName, pszSubName, pszIndexName);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadNetworkVarialbe(const CPDUInfo *pPDU,
												const CData &Data,
												const DOMElement *pElement,
												CVariable *&pOV)
{
	_START(LOAD_NETWORK_VARIABLE);

#ifdef _DEBUG_
	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_3);

	if (pOV)
		_RET(PARAMETER_NOT_NULL | PARAMETER_4
			);
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
		sprintf(szName, 
				"%s.%s", 
				(const ch_1 *)sGroupName, 
				(const ch_1 *)sFieldName);
	else
		sprintf(szName, "%s", (const ch_1 *)sFieldName);

	CField *pField = null_v;

	if (SUCCESS != _ERR(((CPDUInfo *)pPDU)->GetField(szName, pField)))
		_RET(XML_LOADER_ERROR);

	if (0 == strcmp(sIndex, SIGN_UNBOUNDED))
		pOV = new CVarNetwork(pField);
	else
		pOV = new CVarNetwork(pField, sIndex);

	_RET(SUCCESS);
}

ret_ CXMLLoaderTransaction::LoadExpression(const CData &Data,
										   const DOMElement *pElement,
										   const CPDUInfo *pPDU,
										   CExpression *&pExpression)
{
	_START(LOAD_EXPRESSION);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (!pPDU)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (pExpression)
		_RET(PARAMETER_NOT_NULL | PARAMETER_3);
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
		// Fixed: not
		// auto_xerces_str sRelation(pElement->getAttribute(wsRelation));

		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			_RET(XML_LOADER_ERROR);

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
				if (SUCCESS != _ERR(LoadExpression(Data,
												   pChild,
												   pPDU,
												   pExp)))
				{
					_RET(XML_LOADER_ERROR);
				}

				break;
			}

			pChild = (DOMElement *)pChild->getNextSibling();
		}

		if (!pExp)
			_RET(XML_LOADER_ERROR);

		pExpression = (CExpression *)new CExpNot(pExp);
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   wsExpressionDuality))
	{
		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			_RET(XML_LOADER_ERROR);

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
				if (SUCCESS != _ERR(LoadExpression(Data,
												   pChild,
												   pPDU,
												   pExp[n++])))
				{
					_RET(XML_LOADER_ERROR);
				}
			}

			pChild = (DOMElement *)pChild->getNextSibling();
		}

		if (2 != n)
			_RET(XML_LOADER_ERROR);

		auto_xerces_str sRelation(pElement->getAttribute(wsRelation));

		if (0 == strcmp((const ch_1 *)sRelation, "and"))
			pExpression = (CExpression *)new CExpAnd(pExp[0], pExp[1]);
		else if (0 == strcmp((const ch_1 *)sRelation, "or"))
			pExpression = (CExpression *)new CExpOr(pExp[0], pExp[1]);
		else
			_RET(XML_LOADER_ERROR);
	}
	else if (0 == XMLString::compareString(pElement->getNodeName(),
										   wsConditionUnitary))
	{
		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			_RET(XML_LOADER_ERROR);

		CAutoPtr<CVariable> v;

		while (pChild)
		{
			ret_ Ret = LoadVariable(pPDU, Data, pChild, v.Ptr());
		
			if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
				_RET_BY(Ret);

			if (SUCCESS == _ERR(Ret))
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
			_RET(XML_LOADER_ERROR);

		CAutoPtr<CVariable> v[2];
		size_ n = 0;

		while (pChild)
		{
			ret_ Ret = LoadVariable(pPDU, Data, pChild, v[n].Ptr());
		
			if (SUCCESS != _ERR(Ret) && XML_INVALID_ELEMENT != _ERR(Ret))
				_RET_BY(Ret);

			if (SUCCESS == _ERR(Ret))
				if (2 <= ++n)
					break;

			pChild = (DOMElement *)pChild->getNextSibling();
		}

		auto_xerces_str sOperator(pElement->getAttribute(wsCalculate));
		ECompareCalculate Calculate;

		if (SUCCESS != _ERR(GetCompareOperator((const ch_1 *)sOperator,
											   Calculate)))
		{
			_RET(XML_LOADER_ERROR);
		}


		pExpression = new CExpVarDuality(v[0].Ptr(), Calculate, v[1].Ptr());
	}

	_RET(SUCCESS);
}

