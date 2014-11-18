#ifndef CDATA_H
#define CDATA_H

#include "DataCommon.h"
#include "CFieldGroupDefined.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, v_ *> map_variable;
typedef map<string, TFieldGroup *> map_data;

class CData
{
public:
	CData()
	{
		m_pParent = null_v;
	}

	virtual ~CData()
	{
		Clear();
	}

	CData(const CData &Data);
	const CData &operator =(const CData &Data);

	void SetParent(const CData *pParent)
	{
		m_pParent = (CData *)pParent;
	}

	// Define variables for any type without initialized value.
	bool_ Define(
		const ch_1 *pszName,		// Variable's name.
		evt_ Type		// Variable's type.
		);

	// Define vairables with initialized value, integer number less than 32 bit.
	bool_ Define(
		const ch_1 *pszName,	// Variable's name.
		evt_ Type,	// Variable's type, except STR and OBJ.
		b_4 Data	// Vairable's initialized value.
		);

	// Define vairables with initialized value, 64 bit signed integer number.
	bool_ Define(
		const ch_1 *pszName,	// Variable's name.
		b_8 Data	// Vairable's initialized value.
		);

	// Define vairables with initialized value, 64 bit unsigned integer number.
	bool_ Define(
		const ch_1 *pszName,	// Variable's name.
		ub_8 Data	// Vairable's initialized value.
		);

	// Define vairables with initialized value, 32 bit float number.
	bool_ Define(
		const ch_1 *pszName,	// Variable's name.
		fb_4 Data	// Vairable's initialized value.
		);

	// Define vairables with initialized value, 64 bit float number.
	bool_ Define(
		const ch_1 *pszName,	// Variable's name.
		fb_8 Data	// Vairable's initialized value.
		);

	// Define vairables just for STR with initialized value.
	bool_ Define(
		const ch_1 *pszName,	// Variable's name.
		const ch_1 *pszValue	// Vairable's initialized value.
		);

	// Define vairables just for OBJ with initialized value.
	bool_ Define(
		const ch_1 *pszName,	// Variable's name.
		obj_ Object	// Vairable's initialized value.
		);

	// Define variables just for Group without initialized value.
	bool_ Define(const CFieldGroupDefined *pFieldGroup);
 
	// Get normal variable's value.
	v_ *Value(const ch_1 *pszName) const ;

	// Get group or indexed variable's struct
	v_ *Value(const ch_1 *pszGroupName,
			  const ch_1 *pszSubName, 
			  TFieldGroup *&pData) const;

	void Clear();

private:
	CData *m_pParent;

	map_variable m_VariableMap;
	map_data m_DataMap;
};

#endif // CDATA_H
