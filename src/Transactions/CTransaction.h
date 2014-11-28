#ifndef _C_TRANSACTION_H_
#define _C_TRANSACTION_H_

#include "CProcessor.h"
#include "../Common/CResource.h"

class CTransaction {
public:
    CTransaction(const CProcessor *processor, const size_ &size)
            : _resource(size, processor) {
    }

    virtual ~CTransaction() {
    }

    CProcessor *allocate() {
        return _resource.allocate();
    }

    b_4 release(CProcessor *&unit) {
        assert(unit);
        return _resource.reclaim(unit);
    }

    size_ getFreeSize() {
        return _resource.size();
    }

private:
    CTransaction();

    CTransaction(const CTransaction &);

    const CTransaction &operator=(const CTransaction &);

    CResource<CProcessor> _resource;
};

#endif // _C_TRANSACTION_H_
