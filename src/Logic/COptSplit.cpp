#include "COptSplit.h"
#include "../System/CSysCall.h"

none_ COptSplit::work(const TMessageUnit *tmu) {
    v_ success((b_4) true_v);
    v_ failure((b_4) false_v);

    (*_result->value(tmu)) = failure;

    v_ command("./ComEgg ", 0);

    command = command + (*_environment->value(tmu));

    CSysCall sysCall;

    if (!sysCall.exec((const ch_1 *) command)) {
        return;
    }

    (*_result->value(tmu)) = success;
}



