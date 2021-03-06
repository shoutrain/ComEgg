#include "CTimerManager.h"

CTimerManager::CTimerManager(ub_4 maxTimerNum, ub_4 threadStackSize) :
		_worker(threadStackSize), _mutex(true_v), _timerRes(maxTimerNum) {
	_timerList = null_v;
	_lastTimer = null_v;
	_curTimer = null_v;

	_worker.work(this, true_v);
}

CTimerManager::~CTimerManager() {
}

obj_ CTimerManager::setTimer(ub_4 period, obj_ parameter, ub_4 times) {
	TTimer *timer = _timerRes.allocate();

	if (null_v == timer) {
		log_crit("CTimerManager::setTimer: no more timers can be allocated.");

		return 0;
	}

	assert(NOTHING == timer->status || DELETED == timer->status);
	struct timeval curTime;
	gettimeofday(&curTime, null_v);

	timer->period = period;
	timer->parameter = parameter;
	timer->times = times;
	timer->baseS = curTime.tv_sec;
	timer->baseUS = curTime.tv_usec;
	timer->previous = null_v;
	timer->next = null_v;
	timer->status = TO_BE_ADD;

	_mutex.lock();
	_queueForAdd.push(timer);
	_mutex.unlock();

	log_debug(
			"CTimerManager::setTimer: from-%p, time id-%p, period-%uSec, "
					"times-%u.", parameter, timer, period, times);

	return (obj_) timer;
}

none_ CTimerManager::killTimer(obj_ timer) {
	assert(timer > 0);
	TTimer *localTimer = (TTimer *) timer;
	assert(NOTHING != localTimer->status);
	CAutoLock al(&_mutex);

	if (TO_BE_ADD == localTimer->status) {
		localTimer->status = DELETED;
		_timerRes.reclaim(localTimer);

		return;
	}

	if (ADDED != localTimer->status) {
		return; // The timer will be deleted or has been deleted
	}

	localTimer->status = TO_BE_DEL;

	_mutex.lock();
	_queueForDel.push(localTimer);
	_mutex.unlock();

	log_debug("CTimerManager::killTimer: time id-%p.", localTimer);
}

bool_ CTimerManager::working() {
	_mutex.lock();

	while (!_queueForAdd.empty()) {
		TTimer *timer = _queueForAdd.front();

		if (TO_BE_ADD == timer->status) {
			addTimer(timer);
		}

		_queueForAdd.pop();
	}

	while (!_queueForDel.empty()) {
		TTimer *timer = _queueForDel.front();

		if (TO_BE_DEL == (timer->status & TO_BE_DEL)
				&& ADDED == (timer->status & ADDED)) {
			if (timer == _curTimer) {
				_curTimer = _curTimer->next;
			}

			delTimer(timer);
		}

		_queueForDel.pop();
	}

	_mutex.unlock();

	struct timeval curTime;

	gettimeofday(&curTime, null_v);

	if (null_v == _curTimer) {
		if (null_v == _timerList) {
			// Sleep for 0.1s
			CGlobal::sleep(0, 100);

			return true_v;
		}

		_curTimer = _timerList;
	}

	b_4 i = _curTimer->period + _curTimer->baseS;

	if ((i < curTime.tv_sec)
			|| (i == curTime.tv_sec && _curTimer->baseUS <= curTime.tv_usec)) {
		if (onTimer((obj_) _curTimer, _curTimer->parameter)) {
			_curTimer->baseS = curTime.tv_sec;
			_curTimer->baseUS = curTime.tv_usec;

			if (0 != _curTimer->times) {
				_curTimer->times--;

				if (0 == _curTimer->times) {
					TTimer *curTimer = _curTimer;

					_curTimer = _curTimer->next;
					delTimer(curTimer);

					return true_v;
				}
			}
		} else {
			TTimer *curTimer = _curTimer;

			_curTimer = _curTimer->next;
			delTimer(curTimer);

			return true_v;
		}
	}

	_curTimer = _curTimer->next;

	return true_v;
}

none_ CTimerManager::addTimer(TTimer *timer) {
	assert(null_v != timer);

	if (null_v == _timerList) {
		assert(null_v == _lastTimer);
		_lastTimer = _timerList = timer;
	} else {
		timer->previous = _lastTimer;
		_lastTimer->next = timer;
		_lastTimer = timer;
	}

	timer->status = ADDED;
}

none_ CTimerManager::delTimer(TTimer *timer) {
	assert(null_v != timer);

	if (null_v == timer->previous) {
		assert(timer == _timerList);

		if (null_v == timer->next) {
			assert(timer == _lastTimer);
			_lastTimer = _timerList = null_v;
		} else {
			_timerList = timer->next;
			_timerList->previous = null_v;
		}
	} else {
		if (null_v == timer->next) {
			assert(timer == _lastTimer);
			_lastTimer = timer->previous;
			_lastTimer->next = null_v;
		} else {
			timer->previous->next = timer->next;
			timer->next->previous = timer->previous;
		}
	}

	timer->status = DELETED;
	_timerRes.reclaim(timer);
}
