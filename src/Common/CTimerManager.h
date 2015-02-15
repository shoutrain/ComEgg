/*!
* \file CTimerManager.h
* \brief The header file for class of CTimerManager.
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 12/15/2014
*/

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

/// \brief CTimerManager can manage a lot of timers.
///
/// All timers in CTimerManager have precision with 1 second.
class CTimerManager : public CGlobal, public IWorkable {
public:
    CTimerManager(ub_4 maxTimerNum, ub_4 threadStackSize);

    virtual ~CTimerManager();

    /// \brief Create timer and add timer into CTimerManager
    ///
    /// \param period The interval seconds the timer will be activated.
    /// \param parameter The parameter will be passed to timer and you can
    // used it when the time is activated.
    /// \param times 0 means the timer will be activated forever until calling
    /// killTimer; other number means the timers the timer can be activated.
    /// \return The timer id.
    obj_ setTimer(ub_4 period, obj_ parameter, ub_4 times = 1);

    none_ killTimer(obj_ timer);

    virtual bool_ working();

protected:
    virtual bool_ onTimer(obj_ timer, obj_ parameter) = 0;

private:
    none_ addTimer(TTimer *timer);

    none_ delTimer(TTimer *timer);

    CWorker _worker;
    CMutex _mutex;

    CResource<TTimer, CTimerManager> _timerRes;
    TTimer *_timerList;
    TTimer *_lastTimer;

    OperatorQueue _queueForAdd;
    OperatorQueue _queueForDel;
    TTimer        *_pCurTimer;
};

#endif // _C_TIMER_MANAGER_H_
