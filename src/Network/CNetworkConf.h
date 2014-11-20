#ifndef CNETWORK_CONF_H
#define CNETWORK_CONF_H

#include "NetworkCommon.h"
#include "../Protocols/ProtocolCommon.h"
#include "../Protocols/CProtocolInfo.h"
#include "../Protocols/CPDUInfo.h"
#include "../Transactions/CTransaction.h"

#include <map>

using namespace std;

typedef map<size_, const CPDUInfo *> MapPduTable;
typedef map<const CPDUInfo *, size_> MapIdTable;

class CNetworkConf: public CBase {
public:
	b_4 configPdu(const v_ &id, const CPDUInfo *pduInfo, EDirection direction);
	b_4 identifyId(const v_ &id, CPDUInfo *&pduInfo, EDirection direction);
	b_4 identifyPdu(const CPDUInfo *pPDUInfo, v_ &id, EDirection direction);

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

	void setTransaction(const CTransaction *transaction) {
		_transaction = (CTransaction *) transaction;
	}

	const CTransaction *getTransaction() const {
		return _transaction;
	}

protected:
	CNetworkConf(const CProtocolInfo *protocol, const CField *commandId,
			const CField *sizeId, ub_2 localPort) {
		_protocol = (CProtocolInfo *) protocol;
		_commandId = (CField *) commandId;
		_sizeId = (CField *) sizeId;
		_localPort = localPort;

		_transaction = null_v;
	}

	virtual ~CNetworkConf() {
		_pduInTableMap.clear();
		_pduOutTableMap.clear();
	}

private:
	bool_ findPdu(const v_ &id, EDirection direction, CPDUInfo *&pduInfo);
	bool_ findId(const CPDUInfo *pduInfo, EDirection direction, v_ &id);

	MapPduTable _pduInTableMap;
	MapPduTable _pduOutTableMap;

	MapIdTable _idInTableMap;
	MapIdTable _idOutTablemap;

	CProtocolInfo *_protocol;
	CField *_commandId;
	CField *_sizeId;
	ub_2 _localPort;

	CTransaction *_transaction;
};

#endif // CNETWORK_CONF_H
