#ifndef _C_LOOP_BUFFER_H_
#define _C_LOOP_BUFFER_H_

#include "CGlobal.h"

class CMutex;

class CLoopBuffer {
public:
    CLoopBuffer(ub_4 size, CMutex *mutex = null_v, bool_ isPadding = false_v);

    virtual ~CLoopBuffer();

    // buffer: the buffer to be writeFile to the LoopBuffer
    // size: the buffer size
    // Return true if success, otherwise false
    bool_ write(const ch_1 *buffer, ub_4 size);

    // buffer: the buffer to be readFile in
    // size: the buffer size, the actual readFile size
    // Return true if success, otherwise false
    bool_ read(ch_1 *buffer, ub_4 &size);

    none_ reset();

    ub_4 getTotalSize() const {
        return _totalSize;
    }

    ub_4 getActualSize() const {
        return _actualSize;
    }

    ub_4 getFreeSize() const {
        return _freeSize;
    }

    ub_4 getUsedSize() const {
        return _usedSize;
    }

protected:
    char *_buffer;

private:
    const ub_4 _totalSize;
    ub_4  _actualSize; // _totalSize - _padding
    ub_4  _usedSize; // _actualSize - _freeSize
    ub_4  _freeSize; // _actualSize - _userSize

    bool_ _isPadding;
    ub_4  _padding; // _totalSize - _actualSize

    ch_1 *_writePoint;
    ch_1 *_readPoint;

    CMutex *_mutex;
};

#endif // _C_LOOP_BUFFER_H_
