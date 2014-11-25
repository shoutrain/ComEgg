#ifndef _C_MODULE_MANAGER_H_
#define _C_MODULE_MANAGER_H_

#include "ModuleCommon.h"

#include <string>
#include <map>

using namespace std;

class CModuleInfo;

typedef map<string, const CModuleInfo *> mapModule;

class CModuleManager : public CBase {
public:
    static CModuleManager *instance() {
        if (_instance) {
            return _instance;
        }

        _instance = new CModuleManager;

        return _instance;
    }

    static void destroy() {
        _DEL(_instance);
    }

    b_4 addModule(const ch_1 *path,
            const ch_1 *name,
            const ch_1 *ext,
            CModuleInfo *&module);

    CModuleInfo *getModule(const ch_1 *name);

    bool_ isModuleReady(const ch_1 *name) {
        if (!name) {
            return false_v;
        }

        if (_moduleMap.end() == _moduleMap.find(name)) {
            return false_v;
        }

        return true_v;
    }

protected:
    void stop();

private:
    CModuleManager() {
    }

    CModuleManager(const CModuleManager &);

    const CModuleManager &operator=(const CModuleManager &);

    virtual ~CModuleManager() {
        stop();
    }

    mapModule _moduleMap;

    static CModuleManager *_instance;
};

#endif // _C_MODULE_MANAGER_H_
