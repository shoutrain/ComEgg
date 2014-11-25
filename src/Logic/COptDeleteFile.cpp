#include "COptDeleteFile.h"

#include "../System/CFile.h"

none_ COptDeleteFile::work(const TMessageUnit *tmu) {
    v_ success((b_4) true_v);
    v_ failure((b_4) false_v);

    (*_result->value(tmu)) = failure;

    CFile delFile;

    if (!delFile.delFile((const ch_1 *) (*_filePath->Value(tmu)))) {
        assert(0);
        // TODO do something to let outside know
        return;
    }

    (*_result->Value(tmu)) = success;
}


