#ifndef _C_OPT_READ_FILE_H_
#define _C_OPT_READ_FILE_H_

#include "COperator.h"

class COptReadFile : public COperator {
public:
    COptReadFile(const CVariable *filePath,
            const CVariable *fileName,
            const CVariable *result)
            : COperator(OT_READ_FILE) {
        _filePath = filePath->clone();
        _fileName = fileName->clone();
        _result = result->clone();
    }

    virtual ~COptReadFile() {
        _DEL(_filePath);
        _DEL(_fileName);
        _DEL(_result);
    }

    COptReadFile(const COptReadFile &opt) : COperator(opt) {
        _filePath = opt._filePath->clone();
        _fileName = opt._fileName->clone();
        _result = opt._result->clone();;
    }

    const COptReadFile &operator=(const COptReadFile &opt) {
        if (this != &opt) {
            COperator::operator=(opt);

            _DEL(_filePath);
            _DEL(_fileName);
            _DEL(_result);
            _filePath = opt._filePath->clone();
            _fileName = opt._fileName->clone();
            _result = opt._result->clone();
        }

        return *this;
    }

    virtual COperator *clone() const {
        return (COperator *) new COptReadFile(*this);
    }

    virtual void init(const optUnit *unit) {
        COperator::init(unit);

        _filePath->init(unit->data);
        _fileName->init(unit->data);
        _result->init(unit->data);
    }

    virtual void work(const TMessageUnit *tmu);

private:
    CVariable *_filePath;
    CVariable *_fileName;
    CVariable *_result;
};

#endif // _C_OPT_READ_FILE_H_
