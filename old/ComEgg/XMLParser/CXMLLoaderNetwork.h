#ifndef CXML_LOADER_NETWORK_H
#define CXML_LOADER_NETWORK_H

#include "CXMLLoader.h"
#include "CXMLLoaderProtocol.h"

class CXMLLoaderNetwork: public CXMLLoader
{
public:
	static CXMLLoaderNetwork *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CXMLLoaderNetwork;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ Load(XercesDOMParser *pParser, const ch_1 *pszEnvironmentPath);

private:
	CXMLLoaderNetwork(): CXMLLoader(CXMLLOADERNETWORK) {}

	CXMLLoaderNetwork(const CXMLLoaderNetwork &);
	const CXMLLoaderNetwork &operator =(const CXMLLoaderNetwork &);

	static CXMLLoaderNetwork *m_pInstance;
};

#endif // CXML_LOADER_NETWORK_H

