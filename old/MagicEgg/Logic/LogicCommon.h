#ifndef LOGIC_COMMMON_H
#define LOGIC_COMMMON_H

#include "../Common/Common.h"

// Operation types define
enum EOperatorType
{
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

	OT_READ_FILE,
	OT_SAVE_FILE,
	OT_DELETE_FILE,

	OT_SPLIT,

	OT_DIE,

	OT_SHOW_WINDOW,
	OT_WAIT_MESSAGE,
	OT_ALERT,
	OT_ENABLE,
	OT_ADD_ITEM,

	OT_PROGRAM,
};

enum EUnitaryCalculate
{
	UC_EQL,
	UC_NEG,
	UC_NOT,
	UC_OBV
};

enum EDualityCalculate
{
	EC_ADD,
	EC_SUB,
	EC_MUL,
	EC_DIV,
	EC_MOD,
	EC_AND,
	EC_OR,
	EC_XOR
};

enum ECompareCalculate
{
	CC_EQ,
	CC_GL,
	CC_GT,
	CC_GE,
	CC_LS,
	CC_LE
};

enum ECompareRelation
{
	CR_AND,
	CR_OR,
	CR_NOT
};

#include <vector>

using namespace std;

class COperator;
typedef vector<const COperator *> vector_opt;

class CExpression;
typedef vector<const CExpression *> vector_exp;

class CVariable;
typedef vector<const CVariable *> vector_var;

class CData;

// Connect data and corresponding operation toghter
typedef struct
{
	CData		*pData;
	COperator	*pParent;
} opt_unit;

typedef struct {} call_continue;
typedef struct {} call_block;
typedef struct {} call_break;

class CField;
class CVariable;

struct TEvaluate
{
	CField *pFieldInfo;
	CVariable *pField;
	CVariable *pValue;
};

#include <vector>

using namespace std;

typedef vector<TEvaluate *>	vector_evaluate;

#endif // LOGIC_COMMMON_H
