#ifndef _LOGIC_COMMMON_H_
#define _LOGIC_COMMMON_H_

#include "CGlobal.h"

// Operation types define
enum EOperatorType {
    OT_EMPTY,

    OT_UNITARY_CALCULATE,
    OT_DUALITY_CALCULATE,

    OT_CONFIG_GROUP,

    OT_IF,
    OT_WHILE,
    OT_CONTINUE,
    OT_BREAK,
    OT_BLOCK,

    OT_SEND,
    OT_FORWARD,

    OT_GET_ADDRESS,

    OT_REGISTER,
    OT_UNREGISTER,
    OT_SEARCH,

    OT_GET_USAGE,

    OT_NETWORK_WAKE_UP,
    OT_NETWORK_SLEEP,

    OT_READ_FILE,
    OT_SAVE_FILE,
    OT_DELETE_FILE,

    OT_USE_MODULE,

    OT_SPLIT,

    OT_DIE,

    OT_PROGRAM
};

enum EUnitaryCalculate {
    UC_EQL,
    UC_NEG,
    UC_NOT,
    UC_OBV
};

enum EDualityCalculate {
    EC_ADD,
    EC_SUB,
    EC_MUL,
    EC_DIV,
    EC_MOD,
    EC_AND,
    EC_OR,
    EC_XOR
};

enum ECompareCalculate {
    CC_EQ,
    CC_GL,
    CC_GT,
    CC_GE,
    CC_LS,
    CC_LE
};

enum ECompareRelation {
    CR_AND,
    CR_OR,
    CR_NOT
};

#include <vector>

using namespace std;

class COperator;

typedef vector<const COperator *> VectorOpt;

class CExpression;

typedef vector<const CExpression *> VectorExp;

class CData;

class CProcessor;

// Connect data and corresponding operation toghter
typedef struct {
    CData *data;
    CProcessor *container;
    COperator *parent;
} optUnit;


typedef struct {
} callContinue;

typedef struct {
} callBlock;

typedef struct {
} callBreak;

class CField;

class CVariable;

struct TEvaluate {
    CField *fieldInfo;
    CVariable *field;
    CVariable *value;
};

#include <vector>

using namespace std;

typedef vector<TEvaluate *> VectorEvaluate;

#endif // _LOGIC_COMMMON_H_
