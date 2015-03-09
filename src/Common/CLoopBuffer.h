/*!
* \file CLoopBuffer.h
* \brief The buffer like a cycle, which is often used as socket receiving
* buffer
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/15/2015
*/

#ifndef _C_LOOP_BUFFER_H_
#define _C_LOOP_BUFFER_H_

#include "CGlobal.h"

class CMutex;

class CLoopBuffer : CGlobal {
public:
    CLoopBuffer(ub_4 size, CMutex *mutex = null_v, bool_ isPadding = false_v);

    virtual ~CLoopBuffer();

    /// \brief Write data into the buffer.
    ///
    /// \param buffer The buffer to be write into the loop buffer.
    /// \param size The size of the buffer to be write.
    /// \return true_v if success, otherwise false_v.
    bool_ write(const ch_1 *buffer, ub_4 size);

    /// \brief Read data from the loop buffer to buffer
    ///
    /// \param buffer The buffer to be read from the loop buffer to.
    /// \param size The buffer size and the actual read size after returned.
    /// \return true_v if success, otherwise false_v.
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
