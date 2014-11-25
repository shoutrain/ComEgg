#include "CProgram.h"

CProgram::CProgram(const CProgram &opt) : COperator(opt) {
    _ornData = opt._ornData;
    _data    = opt._data;

    size_ n = (size_) opt._optVector.size();

    for (size_ i = 0; i < n; i++) {
        _optVector.push_back(opt._optVector[i]->clone());
    }
}

const CProgram &CProgram::operator=(const CProgram &opt) {
    if (this != &opt) {
        COperator::operator=(opt);

        clear();

        _ornData = opt._ornData;
        _data    = opt._data;

        size_ n = (size_) opt._optVector.size();

        for (size_ i = 0; i < n; i++) {
            _optVector.push_back(opt._optVector[i]->clone());
        }
    }

    return *this;
}

bool_ CProgram::addOperator(const COperator *opt) {
    assert(opt);
    _optVector.push_back(opt);

    return true_v;
}

void CProgram::reset() {
    _data = _ornData;

    size_ n = (size_) _optVector.size();

    for (size_ i = 0; i < n; i++) {
        ((COperator *) _optVector[i])->reset();
    }
}

void CProgram::init(const optUnit *unit) {
    COperator::init(unit);
    _data.SetParent(unit->data);

    optUnit ou;

    memcpy(&ou, unit, sizeof(optUnit));
    ou.data   = &_data;
    ou.parent = this;

    size_ n = (size_) _optVector.size();

    for (size_ i = 0; i < n; i++) {
        ((COperator *) _optVector[i])->init(&ou);
    }
}

void CProgram::work(const TMessageUnit *tmu) {
    size_ n = (size_) _optVector.size();

    for (size_ i = 0; i < n; i++) {
        try {
            ((COperator *) _optVector[i])->work(tmu);
        } catch (callBlock) {
            reset();

            if (getParent()) {
                throw;
            } else {
                return;
            }
        }
    }

    reset();
}

void CProgram::clear() {
    _data.clear();
    _ornData.clear();

    size_ n = (size_) _optVector.size();

    for (size_ i = 0; i < n; i++) {
        _DEL(_optVector[i])
    };

    _optVector.clear();
}
