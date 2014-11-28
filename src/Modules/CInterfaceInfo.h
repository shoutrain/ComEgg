#ifndef _C_INTERFACE_INFO_H_
#define _C_INTERFACE_INFO_H_

#include "ModuleCommon.h"
#include "CModuleInfo.h"

#include <string.h>

class CInterfaceInfo : public CBase {
public:
    CInterfaceInfo(const CModuleInfo *moduleInfo, const ch_1 *name) {
        _inField    = null_v;
        _inCurField = null_v;
        _outField   = null_v;
        _outCurField = null_v;
        _moduleInfo = (CModuleInfo *) moduleInfo;
        memset(_name, 0, INTERFACE_NAME_LEGNTH);
        strncpy(_name, name, INTERFACE_NAME_LEGNTH);
    }

    virtual ~CInterfaceInfo() {
    }

    CModuleInfo *getModuleInfo() const {
        return _moduleInfo;
    }

    const ch_1 *name() const {
        return _name;
    }

    // If GroupName is not null, Field is sub-field, GroupName is the name
    // of group.
    none_ addInField(const TField &field,
            const ch_1 *groupName = null_v);

    none_ addOutField(const TField &field,
            const ch_1 *groupName = null_v);

    // Get field
    CField *getInField(const ch_1 *name);

    CField *getOutField(const ch_1 *name);

    // Get struct
    CField *getInStruct() {
        return _inField;
    }

    CField *getOutStruct() {
        return _outField;
    }

protected:
    none_ stop();

private:
    MapField _inFieldMap;
    MapField _outFieldMap;

    CField *_inField;
    CField *_inCurField;

    CField *_outField;
    CField *_outCurField;

    CModuleInfo *_moduleInfo;
    ch_1  _name[INTERFACE_NAME_LEGNTH];
};

#endif // _C_INTERFACE_INFO_H_
