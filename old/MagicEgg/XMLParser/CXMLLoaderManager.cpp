#include "CXMLLoaderManager.h"

CXMLLoaderManager *CXMLLoaderManager::m_pInstance = null_v;

ret_ CXMLLoaderManager::Start()
{
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException &err)
	{
		auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

		return XML_INITIALIZE_ERROR;
	}

    m_pParser = new XercesDOMParser();

    m_pParser->setValidationScheme(XercesDOMParser::Val_Always);
    m_pParser->setDoNamespaces(true);
    m_pParser->setDoSchema(true);
    m_pParser->setValidationSchemaFullChecking(true);

    m_pErrorHandle = new CXMLLoaderErrorHandle();

    m_pParser->setErrorHandler(m_pErrorHandle);

	return SUCCESS;
}

ret_ CXMLLoaderManager::Stop()
{
    _DEL(m_pErrorHandle);
	_DEL(m_pParser);

	try
	{
		XMLPlatformUtils::Terminate();
	}
	catch (const XMLException &err)
	{
		auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

		return XML_UNINITIALIZE_ERROR;
	}

	return SUCCESS;
}

ret_ CXMLLoaderManager::Load(const ch_1 *pszDirectory)
{
#ifdef _DEBUG_
	if (!m_pParser)
		return ELEMENT_NULL_IN_CONTAINER;
#endif

	ch_1 szEnvironmentPath[ENVIRONMENT_PATH_LENGTH];

	memset(szEnvironmentPath, 0, ENVIRONMENT_PATH_LENGTH);

	if (pszDirectory)
	{
		sprintf(szEnvironmentPath, 
				"%s%s%s", 
				DEFAULT_ENVIRONMENT_PATH, 
				pszDirectory, 
				"/");
	}
	else
	{
		sprintf(szEnvironmentPath, "%s", DEFAULT_ENVIRONMENT_PATH);
	}

	// Load protocol
	if (SUCCESS != CXMLLoaderProtocol::Instance()->Load(m_pParser,
														szEnvironmentPath))
	{
		return FAILURE;
	}

	CXMLLoaderProtocol::Instance()->Destory();

	// Load network
	if (SUCCESS != CXMLLoaderNetwork::Instance()->Load(m_pParser,
													   szEnvironmentPath))
	{
		return FAILURE;
	}

	CXMLLoaderNetwork::Instance()->Destory();

	// Load interface
	if (SUCCESS != CXMLLoaderInterface::Instance()->Load(m_pParser,
														 szEnvironmentPath))
	{
		return FAILURE;
	}

	CXMLLoaderInterface::Instance()->Destory();

	// Load actions
	if (SUCCESS != CXMLLoaderActions::Instance()->Load(m_pParser,
													   szEnvironmentPath))
	{
		return FAILURE;
	}

	CXMLLoaderActions::Instance()->Destory();
	
	return SUCCESS;
}
