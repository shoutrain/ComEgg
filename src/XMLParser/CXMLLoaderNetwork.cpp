#include "CXMLLoaderNetwork.h"

#include <xercesc/dom/DOMAttr.hpp>


CXMLLoaderNetwork *CXMLLoaderNetwork::m_pInstance = null_v;

ret_ CXMLLoaderNetwork::Load(XercesDOMParser *pParser,
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

	ch_1 sNetwork[ENVIRONMENT_PATH_LENGTH];

	memset(sNetwork, 0, ENVIRONMENT_PATH_LENGTH);
	strncpy(sNetwork, pszEnvironmentPath, ENVIRONMENT_PATH_LENGTH);
	strncat(sNetwork, NETWORK_XML_FILE, ENVIRONMENT_PATH_LENGTH);

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
        auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

 		_RET(XML_LOADER_ERROR);
	}
	catch (...)
    {
		printf("Unexpected error during parsing.\n");

		_RET(XML_LOADER_ERROR);
    }

	DOMElement *pRoot = pNetworkDoc->getDocumentElement();

	if (!pRoot)
		_RET(XML_LOADER_ERROR);

	DOMElement *pChild = (DOMElement *)pRoot->getFirstChild();

	if (!pChild)
		_RET(XML_LOADER_ERROR);

	auto_xerces_str wsIdentity		("identity");
	auto_xerces_str wsPDU			("pdu");
	auto_xerces_str wsDirection		("direction");
	auto_xerces_str	wsName			("name");
	auto_xerces_str	wsProtocolName	("protocol");
	auto_xerces_str wsCommandID		("command_id");
	auto_xerces_str wsSizeID		("size_id");
	auto_xerces_str	wsLocalPort		("local_port");
	auto_xerces_str wsAuto			("auto");

	auto_xerces_str wsFilter		("filter");
	auto_xerces_str wsMaxConnections("max_connections");
	auto_xerces_str wsRemoteIP		("remote_ip");
	auto_xerces_str	wsRemotePort	("remote_port");
	auto_xerces_str wsReconnect		("reconnect");

	auto_xerces_str wsAcceptorName	("acceptor");
	auto_xerces_str	wsConnectorName	("connector");
 	auto_xerces_str wsReceiverName	("receiver");
	auto_xerces_str wsSenderName	("sender");

	auto_xerces_str wsType			("type");


	while (pChild)
    {
		ENetworkType NetworkType = NETWORK_NONE;
		CProtocolInfo *pProtocol = null_v;
		CField *pCommandIDField	= null_v;
		CField *pSizeIDField = null_v;
		bool_ bIsAutoStart = true_v;

		if (0 == XMLString::compareString(pChild->getNodeName(),
										  wsAcceptorName))
		{
			NetworkType = NETWORK_ACCEPTOR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsConnectorName))
		{
			NetworkType = NETWORK_CONNECTOR;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsReceiverName))
		{
			NetworkType = NETWORK_RECEIVER;
		}
		else if (0 == XMLString::compareString(pChild->getNodeName(),
											   wsSenderName))
		{
			NetworkType = NETWORK_SENDER;
		}
		else
		{
			pChild = (DOMElement *)pChild->getNextSibling();

			continue;
		}

		auto_xerces_str sProtocolName(pChild->getAttribute(wsProtocolName));

		if (SUCCESS != _ERR(
				CXMLLoaderProtocol::Instance()->Load(pParser,
													 pszEnvironmentPath,
													 sProtocolName)))
		{
			_RET(XML_LOADER_ERROR);
		}

		//
		if (SUCCESS != _ERR(
                CProtocolManager::instance()->getProtocol(sProtocolName,
                        pProtocol)))
		{
			_RET(XML_LOADER_ERROR);
		}

		//
		auto_xerces_str sCommandID(pChild->getAttribute(wsCommandID));

        if (SUCCESS != _ERR(pProtocol->getHeadField(sCommandID,
                pCommandIDField))
			|| FIELD_NORMAL_STYLE !=
                (pCommandIDField->type() & FIELD_NORMAL_STYLE)
                || 4 < _LEN(pCommandIDField->type()))
		{
			_RET(XML_LOADER_ERROR);
		}

		//
		auto_xerces_str sSizeID(pChild->getAttribute(wsSizeID));

        if (SUCCESS != _ERR(pProtocol->getHeadField(sSizeID,
                pSizeIDField))
			|| FIELD_NORMAL_STYLE !=
                (pSizeIDField->type() & FIELD_NORMAL_STYLE)
                || 4 < _LEN(pSizeIDField->type()))
		{
			_RET(XML_LOADER_ERROR);
		}

		//
		auto_xerces_str wsAutoFalse("false");

		if (0 == XMLString::compareString(wsAutoFalse,
										  pChild->getAttribute(wsAuto)))
		{
			bIsAutoStart = false_v;
		}

        CNode *pNetwork = null_v;
		auto_xerces_str sName(pChild->getAttribute(wsName));

		switch (NetworkType)
		{
		case NETWORK_NONE:
			_RET(XML_LOADER_ERROR);
		case NETWORK_ACCEPTOR:
			{
				auto_xerces_str	sLocalPort(pChild->getAttribute(wsLocalPort));
				auto_xerces_str
					sMaxConnections(pChild->getAttribute(wsMaxConnections));

				pNetwork = new CAcceptor(pProtocol,
										 pCommandIDField,
										 pSizeIDField,
										 (ub_2)atoi(sLocalPort),
										 (size_)atoi(sMaxConnections),
										 bIsAutoStart);
			}

			break;
		case NETWORK_CONNECTOR:
			{
				//
				auto_xerces_str	nLocalPort	(pChild->getAttribute(wsLocalPort));
				auto_xerces_str	sRemoteIP	(pChild->getAttribute(wsRemoteIP));
				auto_xerces_str	nRemotePort
					(pChild->getAttribute(wsRemotePort));
				auto_xerces_str	sReconnect	(pChild->getAttribute(wsReconnect));

				pNetwork = new CConnector(pProtocol,
										  pCommandIDField,
										  pSizeIDField,
										  (ub_2)atoi(nLocalPort),
										  (const ch_1 *)sRemoteIP,
										  (ub_2)atoi(nRemotePort),
										  (b_4)atoi(sReconnect),
										  bIsAutoStart);
			}

			break;
		case NETWORK_RECEIVER:
			{
				//
				auto_xerces_str sLocalPort(pChild->getAttribute(wsLocalPort));


				pNetwork = new CReceiver(pProtocol,
										 pCommandIDField,
										 pSizeIDField,
										 (ub_2)atoi(sLocalPort),
										 bIsAutoStart);
			}

			break;
		case NETWORK_SENDER:
			{
				//
				auto_xerces_str sLocalPort(pChild->getAttribute(wsLocalPort));

				pNetwork = new CSender(pProtocol,
									   pCommandIDField,
									   pSizeIDField,
									   (ub_2)atoi(sLocalPort),
									   bIsAutoStart);
			}
		}

        CNodeConf *pNetworkConf = (CNodeConf *) pNetwork->getConf();

		//
		DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

		if (!pSub)
			_RET(XML_LOADER_ERROR);

		while (pSub)
		{
			if (0 == XMLString::compareString(pSub->getNodeName(),
											  wsIdentity))
			{
				//
				auto_xerces_str sIdentity(pSub->getAttribute(wsIdentity));
				ch_1 			*sIdentityName = null_v;

				if (SUCCESS != _ERR(GetLastName(sIdentity, sIdentityName)))
					_RET(XML_LOADER_ERROR);

                v_ *pV = pProtocol->data().value(sIdentityName);

				if (!pV)
					_RET(XML_LOADER_ERROR);

				//
				auto_xerces_str	sPDU(pSub->getAttribute(wsPDU));
                CPduInfo *pPDU = null_v;

                if (SUCCESS != _ERR(pProtocol->getPdu(sPDU, pPDU)))
					_RET(XML_LOADER_ERROR);

				//
				auto_xerces_str sDirection(pSub->getAttribute(wsDirection));
				EDirection		Direction;

				if (SUCCESS != _ERR(GetDirection(sDirection, Direction)))
					_RET(XML_LOADER_ERROR);

				//
				if (SUCCESS != _ERR(pNetworkConf->ConfigPDU(*pV,
															pPDU,
															Direction)))
				{
					_RET(XML_LOADER_ERROR);
				}
			}
			else if (0 == XMLString::compareString(pSub->getNodeName(),
												   wsFilter))
			{
				CIPFilter *pIPFilter = null_v;

				if (NETWORK_ACCEPTOR == NetworkType)
				{
					pIPFilter =
						&((CAcceptorConf *)pNetworkConf)->IPFilter();
				}
				else if (NETWORK_RECEIVER == NetworkType)
				{
					pIPFilter =
						&((CReceiverConf *)pNetworkConf)->IPFilter();
				}
				else
				{
					_RET(XML_LOADER_ERROR);
				}

				auto_xerces_str sType(pSub->getAttribute(wsType));

				if (0 == strcmp(sType, "forbid")) {
                    pIPFilter->setForbid(true_v);
                } else if (0 == strcmp(sType, "permit")) {
                    pIPFilter->setForbid(false_v);
                }

                auto_xerces_str sIPGroup(pSub->getTextContent());

                if (false_v == pIPFilter->addIpGroup((const ch_1 *) sIPGroup))
					_RET(XML_LOADER_ERROR);
			}

			pSub = (DOMElement *)pSub->getNextSibling();
		}

        if (SUCCESS != _ERR(CNetworkManager::instance()->AddNetwork(
														(const char *)sName,
														NetworkType,
														pNetwork)))
		{
			_RET(XML_LOADER_ERROR);
		}

		pChild = (DOMElement *)pChild->getNextSibling();
	}

	_RET(SUCCESS);
}

