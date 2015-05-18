#include "CXMLLoaderProtocol.h"

CXMLLoaderProtocol *CXMLLoaderProtocol::m_pInstance = null_v;

ret_ CXMLLoaderProtocol::Load(XercesDOMParser *pParser,
							  const ch_1 *pszEnvironmentPath)
{
#ifdef _DEBUG_
	if (!pParser)
		return (PARAMETER_NULL | PARAMETER_1);

	if (!pszEnvironmentPath)
		return (PARAMETER_NULL | PARAMETER_2);

	if (null_v == pszEnvironmentPath[0])
		return (PARAMETER_EMPTY | PARAMETER_2);
#endif

	SetParser(pParser);
	m_pProtocol = CProtocolManager::Instance()->GetProtocol();

	ch_1 sProtocol[ENVIRONMENT_PATH_LENGTH];

	memset(sProtocol, 0, ENVIRONMENT_PATH_LENGTH);
	sprintf(sProtocol, "%s%s", pszEnvironmentPath, PROTOCOL_XML_FILE);

	DOMDocument *pProtocolDoc = null_v;

	try
	{
        GetParser()->parse(sProtocol);
        pProtocolDoc = GetParser()->getDocument();
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

	if (!pProtocolDoc)
		return XML_LOADER_ERROR;
	
	DOMElement *pRoot = pProtocolDoc->getDocumentElement();

	if (!pRoot)
		return XML_LOADER_ERROR;

	auto_xerces_str wsCommand	("command_id_value");
	auto_xerces_str	wsHead		("head");
	auto_xerces_str	wsPDU		("pdu");
	auto_xerces_str wsName		("name");
	auto_xerces_str wsValue		("value");

	DOMElement *pChild = (DOMElement *)pRoot->getFirstChild();

	if (!pChild)
		return XML_LOADER_ERROR;

    while (pChild)
	{
		if (0 == XMLString::compareString(pChild->getNodeName(), wsCommand))
		{
			auto_xerces_str sName(pChild->getAttribute(wsName));
			auto_xerces_str sValue(pChild->getAttribute(wsValue));

			if (!m_pProtocol->Data().Define(sName, UB_4, (ub_4)atoi(sValue)))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsHead))
		{
			// Load head of protocol
			if (SUCCESS != LoadPDU((const DOMElement *)pChild))
				return XML_LOADER_ERROR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(), wsPDU))
		{
			auto_xerces_str sName(pChild->getAttribute(wsName));

			// Load normal pdu of protocol
			if (SUCCESS != LoadPDU((const DOMElement *)pChild, sName))
				return XML_LOADER_ERROR;
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	return SUCCESS;
}

ret_ CXMLLoaderProtocol::LoadPDU(const DOMElement *pElement,
								 const ch_1 *pszPDUName)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_1);
#endif

	auto_xerces_str wsNormal("normal");
	auto_xerces_str wsFloat	("float");
	auto_xerces_str wsString("string");
	auto_xerces_str	wsGroup	("group");
	auto_xerces_str	wsName	("name");

	if (pszPDUName)
	{
#ifdef _DEBUG_
		if (0 == pszPDUName[0])
			return (PARAMETER_EMPTY | PARAMETER_2);

		// There should not be same pdu in protocol
		if (m_pProtocol->IsPDUReady(pszPDUName))
			return XML_LOADER_ERROR;
#endif

		auto_xerces_str	sName(pElement->getAttribute(wsName));
		CPDUInfo		*pPDUInfo = null_v;

		if (SUCCESS != m_pProtocol->AddPDU(sName, pPDUInfo))
			return XML_LOADER_ERROR;

		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			return SUCCESS;

		while (pChild)
		{
			if (0 == XMLString::compareString(pChild->getNodeName(), wsNormal))
			{
				if (SUCCESS != LoadPDUField(pChild,
											FIELD_NORMAL_STYLE,
											pPDUInfo))
				{
					return XML_LOADER_ERROR;
				}
			}
			else if (0 == XMLString::compareString(pChild->getNodeName(),
												   wsFloat))
			{
				if (SUCCESS != LoadPDUField(pChild,
											FIELD_FLOAT_STYLE,
											pPDUInfo))
				{
					return XML_LOADER_ERROR;
				}
			}
			else if (0 == XMLString::compareString(pChild->getNodeName(),
												   wsString))
			{
				if (SUCCESS != LoadPDUField(pChild,
											FIELD_STRING_STYLE,
											pPDUInfo))
				{
					return XML_LOADER_ERROR;
				}
			}
			else if (0 == XMLString::compareString(pChild->getNodeName(),
												   wsGroup))
			{
				ch_1 sGroupName[VARIABLE_NAME_LENGTH];

				memset(sGroupName, 0, VARIABLE_NAME_LENGTH);

				if (SUCCESS != LoadPDUField(pChild,
											FIELD_GROUP_STYLE,
											pPDUInfo,
											false_v,
											sGroupName))
				{
					return XML_LOADER_ERROR;
				}

				DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

				if (!pSub)
					return XML_LOADER_ERROR;

				while (pSub)
				{
					if (0 == XMLString::compareString(pSub->getNodeName(),
													  wsNormal))
					{
						if (SUCCESS != LoadPDUField(pSub,
													FIELD_NORMAL_STYLE,
													pPDUInfo,
													true_v,
													sGroupName))
						{
							return XML_LOADER_ERROR;
						}
					}
					else if (0 == XMLString::compareString(pSub->getNodeName(),
														   wsFloat))
					{
						if (SUCCESS != LoadPDUField(pSub,
													FIELD_FLOAT_STYLE,
													pPDUInfo,
													true_v,
													sGroupName))
						{
							return XML_LOADER_ERROR;
						}
					}
					else if (0 == XMLString::compareString(pSub->getNodeName(),
														   wsString))
					{
						if (SUCCESS != LoadPDUField(pSub,
													FIELD_STRING_STYLE,
													pPDUInfo,
													true_v,
													sGroupName))
						{
							return XML_LOADER_ERROR;
						}
					}

					pSub = (DOMElement *)pSub->getNextSibling();
				}
			}

			pChild = (DOMElement *)pChild->getNextSibling();
		}
	}
	else
	{
		DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

		if (!pChild)
			return XML_LOADER_ERROR;

		while (pChild)
		{
			if (0 == XMLString::compareString(pChild->getNodeName(),
											  wsNormal))
			{
				if (SUCCESS != LoadPDUField(pChild,	FIELD_NORMAL_STYLE))
					return XML_LOADER_ERROR;
			}
			else if (0 == XMLString::compareString(pChild->getNodeName(),
												   wsFloat))
			{
				if (SUCCESS != LoadPDUField(pChild, FIELD_FLOAT_STYLE))
					return XML_LOADER_ERROR;
			}
			else if (0 == XMLString::compareString(pChild->getNodeName(),
												   wsString))
			{
				if (SUCCESS != LoadPDUField(pChild, FIELD_STRING_STYLE))
					return XML_LOADER_ERROR;
			}
			else if (0 == XMLString::compareString(pChild->getNodeName(),
												   wsGroup))
			{
				ch_1 sGroupName[VARIABLE_NAME_LENGTH];

				memset(sGroupName, 0, VARIABLE_NAME_LENGTH);

				if (SUCCESS != LoadPDUField(pChild,
											FIELD_GROUP_STYLE,
											null_v,
											false_v,
											sGroupName))
				{
					return XML_LOADER_ERROR;
				}

				DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

				if (!pSub)
					return XML_LOADER_ERROR;

				while (pSub)
				{
					if (0 == XMLString::compareString(pSub->getNodeName(),
													  wsNormal))
					{
						if (SUCCESS != LoadPDUField(pSub,
													FIELD_NORMAL_STYLE,
													null_v,
													true_v,
													sGroupName))
						{
							return XML_LOADER_ERROR;
						}
					}
					else if (0 == XMLString::compareString(pSub->getNodeName(),
														   wsFloat))
					{
						if (SUCCESS != LoadPDUField(pSub,
													FIELD_FLOAT_STYLE,
													null_v,
													true_v,
													sGroupName))
						{
							return XML_LOADER_ERROR;
						}
					}
					else if (0 == XMLString::compareString(pSub->getNodeName(),
														   wsString))
					{
						if (SUCCESS !=  LoadPDUField(pSub,
													 FIELD_STRING_STYLE,
													 null_v,
													 true_v,
													 sGroupName))
						{
							return XML_LOADER_ERROR;
						}
					}

					pSub = (DOMElement *)pSub->getNextSibling();
				}
			}

			pChild = (DOMElement *)pChild->getNextSibling();
		}
	}

	return SUCCESS;
}

// Produce PDU fields
ret_ CXMLLoaderProtocol::LoadPDUField(const DOMElement *pElement,
									  EFieldStyle FieldStyle, 
									  CPDUInfo *pPDUInfo,
									  bool_ bIsSubField,
									  ch_1 *pszGroupName)
{
#ifdef _DEBUG_
	if (!pElement)
		return (PARAMETER_NULL | PARAMETER_1);

	if (FIELD_NORMAL_STYLE > FieldStyle	|| FIELD_GROUP_STYLE < FieldStyle)
		return (PARAMETER_TYPE_ERROR | PARAMETER_2);
#endif

	TField Field;

	memset(&Field, 0, sizeof(TField));
	Field.Style	= FieldStyle;

	auto_xerces_str	wsName	("name");
	auto_xerces_str sName	(pElement->getAttribute(wsName));

	strncpy(Field.sName, sName, VARIABLE_NAME_LENGTH);

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
	else if (!bIsSubField) // FIELD_GROUP_STYLE
	{
		if (pszGroupName)
			strncpy(pszGroupName, Field.sName, VARIABLE_NAME_LENGTH);
		else
			return (PARAMETER_NULL | PARAMETER_5);

		auto_xerces_str sSize(pElement->getAttribute(wsSize));

		strncpy((ch_1 *)Field.sSizeName, sSize, VARIABLE_NAME_LENGTH);
	}

	if (pPDUInfo)
	{
		if (!bIsSubField)
		{
			if (SUCCESS != pPDUInfo->AddField(Field))
				return XML_LOADER_ERROR;
		}
		else
		{
#ifdef _DEBUG_
			if (!pszGroupName)
				return (PARAMETER_NULL | PARAMETER_5);

			if (null_v == pszGroupName[0])
				return (PARAMETER_EMPTY | PARAMETER_5);
#endif
			if (SUCCESS != pPDUInfo->AddField(Field, pszGroupName))
				return XML_LOADER_ERROR;
		}
	}
	else
	{
		if (!bIsSubField)
		{
			if (SUCCESS != m_pProtocol->AddHeadField(Field))
				return XML_LOADER_ERROR;
		}
		else
		{
#ifdef _DEBUG_
			if (!pszGroupName)
				return (PARAMETER_NULL | PARAMETER_5);

			if (null_v == pszGroupName[0])
				return (PARAMETER_EMPTY | PARAMETER_5);
#endif
			if (SUCCESS != m_pProtocol->AddHeadField(Field, 
													 pszGroupName))
			{
				return XML_LOADER_ERROR;
			}
		}
	}

	return SUCCESS;
}


