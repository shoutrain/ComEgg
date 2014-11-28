#ifndef _C_TIMER_MANAGER_H_
#define _C_TIMER_MANAGER_H_

#include "CGlobal.h"
#include "IWorkable.h"
#include "CWorker.h"
#include "CMutex.h"
#include "CResource.h"

enum ETimerStatus {
    NOTHING = 0x0000,

    TO_BE_ADD = 0x0001, ADDED = 0x0002, TO_BE_DEL = 0x0004, DELETED = 0x0008,
};

struct TTimer {
    ub_4 period; // seconds
    obj_ parameter;
    ub_4 times;

    b_4 baseS;
    b_4 baseUS;

    TTimer *previous;
    TTimer *next;

    b_4 status;
};

#include <queue>

typedef std::queue<TTimer *> OperatorQueue;

// A timer manager, which can accept 1 second as the minimal unit
class CTimerManager : public IWorkable {
public:
    CTimerManager(ub_4 maxTimerNum, ub_4 threadStackSize);

    virtual ~CTimerManager();

    // timers == 0: Infinite
    // return timer id or 0: failed
    obj_ setTimer(ub_4 period, obj_ parameter, ub_4 times = 1);

    none_ killTimer(obj_ timer);

    virtual bool_ working();

protected:
    virtual bool_ onTimer(obj_ timer, obj_ parameter) = 0;

private:
    none_ addTimer(TTimer *timer);

    none_ delTimer(TTimer *timer);

    CWorker _worker;
    CMutex        _mutex;

    CResource<TTimer, CTimerManager> _timerRes;
    TTimer        *_timerList;
    TTimer        *_lastTimer;

    OperatorQueue _queueForAdd;
    OperatorQueue _queueForDel;
    TTimer        *_pCurTimer;
};

#endif // _C_TIMER_MANAGER_H_
