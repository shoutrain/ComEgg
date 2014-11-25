#ifndef _C_MODULE_INFO_H_
#define _C_MODULE_INFO_H_

#include "ModuleCommon.h"
#include "../Data/CData.h"

#include <string>
#include <map>

using namespace std;

class CInterfaceInfo;

typedef map<string, const CInterfaceInfo *> mapInterface;

class CModuleInfo : public CBase {
public:
    CModuleInfo(const ch_1 *path, const ch_1 *name, const ch_1 *ext) {
        memset(_path, 0, MODULE_PATH_LENGTH);
        strncpy(_path, path, MODULE_PATH_LENGTH);
        memset(_name, 0, MODULE_NAME_LENGTH);
        strncpy(_name, name, MODULE_NAME_LENGTH);
        memset(_ext, 0, MODULE_EXT_LENGTH);
        strncpy(_ext, ext, MODULE_EXT_LENGTH);
    }

    virtual ~CModuleInfo() {
        stop();
    }

    const char *getPath() const {
        return _path;
    }

    const char *getName() const {
        return _name;
    }

    const char *getExt() const {
        return _ext;
    }

    b_4 addInterface(const ch_1 *name, CInterfaceInfo *&interfaceInfo);

    CInterfaceInfo *getInterface(const ch_1 *name);

    bool_ isInterfaceReady(const ch_1 *name) {
        if (_interfaceInfoMap.end() != _interfaceInfoMap.find(name)) {
            return true_v;
        }

        return false_v;
    }

protected:
    none_ stop();

private:
    mapInterface _interfaceInfoMap;

    ch_1 _path[MODULE_PATH_LENGTH];
    ch_1 _name[MODULE_NAME_LENGTH];
    ch_1 _ext[MODULE_EXT_LENGTH];
};

#endif // _C_MODULE_INFO_H_
