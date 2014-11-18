#ifndef CSYS_FACTORY_H
#define CSYS_FACTORY_H

#include "CLinuxFileImp.h"
#include "CLinuxSysInfoImp.h"
#include "CLinuxSysCallImp.h"
#include "CLinuxModuleCallImp.h"

class CSysFactory
{
public:
	static CSysFactory *Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSysFactory();

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	CFileImp *MakeFile()
	{
		return (CFileImp *)new CLinuxFileImp();
	}

	CSysInfoImp *MakeSysInfo()
	{
		return (CSysInfoImp *)new CLinuxSysInfoImp();
	}

	CSysCallImp *MakeSysCall()
	{
		return (CSysCallImp *)new CLinuxSysCallImp();
	}

	CModuleCallImp *MakeModuleCall()
	{
		return (CModuleCallImp *)new CLinuxModuleCallImp();
	}

private:
	CSysFactory() {};

	CSysFactory(const CSysFactory &);
	const CSysFactory &operator =(const CSysFactory &);

	~CSysFactory();

	static CSysFactory *m_pInstance;
};

#endif // CSYS_FACTORY_H
