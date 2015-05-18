#include "CXMLLoaderNetwork.h"

CXMLLoaderNetwork *CXMLLoaderNetwork::m_pInstance = null_v;

ret_ CXMLLoaderNetwork::Load(XercesDOMParser *pParser,
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

	ch_1 sNetwork[ENVIRONMENT_PATH_LENGTH];
	
	memset(sNetwork, 0, ENVIRONMENT_PATH_LENGTH);
	sprintf(sNetwork, "%s%s", pszEnvironmentPath, NETWORK_XML_FILE);

	DOMDocument *pNetworkDoc = null_v;

	try
	{
		GetParser()->parse(sNetwork);
        pNetworkDoc = GetParser()->getDocument();
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
        auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

 		return XML_LOADER_ERROR;
	}
	catch (...)
    {
		printf("Unexpected error during parsing.\n");

		return XML_LOADER_ERROR;
    }

	if (!pNetworkDoc)
		return XML_LOADER_ERROR;
	
	DOMElement *pRoot = pNetworkDoc->getDocumentElement();

	if (!pRoot)
		return XML_LOADER_ERROR;

	DOMElement *pChild = (DOMElement *)pRoot->getFirstChild();

	if (!pChild)
		return XML_LOADER_ERROR;

	auto_xerces_str wsIdentity		("identity");
	auto_xerces_str wsPDU			("pdu");
	auto_xerces_str wsDirection		("direction");
	auto_xerces_str	wsProtocolName	("protocol");
	auto_xerces_str wsCommandID		("command_id");
	auto_xerces_str wsSizeID		("size_id");
	auto_xerces_str	wsLocalPort		("local_port");

	auto_xerces_str wsRemoteIP		("remote_ip");
	auto_xerces_str	wsRemotePort	("remote_port");
	auto_xerces_str wsReconnect		("reconnect");

	auto_xerces_str	wsConnectorName	("connector");

	auto_xerces_str wsType			("type");

	while (pChild)
    {
		CField *pCommandIDField	= null_v;
		CField *pSizeIDField = null_v;

		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsConnectorName))
		{
			// Before get protocol, the protocl should be ready.
			CProtocolInfo *pProtocol =  
				CProtocolManager::Instance()->GetProtocol();
			
			//
			auto_xerces_str sCommandID(pChild->getAttribute(wsCommandID));

			if (SUCCESS != pProtocol->GetHeadField(sCommandID, pCommandIDField)
				|| FIELD_NORMAL_STYLE != 
				(pCommandIDField->Type() & FIELD_NORMAL_STYLE)
				|| 4 < _LEN(pCommandIDField->Type()))
			{
				return XML_LOADER_ERROR;
			}

			//
			auto_xerces_str sSizeID(pChild->getAttribute(wsSizeID));

			if (SUCCESS != pProtocol->GetHeadField(sSizeID, pSizeIDField)
				|| FIELD_NORMAL_STYLE != 
				(pSizeIDField->Type() & FIELD_NORMAL_STYLE)
				|| 4 < _LEN(pSizeIDField->Type()))
			{
				return XML_LOADER_ERROR;
			}

			//
			auto_xerces_str	nLocalPort	(pChild->getAttribute(wsLocalPort));
			auto_xerces_str	sRemoteIP	(pChild->getAttribute(wsRemoteIP));
			auto_xerces_str	nRemotePort (pChild->getAttribute(wsRemotePort));
			auto_xerces_str	sReconnect	(pChild->getAttribute(wsReconnect));

			CConnector *pNetwork = new CConnector(pCommandIDField,
												  pSizeIDField,
												  (ub_2)atoi(nLocalPort),
												  (const ch_1 *)sRemoteIP,
												  (ub_2)atoi(nRemotePort),
												  (b_4)atoi(sReconnect));

			CNetworkConf *pNetworkConf = (CNetworkConf *)pNetwork->GetConf();

			//
			DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

			if (!pSub)
				return XML_LOADER_ERROR;

			while (pSub)
			{
				if (0 == XMLString::compareString(pSub->getNodeName(),
												  wsIdentity))
				{
					//
					auto_xerces_str sIdentity(pSub->getAttribute(wsIdentity));
					v_ *pV = pProtocol->Data().Value(sIdentity);

					if (!pV)
						return XML_LOADER_ERROR;

					//
					auto_xerces_str	sPDU(pSub->getAttribute(wsPDU));
					CPDUInfo		*pPDU = null_v;

					if (SUCCESS != pProtocol->GetPDU(sPDU, pPDU))
						return XML_LOADER_ERROR;

					//
					auto_xerces_str sDirection(pSub->getAttribute(wsDirection));
					EDirection		Direction;

					if (SUCCESS != GetDirection(sDirection, Direction))
						return XML_LOADER_ERROR;

					//
					if (SUCCESS != pNetworkConf->ConfigPDU(*pV,
														   pPDU,
														   Direction))
					{
						return XML_LOADER_ERROR;
					}
				}

				pSub = (DOMElement *)pSub->getNextSibling();
			}

			if (!CNetworkManager::Instance()->SetNetwork(pNetwork))
				return XML_LOADER_ERROR;

			return SUCCESS;
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	return XML_LOADER_ERROR;
}

