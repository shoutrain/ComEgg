#include "CProcessor.h"

#include "CTransactionManager.h"
#include "../Network/CNetworkHandle.h"
#include "../Common/CRegister.h"

CProcessor::CProcessor() {
    _data.setParent(CTransactionManager::instance()->data());

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
    _data.setParent(CTransactionManager::instance()->data());

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
    mapHandle::iterator pos1;

    for (pos1 = _handleInMap.begin(); pos1 != _handleInMap.end(); pos1++) {
        assert(pos1->second);
        _DEL(pos1->second);
    }

    for (pos1 = _handleOutMap.begin(); pos1 != _handleOutMap.end(); pos1++) {
        assert(pos1->second);
        _DEL(pos1->second);
    }

    _handleInMap.clear();
    _handleOutMap.clear();

    for (mapRegister::iterator pos2 = _registerMap.begin();
         pos2 != _registerMap.end(); pos2++) {
        assert(pos1->second);

        for (setRegister::iterator pos3 = pos2->second->begin();
             pos3 != pos2->second->end(); pos3++) {
            ch_1 *category = (ch_1 *) pos2->first.data();
            ch_1 *key      = (ch_1 *) pos3->data();
            b_4  ret       = CRegister::instance()->unregisterItem(category, key);

            assert(0 == ret);
            CTransactionManager::instance()->unregisterItem(category, key);
        }

        pos2->second->clear();
        _DEL(pos2->second);
    }

    _registerMap.clear();
}

none_ CProcessor::reset() {
    _data = _ornData;

    for (size_ i = 0; i < (size_) NORMAL_HANDLE; i++) {
        _normalHandle[i].reset();
    }

    _handle = null_v;

    mapHandle::iterator pos1;

    for (pos1 = _handleInMap.begin(); pos1 != _handleInMap.end(); pos1++) {
        assert(pos1->second);
        ((CProgram *) pos1->second)->reset();
    }

    for (pos1 = _handleOutMap.begin(); pos1 != _handleOutMap.end(); pos1++) {
        assert(pos1->second);
        ((CProgram *) pos1->second)->reset();
    }

    for (mapRegister::iterator pos2 = _registerMap.begin();
         pos2 != _registerMap.end(); pos2++) {
        assert(pos1->second);

        for (setRegister::iterator pos3 = pos2->second->begin();
             pos3 != pos2->second->end(); pos3++) {
            ch_1 *category = (ch_1 *) pos2->first.data();
            ch_1 *key      = (ch_1 *) pos3->data();
            b_4  ret       =
                         CRegister::instance()->unregisterItem(category, key);

            assert(0 == ret);
            CTransactionManager::instance()->unregisterItem((const ch_1 *) category,
                    key);
        }

        pos2->second->clear();
        _DEL(pos2->second);
    }

    _registerMap.clear();
}

none_ CProcessor::setMsgHandle(const CProgram &program,
        EDirection direction,
        const CPduInfo *pduInfo) {
    assert(DIRECTION_IN == direction ||
            DIRECTION_OUT == direction ||
            DIRECTION_ALL == direction);
    assert(pduInfo);

    if (DIRECTION_IN == (EDirection) (direction & DIRECTION_IN)) {
        assert(_handleInMap.end() != _handleInMap.find(pduInfo));
        CProgram *handle = new CProgram(program);

        _handleInMap.insert(mapHandle::value_type(pduInfo, handle));
    }

    if (DIRECTION_OUT == (EDirection) (direction & DIRECTION_OUT)) {
        assert(_handleOutMap.end() == _handleOutMap.find(pduInfo));
        CProgram *handle = new CProgram(program);

        _handleOutMap.insert(mapHandle::value_type(pduInfo, handle));
    }
}

none_ CProcessor::execNormalHandle(const TMsgInfo *msgInfo, ENormalHandle enh) {
    TMessageUnit tmu;

    memset(&tmu, 0, sizeof(TMessageUnit));
    tmu.msgInfo = (TMsgInfo *) msgInfo;

    _normalHandle[enh].work(&tmu);
}

none_ CProcessor::execMsgHandle(const CPduInfo *pduInfo,
        const ub_1 *msg,
        size_ size,
        const TMsgInfo *msgInfo,
        EDirection direction) {
    assert(pduInfo && msg && 0 >= size);
    assert(DIRECTION_IN == direction ||
            DIRECTION_OUT == direction);

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
}

none_ CProcessor::setHandle(const CNetworkHandle *handle) {
    assert(handle);
    _handle = (CNetworkHandle *) handle;
}

b_4 CProcessor::send(const CPduInfo *pduInfo,
        const ub_1 *msg,
        size_ size,
        const TMsgInfo *msgInfo) {
    assert(_handle && pduInfo && msg && 0 >= size && msgInfo);

    if (0 != _handle->CheckSend(pduInfo, msg, size)) {
        return 1;
    }

    TMsgInfo localMsgInfo;

    memcpy(&localMsgInfo, msgInfo, sizeof(TMsgInfo));
    memcpy(localMsgInfo.localIP, _handle->GetLocalIP(), IP_MAX_LENGTH);
    localMsgInfo.localPort = _handle->GetLocalPort();
    execMsgHandle(pduInfo, msg, size, &localMsgInfo, DIRECTION_OUT);

    return _handle->Send(msg,
            size,
            localMsgInfo.remoteIP,
            localMsgInfo.remotePort);
}

none_ CProcessor::registerItem(const ch_1 *category, const ch_1 *key, bool_ isCovered) {
    assert(category && 0 != category[0] && key && != key[0]);

    v_ variable((obj_) this);

    CRegister::instance()->registerItem(category,
            key,
            &variable,
            isCovered);

    mapRegister::iterator pos1 = _registerMap.find(category);

    if (_registerMap.end() != pos1) {
        setRegister::iterator pos2 = pos1->second->find(key);

        if (pos1->second->end() == pos2) {
            pos1->second->insert(key);
        }
    } else {
        setRegister *set = new setRegister;

        set->insert(key);
        _registerMap.insert(mapRegister::value_type(category, set));
    }

    CTransactionManager::instance()->registerItem(category,
            key,
            *this,
            isCovered);
}

none_ CProcessor::unregisterItem(const ch_1 *category, const ch_1 *key) {
    assert(category || 0 != category[0] || key || 0 != key[0]);

    CProcessor *processor = CTransactionManager::instance()->searchItem(category,
            key);
    assert(processor);

    mapRegister::iterator pos1 = _registerMap.find(category);

    if (_registerMap.end() != pos1) {
        setRegister::iterator pos2 = pos1->second->find(key);

        if (pos1->second->end() != pos2) {
            pos1->second->erase(key);

            if (0 == pos1->second->size()) {
                _registerMap.erase(category);
            }
        }
    }

    CTransactionManager::instance()->unregisterItem(category, key);
    CRegister::instance()->unregisterItem(category, key);
}
