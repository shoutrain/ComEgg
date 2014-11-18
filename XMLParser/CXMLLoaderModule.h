#ifndef CXML_LOADER_MODULE_H
#define CXML_LOADER_MODULE_H

#include "CXMLLoader.h"

#include "../Modules/CModuleInfo.h"
#include "../Modules/CInterfaceInfo.h"

class CXMLLoaderModule: public CXMLLoader
{
public:
	static CXMLLoaderModule *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CXMLLoaderModule;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ Load(XercesDOMParser *pParser, const ch_1 *pszEnvironmentPath);

private:
	ret_ LoadModule(const DOMElement *pElement);
	ret_ LoadInterface(const DOMElement *pElement);
	ret_ LoadInterfaceField(const DOMElement *pElement, 
							EFieldStyle FieldStyle,
							bool_ bIsInField = true_v,
							bool_ bIsSubField = false_v,
							ch_1 *pszGroupName = null_v);

	CXMLLoaderModule()
		: CXMLLoader(CXMLLOADERMODULE), 
		  m_pModule(null_v),
		  m_pInterface(null_v) {}

	CXMLLoaderModule(const CXMLLoaderModule &);
	const CXMLLoaderModule &operator =(const CXMLLoaderModule &);

	static CXMLLoaderModule *m_pInstance;

	CModuleInfo *m_pModule;
	CInterfaceInfo *m_pInterface;
};

#endif // CXML_LOADER_MODULE_H

