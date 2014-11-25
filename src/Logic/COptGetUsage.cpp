#include "COptGetUsage.h"

#include "../System/CSysInfo.h"

none_ COptGetUsage::work(const TMessageUnit *tmu) {
    CSysInfo si;
    v_ usage((ub_1) si.getUsage());

    (*_result->value(tmu)) = usage;
}



