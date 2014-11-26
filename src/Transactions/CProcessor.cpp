#include "CProcessor.h"

#include "CTransactionManager.h"

#include "../Logic/LogicCommon.h"
#include "../Network/CNetworkHandle.h"
#include "../Common/CRegister.h"

CProcessor::CProcessor() {
    _data.setParent((const CData *) &CTransactionManager::instance()->data());

    optUnit unit;

    unit.data      = &_data;
    unit.container = this;
    unit.parent    = null_v;

    for (size_ i = 0; i < (size_) NORMAL_HANDLE; i++) {
        _normalHandle[i].init(&unit);
    }

    _handle = null_v;
}

CProcessor::CProcessor(const CProcessor &processor) {
    _ornData = processor._ornData;
    _data    = processor._data;
    _data.setParent((const CData *) &CTransactionManager::instance()->data());

    optUnit unit;

    unit.container = this;
    unit.data      = &_data;
    unit.parent    = null_v;

    for (size_ i = 0; i < (size_) NORMAL_HANDLE; i++) {
        _normalHandle[i] = processor._normalHandle[i];
        _normalHandle[i].init(&unit);
    }

    _handle = null_v;

    mapHandle::const_iterator pos;

    for (pos = processor._handleInMap.begin();
         pos != processor._handleInMap.end(); pos++) {
        CProgram *handle = new CProgram(*pos->second);

        _handleInMap.insert(mapHandle::value_type(pos->first, handle));
    }

    for (pos = processor._handleOutMap.begin();
         pos != processor._handleOutMap.end(); pos++) {
        CProgram *handle = new CProgram(*pos->second);

        _handleOutMap.insert(mapHandle::value_type(pos->first, handle));
    }
}

const CProcessor &CProcessor::operator=(const CProcessor &processor) {
    if (this != &processor) {
        stop();

        _ornData = processor._ornData;
        _data    = processor._data;

        optUnit unit;

        unit.container = this;
        unit.data      = &_data;
        unit.parent    = null_v;

        for (size_ i = 0; i < (size_) NORMAL_HANDLE; i++) {
            _normalHandle[i] = processor._normalHandle[i];
            _normalHandle[i].init(&unit);
        }

        _handle = null_v;

        mapHandle::const_iterator pos;

        for (pos = processor._handleInMap.begin();
             pos != processor._handleInMap.end(); pos++) {
            CProgram *handle = new CProgram(*pos->second);

            _handleInMap.insert(mapHandle::value_type(pos->first, handle));
        }

        for (pos = processor._handleOutMap.begin();
             pos != processor._handleOutMap.end(); pos++) {
            CProgram *handle = new CProgram(*pos->second);

            _handleOutMap.insert(mapHandle::value_type(pos->first, handle));
        }
    }

    return *this;
}

none_ CProcessor::stop() {
    mapHandle::iterator pos;

    for (pos = _handleInMap.begin(); pos != _handleInMap.end(); pos++) {
        assert(pos->second);
        _DEL(pos->second);
    }

    for (pos = _handleOutMap.begin(); pos != _handleOutMap.end(); pos++) {
        assert(pos->second);
        _DEL(pos->second);
    }

    _handleInMap.clear();
    _handleOutMap.clear();

    for (mapRegister::iterator pos_ = _registerMap.begin();
         pos_ != _registerMap.end(); pos_++) {
        assert(pos->second);

        for (setRegister::iterator pos_1 = pos_->second->begin();
             pos_1 != pos_->second->end(); pos_1++) {
            ch_1 *category = (ch_1 *) pos_->first.data();
            ch_1 *key      = (ch_1 *) pos_1->data();
            b_4  ret       = CRegister::instance()->unregisterItem(category, key);

            assert(0 == ret);
            CTransactionManager::instance()->unregisterItem(category, key);
        }

        pos_->second->clear();
        _DEL(pos_->second);
    }

    _registerMap.clear();
}

none_ CProcessor::reset() {
    _data = _ornData;

    for (size_ i = 0; i < (size_) NORMAL_HANDLE; i++) {
        _normalHandle[i].reset();
    }

    _handle = null_v;

    mapHandle::iterator pos;

    for (pos = _handleInMap.begin(); pos != _handleInMap.end(); pos++) {
        assert(pos->second);
        ((CProgram *) pos->second)->reset();
    }

    for (pos = _handleOutMap.begin(); pos != _handleOutMap.end(); pos++) {
        assert(pos->second);
        ((CProgram *) pos->second)->reset();
    }

    for (mapRegister::iterator pos_ = _registerMap.begin();
         pos_ != _registerMap.end(); pos_++) {
        assert(pos->second);

        for (setRegister::iterator pos_1 = pos_->second->begin();
             pos_1 != pos_->second->end(); pos_1++) {
            ch_1 *category = (ch_1 *) pos_->first.data();
            ch_1 *key      = (ch_1 *) pos_1->data();
            b_4  ret       =
                         CRegister::instance()->unregisterItem(category, key);

            assert(0 == ret);
            CTransactionManager::instance()->unregisterItem((const ch_1 *) category,
                    key);
        }

        pos_->second->clear();
        _DEL(pos_->second);
    }

    _registerMap.clear();
}

b_4 CProcessor::setMsgHandle(const CProgram &program,
        EDirection direction,
        const CPduInfo *pduInfo) {
    if (DIRECTION_IN != direction &&
            DIRECTION_OUT != direction &&
            DIRECTION_ALL != direction) {
        return 1;
    }

    if (!pduInfo) {
        return 2;
    }

    if (DIRECTION_IN == (EDirection) (direction & DIRECTION_IN)) {
        if (_handleInMap.end() == _handleInMap.find(pduInfo)) {
            assert(0);
            return 3;
        }

        CProgram *handle = new CProgram(program);

        _handleInMap.insert(mapHandle::value_type(pduInfo, handle));
    }

    if (DIRECTION_OUT == (EDirection) (direction & DIRECTION_OUT)) {
        if (_handleOutMap.end() == _handleOutMap.find(pduInfo)) {
            assert(0);
            return 4;
        }

        CProgram *handle = new CProgram(program);

        _handleOutMap.insert(mapHandle::value_type(pduInfo, handle));
    }

    return 0;
}

none_ CProcessor::execNormalHandle(const TMsgInfo *msgInfo, ENormalHandle enh) {
    TMessageUnit tmu;

    memset(&tmu, 0, sizeof(TMessageUnit));
    tmu.msgInfo = (TMsgInfo *) msgInfo;

    _normalHandle[enh].work(&tmu);
}

b_4 CProcessor::execMsgHandle(const CPduInfo *pduInfo,
        const ub_1 *msg,
        size_ size,
        const TMsgInfo *msgInfo,
        EDirection direction) {
    if (!pduInfo || !msg || 0 >= size) {
        return 1;
    }

    if (DIRECTION_IN != direction &&
            DIRECTION_OUT != direction) {
        return 2;
    }

    TMessageUnit tmu;

    tmu.pduInfo = (CPduInfo *) pduInfo;
    tmu.message = (ub_1 *) msg;
    tmu.size    = size;
    tmu.msgInfo = (TMsgInfo *) msgInfo;

    optUnit unit;

    unit.data      = &_data;
    unit.container = this;
    unit.parent    = null_v;

    mapHandle::const_iterator pos;

    if (DIRECTION_IN == direction) {
        pos = _handleInMap.find(pduInfo);

        if (pos != _handleInMap.end()) {
            assert(pos->second);

            ((CProgram *) pos->second)->init(&unit);
            ((CProgram *) pos->second)->work(&tmu);
        } else {
            _normalHandle[DEFAULT_IN_HANDLE].work(&tmu);
        }
    } else if (DIRECTION_OUT == direction) {
        pos = _handleOutMap.find(pduInfo);

        if (pos != _handleOutMap.end()) {
            assert(pos->second);

            ((CProgram *) pos->second)->init(&unit);
            ((CProgram *) pos->second)->work(&tmu);
        } else {
            _normalHandle[DEFAULT_OUT_HANDLE].work(&tmu);
        }
    }

    return 0;
}

none_ CProcessor::setHandle(const CNetworkHandle *handle) {
    assert(handle);
    _handle = (CNetworkHandle *) handle;
}

b_4 CProcessor::send(const CPduInfo *pduInfo,
        const ub_1 *msg,
        size_ size,
        const TMsgInfo *msgInfo) {
    if (!_handle || !pduInfo || !msg || 0 >= size || !msgInfo) {
        return 1;
    }

    if (0 != _handle->CheckSend(pduInfo, msg, size)) {
        return 2;
    }

    TMsgInfo localMsgInfo;

    memcpy(&localMsgInfo, msgInfo, sizeof(TMsgInfo));
    memcpy(localMsgInfo.localIP, _handle->GetLocalIP(), IP_MAX_LENGTH);
    localMsgInfo.localPort = _handle->GetLocalPort();

    if (0 != execMsgHandle(pduInfo, msg, size, &localMsgInfo, DIRECTION_OUT)) {
        return 3;
    }

    return _handle->Send(msg,
            size,
            localMsgInfo.remoteIP,
            localMsgInfo.remotePort);
}

b_4 CProcessor::registerItem(const ch_1 *category, const ch_1 *key, bool_ isCovered) {
    if (!category || 0 == category[0] || !key || 0 == key[0]) {
        return 1;
    }

    v_ variable((obj_) this);

    if (0 != CRegister::instance()->registerItem(category,
            key,
            &variable,
            isCovered)) {
        return 2;
    }

    mapRegister::iterator pos = _registerMap.find(category);

    if (_registerMap.end() != pos) {
        setRegister::iterator pos_ = pos->second->find(key);

        if (pos->second->end() == pos_) {
            pos->second->insert(key);
        }
    } else {
        setRegister *set = new setRegister;

        set->insert(key);
        _registerMap.insert(mapRegister::value_type(category, set));
    }

    CProcessor *processor = this;

    CTransactionManager::instance()->registerItem(category,
            key,
            processor,
            isCovered);
}

b_4 CProcessor::unregisterItem(const ch_1 *category, const ch_1 *key) {
    if (!category || 0 == category[0] || !key || 0 == key[0]) {
        return 1;
    }

    CProcessor *processor = null_v;

    if (0 == CTransactionManager::instance()->searchItem(category,
            key,
            processor)) {
        assert(processor);
        mapRegister::iterator pos = _registerMap.find(category);

        if (_registerMap.end() != pos) {
            setRegister::iterator pos_ = pos->second->find(key);

            if (pos->second->end() != pos_) {
                pos->second->erase(key);

                if (0 == pos->second->size()) {
                    _registerMap.erase(category);
                }
            }
        }

        CTransactionManager::instance()->unregisterItem(category, key);
    }

    return CRegister::instance()->unregisterItem(category, key);
}

