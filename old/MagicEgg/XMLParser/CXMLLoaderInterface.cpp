#include "CXMLLoaderInterface.h"

#include "../UI/CContainer.h"
#include "../UI/CLabel.h"
#include "../UI/CText.h"
#include "../UI/CTable.h"
#include "../UI/CButton.h"

CXMLLoaderInterface *CXMLLoaderInterface::m_pInstance = null_v;

ret_ CXMLLoaderInterface::Load(XercesDOMParser *pParser,
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

	ch_1 sInterface[ENVIRONMENT_PATH_LENGTH];

	memset(sInterface, 0, ENVIRONMENT_PATH_LENGTH);
	sprintf(sInterface, "%s%s", pszEnvironmentPath, UI_XML_FILE);

	DOMDocument *pInterfaceDoc = null_v;

	try
	{
        GetParser()->parse(sInterface);
        pInterfaceDoc = GetParser()->getDocument();
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

	if (!pInterfaceDoc)
		return XML_LOADER_ERROR;
	
	DOMElement *pRoot = pInterfaceDoc->getDocumentElement();

	if (!pRoot)
		return XML_LOADER_ERROR;

	auto_xerces_str wsContainer("container");
	auto_xerces_str wsLeft("left");
	auto_xerces_str wsTop("top");
	auto_xerces_str wsWidth("width");
	auto_xerces_str wsHeight("height");
	auto_xerces_str wsName("name");
	
	auto_xerces_str wsTitle("title");
	auto_xerces_str wsMaxLength("maxlength");
	auto_xerces_str wsReadOnly("readonly");	
	auto_xerces_str wsMultiline("multiline");
	auto_xerces_str wsSecret("secret");
	auto_xerces_str wsDisable("disable");
	auto_xerces_str wsValue("value");
	
	auto_xerces_str wsLabel("label");
	auto_xerces_str wsText("text");
	auto_xerces_str wsTable("table");
	auto_xerces_str wsButton("button");

	DOMElement *pElement = (DOMElement *)pRoot->getFirstChild();

	if (!pElement)
		return XML_LOADER_ERROR;

    while (pElement)
	{
		if (0 == XMLString::compareString(pElement->getNodeName(), wsContainer))
		{
			auto_xerces_str sLeft(pElement->getAttribute(wsLeft));
			auto_xerces_str sTop(pElement->getAttribute(wsTop));
			auto_xerces_str sWidth(pElement->getAttribute(wsWidth));
			auto_xerces_str sHeight(pElement->getAttribute(wsHeight));
			auto_xerces_str sName(pElement->getAttribute(wsName));
			auto_xerces_str sTitle(pElement->getAttribute(wsTitle));

			CContainer *pContainer = new CContainer(atoi(sLeft), 
													atoi(sTop),
													atoi(sWidth),
													atoi(sHeight),
													sName,
													sTitle);

			if (!CUIManager::Instance()->AddContainer(pContainer))
				return XML_LOADER_ERROR;

			DOMElement *pChild = (DOMElement *)pElement->getFirstChild();

			if (!pChild)
				return XML_LOADER_ERROR;

			while (pChild)
			{
				if (0 == XMLString::compareString(pChild->getNodeName(),
												  wsLabel))
				{
					auto_xerces_str sLeft(pChild->getAttribute(wsLeft));
					auto_xerces_str sTop(pChild->getAttribute(wsTop));
					auto_xerces_str sWidth(pChild->getAttribute(wsWidth));
					auto_xerces_str sHeight(pChild->getAttribute(wsHeight));
					auto_xerces_str sName(pChild->getAttribute(wsName));
					auto_xerces_str sValue(pChild->getAttribute(wsValue));

					CLabel *pLabel = new CLabel(atoi(sLeft),
												atoi(sTop),
												atoi(sWidth),
												atoi(sHeight),
												sName,
												sValue);

					if (!pContainer->AddChild(pLabel))
						return XML_LOADER_ERROR;
				}
				else if (0 == XMLString::compareString(pChild->getNodeName(),
													   wsText))
				{
					auto_xerces_str sLeft(pChild->getAttribute(wsLeft));
					auto_xerces_str sTop(pChild->getAttribute(wsTop));
					auto_xerces_str sWidth(pChild->getAttribute(wsWidth));
					auto_xerces_str sHeight(pChild->getAttribute(wsHeight));
					auto_xerces_str sName(pChild->getAttribute(wsName));
					auto_xerces_str sMaxLength(pChild->getAttribute(wsMaxLength));
					auto_xerces_str sReadOnly(pChild->getAttribute(wsReadOnly));	
					auto_xerces_str sMultiline(pChild->getAttribute(wsMultiline));
					auto_xerces_str sSecret(pChild->getAttribute(wsSecret));
					auto_xerces_str sValue(pChild->getAttribute(wsValue));

					CText *pText = new CText(
						atoi(sLeft),
						atoi(sTop),
						atoi(sWidth),
						atoi(sHeight),
						sName,
						atoi(sMaxLength),
						0 == strcmp(sReadOnly, "false") ? false_v : true_v,
						0 == strcmp(sMultiline, "false") ? false_v : true_v,
						0 == strcmp(sSecret, "false") ? false_v : true_v,
						sValue);
					
					if (!pContainer->AddChild(pText))
						return XML_LOADER_ERROR;
				}
				else if (0 == XMLString::compareString(pChild->getNodeName(),
													   wsTable))
				{
					auto_xerces_str sLeft(pChild->getAttribute(wsLeft));
					auto_xerces_str sTop(pChild->getAttribute(wsTop));
					auto_xerces_str sWidth(pChild->getAttribute(wsWidth));
					auto_xerces_str sHeight(pChild->getAttribute(wsHeight));
					auto_xerces_str sName(pChild->getAttribute(wsName));

					CTable *pTable = new CTable(atoi(sLeft),
												atoi(sTop),
												atoi(sWidth),
												atoi(sHeight),
												sName);

					if (!pContainer->AddChild(pTable))
						return XML_LOADER_ERROR;

					DOMElement *pSub = (DOMElement *)pChild->getFirstChild();

					while (pSub)
					{
						auto_xerces_str wsColumn("column");

						if (0 == XMLString::compareString(pSub->getNodeName(),
														  wsColumn))
						{
							auto_xerces_str sName(pSub->getAttribute(wsName));
							auto_xerces_str sWidth(pSub->getAttribute(wsWidth));

							if (!pTable->AddColumn(sName, atoi(sWidth)))
								return XML_LOADER_ERROR;
						}
						
						pSub = (DOMElement *)pSub->getNextSibling();
					}
				}
				else if (0 == XMLString::compareString(pChild->getNodeName(),
													   wsButton))
				{
					auto_xerces_str sLeft(pChild->getAttribute(wsLeft));
					auto_xerces_str sTop(pChild->getAttribute(wsTop));
					auto_xerces_str sWidth(pChild->getAttribute(wsWidth));
					auto_xerces_str sHeight(pChild->getAttribute(wsHeight));
					auto_xerces_str sName(pChild->getAttribute(wsName));
					auto_xerces_str sDisable(pChild->getAttribute(wsDisable));
					auto_xerces_str sValue(pChild->getAttribute(wsValue));

					CButton *pButton = new CButton(
						atoi(sLeft),
						atoi(sTop),
						atoi(sWidth),
						atoi(sHeight),
						sName,
						// Enable, not disable
						0 == strcmp(sDisable, "false") ? true_v : false_v,
						sValue);
					
					if (!pContainer->AddChild(pButton))
						return XML_LOADER_ERROR;
				}
				
				pChild = (DOMElement *)pChild->getNextSibling();
			}
		}

		pElement = (DOMElement *)pElement->getNextSibling();
	}

	return SUCCESS;
}

