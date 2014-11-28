#include "CNodeConf.h"

none_ CNodeConf::configPdu(const v_ &id, const CPduInfo *pduInfo,
        EDirection direction) {
    assert(pduInfo);

    if (DIRECTION_IN == (EDirection) (direction & DIRECTION_IN)) {
        assert(null_v == findPdu(id, DIRECTION_IN));
        assert(0 == findId(pduInfo, DIRECTION_IN));
        _pduInTableMap.insert(MapPduTable::value_type((ub_4) id, pduInfo));
        _idInTableMap.insert(MapIdTable::value_type(pduInfo, (ub_4) id));
    }

    if (DIRECTION_OUT == (EDirection) (direction & DIRECTION_OUT)) {
        assert(null_v == findPdu(id, DIRECTION_OUT));
        assert(0 == findId(pduInfo, DIRECTION_OUT));
        _pduOutTableMap.insert(
                MapPduTable::value_type((size_) id, pduInfo));
        _idOutTableMap.insert(MapIdTable::value_type(pduInfo, (size_) id));
    }
}

CPduInfo *CNodeConf::findPdu(const v_ &id, EDirection direction) {
    MapPduTable::const_iterator pos;

    if (DIRECTION_IN == direction) {
        pos = _pduInTableMap.find((ub_4) id);

        if (_pduInTableMap.end() != pos) {
            assert(pos->second);
            return pos->second;
        }
    } else if (DIRECTION_OUT == direction) {
        pos = _pduOutTableMap.find((ub_4) id);

        if (_pduOutTableMap.end() != pos) {
            assert(pos->second);
            return pos->second;
        }
    }

    return null_v;
}

ub_4 CNodeConf::findId(const CPduInfo *pduInfo, EDirection direction) {
    MapIdTable::const_iterator pos;

    if (DIRECTION_IN == direction) {
        pos = _idInTableMap.find((CPduInfo *) pduInfo);

        if (_idInTableMap.end() != pos) {
            assert(pos->second);
            return pos->second;
        }
    } else if (DIRECTION_OUT == direction) {
        pos = _idOutTableMap.find((CPduInfo *) pduInfo);

        if (_idOutTableMap.end() != pos) {
            assert(pos->second);
            return pos->second;
        }
    }

    return 0;
}

