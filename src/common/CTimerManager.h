#ifndef C_TIMERMANAGER_H_
#define C_TIMERMANAGER_H_

#include "CBase.h"
#include "IWorkable.h"
#include "CWorker.h"
#include "CMutex.h"
#include "CResource.h"

enum ETimerStatus {
    NOTHING = 0x0000,

    TO_BE_ADD = 0x0001,
    ADDED = 0x0002,
    TO_BE_DEL = 0x0004,
    DELETED = 0x0008,
};

struct TTimer {
    ub_4 period; // seconds
    obj_ pParameter;
    ub_4 times;

    b_4 baseS;
    b_4 baseUS;

    TTimer *pPrevious;
    TTimer *pNext;

    b_4 status;
};

#include <queue>

typedef std::queue<TTimer *> OperatorQueue;

// A timer manager, which can accept 1 second as the minimal unit

class CTimerManager: public CBase, public IWorkable {
public:
    CTimerManager(ub_4 maxTimerNum, ub_4 threadStackSize);
    virtual ~CTimerManager();

    // timers == 0: infinite
    // return timer id or 0: failed
    ub_8 setTimer(ub_4 period, obj_ pParameter, ub_4 times = 1);
    void killTimer(ub_8 timerId);

    virtual bool_ working();

protected:
    virtual bool_ onTimer(ub_8 timerId, obj_ pParameter) = 0;

private:
    void addTimer(TTimer *pTimer);
    void delTimer(TTimer *pTimer);

    CWorker _worker;
    CMutex _mutex;

    CResource<TTimer, CTimerManager> _timerRes;
    TTimer *_pTimerList;
    TTimer *_pLastTimer;

    OperatorQueue _queueForAdd;
    OperatorQueue _queueForDel;
    TTimer *_pCurTimer;
};

#endif // _C_TIMER_MANAGER_H_
