#ifndef _C_REACTOR_H_
#define _C_REACTOR_H_

#include "../Common/CBase.h"
#include "../Common/IWorkable.h"

class CReactor : public CBase, public IWorkable {
public:
    CReactor(size_ threadStackSize,
            size_ epollWaitEventNum,
            size_ epollWaitTimeout)
            :
            _threadStackSize(threadStackSize),
            _epollWaitEventNum(epollWaitEventNum),
            _epollWaitTimeout(epollWaitTimeout) {

    }

    virtual ~CReactor();

    none_ work();

protected:
    virtual bool_ working();

private:
    const size_ _threadStackSize;

    const size_ _epollWaitEventNum;
    const size_ _epollWaitTimeout;
};

#endif // _C_REACTOR_H_