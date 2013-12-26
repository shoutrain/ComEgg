#include "CLoopBuffer.h"
#include "CMutex.h"
#include "CAutoLock.h"

#include <cstring>

CLoopBuffer::CLoopBuffer(ub_4 size, CMutex *pMutex, bool_ isPadding) :
        _totalSize(size) {
    assert(size);
    _actualSize = size;
    _usedSize = 0;
    _freeSize = size;
    _pMutex = pMutex;
    _isPadding = isPadding;
    _padding = 0;
    _pWritePoint = _pReadPoint = _pBuffer = new b_1[size];
    assert(_pBuffer);
}

CLoopBuffer::~CLoopBuffer() {
    __del_arr(_pBuffer);
}

bool_ CLoopBuffer::write(const b_1 *pBuffer, ub_4 size) {
    assert(pBuffer);
    assert(size);

    CAutoLock al(_pMutex);

    if (size > _freeSize) {
        return false_v;
    }

    if (_pWritePoint >= _pReadPoint) {
        ub_4 rightSize = _pBuffer + _totalSize - _pWritePoint;
        ub_4 leftSize = _pReadPoint - _pBuffer;

        assert(_padding == 0);
        assert(_actualSize == _totalSize);
        assert(_freeSize <= _totalSize);
        assert(_pWritePoint - _pReadPoint == (b_4) _usedSize);
        assert(rightSize + leftSize == _freeSize);

        if (rightSize >= size) {
            memcpy(_pWritePoint, pBuffer, size);
            _pWritePoint += size;
        } else if (_isPadding) {
            if (size > leftSize)
                return false_v;

            _padding = rightSize;
            _actualSize -= _padding;
            _freeSize -= _padding;
            assert(_freeSize == leftSize);

            memcpy(_pBuffer, pBuffer, size);
            _pWritePoint = _pBuffer + size;
        } else {
            memcpy(_pWritePoint, pBuffer, rightSize);
            memcpy(_pBuffer, pBuffer + rightSize, size - rightSize);
            _pWritePoint = _pBuffer + size - rightSize;
        }
    } else {
        assert(_pReadPoint - _pWritePoint == (b_4) _freeSize);
        memcpy(_pWritePoint, pBuffer, size);
        _pWritePoint += size;
        assert(_pWritePoint <= _pReadPoint);
    }

    _usedSize += size;
    _freeSize -= size;

    return true_v;
}

bool_ CLoopBuffer::read(b_1 *pBuffer, ub_4 &size) {
    assert(pBuffer);
    assert(size);

    CAutoLock al(_pMutex);

    if (0 == _usedSize) {
        size = 0;

        return true_v;
    }

    if (_pWritePoint > _pReadPoint) {
        assert(_padding == 0);
        assert(_pWritePoint - _pReadPoint == (b_4) _usedSize);

        if (size > _usedSize)
            size = _usedSize;

        memcpy(pBuffer, _pReadPoint, size);
        _pReadPoint += size;
    } else {
        assert(_pReadPoint - _pWritePoint == (b_4) _freeSize);

        ub_4 rightSize = _pBuffer + _actualSize - _pReadPoint;
        ub_4 leftSize = _pWritePoint - _pBuffer;

        assert(_actualSize == _totalSize - _padding);
        assert(rightSize + leftSize == _usedSize);

        if (rightSize >= size) {
            memcpy(pBuffer, _pReadPoint, size);
            _pReadPoint += size;

            if (rightSize == size && _padding) {
                _actualSize += _padding;
                _freeSize += _padding;
                _padding = 0;
                _pReadPoint = _pBuffer;
            }
        } else {
            if (_usedSize < size) {
                size = _usedSize;
            }

            memcpy(pBuffer, _pReadPoint, rightSize);
            memcpy(pBuffer + rightSize, _pBuffer, size - rightSize);
            _pReadPoint = _pBuffer + size - rightSize;

            if (_padding) {
                _actualSize += _padding;
                _freeSize += _padding;
                _padding = 0;
            }
        }
    }

    _usedSize -= size;
    _freeSize += size;

    return true_v;
}

void CLoopBuffer::reset() {
    CAutoLock al(_pMutex);

    _actualSize = _totalSize;
    _usedSize = 0;
    _freeSize = _totalSize;
    _padding = 0;
    _pWritePoint = _pReadPoint = _pBuffer;
}

