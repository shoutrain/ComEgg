#ifndef _C_PROTOCOL_INFO_H_
#define _C_PROTOCOL_INFO_H_

#include "ProtocolCommon.h"
#include "../Data/CData.h"

#include <string>
#include <map>

using namespace std;

class CPduInfo;

typedef map<string, CPduInfo *> mapPdu;

class CProtocolInfo : public CBase {
public:
    CProtocolInfo() {
        _field    = null_v;
        _curField = null_v;
    }

    virtual ~CProtocolInfo() {
        stop();
    }

    // If GroupName is not null, Field is sub-field, GroupName is the name
    // of group.
    none_ addHeadField(const TField &field,
            const ch_1 *groupName = null_v);

    // Get field
    CField *getHeadField(const ch_1 *name);

    none_ addPdu(const ch_1 *name, CPduInfo *&pduInfo);

    CPduInfo *getPdu(const ch_1 *name);

    CData &data() {
        return _data;
    }

    bool_ isPduReady(const ch_1 *name) {
        if (_pduInfoMap.end() != _pduInfoMap.find(name)) {
            return true_v;
        }

        return false_v;
    }

protected:
    none_ stop();

private:
    mapField _headFieldMap;
    mapPdu   _pduInfoMap;

    CField *_field;
    CField *_curField;

    CData _data;
};

#endif // _C_PROTOCOL_INFO_H_
