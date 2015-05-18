#ifndef CXML_LOADER_ERROR_HANDLE_H
#define CXML_LOADER_ERROR_HANDLE_H

#include "XMLParserCommon.h"

class CXMLLoaderErrorHandle: public ErrorHandler, public CBaseClass
{
public:
	CXMLLoaderErrorHandle(): CBaseClass(CXMLLOADERERRORHANDLE) 
    {
        m_bIsError = false_v;
    }
    
	virtual ~CXMLLoaderErrorHandle() {}

    void warning(const SAXParseException &toCatch);
    void error(const SAXParseException &toCatch);
    void fatalError(const SAXParseException &toCatch);
    void resetErrors();

    bool IsError() const
    {
        return m_bIsError;
    }

private :
    CXMLLoaderErrorHandle(const CXMLLoaderErrorHandle &);
    const CXMLLoaderErrorHandle &operator =(const CXMLLoaderErrorHandle &);

    bool_ m_bIsError;
};

#endif // CXML_LOADER_ERROR_HANDLE_H
