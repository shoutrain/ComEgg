#ifndef _C_OPT_DELETE_FILE_H_
#define _C_OPT_DELETE_FILE_H_

#include "COperator.h"

class COptDeleteFile : public COperator {
public:
    COptDeleteFile(const CVariable *filePath,
            const CVariable *result)
            : COperator(OT_DELETE_FILE) {
        _filePath = filePath->clone();
        _result = result->clone();
    }

    virtual ~COptDeleteFile() {
        _DEL(_filePath);
        _DEL(_result);
    }

    COptDeleteFile(const COptDeleteFile &opt) : COperator(opt) {
        _filePath = opt._filePath->clone();
        _result = opt._result->clone();
    }

    const COptDeleteFile &operator=(const COptDeleteFile &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_filePath);
            _DEL(_result);

            _filePath = opt._filePath->clone();
            _result = opt._result->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptDeleteFile(*this);
    }

    virtual none_ init(const optUnit *unit) {
        COperator::init(unit);

        _filePath->init(unit->data);
        _result->init(unit->data);
    }

    virtual none_ work(const TMessageUnit *tmu);

private:
    CVariable *_filePath;
    CVariable *_result;
};

#endif // _C_OPT_DELETE_FILE_H_

