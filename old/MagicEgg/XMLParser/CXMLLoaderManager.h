#ifndef CXML_LOADER_MANAGER_H
#define CXML_LOADER_MANAGER_H

#include "CXMLLoaderErrorHandle.h"
#include "CXMLLoaderProtocol.h"
#include "CXMLLoaderNetwork.h"
#include "CXMLLoaderInterface.h"
#include "CXMLLoaderActions.h"

class CXMLLoaderManager
{
public:
	static CXMLLoaderManager *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CXMLLoaderManager;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ Load(const ch_1 *pszDirectory = null_v);

protected:
	ret_ Start();
	ret_ Stop();

private:
	CXMLLoaderManager()
	{
		Start();
	}

	CXMLLoaderManager(const CXMLLoaderManager &Manager);
	const CXMLLoaderManager &operator =(const CXMLLoaderManager &);

	virtual ~CXMLLoaderManager()
	{
		Stop();
	}

	XercesDOMParser *m_pParser;
    CXMLLoaderErrorHandle *m_pErrorHandle;

	static CXMLLoaderManager *m_pInstance;
};

#endif // CXML_LOADER_MANAGER_H
