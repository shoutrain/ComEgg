#include "CBase.h"

#include <sys/time.h>
#include <sys/select.h>

log4c_category_t *CBase::_category = null_v;

bool_ CBase::init() {
    if (0 != log4c_init()) {
        return false_v;
    }

    _category = log4c_category_get("ComEggLog");

    return true_v;
}

none_ CBase::deinit() {
    log4c_fini();
}

log4c_category_t *CBase::getCategory() {
    return _category;
}

b_4 CBase::sleep(ub_4 secs, ub_4 ms) {
    struct timeval delay;

    delay.tv_sec = secs;
    delay.tv_usec = ms * 1000;

    return select(0, null_v, null_v, null_v, &delay);
}

CBase::CBase() {
}

CBase::~CBase() {
}
