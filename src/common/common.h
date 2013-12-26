#ifndef COMMON_H_
#define COMMON_H_

typedef char b_1;
typedef unsigned char ub_1;
typedef short b_2;
typedef unsigned short ub_2;
typedef int b_4;
typedef unsigned int ub_4;
typedef long long b_8;
typedef unsigned long long ub_8;

typedef float fb_4;
typedef double fb_8;

typedef char ch_1;

typedef enum {
    false_v,
    true_v
} bool_;

const b_4 null_v = 0;

typedef ub_4 size_;
typedef b_4 ret_;
typedef void *obj_;
typedef fb_8 max_v_;
typedef b_4 type_;

#define __del(POINT) { \
        delete POINT; \
        POINT = null_v; \
    }

#define __del_arr(POINT) { \
        delete[] POINT;  \
        POINT = null_v; \
    }

b_4 __sleep(ub_4 sec, ub_4 ms);

#include <log4c.h>

extern log4c_category_t *g_pCategory;

bool_ __init_log();
void __fini_log();

#define __debug(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_DEBUG, message, ##args)
#define __info(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_INFO, message, ##args)
#define __notice(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_NOTICE, message, ##args)
#define __warn(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_WARN, message, ##args)
#define __error(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_ERROR, message, ##args)
#define __crit(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_CRIT, message, ##args)
#define __alert(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_ALERT, message, ##args)
#define __fatal(message, args...) \
    log4c_category_log(g_pCategory, LOG4C_PRIORITY_FATAL, message, ##args)

#include <assert.h>

#endif // COMMON_H_