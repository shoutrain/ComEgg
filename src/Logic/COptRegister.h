#ifndef _C_OPT_REGISTER_H_
#define _C_OPT_REGISTER_H_

#include "COperator.h"
#include "../Common/CRegister.h"
#include "../Transactions/CTransactionManager.h"

class COptRegister : public COperator {
public:
    COptRegister(const CVariable *category,
            const CVariable *key,
            const CVariable *object,
            const bool_ isCovered = false_v)
            : COperator(OT_REGISTER) {
        _category = category->clone();
        _key = key->clone();
        _object = object->clone();
        _isCovered = isCovered;
    }

    virtual ~COptRegister() {
        _DEL(_category);
        _DEL(_key);
        _DEL(_object);
    }

    COptRegister(const COptRegister &opt) : COperator(opt) {
        _category = opt._category->clone();
        _key = opt._key->clone();
        _object = opt._object->clone();
        _isCovered = opt._isCovered;
    }

    const COptRegister &operator=(const COptRegister &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_category);
            _DEL(_key);
            _DEL(_object);
            _category = opt._category->clone();
            _key = opt._key->clone();
            _object = opt._object->clone();
            _isCovered = opt._isCovered;
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptRegister(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _category->init(unit->data);
        _key->init(unit->data);
        _object->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_category;
    CVariable *_key;
    CVariable *_object;
    bool_ _isCovered;
};

#endif // _C_OPT_REGISTER_H_
