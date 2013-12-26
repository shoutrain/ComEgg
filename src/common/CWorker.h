#ifndef C_WORKER_H_
#define C_WORKER_H_

#include "CBase.h"
#include "CMutex.h"
#include "CCond.h"

class IWorkable;

class CWorker: public CBase {
public:
    CWorker(ub_4 threadStackSize /* k */);
    virtual ~CWorker();

    // sync is invalid unless informed = true
    void work(IWorkable *pWorkable, bool_ informed = false_v, bool_ sync =
            false_v);

    static void stop() {
        _workingCondition = false_v;
    }

    static ub_4 getTotalNum() {
        return _workerNum;
    }

private:
    static obj_ run(obj_ pObject);

    static CMutex _mutexWorker;
    static ub_4 _workerNum;
    static bool_ _workingCondition;

    bool_ createThread();

    ub_4 _threadStackSize; // k
    pthread_t _handle;
    bool_ _informed;
    CMutex _mutexInformed;
    CCond _condInformed;

    IWorkable *_pWorkable;
};

#endif // C_WORKER_H_
