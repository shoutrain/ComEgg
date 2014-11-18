#include "CXMLLoaderModule.h"

CXMLLoaderModule *CXMLLoaderModule::m_pInstance = null_v;

ret_ CXMLLoaderModule::Load(XercesDOMParser *pParser,
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

	ch_1 sModuleName[ENVIRONMENT_PATH_LENGTH];

	memset(sModuleName, 0, ENVIRONMENT_PATH_LENGTH);
	sprintf(sModuleName, "%s%s", pszEnvironmentPath, MODULE_XML_FILE);

	DOMDocument *pProtocolDoc = null_v;

	try
	{
        GetParser()->parse(sModuleName);
        pProtocolDoc = GetParser()->getDocument();
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

	if (!pProtocolDoc)
		_RET(XML_FILE_NOT_EXIST);
	
	DOMElement *pRoot = pProtocolDoc->getDocumentElement();

	if (!pRoot)
		_RET(XML_LOADER_ERROR);

	auto_xerces_str wsModule	("module");
	auto_xerces_str	wsPath		("path");
	auto_xerces_str wsName		("name");
	auto_xerces_str wsExt		("ext");

	DOMElement *pChild = (DOMElement *)pRoot->getFirstChild();

	if (!pChild)
		_RET(XML_MODULE_NOT_EXIST);

    while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(), wsModule))
		{
			auto_xerces_str sPath	(pChild->getAttribute(wsPath));
			auto_xerces_str sName	(pChild->getAttribute(wsName));
			auto_xerces_str sExt	(pChild->getAttribute(wsExt));

			m_pModule = null_v;

			ret_ Ret = CModuleManager::Instance()->AddModule(sPath, 
															 sName, 
															 sExt, 
															 m_pModule);

#ifdef _DEBUG_
			if (SUCCESS != _ERR(Ret))
				_RET(XML_LOADER_ERROR);
#endif

			if (SUCCESS != _ERR(LoadModule(pChild)))
				_RET(XML_LOADER_ERROR);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	_RET(SUCCESS);
}

ret_ CXMLLoaderModule::LoadModule(const DOMElement *pElement)
{
	_START(LOAD_MODULE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

	auto_xerces_str wsInterface	("interface");
	auto_xerces_str	wsName		("name");

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

	while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(), wsInterface))
		{
			auto_xerces_str sName(pChild->getAttribute(wsName));
			
			m_pInterface = null_v;

			ret_ Ret = m_pModule->AddInterface(sName, m_pInterface);

#ifdef _DEBUG_
			if (SUCCESS != _ERR(Ret))
				_RET(XML_LOADER_ERROR);
#endif

			if (SUCCESS != _ERR(LoadInterface(pChild)))
				_RET(XML_LOADER_ERROR);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	_RET(SUCCESS);
}

ret_ CXMLLoaderModule::LoadInterface(const DOMElement *pElement)
{
	_START(LOAD_INTERFACE);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_1);
#endif

	auto_xerces_str wsParameterIn	("parameter_in");
	auto_xerces_str wsParameterOut	("parameter_out");
	auto_xerces_str wsNormal		("normal");
	auto_xerces_str wsFloat			("float");
	auto_xerces_str wsString		("string");
	auto_xerces_str	wsGroup			("group");
	auto_xerces_str	wsName			("name");

	DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

	while (pChild)
	{
		bool_ bInField = true_v;
		bool_ bDeal = false_v;
		
		if (0 == XMLString::compareString(pChild->getNodeName(), 
										  wsParameterIn))
		{
			bInField = true_v;
			bDeal = true_v;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsParameterOut))
		{
			bInField = false_v;
			bDeal = true_v;
		}

		if (bDeal)
		{
			DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

			if (!pSub)
				_RET(XML_LOADER_ERROR);

			
			while (pSub)
			{
				if (0 == XMLString::compareString(pSub->getNodeName(),
												  wsNormal))
				{
					if (SUCCESS != _ERR(LoadInterfaceField(
											pSub,
											FIELD_NORMAL_STYLE,
											bInField)))
					{
						_RET(XML_LOADER_ERROR);
					}
				}
				else if (0 == XMLString::compareString(pSub->getNodeName(),
													   wsFloat))
				{
					if (SUCCESS != _ERR(LoadInterfaceField(
											pSub,
											FIELD_FLOAT_STYLE,
											bInField)))
					{
						_RET(XML_LOADER_ERROR);
					}
				}
				else if (0 == XMLString::compareString(pSub->getNodeName(),
													   wsString))
				{
					if (SUCCESS != _ERR(LoadInterfaceField(
											pSub,
											FIELD_STRING_STYLE,
											bInField)))
					{
						_RET(XML_LOADER_ERROR);
					}
				}
				else if (0 == XMLString::compareString(pSub->getNodeName(),
													   wsGroup))
				{
					ch_1 sGroupName[VARIABLE_NAME_LENGTH];

					memset(sGroupName, 0, VARIABLE_NAME_LENGTH);

					if (SUCCESS != _ERR(LoadInterfaceField(
											pSub,
											FIELD_GROUP_STYLE,
											bInField, 
											false_v,
											sGroupName)))
					{
						_RET(XML_LOADER_ERROR);
					}

					DOMElement *pSubSub = (DOMElement *)pSub->getFirstChild();

					if (!pSubSub)
						_RET(XML_LOADER_ERROR);

					while (pSubSub)
					{
						if (0 == XMLString::compareString(
								pSubSub->getNodeName(),
								wsNormal))
						{
							if (SUCCESS != _ERR(LoadInterfaceField(
													pSubSub,
													FIELD_NORMAL_STYLE,
													bInField,
													true_v,
													sGroupName)))
							{
								_RET(XML_LOADER_ERROR);
							}
						}
						else if (0 == XMLString::compareString(
									 pSubSub->getNodeName(),
									 wsFloat))
						{
							if (SUCCESS != _ERR(LoadInterfaceField(
													pSubSub,
													FIELD_FLOAT_STYLE,
													bInField,
													true_v,
													sGroupName)))
							{
								_RET(XML_LOADER_ERROR);
							}
						}
						else if (0 == XMLString::compareString(
									 pSubSub->getNodeName(),
									 wsString))
						{
							if (SUCCESS != _ERR(LoadInterfaceField(
													pSubSub,
													FIELD_STRING_STYLE,
													bInField,
													true_v,
													sGroupName)))
							{
								_RET(XML_LOADER_ERROR);
							}
						}

						pSubSub = (DOMElement *)pSubSub->getNextSibling();
					}
				}

				pSub = (DOMElement *)pSub->getNextSibling();
			}
		}

		pChild = (DOMElement *)pChild->getNextSibling();		
	}

	_RET(SUCCESS);
}

// Produce PDU fields
ret_ CXMLLoaderModule::LoadInterfaceField(const DOMElement *pElement, 
										  EFieldStyle FieldStyle,
										  bool_ bIsInField,
										  bool_ bIsSubField,
										  ch_1 *pszGroupName)
{
	_START(LOAD_INTERFACE_FIELD);

#ifdef _DEBUG_
	if (!pElement)
		_RET(PARAMETER_NULL | PARAMETER_1);

	if (FIELD_NORMAL_STYLE > FieldStyle	|| FIELD_GROUP_STYLE < FieldStyle)
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_2);
#endif

	TField Field;

	memset(&Field, 0, sizeof(TField));
	Field.Style	= FieldStyle;

	auto_xerces_str	wsName	("name");
	auto_xerces_str sName	(pElement->getAttribute(wsName));

	strncpy((ch_1 *)Field.sName, sName, VARIABLE_NAME_LENGTH);

	auto_xerces_str	wsLength("length");
	auto_xerces_str	wsSigned("signed");
	auto_xerces_str	wsSize	("size");

	if (FIELD_NORMAL_STYLE == FieldStyle
		|| FIELD_FLOAT_STYLE == FieldStyle)
	{
		auto_xerces_str	sLength(pElement->getAttribute(wsLength));
		auto_xerces_str	sSigned(pElement->getAttribute(wsSigned));

		Field.nLength	= atoi(sLength);
		Field.IsSigned	=
			(0 == strcmp(sSigned, "true") ? true_v : false_v);
	}
	else if (FIELD_STRING_STYLE == FieldStyle)
	{
		auto_xerces_str sSize(pElement->getAttribute(wsSize));

		Field.nSize = (size_)atoi(sSize);
	}
	else if (FIELD_GROUP_STYLE == FieldStyle) // FIELD_GROUP_STYLE
	{
		// For now, do not support group to be a sub field
		if (bIsSubField)
			_RET(PARAMETER_TYPE_ERROR | PARAMETER_4);
		
		if (pszGroupName)
			strncpy(pszGroupName, Field.sName, VARIABLE_NAME_LENGTH);
		else
			_RET(PARAMETER_NULL | PARAMETER_5);

		auto_xerces_str sSize(pElement->getAttribute(wsSize));

		strncpy((ch_1 *)Field.sSizeName, sSize, VARIABLE_NAME_LENGTH);
	}

	ret_ Ret;
	ch_1 *pszGN = null_v;

	if (bIsSubField)
	{
		if (!pszGroupName)
			_RET(PARAMETER_NULL | PARAMETER_5);

		if (null_v == pszGroupName[0])
			_RET(PARAMETER_EMPTY | PARAMETER_5);
		
		pszGN = pszGroupName;
	}

	if (bIsInField)
		Ret = m_pInterface->AddInField(Field, pszGN);
	else
		Ret = m_pInterface->AddOutField(Field, pszGN);
	
	if (SUCCESS != _ERR(Ret))
		_RET(XML_LOADER_ERROR);

	_RET(SUCCESS);
}


