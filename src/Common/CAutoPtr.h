/*!
 * \file CAutoPtr.h
 * \brief Define auto pointer here.
 *
 *
 *
 * \author Rafael Gu(shoutrain.goo@gmail.com)
 * \version 1.0.0
 * \date 02/15/2015
 */

#ifndef SRC_COMMON_CAUTOPTR_H_
#define SRC_COMMON_CAUTOPTR_H_

#include "CGlobal.h"

#include <stdio.h>

template<class T>
class CAutoPtr: CGlobal {
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
	/// \brief Cannot new this class directly,
	///
	/// It is used only with stack variable style.
	obj_ operator new(size_t size);

	T *_p;
};

#endif /* SRC_COMMON_CAUTOPTR_H_ */
