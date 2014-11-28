#include "CGlobal.h"

log4c_category_t *CGlobal::_category = null_v;

bool_ CGlobal::init() {
    if (0 != log4c_init()) {
        return false_v;
    }

    _category = log4c_category_get("ComEggLog");

    return true_v;
}

none_ CGlobal::deinit() {
    log4c_fini();
}

log4c_category_t *CGlobal::getCategory() {
    return _category;
}

b_4 CGlobal::sleep(ub_4 secs, ub_4 ms) {
    struct timeval delay;

    delay.tv_sec = secs;
    delay.tv_usec = ms * 1000;

    return select(0, null_v, null_v, null_v, &delay);
}
