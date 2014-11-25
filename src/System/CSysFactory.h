#ifndef _C_SYS_FACTORY_H_
#define _C_SYS_FACTORY_H_

#include "CLinuxFileImp.h"
#include "CLinuxSysInfoImp.h"
#include "CLinuxSysCallImp.h"
#include "CLinuxModuleCallImp.h"
#include "../Common/BaseType.h"

class CSysFactory {
public:
    static CSysFactory *instance() {
        if (!_instance) {
            _instance = new CSysFactory();
        }

        return _instance;
    }

    static none_ destroy() {
        _DEL(_instance);
    }

    CFileImp *makeFile() {
        return (CFileImp *) new CLinuxFileImp();
    }

    CSysInfoImp *makeSysInfo() {
        return (CSysInfoImp *) new CLinuxSysInfoImp();
    }

    CSysCallImp *makeSysCall() {
        return (CSysCallImp *) new CLinuxSysCallImp();
    }

    CModuleCallImp *makeModuleCall() {
        return (CModuleCallImp *) new CLinuxModuleCallImp();
    }

private:
    CSysFactory() {
    };

    CSysFactory(const CSysFactory &);

    const CSysFactory &operator=(const CSysFactory &);

    ~CSysFactory();

    static CSysFactory *_instance;
};

#endif // _C_SYS_FACTORY_H_
