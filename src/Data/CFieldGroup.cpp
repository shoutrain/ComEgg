#include "CFieldGroup.h"

size_ CFieldGroup::size(const ub_1 *block, size_ blockSize) const {
    if (!block || 0 == blockSize) {
        assert(0);
        logError("The parameters block and blockSize are not right in CFieldGroup::size");
        return 0;
    }

    if (null_v == _sizeField) {
        assert(0);
        logError("_sizeField is not right in CFieldGroup::size");
        return 0;
    }

    size_ unitNum = (size_) *(block + _sizeField->offset(block,
            blockSize));

    return _unitSize * unitNum;
}

size_ CFieldGroup::offset(const ub_1 *block,
        size_ blockSize,
        size_ index) const {
    if (!block || 0 == blockSize) {
        assert(0);
        logError("The parameters block and blockSize are not right in CFieldGroup::offset");
        return 0;
    }

    size_ offset = 0;

    if (_prevField) {
        offset += _prevField->offset(block, blockSize)
                + _prevField->size(block, blockSize);
    }

    if (index) {
        offset += (index - 1) * _unitSize;
    }

    if (blockSize <= offset) {
        assert(0);
        logError("blockSize in CFieldGroup::offset is overloaded");
        return 0;
    }

    return offset;
}
