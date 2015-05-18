#ifndef CSYS_FACTORY_H
#define CSYS_FACTORY_H

#include "CLinuxFileImp.h"
#include "CLinuxSysCallImp.h"

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

	CSysCallImp *MakeSysCall()
	{
		return (CSysCallImp *)new CLinuxSysCallImp();
	}

private:
	CSysFactory() {};

	CSysFactory(const CSysFactory &);
	const CSysFactory &operator =(const CSysFactory &);

	~CSysFactory();

	static CSysFactory *m_pInstance;
};

#endif // CSYS_FACTORY_H
