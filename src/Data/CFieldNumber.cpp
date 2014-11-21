#include "CFieldNumber.h"

size_ CFieldNumber::offset(const ub_1 *block,
        size_ blockSize,
        size_ index) const {
    if (!block || 0 == blockSize) {
        assert(0);
        logError("The parameters block and blockSize are not right in CFieldNumber::offset");
        return 0;
    }

    size_ nOffset = 0;

    if (_prevField) {
        nOffset += _prevField->offset(block, blockSize)
                + _prevField->size(block, blockSize);
    }

    if (index && _groupField) {
        nOffset += _groupField->offset(block, blockSize, index);
    }

    if (blockSize < nOffset + size(block, blockSize)) {
        assert(0);
        logError("blockSize in CFieldNumber::offset is overloaded");
        return 0;
    }

    return nOffset;
}

