/*!
* \file CResource.h
* \brief The header file for class of CResource.
*
*
*
* \author Rafael Gu(shoutrain.goo@gmail.com)
* \version 1.0.0
* \date 12/15/2014
*/

#ifndef _C_RESOURCE_H_
#define _C_RESOURCE_H_

#include "CAutoLock.h"

#include <deque>

class CMutex;

/// \brief CResource can manager a lot of objects.
///
/// CResource can avoid using of new/delete, you can allocate some objects in
/// advance and use some of them and free some of them without worrying about
/// memory leak.
template<class T, class Y>
class CResource {
public:
    /// \brief The constructor of CResource.
    ///
    /// \param maxNum The total number of objects you want to manager.
    /// \param mutex Make the instance of CResource to support multi-thread if
    /// mutex is not null_v.
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

    /// \brief The constructor of CResource.
    ///
    /// You can assign container to these objects, but you should ensure these
    /// objects has corresponding construct with container as the only param.
    /// \param maxNum The total number of objects you want to manager.
    /// \param container These objects' container, which should be passed to
    /// the constructor of these objects.
    /// \param mutex Make the instance of CResource to support multi-thread if
    /// mutex is not null_v.
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

    /// \brief The destructor of CResource.
    virtual ~CResource() {
        _freeDeque.clear();

        for (ub_4 ui = 0; ui < _maxNum; ui++) {
            _DEL(_unitGroup[ui]);
        }

        _DEL_ARR(_unitGroup);
    }

    /// \brief Allocate object to use.
    ///
    /// \return The allocated object to use, return null_v if there is no more
    /// object to be allocated.
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

    /// \brief Reclaim object to sleep.
    ///
    /// \param unit The object will not be used any more and should be reclaimed
    /// back to CResource instance.
    /// \return Returning false_v means the object in unit is not owned by this
    /// CResource instance.
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

    /// \brief Get the free objects number
    ///
    /// \return The number of free objects which can be allocated
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
