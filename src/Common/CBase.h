#ifndef _C_BASE_H_
#define _C_BASE_H_

#include "BaseType.h"

#include <assert.h>
#include <log4c.h>

class CBase {
public:
    static bool_ init();

    static none_ deinit();

    static log4c_category_t *getCategory();

    static b_4 sleep(ub_4 secs, ub_4 ms = 0);

protected:
    CBase();

    ~CBase();

private:
    static log4c_category_t *_category;
};

#define logDebug(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_DEBUG, message, ##args)
#define logInfo(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_INFO, message, ##args)
#define logNotice(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_NOTICE, message, ##args)
#define logWarn(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_WARN, message, ##args)
#define logError(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_ERROR, message, ##args)
#define logCrit(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_CRIT, message, ##args)
#define logAlert(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_ALERT, message, ##args)
#define logFatal(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_FATAL, message, ##args)

#endif // _C_BASE_H_
