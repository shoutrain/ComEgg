#ifndef C_LOOP_BUFFER_H_
#define C_LOOP_BUFFER_H_

#include "CBase.h"

class CMutex;

class CLoopBuffer: public CBase {
public:
    CLoopBuffer(ub_4 size, CMutex *pMutex = null_v, bool_ isPadding = false_v);
    virtual ~CLoopBuffer();

    // pBuffer: the buffer to be write to the LoopBuffer
    // uiSize: the buffer size
    // Return true if success, otherwise false
    bool_ write(const b_1 *pBuffer, ub_4 size);

    // pBuffer: the buffer to be read in
    // uiSize: the buffer size, the actual read size
    // Return true if success, otherwise false
    bool_ read(b_1 *pBuffer, ub_4 &size);

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
    char *_pBuffer;

private:
    const ub_4 _totalSize;
    ub_4 _actualSize; // = _totalSize - _isPadding
    ub_4 _usedSize; // _actualSize - _freeSize
    ub_4 _freeSize; // _actualSize - _usedSize

    bool_ _isPadding;
    ub_4 _padding; // = _totalSize - _actualSize

    b_1 *_pWritePoint;
    b_1 *_pReadPoint;

    CMutex *_pMutex;
};

#endif // C_LOOP_BUFFER_H_
