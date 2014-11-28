#ifndef _C_RESOURCE_H_
#define _C_RESOURCE_H_

#include "CAutoLock.h"

#include <deque>

class CMutex;

template<class T, class Y>
class CResource {
public:
    CResource(const ub_4 maxNum, CMutex *mutex = null_v) :
            _maxNum(maxNum) {
        assert(_maxNum > 1);
        _unitGroup = (T **) new char[_maxNum * sizeof(T *)];
        _mutex = mutex;

        for (ub_4 n = 0; n < _maxNum; n++) {
            _unitGroup[n] = new T();
            _freeDeque.push_back(_unitGroup[n]);
        }
    }

    CResource(const ub_4 maxNum,
            Y *container,
            CMutex *mutex = null_v) :
            _maxNum(maxNum) {
        assert(_maxNum > 1);
        assert(null_v != container);
        _unitGroup = (T **) new char[_maxNum * sizeof(T *)];
        _mutex = mutex;

        for (ub_4 ui = 0; ui < _maxNum; ui++) {
            _unitGroup[ui] = new T(container);
            _freeDeque.push_back(_unitGroup[ui]);
        }
    }

    virtual ~CResource() {
        _freeDeque.clear();

        for (ub_4 ui = 0; ui < _maxNum; ui++) {
            _DEL(_unitGroup[ui]);
        }

        _DEL_ARR(_unitGroup);
    }

    T *allocate() {
        CAutoLock al(_mutex);

        if (0 < _freeDeque.size()) {
            T *unit = _freeDeque.front();

            assert(unit);
            _freeDeque.pop_front();

            return unit;
        }

        return null_v;
    }

    bool_ reclaim(T *&unit) {
        assert(unit);
        CAutoLock al(_mutex);

        ub_4 n = 0;

        for (; n < _maxNum; n++) {
            if (unit == _unitGroup[n]) {
                break;
            }
        }

        if (n != _maxNum) {
            _freeDeque.push_back(unit);
            unit = null_v;

            return true_v;
        }

        return false_v;
    }

    size_ size() const {
        return (size_) _freeDeque.size();
    }

private:
    const ub_4 _maxNum;
    T      **_unitGroup;
    CMutex *_mutex;

    std::deque<T *> _freeDeque;
};

#endif // _C_RESOURCE_H_
