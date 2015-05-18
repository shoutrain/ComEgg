#ifndef COMMON_H
#define COMMON_H

#define _DEBUG_

#include "variable.h"
	
// Parser returned value
#define _MOD(RET) \
	(MODULE_SIGN & (RET))

#define _CLS(RET) \
	(CLASS_SIGN & (RET))

#define _FUN(RET) \
	(FUN_ID & (RET))

#define _ERR(RET) \
	(ERROR_CODE & (RET))

//
#ifdef _DEBUG_

	#define _START(FUN_ID) \
		fun_id FunID = (FUN_ID); \
		SetFunID(FunID)

	#define _RET(ERROR) \
		return GetRetCode(FunID, (ERROR))

#else

	#define _START(FUN_ID)

	#define _RET(ERROR) \
		return (ERROR)

#endif

// Retrun result by called functions'
#define _RET_BY(RET) \
	return (RET)

#endif // COMMON_H
