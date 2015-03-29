/*!
* \file CWorker.h
* \brief The header file for class of CWorker.
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 12/15/2014
*/

#ifndef SRC_COMMON_CWORKER_H_
#define SRC_COMMON_CWORKER_H_

#include "CGlobal.h"
#include "CMutex.h"
#include "CCond.h"

class IWorkable;

/// \brief CWorker wraps a thread with an internal signal queue.
///
///
class CWorker : CGlobal {
public:
    /// \brief The constructor of CWorker.
    ///
    /// \param threadStackSize The stack size(kilobyte) of the thread.
    /// \param signalBufferSize The size(byte) of the signal buffer size.
    CWorker(ub_4 threadStackSize, ub_4 signalBufferSize);

    /// \brief The destructor of CWorker.
    virtual ~CWorker();

    /// \brief Make CWorker instance to run.
    ///
    /// \param workable IWorkable instance.
    /// \param informed If informed is true, the function will return until the
    /// thread has been started successfully.
    /// \param sync If sync is true(the param is valid only informed is true),
    /// the invoke thread will be hold until the thread has been finished.
    none_        work(IWorkable *workable,
            bool_ informed = false_v,
            bool_ sync = false_v);

    /// \brief Stop all threads wrapped by CWorker.
    ///
    /// This function just unset the running condition of all threads wrapped
    /// by CWorker to exit.
    static none_ stop() {
        _workingCondition = false_v;
    }


    /// \brief Get the total number of the running threads wrapped by CWorker.
    ///
    /// \return The total num of the running threads wrapped by CWorker.
    static ub_4 getTotalNum() {
        return _workerNum;
    }

private:
    static obj_ run(obj_ object);

    static CMutex _mutexWorker;
    static ub_4  _workerNum;
    static bool_ _workingCondition;

    bool_ createThread();

    ub_4   _threadStackSize; // k
    pthread_t _handle;
    bool_  _informed;
    CMutex _mutexInformed;
    CCond  _condInformed;

    IWorkable *_workable;
};

#endif /* SRC_COMMON_CWORKER_H_ */
