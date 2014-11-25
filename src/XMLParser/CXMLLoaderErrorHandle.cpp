#include "CXMLLoaderErrorHandle.h"

none_ CXMLLoaderErrorHandle::warning(const SAXParseException &)
{
}

none_ CXMLLoaderErrorHandle::error(const SAXParseException &toCatch)
{
    m_bIsError = true_v;
}

none_ CXMLLoaderErrorHandle::fatalError(const SAXParseException &toCatch)
{
    m_bIsError = true_v;
}

none_ CXMLLoaderErrorHandle::resetErrors()
{
    m_bIsError = false_v;
}
