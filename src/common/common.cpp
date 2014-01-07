/*
 * common.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: rafael
 */

#include "common.h"

#include <sys/time.h>
#include <sys/select.h>

b_4 __sleep(ub_4 sec, ub_4 ms) {
    struct timeval delay;

    delay.tv_sec = sec;
    delay.tv_usec = ms * 1000;

    return select(0, null_v, null_v, null_v, &delay);
}

log4c_category_t *g_pCategory;

bool_ __init_log() {
    if (0 != log4c_init()) {
        return false_v;
    }

    g_pCategory = log4c_category_get("ComEgg");

    return true_v;
}

none_ __fini_log() {
    log4c_fini();
}
