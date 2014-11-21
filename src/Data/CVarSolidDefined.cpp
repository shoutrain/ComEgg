#include "CVarSolidDefined.h"

CVariable *CVarSolidDefined::clone() const {
    return (CVariable *) new CVarSolidDefined(_name);
}

void CVarSolidDefined::init(const CData *data) {
    _value = data->value(_name);
}

v_ *CVarSolidDefined::value(const TMessageUnit *tmu) {
    return _value;
}
