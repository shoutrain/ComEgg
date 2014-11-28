#ifndef _TRANSACTION_COMMON_H_
#define _TRANSACTION_COMMON_H_

#include "CGlobal.h"
#include "../Logic/CProgram.h"
#include "../Network/NetworkCommon.h"

const ub_4 TRANSACTION_NAME_LENGTH = 32;
const ub_4 CATEGORY_NAME_LENGTH    = 32;
const ub_4 KEY_NAME_LENGTH         = 32;

enum ENormalHandle {
    START_HANDLE,
    OVER_HANDLE,
    DEFAULT_IN_HANDLE,
    DEFAULT_OUT_HANDLE,

    NORMAL_HANDLE
};

#endif // _TRANSACTION_COMMON_H_
