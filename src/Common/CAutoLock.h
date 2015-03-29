/*!
 * \file CAutolOCK.h
 * \brief Define auto lock here.
 *
 *
 *
 * \author Rafael Gu(shoutrain.goo@gmail.com)
 * \version 1.0.0
 * \date 02/15/2015
 */

#ifndef SRC_COMMON_CAUTOLOCK_H_
#define SRC_COMMON_CAUTOLOCK_H_

#include "CLock.h"

class CAutoLock {
public:
	CAutoLock(CLock *lock = null_v);

	virtual ~CAutoLock();

	const CLock *get() const {
		return _lock;
	}

private:
	// Cannot new this class
	obj_ operator new(size_t size);

	CLock *_lock;
};

#endif /* SRC_COMMON_CAUTOLOCK_H_ */
