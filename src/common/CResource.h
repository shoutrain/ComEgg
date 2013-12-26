#ifndef C_RESOURCE_H_
#define C_RESOURCE_H_

#include "CBase.h"
#include "CAutoLock.h"

#include <deque>

class CMutex;

template<class T, class Y>
class CResource: public CBase {
public:

    CResource(const ub_4 maxNum, CMutex *pMutex = null_v) :
            _maxNum(maxNum) {
        assert(_maxNum > 1);
        _ppUnitGroup = (T **) new char[_maxNum * sizeof(T *)];
        _pMutex = pMutex;

        for (ub_4 n = 0; n < _maxNum; n++) {
            _ppUnitGroup[n] = new T();
            _freeDeque.push_back(_ppUnitGroup[n]);
        }
    }

    CResource(const ub_4 uiMaxNum, Y *pContainer, CMutex *pMutex = null_v) :
            _maxNum(uiMaxNum) {
        assert(_maxNum > 1);
        assert(null_v != pContainer);
        _ppUnitGroup = (T **) new b_1[_maxNum * sizeof(T *)];
        _pMutex = pMutex;

        for (ub_4 n = 0; n < _maxNum; n++) {
            _ppUnitGroup[n] = new T(pContainer);
            _freeDeque.push_back(_ppUnitGroup[n]);
        }
    }

    virtual ~CResource() {
        _freeDeque.clear();

        for (ub_4 n = 0; n < _maxNum; n++) {
            delete _ppUnitGroup[n];
        }

        __del_arr(_ppUnitGroup);
    }

    T *allocate() {
        CAutoLock al(_pMutex);

        if (0 < _freeDeque.size()) {
            T *pUnit = _freeDeque.front();

            assert(pUnit);
            _freeDeque.pop_front();

            return pUnit;
        }

        return null_v;
    }

    bool_ reclaim(T *&pUnit) {
        assert(pUnit);
        CAutoLock al(_pMutex);

        ub_4 n = 0;

        for (; n < _maxNum; n++) {
            if (pUnit == _ppUnitGroup[n]) {
                break;
            }
        }

        if (n != _maxNum) {
            _freeDeque.push_back(pUnit);
            pUnit = null_v;

            return true_v;
        }

        return false_v;
    }

    ub_4 size() const {
        return (ub_4) _freeDeque.size();
    }

private:
    const ub_4 _maxNum;
    T **_ppUnitGroup;
    CMutex *_pMutex;

    std::deque<T*> _freeDeque;
};

#endif // C_RESOURCE_H_
