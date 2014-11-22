#include "COptSaveFile.h"
#include "../System/CFile.h"

void COptSaveFile::work(const TMessageUnit *tmu) {
    v_ success((b_4) true_v);
    v_ failure((b_4) false_v);

    (*_result->value(tmu)) = failure;

    v_ dstFileName = (*_filePath->value(tmu))
            + (*_fileName->value(tmu));
    CFile writeFile;

    if (!writeFile.Write((const ch_1 *) dstFileName,
            (const ub_1 *)
                    (const obj_) (*_fileContent->value(tmu)),
            REV_BUFFER_MAX_SIZE)) {
        assert(0);
        // TODO do something to tell outsider
        return;
    }

    (*_result->value(tmu)) = success;
}


