#ifndef _C_IP_FILTER_H_
#define _C_IP_FILTER_H_

#include "NetworkCommon.h"

#include <set>
#include <string>

using namespace std;

typedef set<string> SetString;

class CIPFilter {
public:
    CIPFilter() {
        _isForbid = false_v;
        _isWork   = false_v;
    }

    virtual ~CIPFilter() {
        _ipSet.clear();
    }

    none_ setForbid(bool_ isForbid = true_v) {
        _isForbid = isForbid;
        _isWork   = true_v;
    }

    bool_ addIP(const ch_1 *ip) {
        assert(ip && 0 != ip[0]);

        if (!_isWork) {
            return false_v;
        }

        if (!_ipSet.count(ip)) {
            _ipSet.insert(ip);
        }

        return true_v;
    }

    bool_ addIpGroup(const ch_1 *ip);

    bool_ ipPermit(const ch_1 *ip) {
        assert(ip && 0 != ip[0]);

        if (!_isWork) {
            return true_v;
        }

        if (_isForbid) {
            if (_ipSet.count(ip)) {
                return false_v;
            } else {
                return true_v;
            }
        } else {
            if (_ipSet.count(ip)) {
                return true_v;
            } else {
                return false_v;
            }
        }
    }

private:
    CIPFilter(const CIPFilter &);

    const CIPFilter &operator=(const CIPFilter &);

    bool_ _isWork;
    bool_ _isForbid;

    SetString _ipSet;
};

#endif // _C_IP_FILTER_H_
