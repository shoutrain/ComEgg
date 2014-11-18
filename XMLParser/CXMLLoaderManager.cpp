#include "CXMLLoaderManager.h"

CXMLLoaderManager *CXMLLoaderManager::m_pInstance = null_v;

ret_ CXMLLoaderManager::Start()
{
	_START(START);

	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException &err)
	{
		auto_xerces_str sErr(err.getMessage());

		printf("%s\n", (const ch_1 *)sErr);

		_RET(XML_INITIALIZE_ERROR);
	}

//	XMLCh				wsLS[]	= {chLatin_L, chLatin_S, chNull};
//	DOMImplementation	*pImpl	=
//		DOMImplementationRegistry::getDOMImplementation(wsLS);

    m_pParser = new XercesDOMParser();

    m_pParser->setValidationScheme(XercesDOMParser::Val_Always);
    m_pParser->setDoNamespaces(true);
    m_pParser->setDoSchema(true);
    m_pParser->setValidationSchemaFullChecking(true);

    m_pErrorHandle = new CXMLLoaderErrorHandle();

    m_pParser->setErrorHandler(m_pErrorHandle);

	_RET(SUCCESS);
}

ret_ CXMLLoaderManager::Stop()
{
	_START(STOP);

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

		_RET(XML_UNINITIALIZE_ERROR);
	}

	_RET(SUCCESS);
}

ret_ CXMLLoaderManager::Load(const ch_1 *pszDirectory)
{
	_START(LOAD);

#ifdef _DEBUG_
	if (!m_pParser)
		_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

	ch_1 pszEnvironmentPath[ENVIRONMENT_PATH_LENGTH];

	memset(pszEnvironmentPath, 0, ENVIRONMENT_PATH_LENGTH);

	if (pszDirectory)
	{
		strcpy(pszEnvironmentPath, pszDirectory);
		strcat(pszEnvironmentPath, "/");
	}
	else
	{
		strcpy(pszEnvironmentPath, DEFAULT_ENVIRONMENT_PATH);
	}

	// Load networks and protocols
	ret_ Ret = CXMLLoaderNetwork::Instance()->Load(m_pParser,
												   pszEnvironmentPath);

	if (SUCCESS != _ERR(Ret))
		_RET_BY(Ret);

	CXMLLoaderNetwork::Instance()->Destory();


	// Load modules
	Ret = CXMLLoaderModule::Instance()->Load(m_pParser,
											 pszEnvironmentPath);

	if (SUCCESS != _ERR(Ret) &&
		XML_FILE_NOT_EXIST != _ERR(Ret) &&
		XML_MODULE_NOT_EXIST != _ERR(Ret))
	{
		_RET_BY(Ret);
	}

	CXMLLoaderModule::Instance()->Destory();

	// Load transactions
	Ret = CXMLLoaderTransaction::Instance()->Load(m_pParser,
												  pszEnvironmentPath);


	if (SUCCESS != _ERR(Ret))
		_RET_BY(Ret);

	CXMLLoaderTransaction::Instance()->Destory();

	_RET(SUCCESS);
}
