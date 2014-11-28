#ifndef _C_AUTO_PTR_H_
#define _C_AUTO_PTR_H_

#include "CGlobal.h"

#include <stdio.h>

template<class T>
class CAutoPtr {
public:

    explicit CAutoPtr(T *p = null_v) :
            _p(p) {
    }

    CAutoPtr(CAutoPtr<T> &ptr) :
            _p(ptr.release()) {
    }

    virtual ~CAutoPtr() {
        _DEL(_p);
    }

    T *release() {
        T *p = _p;

        _p = null_v;

        return p;
    }

    const T *get() const {
        return _p;
    }

    none_ reset(const T *p = null_v) {
        if (p != _p) {
            _DEL(_p);
            _p = p;
        }
    }

    CAutoPtr<T> &operator=(CAutoPtr<T> &ptr) {
        if (this != &ptr) {
            reset(ptr.release());
        }

        return *this;
    }

    T &operator*() const {
        return *_p;
    }

    T *operator->() const {
        return _p;
    }

private:
    // Cannot new this class
    obj_ operator new(size_t size);

    T *_p;
};

#endif // _C_AUTO_PTR_H_
