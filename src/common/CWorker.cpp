#include "CWorker.h"
#include "CAutoLock.h"
#include "IWorkable.h"

CMutex CWorker::_mutexWorker;
ub_4 CWorker::_workerNum = 0;
bool_ CWorker::_workingCondition = true_v;

CWorker::CWorker(ub_4 threadStackSize) :
        _condInformed(&_mutexInformed) {
    _threadStackSize = threadStackSize * 1024;
    _handle = null_v;
    _informed = false_v;
    _pWorkable = null_v;
}

CWorker::~CWorker() {
}

void CWorker::work(IWorkable *pWorkable, bool_ informed, bool_ sync) {
    if (_handle) {
        return;
    }

    assert(null_v != pWorkable);
    _pWorkable = pWorkable;

    if (!informed) {
        createThread();
    } else {
        CAutoLock al(&_mutexInformed);

        _informed = informed;

        if (false_v == createThread()) {
            return;
        }

        if (_informed) {
            _condInformed.lock();
        }

        if (sync) {
            pthread_join(_handle, null_v);
        }
    }
}

obj_ CWorker::run(obj_ pObject) {
    CWorker *pWorker = (CWorker *) pObject;

    _mutexWorker.lock();
    _workerNum++;
    __debug("Worker(%016lu) started, totally %d workers ",
            pthread_self(), _workerNum);
    _mutexWorker.unlock();

    pWorker->_mutexInformed.lock();

    if (pWorker->_informed) {
        pWorker->_informed = false_v;
        pWorker->_condInformed.unlock();
    }

    pWorker->_mutexInformed.unlock();

    while (_workingCondition) {
        if (!pWorker->_pWorkable->working()) {
            break;
        }
    }

    _mutexWorker.lock();
    _workerNum--;
    __debug("Worker(%016lu) ended, totally %d workers",
            pthread_self(), _workerNum);
    _mutexWorker.unlock();

    pWorker->_handle = null_v;

    return null_v;
}

bool_ CWorker::createThread() {
    pthread_attr_t attr;

    if (0 != pthread_attr_init(&attr)) {
        __fatal("CWorker::createThread: failed to call pthread_attr_init");

        return false_v;
    }

    if (0 != pthread_attr_setstacksize(&attr, _threadStackSize)) {
        __fatal(
                "CWorker::createThread: failed to call pthread_attr_setstacksize");

        return false_v;
    }

    if (0 != pthread_create(&_handle, &attr, CWorker::run, (obj_) this)) {
        __fatal("CWorker::createThread: failed to call pthread_create");

        return false_v;
    }

    pthread_attr_destroy(&attr);

    return true_v;

}
