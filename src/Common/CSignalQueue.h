/*!
* \file CSignalQueue.h
* \brief the header file for class of CQueue.h.
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 02/26/2015
*/

#ifndef _C_SIGNAL_QUEUE_H_
#define _C_SIGNAL_QUEUE_H_

#include "CGlobal.h"
#include "CResource.h"

#include <queue>

class CMutex;

class CSignal;

/// \brief CSignalQueue can queue a lot of CSignal instances.
///
/// CSignalQueue can avoid using of delete.
/// Notice: This class can support multi-thread signal sending and
/// single-thread signal receiving.
class CSignalQueue : CGlobal {
public:
    /// \brief The Constructor of CSignalQueue.
    ///
    /// \param maxNum The total number of CSignal instances you want to put
    /// into the queue.
    /// \param mutex Make the instance of CSignalQueue to support multi-thread
    /// if mutex is not null_v.
    CSignalQueue(const ub_4 maxNum, CMutex *mutex = null_v);

    /// \brief The Destructor of CSignalQueue.
    ~CSignalQueue();

    /// \brief Prepare the signal if there are free CSignal objects.
    ///
    /// \return Obtain null_v is there is no more CSignal object. DON'T FORGET
    /// to reclaim the signal by calling complete().
    CSignal *prepare();

    /// \brief Put the prepared signal into queue.
    ///
    /// Please call prepare() first before call this function
    /// \param signal The signal returned by calling prepare(), and don't call
    /// send twice or more for one signal.
    none_ send(const CSignal *signal);

    /// \brief Obtain the next signal if there are new signals
    ///
    /// \return Obtain null_v is there is no more signal
    CSignal *receive();

    /// \brief Reclaim the used signal.
    ///
    /// Any signal returned by calling receive() must call this function to
    /// reclaim.
    /// \param singal The signal returned by calling receive().
    none_ complete(const CSignal *signal);

private:
    const ub_4 _totalNum;
    CMutex     *_mutex;

    CResource<CSignal, CSignalQueue> _res;

    std::queue<CSignal *> _queue;
};

#endif // _C_SIGNAL_QUEUE_H_