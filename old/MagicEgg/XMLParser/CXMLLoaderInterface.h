#ifndef CXML_LOADER_INTERFACE_H
#define CXML_LOADER_INTERFACE_H

#include "CXMLLoader.h"

class CXMLLoaderInterface: public CXMLLoader
{
public:
	static CXMLLoaderInterface *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CXMLLoaderInterface;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ Load(XercesDOMParser *pParser, const ch_1 *pszEnvironmentPath);

private:
	CXMLLoaderInterface() {}
	CXMLLoaderInterface(const CXMLLoaderInterface &);
	const CXMLLoaderInterface &operator =(const CXMLLoaderInterface &);

	static CXMLLoaderInterface *m_pInstance;
};

#endif // CXML_LOADER_INTERFACE_H

