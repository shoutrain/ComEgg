#include "CFieldString.h"

size_ CFieldString::offset(const ub_1 *block,
        size_ blockSize,
        size_ index) const {
    if (!block || 0 == blockSize) {
        assert(0);
        log_error("The parameters block and blockSize are not right in CFieldString::offset");
        return 0;
    }

    size_ offset = 0;

    if (_prevField) {
        offset += _prevField->offset(block, blockSize)
                + _prevField->size(block, blockSize);
    }

    if (index && _groupField) {
        offset += _groupField->offset(block, blockSize, index);
    }

    if (blockSize < offset + size(block, blockSize)) {
        assert(0);
        log_error("blockSize in CFieldString::offset is overloaded");
        return 0;
    }

    return offset;
}

