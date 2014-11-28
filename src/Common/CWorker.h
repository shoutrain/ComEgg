#ifndef _C_WORKER_H_
#define _C_WORKER_H_

#include "CGlobal.h"
#include "CMutex.h"
#include "CCond.h"

class IWorkable;

class CWorker {
public:
    CWorker(ub_4 threadStackSize /* k */);

    virtual ~CWorker();

    // bSync is invalid unless bInformed = true
    none_        work(IWorkable *workable,
            bool_ informed = false_v,
            bool_ sync = false_v);

    static none_ stop() {
        _workingCondition = false_v;
    }

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

#endif // _C_WORKER_H_
