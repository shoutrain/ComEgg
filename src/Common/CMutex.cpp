#include "CMutex.h"

#include <sys/errno.h>

CMutex::CMutex(pthread_mutexattr_t *attr) {
	if (0 != pthread_mutex_init(&_mutex, attr)) {
		logFatal("CMutex::CMutex: failed to call pthread_mutex_init");
	}
}

CMutex::~CMutex() {
	if (0 != pthread_mutex_destroy(&_mutex)) {
		logFatal("CMutex::~CMutex: failed to call pthread_mutex_destroy");
	}
}

bool_ CMutex::lock(bool_ check) {
	int ret = 0;

	if (check) {
		ret = pthread_mutex_trylock(&_mutex);
	} else {
		ret = pthread_mutex_lock(&_mutex);
	}

	if (EBUSY == ret && check) {
		return false_v;
	}

	if (0 != ret) {
		if (check) {
			logFatal("CMutex::lock: failed to call pthread_mutext_trylock");
		} else {
			logFatal("CMutex::lock: failed to call pthread_mutext_lock");
		}

		return false_v;
	}

	return true_v;
}

void CMutex::unlock() {
	if (0 != pthread_mutex_unlock(&_mutex)) {
		logFatal("CMutex::unlock: failed to call pthread_mutex_unlock");
	}
}

