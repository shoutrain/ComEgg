#include "CFieldGroupDefined.h"

size_ CFieldGroupDefined::offset(size_ size,
        size_ blockSize,
        size_ index) const {
    if (0 == blockSize || size < index || size * _unitSize > blockSize || 0 == _sizeName[0]) {
        assert(0);
        logError("The parameter of CFieldGroupDefined::offset is wrong");
        return 0;
    }

    size_ offset = 0;

    if (index) {
        offset += (index - 1) * _unitSize;
    }

    if (blockSize <= offset) {
        assert(0);
        logError("The offset is not right in CFieldGroupDefined::offset");
        return 0;
    }

    return offset;
}

