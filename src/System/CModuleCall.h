#ifndef CMODULE_CALL_H
#define CMODULE_CALL_H

#include "CSysFactory.h"

class CModuleCall
{
public:
	CModuleCall()
	{
		m_pModuleCall = CSysFactory::Instance()->MakeModuleCall();
	}

	virtual ~CModuleCall()
	{
		_DEL(m_pModuleCall);
	}

	bool_ Call(const ch_1 *pszModulePath,
			   const ch_1 *pszModuleName, 
			   const ch_1 *pszModuleType,
			   const ch_1 *pszInterfaceName,
			   const ub_1 *pIn,
			   size_ nInSize, 
			   ub_1 *&pOut,
			   size_ &nOutSize)
	{
		if (!m_pModuleCall->Open(pszModulePath, pszModuleName, pszModuleType))
			return false_v;

		if (!m_pModuleCall->Call(pszInterfaceName, pIn, nInSize, pOut, nOutSize))
		{
			m_pModuleCall->Close();

			return false_v;
		}

		return m_pModuleCall->Close();
	}

private:
	CModuleCallImp *m_pModuleCall;
};

#endif // CMODULE_CALL_H
