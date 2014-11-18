#ifndef DATA_COMMON_H
#define DATA_COMMON_H

#include "../Common/Common.h"

#include <string>
#include <map>

class CField;
typedef map<string, const CField *>	map_field;

const ub_4 VARIABLE_NAME_LENGTH = 32;

enum EFieldStyle
{
	FIELD_NORMAL_STYLE	= 0x00010000,
	FIELD_FLOAT_STYLE	= 0x00020000,
	FIELD_STRING_STYLE	= 0x00030000,
	FIELD_GROUP_STYLE	= 0x00040000,

	GET_FIELD_STYLE		= 0x000F0000
};

enum EFieldType
{
	FIELD_B_1_TYPE		= B_1	| FIELD_NORMAL_STYLE,
	FIELD_UB_1_TYPE		= UB_1	| FIELD_NORMAL_STYLE,
	FIELD_B_2_TYPE		= B_2	| FIELD_NORMAL_STYLE,
	FIELD_UB_2_TYPE		= UB_2	| FIELD_NORMAL_STYLE,
	FIELD_B_4_TYPE		= B_4	| FIELD_NORMAL_STYLE,
	FIELD_UB_4_TYPE		= UB_4	| FIELD_NORMAL_STYLE,
	FIELD_B_8_TYPE		= B_8	| FIELD_NORMAL_STYLE,
	FIELD_UB_8_TYPE		= UB_8	| FIELD_NORMAL_STYLE,
	FIELD_FB_4_TYPE		= FB_4	| FIELD_FLOAT_STYLE,
	FIELD_FB_8_TYPE		= FB_8	| FIELD_FLOAT_STYLE,

	FIELD_STR_TYPE		= STR	| FIELD_STRING_STYLE,
	FIELD_GROUP_TYPE	= FIELD_GROUP_STYLE
};

struct TField
{
    ch_1 			sName[VARIABLE_NAME_LENGTH];
	EFieldStyle		Style;
	bool_			IsSigned;

	// Length is valid just when Style is not FIELD_GROUP.
	size_			nLength;

	// If Style is FIELD_STRING_STYLE, nSize is valid.
	size_			nSize;

	// If Style is FIELD_GROUP_STYLE, sSizeName is valid.
	ch_1			sSizeName[VARIABLE_NAME_LENGTH];
};

#pragma pack(1)

struct TFieldGroup
{
	size_ nSize;
	ub_1 *pData;
};

#pragma pack()

#endif // DATA_COMMON_H
