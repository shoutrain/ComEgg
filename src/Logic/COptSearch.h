#ifndef _C_OPT_SEARCH_H_
#define _C_OPT_SEARCH_H_

#include "COperator.h"
#include "../Common/CRegister.h"
#include "../Transactions/CTransactionManager.h"

class COptSearch : public COperator {
public:
    COptSearch(const CVariable *category,
            const CVariable *key,
            const CVariable *object)
            : COperator(OT_SEARCH) {
        m_pCategory = category->clone();
        m_pKey = key->clone();
        m_pObject = object->clone();
    }

    virtual ~COptSearch() {
        _DEL(m_pCategory);
        _DEL(m_pKey);
        _DEL(m_pObject);
    }

    COptSearch(const COptSearch &opt) : COperator(opt) {
        m_pCategory = opt.m_pCategory->clone();
        m_pKey = opt.m_pKey->clone();
        m_pObject = opt.m_pObject->clone();
    }

    const COptSearch &operator=(const COptSearch &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(m_pCategory);
            _DEL(m_pKey);
            _DEL(m_pObject);
            m_pCategory = opt.m_pCategory->clone();
            m_pKey = opt.m_pKey->clone();
            m_pObject = opt.m_pObject->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptSearch(*this);
    }

    virtual none_ init(const optUnit *unit) {
        COperator::init(unit);

        m_pCategory->init(unit->data);
        m_pKey->init(unit->data);
        m_pObject->init(unit->data);
    }

    virtual none_ work(const TMessageUnit *tmu);

private:
    CVariable *m_pCategory;
    CVariable *m_pKey;
    CVariable *m_pObject;
};

#endif // _C_OPT_SEARCH_H_
