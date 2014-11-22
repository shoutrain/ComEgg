#include "COptGetUsage.h"

#include "../System/CSysInfo.h"

void COptGetUsage::work(const TMessageUnit *tmu) {
    CSysInfo si;
    v_ usage((ub_1) si.GetUsage());

    (*_result->value(tmu)) = usage;
}



