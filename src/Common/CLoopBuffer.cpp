#include "CLoopBuffer.h"
#include "CMutex.h"
#include "CAutoLock.h"

#include <string.h>

CLoopBuffer::CLoopBuffer(ub_4 size, CMutex *mutex, bool_ isPadding) :
        _totalSize(size) {
    assert(size);
    _actualSize = size;
    _usedSize  = 0;
    _freeSize  = size;
    _mutex     = mutex;
    _isPadding = isPadding;
    _padding   = 0;
    _writePoint = _readPoint = _buffer = new ch_1[size];
    assert(_buffer);
}

CLoopBuffer::~CLoopBuffer() {
    _DEL_ARR(_buffer);
}

bool_ CLoopBuffer::write(const ch_1 *buffer, ub_4 size) {
    assert(buffer);
    assert(size);

    CAutoLock al(_mutex);

    if (size > _freeSize) {
        return false_v;
    }

    if (_writePoint >= _readPoint) {
        ub_4 rightSize = _buffer + _totalSize - _writePoint;
        ub_4 leftSize = _readPoint - _buffer;

        assert(_padding == 0);
        assert(_actualSize == _totalSize);
        assert(_freeSize <= _totalSize);
        assert(_writePoint - _readPoint == (b_4) _usedSize);
        assert(rightSize + leftSize == _freeSize);

        if (rightSize >= size) {
            memcpy(_writePoint, buffer, size);
            _writePoint += size;
        } else if (_isPadding) {
            if (size > leftSize) {
                return false_v;
            }

            _padding = rightSize;
            _actualSize -= _padding;
            _freeSize -= _padding;
            assert(_freeSize == leftSize);

            memcpy(_buffer, buffer, size);
            _writePoint = _buffer + size;
        } else {
            memcpy(_writePoint, buffer, rightSize);
            memcpy(_buffer, buffer + rightSize, size - rightSize);
            _writePoint = _buffer + size - rightSize;
        }
    } else {
        assert(_readPoint - _writePoint == (int) _freeSize);
        memcpy(_writePoint, buffer, size);
        _writePoint += size;
        assert(_writePoint <= _readPoint);
    }

    _usedSize += size;
    _freeSize -= size;

    return true_v;
}

bool_ CLoopBuffer::read(ch_1 *buffer, ub_4 &size) {
    assert(buffer);
    assert(size);

    CAutoLock al(_mutex);

    if (0 == _usedSize) {
        size = 0;

        return true_v;
    }

    if (_writePoint > _readPoint) {
        assert(_padding == 0);
        assert(_writePoint - _readPoint == (int) _usedSize);

        if (size > _usedSize) {
            size = _usedSize;
        }

        memcpy(buffer, _readPoint, size);
        _readPoint += size;
    } else {
        assert(_readPoint - _writePoint == (int) _freeSize);

        ub_4 rightSize = _buffer + _actualSize - _readPoint;
        ub_4 leftSize = _writePoint - _buffer;

        assert(_actualSize == _totalSize - _padding);
        assert(rightSize + leftSize == _usedSize);

        if (rightSize >= size) {
            memcpy(buffer, _readPoint, size);
            _readPoint += size;

            if (rightSize == size && _padding) {
                _actualSize += _padding;
                _freeSize += _padding;
                _padding = 0;
                _readPoint = _buffer;
            }
        } else {
            if (_usedSize < size) {
                size = _usedSize;
            }

            memcpy(buffer, _readPoint, rightSize);
            memcpy(buffer + rightSize, _buffer, size - rightSize);
            _readPoint = _buffer + size - rightSize;

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

none_ CLoopBuffer::reset() {
    CAutoLock al(_mutex);

    _actualSize = _totalSize;
    _usedSize = 0;
    _freeSize = _totalSize;
    _padding  = 0;
    _writePoint = _readPoint = _buffer;
}

