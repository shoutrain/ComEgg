#ifndef C_AUTO_PTR_H_
#define C_AUTO_PTR_H_

#include "CBase.h"

template<class T>
class CAutoPtr: public CBase {
public:

    explicit CAutoPtr(T *p = null) :
            _p(p) {
    }

    CAutoPtr(CAutoPtr<T> &ptr) :
            _p(ptr.release()) {
    }

    virtual ~CAutoPtr() {
        delete _p;
    }

    T *release() {
        T *p = _p;

        _p = null;

        return p;
    }

    const T *get() const {
        return _p;
    }

    void reset(const T *p = null) {
        if (p != _p) {
            delete _p;
            _p = p;
        }
    }

    CAutoPtr<T> &operator =(CAutoPtr<T> &ptr) {
        if (this != &ptr) {
            reset(ptr.release());
        }

        return *this;
    }

    T &operator *() const {
        return *_p;
    }

    T *operator ->() const {
        return _p;
    }

private:
    // Cannot new this class
    void *operator new(size_t size);
    T *_p;
};

#endif // C_AUTO_PTR_H_
