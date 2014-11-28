#include "COptUseModule.h"
#include "../Data/CVarModule.h"
#include "../System/CModuleCall.h"
#include "../Modules/CModuleInfo.h"

COptUseModule::COptUseModule(const CInterfaceInfo *interfaceInfo)
        : COperator(OT_USE_MODULE) {
    _interfaceInfo = (CInterfaceInfo *) interfaceInfo;

    CField    *fieldInfo = _interfaceInfo->getInStruct();
    TEvaluate *evaluate  = null_v;

    while (fieldInfo) {
        if (null_v == fieldInfo->getGroupField()) {
            evaluate = new TEvaluate;

            evaluate->fieldInfo = fieldInfo;
            evaluate->field     = null_v;
            evaluate->value     = null_v;

            _inEvaluateVector.push_back(evaluate);
        }

        fieldInfo = fieldInfo->getNextField();
    }

    fieldInfo = _interfaceInfo->getOutStruct();

    while (fieldInfo) {
        if (null_v == fieldInfo->getGroupField()) {
            evaluate = new TEvaluate;

            evaluate->fieldInfo = fieldInfo;
            evaluate->field     = null_v;
            evaluate->value     = null_v;

            _outEvaluateVector.push_back(evaluate);
        }

        fieldInfo = fieldInfo->getNextField();
    }
}

COptUseModule::COptUseModule(const COptUseModule &opt) : COperator(opt) {
    _interfaceInfo = opt._interfaceInfo;

    for (VectorEvaluate::const_iterator pos = opt._inEvaluateVector.begin();
         pos != opt._inEvaluateVector.end(); pos++) {
        TEvaluate *evaluate = new TEvaluate;

        memset(evaluate, 0, sizeof(TEvaluate));
        evaluate->fieldInfo = (*pos)->fieldInfo;

        if ((*pos)->field) {
            evaluate->field = (*pos)->field->clone();
        }

        if ((*pos)->value) {
            evaluate->value = (*pos)->value->clone();
        }

        _inEvaluateVector.push_back(evaluate);
    }

    for (VectorEvaluate::const_iterator pos_ = opt._outEvaluateVector.begin();
         pos_ != opt._outEvaluateVector.end(); pos_++) {
        TEvaluate *evaluate = new TEvaluate;

        memset(evaluate, 0, sizeof(TEvaluate));
        evaluate->fieldInfo = (*pos_)->fieldInfo;

        if ((*pos_)->field) {
            evaluate->field = (*pos_)->field->clone();
        }

        if ((*pos_)->value) {
            evaluate->value = (*pos_)->value->clone();
        }

        _outEvaluateVector.push_back(evaluate);
    }
}

const COptUseModule &COptUseModule::operator=(const COptUseModule &opt) {
    if (this != &opt) {
        COperator::operator=(opt);

        clear();

        _interfaceInfo = opt._interfaceInfo;

        for (VectorEvaluate::const_iterator pos
                                                    = opt._inEvaluateVector.begin();
             pos != opt._inEvaluateVector.end(); pos++) {
            TEvaluate *evaluate = new TEvaluate;

            memset(evaluate, 0, sizeof(TEvaluate));
            evaluate->fieldInfo = (*pos)->fieldInfo;

            if ((*pos)->field) {
                evaluate->field = (*pos)->field->clone();
            }

            if ((*pos)->value) {
                evaluate->value = (*pos)->value->clone();
            }

            _inEvaluateVector.push_back(evaluate);
        }

        for (VectorEvaluate::const_iterator pos_
                                                    = opt._outEvaluateVector.begin();
             pos_ != opt._outEvaluateVector.end(); pos_++) {
            TEvaluate *evaluate = new TEvaluate;

            memset(evaluate, 0, sizeof(TEvaluate));
            evaluate->fieldInfo = (*pos_)->fieldInfo;

            if ((*pos_)->field) {
                evaluate->field = (*pos_)->field->clone();
            }

            if ((*pos_)->value) {
                evaluate->value = (*pos_)->value->clone();
            }

            _outEvaluateVector.push_back(evaluate);
        }
    }

    return *this;
}

COptUseModule::~COptUseModule() {
    clear();
}

none_ COptUseModule::clear() {
    _interfaceInfo = null_v;

    for (VectorEvaluate::iterator pos = _inEvaluateVector.begin();
         pos != _inEvaluateVector.end(); pos++) {
        _DEL((*pos)->field);
        _DEL((*pos)->value);
        _DEL(*pos);
    }

    for (VectorEvaluate::iterator pos = _outEvaluateVector.begin();
         pos != _outEvaluateVector.end(); pos++) {
        _DEL((*pos)->field);
        _DEL((*pos)->value);
        _DEL(*pos);
    }

    _inEvaluateVector.clear();
    _outEvaluateVector.clear();
}

none_ COptUseModule::init(const optUnit *unit) {
    COperator::init(unit);

    for (VectorEvaluate::iterator pos = _inEvaluateVector.begin();
         pos != _inEvaluateVector.end(); pos++) {
        if ((*pos)->field) {
            (*pos)->field->init(unit->data);
        }

        if ((*pos)->value) {
            (*pos)->value->init(unit->data);
        }
    }

    for (VectorEvaluate::iterator pos_ = _outEvaluateVector.begin();
         pos_ != _outEvaluateVector.end(); pos_++) {
        if ((*pos_)->field) {
            (*pos_)->field->init(unit->data);
        }

        if ((*pos_)->value) {
            (*pos_)->value->init(unit->data);
        }
    }
}

bool_ COptUseModule::addInParameter(CVariable *value) {
    if (!_interfaceInfo || !value) {
        return false_v;
    }

    VectorEvaluate::iterator pos;

    for (pos = _inEvaluateVector.begin();
         pos != _inEvaluateVector.end(); pos++) {
        if (!(*pos)->field || !(*pos)->value) {
            (*pos)->field = (CVariable *) new CVarModule((*pos)->fieldInfo);
            (*pos)->value = value->clone();

            break;
        }
    }

    if (_inEvaluateVector.end() == pos) {
        return false_v;
    }

    return true_v;
}

bool_ COptUseModule::addOutParameter(const ch_1 *fieldName,
        CVariable *value) {
    if (!_interfaceInfo) {
        return false_v;
    }

    if (!fieldName || 0 == fieldName[0]) {
        return false_v;
    }

    if (!value) {
        return false_v;
    }

    CField *fieldInfo = _interfaceInfo->getOutField(fieldName);

    if (null_v == fieldInfo) {
        return false_v;
    }

    VectorEvaluate::iterator pos;

    for (pos = _outEvaluateVector.begin();
         pos != _outEvaluateVector.end(); pos++) {
        if ((*pos)->fieldInfo == fieldInfo) {
            if ((*pos)->field || (*pos)->value) {
                return false_v;
            }

            break;
        }
    }

    if (_outEvaluateVector.end() == pos) {
        return false_v;
    }

    (*pos)->field = (CVariable *) new CVarModule(fieldInfo);
    (*pos)->value = value->clone();

    return true_v;
}

none_ COptUseModule::work(const TMessageUnit *tmu) {
    size_ size = 0;

    for (VectorEvaluate::const_iterator pos = _inEvaluateVector.begin();
         pos != _inEvaluateVector.end(); pos++) {
        if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type()) {
            // If it's Group, check if it's available.
            if ((*pos)->field && (*pos)->value) {
                obj_  temp;
                bool_ isCountSize = false_v;

                if ((*pos)->value->value(temp)) {
                    // If ture, Defined Group
                    isCountSize = true_v;
                } else if ((*pos)->fieldInfo->size(tmu->message, tmu->size)) {
                    // If ture, Network Group
                    isCountSize = true_v;
                }

                if (isCountSize) {
                    size += (*pos)->value->value(tmu)->size();
                }
            }
        } else {
            size += (*pos)->fieldInfo->getUnitSize();
        }
    }

    TMessageUnit inMU;

    memset(&inMU, 0, sizeof(TMessageUnit));
    inMU.size = size;

    if (inMU.size) {
        inMU.message = new ub_1[inMU.size];
        memset(inMU.message, 0, inMU.size);
    }

    TMessageUnit outMU;

    memset(&outMU, 0, sizeof(TMessageUnit));

    for (VectorEvaluate::const_iterator pos = _inEvaluateVector.begin();
         pos != _inEvaluateVector.end(); pos++) {
        v_ *field = (*pos)->field->value(&inMU);
        v_ *value = (*pos)->value->value(tmu);

        (*field) = (*value);
    }

    CModuleCall mc;

    if (!mc.call(_interfaceInfo->getModuleInfo()->getPath(),
            _interfaceInfo->getModuleInfo()->getName(),
            _interfaceInfo->getModuleInfo()->getExt(),
            _interfaceInfo->name(),
            inMU.message,
            inMU.size,
            outMU.message,
            outMU.size)) {
        _DEL_ARR(inMU.message);
        _DEL_ARR(outMU.message);
        // TODO tell outside
        return;
    }

    // Get variable size first, so that can create enough memory to keep it.
    for (VectorEvaluate::const_iterator pos = _outEvaluateVector.begin();
         pos != _outEvaluateVector.end(); pos++) {
        if ((*pos)->field && (*pos)->value) {
            if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type() &&
                    // It must be CFieldGroup(Module), check if it's available.
                            (*pos)->fieldInfo->size(outMU.message, outMU.size)) {
                v_          *field      = (*pos)->field->value(&outMU);
                CField      *valueField = null_v;
                v_          *valueData  =
                                    (*pos)->value->value((obj_ &) valueField);
                TFieldGroup *valueGroup =
                                    (TFieldGroup *) (obj_) *valueData;

                if (valueGroup->size && valueGroup->data) {
                    _DEL_ARR(valueGroup->data);
                    valueGroup->size = 0;
                }

                valueGroup->size = field->size();

                if (valueGroup->size) {
                    // should be true
                    valueGroup->data = new ub_1[valueGroup->size];
                    memset(valueGroup->data, 0, valueGroup->size);
                }
                else {
                    _DEL_ARR(inMU.message);
                    _DEL_ARR(outMU.message);
                    // TODO tell outside
                    return;
                }
            }
        } else {
            _DEL_ARR(inMU.message);
            _DEL_ARR(outMU.message);
            // TODO tell outside
            return;
        }
    }

    for (VectorEvaluate::const_iterator pos = _outEvaluateVector.begin();
         pos != _outEvaluateVector.end(); pos++) {
        if (FIELD_GROUP_TYPE == (*pos)->fieldInfo->type()) {
            CField      *valueField = null_v;
            v_          *valueData  = (*pos)->value->value((obj_ &) valueField);
            TFieldGroup *valueGroup = (TFieldGroup *) (obj_) *valueData;

            if (!valueGroup->size) {
                continue;
            }
        }

        v_ *field = (*pos)->field->value(&outMU);
        v_ *value = (*pos)->value->value(tmu);

        (*value) = (*field);
    }

    _DEL_ARR(inMU.message);
    _DEL_ARR(outMU.message);
}
