#ifndef CXML_LOADER_PROTOCOL_H
#define CXML_LOADER_PROTOCOL_H

#include "CXMLLoader.h"

class CXMLLoaderProtocol: public CXMLLoader
{
public:
	static CXMLLoaderProtocol *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CXMLLoaderProtocol;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ Load(XercesDOMParser *pParser, 
			  const ch_1 *pszEnvironmentPath,
			  const ch_1 *pszProtocolName);

private:
	ret_ LoadPDU(const DOMElement *pElement, const ch_1 *pszPDUName = null_v);
	ret_ LoadPDUField(const DOMElement *pElement, 
					  EFieldStyle FieldStyle,
					  CPDUInfo *pPDUInfo = null_v, 
					  bool_ bIsSubField = false_v,
					  ch_1 *pszGroupName = null_v);

	CXMLLoaderProtocol()
		: CXMLLoader(CXMLLOADERPROTOCOL), 
		  m_pProtocol(null_v) {}

	CXMLLoaderProtocol(const CXMLLoaderProtocol &);
	const CXMLLoaderProtocol &operator =(const CXMLLoaderProtocol &);

	static CXMLLoaderProtocol *m_pInstance;

	CProtocolInfo *m_pProtocol;
};

#endif // CXML_LOADER_PROTOCOL_H

