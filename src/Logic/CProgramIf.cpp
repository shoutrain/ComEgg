#include "CProgramIf.h"

CProgramIf::CProgramIf(const CProgramIf &opt) : CProgram(opt) {
    size_ num = (size_) opt._expVector.size();

    for (size_ n = 0; n < num; n++) {
        _expVector.push_back(opt._expVector[n]->clone());
    }
}

const CProgramIf &CProgramIf::operator=(const CProgramIf &opt) {
    if (this != &opt) {
        clear();

        CProgram::operator=(opt);

        size_ num = (size_) opt._expVector.size();

        for (size_ n = 0; n < num; n++) {
            _expVector.push_back(opt._expVector[n]->clone());
        }
    }

    return *this;
}

bool_ CProgramIf::addOperator(const COperator *opt) {
    assert(opt);

    if (OT_PROGRAM != opt->getType()) {
        return false_v;
    }

    _optVector.push_back(opt);

    return true_v;
}

bool_ CProgramIf::addExpression(const CExpression *expression) {
    assert(expression);
    _expVector.push_back(expression);

    return true_v;
}

none_ CProgramIf::init(const optUnit *unit) {
    CProgram::init(unit);

    optUnit ou;

    memcpy(&ou, unit, sizeof(optUnit));
    ou.data   = &_data;
    ou.parent = this;

    size_ num = (size_) _expVector.size();

    for (size_ n = 0; n < num; n++) {
        ((CExpression *) _expVector[n])->init(&ou);
    }
}

none_ CProgramIf::work(const TMessageUnit *tmu) {
    size_ num = (size_) _expVector.size();

    try {
        for (size_ n = 0; n < num; n++)
            if (_expVector[n]->evaluate(tmu)) {
                ((COperator *) _optVector[n])->work(tmu);
                reset();

                return;
            }

        if (num < (size_) _optVector.size()) {
            ((COperator *) _optVector[num])->work(tmu);
        }
    } catch (...) {
        reset();

        throw;
    }

    reset();
}

none_ CProgramIf::clear() {
    CProgram::clear();

    for (VectorExp::iterator pos = _expVector.begin();
         pos != _expVector.end(); pos++) {
        _DEL(*pos);
    }

    _expVector.clear();
}

