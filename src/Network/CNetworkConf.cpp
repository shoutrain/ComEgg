#include "CNetworkConf.h"

ub_4 CNetworkConf::configPdu(const v_ &id, const CPduInfo *pduInfo,
		EDirection direction) {
	assert(pduInfo);

	if (DIRECTION_IN == (EDirection) (direction & DIRECTION_IN)) {
#ifdef _DEBUG_
		try {
			CPDUInfo *pTempPDUInfo = null_v;
			v_ TempID;

			if (true_v == FindPDU(id, DIRECTION_IN, pTempPDUInfo)
					|| true_v == FindID(pduInfo, DIRECTION_IN, TempID)) {
				_RET(ELEMENT_EXIST_IN_CONTAINER);
			}
		} catch (error_code err) {
			_RET(err);
		}
#endif

		try {
			_pduInTableMap.insert(MapPduTable::value_type((size_) id, pduInfo));
			_idInTableMap.insert(MapIdTable::value_type(pduInfo, (size_) id));
		} catch (error_code err) {
#ifdef _DEBUG_
			_RET(err);
#endif
		}
	}

	if (DIRECTION_OUT == (EDirection) (direction & DIRECTION_OUT)) {
#ifdef _DEBUG_
		try {
			CPDUInfo *pTempPDUInfo = null_v;
			v_ TempID;

			if (true_v == FindPDU(id, DIRECTION_OUT, pTempPDUInfo)
					|| true_v == FindID(pduInfo, DIRECTION_OUT, TempID)) {
				_RET(ELEMENT_EXIST_IN_CONTAINER);
			}
		} catch (error_code err) {
			_RET(err);
		}
#endif

		try {
			_pduOutTableMap.insert(
					MapPduTable::value_type((size_) id, pduInfo));
			_idOutTablemap.insert(MapIdTable::value_type(pduInfo, (size_) id));
		} catch (error_code err) {
#ifdef _DEBUG_
			_RET(err);
#endif
		}
	}

	_RET(SUCCESS);
}

ub_4 CNetworkConf::IdentifyID(const v_ &ID, CPduInfo *&pPDUInfo,
		EDirection Direction) {
	_START(IDENTIFY_ID);

#ifdef _DEBUG_
	if (pPDUInfo)
		_RET(PARAMETER_NOT_NULL | PARAMETER_2);

	if (DIRECTION_IN != Direction && DIRECTION_OUT != Direction) {
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_3);
	}
#endif

	if (false_v == FindPDU(ID, Direction, pPDUInfo))
		_RET(FAILURE);

	_RET(SUCCESS);
}

ub_4 CNetworkConf::IdentifyPDU(const CPduInfo *pPDUInfo, v_ &ID,
		EDirection Direction) {
	_START(IDENTIFY_PDU);

#ifdef _DEBUG_
	if (!pPDUInfo)
		_RET(PARAMETER_NULL | PARAMETER_2);

	if (DIRECTION_IN != Direction && DIRECTION_OUT != Direction) {
		_RET(PARAMETER_TYPE_ERROR | PARAMETER_3);
	}
#endif

	if (false_v == FindID(pPDUInfo, Direction, ID))
		_RET(FAILURE);

	_RET(SUCCESS);
}

bool_ CNetworkConf::findPdu(const v_ &id, EDirection direction,
        CPduInfo *&pduInfo) {
	MapPduTable::const_iterator pos/* = _pduInTableMap.end()*/;

	if (DIRECTION_IN == direction) {
		pos = _pduInTableMap.find(id);

		if (_pduInTableMap.end() != pos) {
            pduInfo = (CPduInfo *) pos->second;

			return true_v;
		}
	} else if (DIRECTION_OUT == direction) {
		pos = _pduOutTableMap.find((size_) id);

		if (_pduOutTableMap.end() != pos) {
            pduInfo = (CPduInfo *) pos->second;

			return true_v;
		}
	}

	return false_v;
}

bool_ CNetworkConf::findid(const CPduInfo *pduInfo, EDirection direction,
		v_ &id) {
	MapIdTable::const_iterator pos;

	if (DIRECTION_IN == direction) {
        pos = _idInTableMap.find((CPduInfo *) pduInfo);

		if (_idInTableMap.end() != pos) {
			id = v_(pos->second);

			return true_v;
		}
	} else if (DIRECTION_OUT == direction) {
        pos = _idOutTablemap.find((CPduInfo *) pduInfo);

		if (_idOutTablemap.end() != pos) {
			id = v_(pos->second);

			return true_v;
		}
	}

	return false_v;
}

