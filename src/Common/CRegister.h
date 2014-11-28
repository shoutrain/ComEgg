#ifndef _C_REGISTER_H_
#define _C_REGISTER_H_

#include "CAutoVar.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, v_ *> MapVariable;
typedef map<string, mapVariable *> mapCategory;

class CRegister : public CBase {
public:
    static CRegister *instance() {
        if (_instance) {
            return _instance;
        }

        _instance = new CRegister;

        return _instance;
    }

    static void destroy() {
        _DEL(_instance);
    }

    v_ *searchItem(const ch_1 *category, const ch_1 *key);

    b_4 registerItem(const ch_1 *category, const ch_1 *key, const v_ *variable,
            const bool_ isCovered = false_v);

    b_4 unregisterItem(const ch_1 *category, const ch_1 *key);

protected:
    CRegister() {
    }

    CRegister(const CRegister &);

    const CRegister &operator=(const CRegister &);

    virtual ~CRegister() {
        stop();
    }

    b_4 stop();

private:
    static CRegister *_instance;

    mapCategory _categoryMap;
};

#endif // _C_REGISTER_H_
