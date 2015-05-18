#ifndef CBASE_CLASS_H
#define CBASE_CLASS_H

#include "Common.h"

#include "stdio.h"

class CBaseClass
{
protected:
	CBaseClass(class_sign ClassID/* = CBASECLASS*/): m_ClassID(ClassID) {}

	void SetFunID(fun_id FunID)
	{
		// can print bug information here
	}

	ret_ GetRetCode(fun_id FunID, error_code ErrorCode) const
	{
		// can print bug information here
		return GetRetCode(FunID, (ret_)ErrorCode);
	}

	ret_ GetRetCode(fun_id FunID, ret_ ErrorCode) const
	{
		// can print bug information here
#ifdef _DEBUG_
		static size_ nSize;

		printf("[%08X] class_id: 0x%08X, fun_id: 0x%08X, error_code: 0x%08X\n",
				++nSize, (b_4)m_ClassID, (b_4)FunID, (b_4)ErrorCode);
#endif

		return (ret_)m_ClassID | (ret_)FunID | ErrorCode;
	}

private:
	CBaseClass();
	// CBaseClass(const CXMLLoader &);
	// const CBaseClass &operator =(const CXMLLoader &);

	class_sign m_ClassID;
};

#endif // CBASE_CLASS_H
