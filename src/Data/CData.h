#ifndef _C_DATA_H_
#define _C_DATA_H_

#include "DataCommon.h"
#include "CFieldGroupDefined.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, v_ *> mapVariable;
typedef map<string, TFieldGroup *> mapData;

class CData {
public:
    CData() {
        _parent = null_v;
    }

    virtual ~CData() {
        clear();
    }

    CData(const CData &data);

    const CData &operator=(const CData &data);

    none_ SetParent(const CData *pParent) {
        _parent = (CData *) pParent;
    }

    // define variables for any type without initialized value.
    bool_ define(
            const ch_1 *name,        // Variable's name.
            evt_ type        // Variable's type.
    );

    // define vairables with initialized value, integer number less than 32 bit.
    bool_ define(
            const ch_1 *name,    // Variable's name.
            evt_ type,    // Variable's type, except STR and OBJ.
            b_4 data    // Vairable's initialized value.
    );

    // define vairables with initialized value, 64 bit signed integer number.
    bool_ define(
            const ch_1 *name,    // Variable's name.
            b_8 data    // Vairable's initialized value.
    );

    // define vairables with initialized value, 64 bit unsigned integer number.
    bool_ define(
            const ch_1 *name,    // Variable's name.
            ub_8 data    // Vairable's initialized value.
    );

    // define vairables with initialized value, 32 bit float number.
    bool_ define(
            const ch_1 *name,    // Variable's name.
            fb_4 data    // Vairable's initialized value.
    );

    // define vairables with initialized value, 64 bit float number.
    bool_ define(
            const ch_1 *name,    // Variable's name.
            fb_8 data    // Vairable's initialized value.
    );

    // define vairables just for STR with initialized value.
    bool_ define(
            const ch_1 *name,    // Variable's name.
            const ch_1 *value    // Vairable's initialized value.
    );

    // define vairables just for OBJ with initialized value.
    bool_ define(
            const ch_1 *name,    // Variable's name.
            obj_ object    // Vairable's initialized value.
    );

    // define variables just for Group without initialized value.
    bool_ define(const CFieldGroupDefined *fieldGroup);

    // Get normal variable's value.
    v_ *value(const ch_1 *name) const;

    // Get group or indexed variable's struct
    v_ *value(const ch_1 *groupName,
            const ch_1 *subName,
            TFieldGroup *&data) const;

    none_ clear();

private:
    CData *_parent;

    mapVariable _variableMap;
    mapData _dataMap;
};

#endif // CDATA_H
