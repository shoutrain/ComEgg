#ifndef C_AUTO_LOCK_H_
#define C_AUTO_LOCK_H_

#include "CLock.h"

class CAutoLock: public CBase {
public:
    CAutoLock(CLock *pLock = null_v);
    virtual ~CAutoLock();

    const CLock *get() const {
        return _pLock;
    }

private:
    // Cannot new this class
    void *operator new(size_t size);
    CLock *_pLock;
};

#endif // C_AUTO_LOCK_H_
