#ifndef _C_OPT_UNREGISTER_H_
#define _C_OPT_UNREGISTER_H_

#include "COperator.h"

#include "../Common/CRegister.h"
#include "../Transactions/CTransactionManager.h"

class COptUnregister : public COperator {
public:
    COptUnregister(const CVariable *category,
            const CVariable *key)
            : COperator(OT_UNREGISTER) {
        _category = category->clone();
        _key      = key->clone();
    }

    virtual ~COptUnregister() {
        _DEL(_category);
        _DEL(_key);
    }

    COptUnregister(const COptUnregister &opt) : COperator(opt) {
        _category = opt._category->clone();
        _key      = opt._key->clone();
    }

    const COptUnregister &operator=(const COptUnregister &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_category);
            _DEL(_key);
            _category = opt._category->clone();
            _key      = opt._key->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptUnregister(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _category->init(unit->data);
        _key->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_category;
    CVariable *_key;
};

#endif // _C_OPT_UNREGISTER_H_
