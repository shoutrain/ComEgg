#ifndef _C_PROCESSOR_H_
#define _C_PROCESSOR_H_

#include "TransactionCommon.h"

class CNetworkHandle;

#include <string>
#include <map>
#include <set>

using namespace std;

typedef map<const CPduInfo *, const CProgram *> mapHandle;

typedef set<string>                setRegister;
typedef map<string, setRegister *> mapRegister;

class CProcessor : public CBase {
public:
    CProcessor();

    CProcessor(const CProcessor &processor);

    const CProcessor &operator=(const CProcessor &processor);

    virtual ~CProcessor() {
        stop();
    }

    none_ reset();

    none_ setData(const CData &data) {
        _ornData = data;
        _data    = data;
    }

    none_ setNormalHandle(const CProgram &program, ENormalHandle enh) {
        _normalHandle[enh] = program;
    }

    b_4 setMsgHandle(const CProgram &program,
            EDirection direction,
            const CPduInfo *pduInfo);

    none_ execNormalHandle(const TMsgInfo *msgInfo, ENormalHandle enh);

    b_4 execMsgHandle(const CPduInfo *pduInfo,
            const ub_1 *msg,
            size_ size,
            const TMsgInfo *msgInfo,
            EDirection direction);

    none_ setHandle(const CNetworkHandle *handle);

    b_4 send(const CPduInfo *pduInfo,
            const ub_1 *msg,
            size_ size,
            const TMsgInfo *msgInfo);

    b_4 registerItem(const ch_1 *category,
            const ch_1 *key,
            bool_ isCovered = false_v);

    b_4 unregisterItem(const ch_1 *category, const ch_1 *key);

    CData &data() {
        return _data;
    }

protected:
    none_ stop();

private:
    CData _ornData;
    CData _data;

    CProgram _normalHandle[NORMAL_HANDLE];

    mapHandle _handleInMap;
    mapHandle _handleOutMap;

    CNetworkHandle *_handle;

    mapRegister _registerMap;
};

#endif // _C_PROCESSOR_H_
