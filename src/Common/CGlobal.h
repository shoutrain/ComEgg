/*!
* \file CGlobal.h
* \brief Define the class of CGlobal and log functions.
*
* All classes in this application should inherit from this class.
* All members in this classes should be static.
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/15/2015
*/

#ifndef _C_GLOBAL_H_
#define _C_GLOBAL_H_

#include "BaseType.h"

#include <log4c.h>

class CGlobal {
public:
    /// \brief Initialize the application.
    ///
    /// \return true_v for successful and false_v for failed.
    static bool_ init();

    /// \brief De-initialize the application.
    static none_ deinit();

    /// \brief Get the log category.
    ///
    /// Don't use is manually.
    static log4c_category_t *getCategory();

    /// \brief Up-level encapsulation for sleep function.
    static b_4 sleep(ub_4 secs, ub_4 ms = 0);

protected:
    CGlobal() {
    }

    ~CGlobal() {
    }

private:
    static log4c_category_t *_category;
};

#define logDebug(message, args...) \
        log4c_category_log(CGlobal::getCategory(), LOG4C_PRIORITY_DEBUG, message, ##args)
#define logInfo(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_INFO, message, ##args)
#define logNotice(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_NOTICE, message, ##args)
#define logWarn(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_WARN, message, ##args)
#define logError(message, args...) \
        log4c_category_log(CGlobal::getCategory(), LOG4C_PRIORITY_ERROR, message, ##args)
#define logCrit(message, args...) \
        log4c_category_log(CGlobal::getCategory(), LOG4C_PRIORITY_CRIT, message, ##args)
#define logAlert(message, args...) \
        log4c_category_log(CBase::getCategory(), LOG4C_PRIORITY_ALERT, message, ##args)
#define logFatal(message, args...) \
        log4c_category_log(CGlobal::getCategory(), LOG4C_PRIORITY_FATAL, message, ##args)

#endif // _C_GLOBAL_H_
