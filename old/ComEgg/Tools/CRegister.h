#ifndef CREGISTER_H
#define CREGISTER_H

#include "../Common/CBaseClass.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, v_ *>			map_variable;
typedef map<string, map_variable *>	map_category;

class CRegister: public CBaseClass
{
public:
	static CRegister *Instance()
	{
		if (m_pInstance)
			return m_pInstance;

		m_pInstance = new CRegister;

		return m_pInstance;
	}

	static void Destory()
	{
		_DEL(m_pInstance);
	}

	ret_ Search(const ch_1 *pszCategory, const ch_1 *pszKey, v_ *&pVariable);
	ret_ Register(const ch_1 *pszCategory, const ch_1 *pszKey, const v_ *pVariable,
				  const bool_ bIsCovered = false_v);
	ret_ Unregister(const ch_1 *pszCategory, const ch_1 *pszKey);

protected:
	CRegister(): CBaseClass(CREGISTER) {}

	CRegister(const CRegister &);
	const CRegister &operator =(const CRegister &);

	virtual ~CRegister()
	{
		Stop();
	}

	ret_ Stop();

private:
	static CRegister *m_pInstance;

	map_category m_CategoryMap;
};

#endif // CREGISTER_H
