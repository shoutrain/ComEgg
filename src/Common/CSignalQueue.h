/*!
* \file CSignalQueue.h
* \brief the header file for class of CQueue.h.
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/18/2015
*/

#ifndef _C_SIGNAL_QUEUE_H_
#define _C_SIGNAL_QUEUE_H_

#include "CGlobal.h"

class CMutex;
class Signal;

/// \brief CSignalQueue can queue a lot of CSignal instances.
///
/// CSignalQueue can avoid using of delete.
/// Notice: This class can support multi-thread signal sending and
/// single-thread signal receiving
class CSignalQueue : CGlobal {
public:
    /// \brief The Constructor of CSignalQueue
    ///
    /// \param maxNum The total number of CSignal instances you want to queue.
    /// \param mutex Make the instance of CSignalQueue to support multi-thread
    /// if mutex is not null_v.
    CSignalQueue(const ub_4 maxNum, CMutex *mutex = null_v);

    /// \brief The Destructor of CSignalQueue
    ~CSignalQueue();

    /// \brief Prepare the signal if there are free CSignal objects
    ///
    /// This function will lock the queue until you call send()
    /// \return Obtain null_v is there is no more CSignal object
    CSignal *prepare();

    /// \brief the signal prepared is ready
    ///
    /// Please call prepare() first before call this function
    none_ send();

    /// \brief Obtain the next signal if there are new signals
    ///
    /// \return Obtain null_v is there is no more signal
    CSignal *receive();

private:
    const ub_4 _maxNum;
    CSignal    *_signals;
    CMutex     *_mutex;

    struct TSignalNode {
        CSignal *prevSignal;
        CSignal *curSignal;
        CSignal *nextSignal;
    };

    CSignal *_curPreparedItem;

    TSignalNode _queueHead;
    TSignalNode _queueTail;
};

#endif // _C_SIGNAL_QUEUE_H_