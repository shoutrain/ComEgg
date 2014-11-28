#ifndef _C_NODE_CONF_H_
#define _C_NODE_CONF_H_

#include "NetworkCommon.h"
#include "../Protocols/ProtocolCommon.h"
#include "../Protocols/CProtocolInfo.h"
#include "../Protocols/CPduInfo.h"
#include "../Transactions/CTransaction.h"

#include <map>

using namespace std;

typedef map<ub_4, const CPduInfo *> MapPduTable;
typedef map<const CPduInfo *, ub_4> MapIdTable;

class CNodeConf : public CBase {
public:
    none_      configPdu(const v_ &id, const CPduInfo *pduInfo, EDirection direction);

    CPduInfo   *findPdu(const v_ &id, EDirection direction);

    ub_4       findId(const CPduInfo *pduInfo, EDirection direction);

	const CProtocolInfo *getProtocol() const {
		return _protocol;
	}

	const CField *getCommandId() const {
		return _commandId;
	}

	const CField *getSizeId() const {
		return _sizeId;
	}

	ub_2 getLocalPort() const {
		return _localPort;
	}

    none_ setTransaction(const CTransaction *transaction) {
		_transaction = (CTransaction *) transaction;
	}

	const CTransaction *getTransaction() const {
		return _transaction;
	}

protected:
    CNodeConf(const CProtocolInfo *protocol, const CField *commandId,
			const CField *sizeId, ub_2 localPort) {
		_protocol = (CProtocolInfo *) protocol;
		_commandId = (CField *) commandId;
		_sizeId = (CField *) sizeId;
		_localPort = localPort;

		_transaction = null_v;
	}

    virtual ~CNodeConf() {
		_pduInTableMap.clear();
		_pduOutTableMap.clear();
	}

private:


	MapPduTable _pduInTableMap;
	MapPduTable _pduOutTableMap;

	MapIdTable _idInTableMap;
    MapIdTable _idOutTableMap;

	CProtocolInfo *_protocol;
	CField *_commandId;
	CField *_sizeId;
	ub_2 _localPort;

	CTransaction *_transaction;
};

#endif // _C_NODE_CONF_H_