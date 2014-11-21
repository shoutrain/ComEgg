#ifndef _C_VAR_NETWORK_H_
#define _C_VAR_NETWORK_H_

#include "CVariable.h"
#include "CField.h"

class CVarNetwork : public CVariable {
public:
    CVarNetwork(const CField *field, const ch_1 *indexName = null_v) {
        _field = (CField *) field;
        memset(_indexName, 0, VARIABLE_NAME_LENGTH);

        if (indexName) {
            strncpy(_indexName, indexName, VARIABLE_NAME_LENGTH);
        }

        _index = null_v;
    }

    virtual CVariable *clone() const;

    virtual void init(const CData *data);

    virtual v_ *value(const TMessageUnit *tmu);

private:
    CVarNetwork();

    CVarNetwork(const CVarNetwork &);

    const CVarNetwork &operator=(const CVarNetwork &);

    CField *_field;
    ch_1 _indexName[VARIABLE_NAME_LENGTH];
    v_ *_index;

    v_ _value;
};

#endif // _C_VAR_NETWORK_H_
