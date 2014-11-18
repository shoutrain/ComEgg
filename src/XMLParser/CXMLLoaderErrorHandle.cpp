#include "CXMLLoaderErrorHandle.h"

void CXMLLoaderErrorHandle::warning(const SAXParseException &)
{
}

void CXMLLoaderErrorHandle::error(const SAXParseException &toCatch)
{
    m_bIsError = true_v;
}

void CXMLLoaderErrorHandle::fatalError(const SAXParseException &toCatch)
{
    m_bIsError = true_v;
}

void CXMLLoaderErrorHandle::resetErrors()
{
    m_bIsError = false_v;
}
