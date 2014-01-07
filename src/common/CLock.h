#ifndef C_LOCK_H_
#define C_LOCK_H_

#include "CBase.h"

class CLock: public CBase {
public:
	virtual bool_ lock(bool_ check = false_v) = 0;
	virtual none_ unlock() = 0;

protected:
	CLock() {
	}

	virtual ~CLock() {
	}
};

#endif // C_LOCK_H_
