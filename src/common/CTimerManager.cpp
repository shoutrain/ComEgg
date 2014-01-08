#include "CTimerManager.h"
#include "CAutoLock.h"

#include <sys/time.h>

CTimerManager::CTimerManager(ub_4 maxTimerNum, ub_4 threadStackSize) :
        _worker(threadStackSize), _timerRes(maxTimerNum) {
    _pTimerList = null_v;
    _pLastTimer = null_v;
    _pCurTimer = null_v;

    _worker.work(this, true_v);
}

CTimerManager::~CTimerManager() {
}

ub_8 CTimerManager::setTimer(ub_4 period, obj_ pParameter, ub_4 times) {
    TTimer *pTimer = _timerRes.allocate();

    if (null_v == pTimer) {
        __crit("CTimerManager::setTimer: no more timers can be allocated");

        return 0;
    }

    struct timeval curTime;
    gettimeofday(&curTime, null_v);

    pTimer->period = period;
    pTimer->pParameter = pParameter;
    pTimer->times = times;
    pTimer->baseS = curTime.tv_sec;
    pTimer->baseUS = curTime.tv_usec;
    pTimer->pPrevious = null_v;
    pTimer->pNext = null_v;
    pTimer->status = TO_BE_ADD;

    _mutex.lock();
    _queueForAdd.push(pTimer);
    _mutex.unlock();

    __debug(
            "CTimerManager::setTimer: from-%p, time id-%p, period-%uSec, times-%u",
            pParameter, pTimer, period, times);

    return (ub_8) pTimer;
}

none_ CTimerManager::killTimer(ub_8 timerId) {
    assert(timerId > 0);
    TTimer *pTimer = (TTimer *) timerId;

    if (TO_BE_DEL == (pTimer->status & TO_BE_DEL)
            || DELETED == (pTimer->status & DELETED)) {
        return; // The timer will be deleted or has been deleted
    }

    pTimer->status |= TO_BE_DEL;

    _mutex.lock();
    _queueForDel.push(pTimer);
    _mutex.unlock();

    __debug("CTimerManager::killTimer: time id-%p.", pTimer);
}

bool_ CTimerManager::working() {
    _mutex.lock();

    while (!_queueForAdd.empty()) {
        TTimer *pTimer = _queueForAdd.front();

        if (TO_BE_ADD == pTimer->status) {
            addTimer(pTimer);
        }

        _queueForAdd.pop();
    }

    while (!_queueForDel.empty()) {
        TTimer *pTimer = _queueForDel.front();

        if (TO_BE_DEL == (pTimer->status & TO_BE_DEL)
                && ADDED == (pTimer->status & ADDED)) {
            if (pTimer == _pCurTimer) {
                _pCurTimer = _pCurTimer->pNext;
            }

            delTimer(pTimer);
        }

        _queueForDel.pop();
    }

    _mutex.unlock();

    struct timeval curTime;
    gettimeofday(&curTime, null_v);

    if (null_v == _pCurTimer) {
        if (null_v == _pTimerList) {
            // Sleep for 0.5s
            __sleep(0, 500);

            return true_v;
        }

        _pCurTimer = _pTimerList;
    }

    b_4 i = _pCurTimer->period + _pCurTimer->baseS;

    if ((i < curTime.tv_sec)
            || (i == curTime.tv_sec && _pCurTimer->baseUS <= curTime.tv_usec)) {
        if (onTimer((ub_8) _pCurTimer, _pCurTimer->pParameter)) {
            _pCurTimer->baseS = curTime.tv_sec;
            _pCurTimer->baseUS = curTime.tv_usec;

            if (0 != _pCurTimer->times) {
                _pCurTimer->times--;

                if (0 == _pCurTimer->times) {
                    TTimer *pCurTimer = _pCurTimer;

                    _pCurTimer = _pCurTimer->pNext;
                    delTimer(pCurTimer);

                    return true_v;
                }
            }
        } else {
            TTimer *pCurTimer = _pCurTimer;

            _pCurTimer = _pCurTimer->pNext;
            delTimer(pCurTimer);

            return true_v;
        }
    }

    _pCurTimer = _pCurTimer->pNext;

    return true_v;
}

none_ CTimerManager::addTimer(TTimer *pTimer) {
    assert(null_v != pTimer);

    if (null_v == _pTimerList) {
        assert(null_v == _pLastTimer);
        _pLastTimer = _pTimerList = pTimer;
    } else {
        pTimer->pPrevious = _pLastTimer;
        _pLastTimer->pNext = pTimer;
        _pLastTimer = pTimer;
    }

    pTimer->status |= ADDED;
}

none_ CTimerManager::delTimer(TTimer *pTimer) {
    assert(null_v != pTimer);

    if (null_v == pTimer->pPrevious) {
        assert(pTimer == _pTimerList);

        if (null_v == pTimer->pNext) {
            assert(pTimer == _pLastTimer);
            _pLastTimer = _pTimerList = null_v;
        } else {
            _pTimerList = pTimer->pNext;
            _pTimerList->pPrevious = null_v;
        }
    } else {
        if (null_v == pTimer->pNext) {
            assert(pTimer == _pLastTimer);
            _pLastTimer = pTimer->pPrevious;
            _pLastTimer->pNext = null_v;
        } else {
            pTimer->pPrevious->pNext = pTimer->pNext;
            pTimer->pNext->pPrevious = pTimer->pPrevious;
        }
    }

    pTimer->status |= DELETED;
    _timerRes.reclaim(pTimer);
}
