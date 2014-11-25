#include "COptReadFile.h"
#include "../System/CFile.h"

none_ COptReadFile::work(const TMessageUnit *tmu) {
    v_ ornFileName = (*_filePath->value(tmu))
            + (*_fileName->value(tmu));
    ub_1 *buffer = new ub_1[REV_BUFFER_MAX_SIZE];
    CFile readFile;
    size_ readSize;

    if (!readFile.readFile((const ch_1 *) ornFileName, buffer,
            REV_BUFFER_MAX_SIZE, readSize)) {
        assert(0);
        // TODO do something to let outside know
        return;
    }

    (*_result->Value(tmu)) = v_((ub_1 *) buffer);
}

