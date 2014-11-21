#ifndef _C_PDU_INFO_H_
#define _C_PDU_INFO_H_

#include "ProtocolCommon.h"

class CPduInfo : public CBase
{
public:
	CPDUInfo(const CField *pField)
		: CBaseClass(CPDUINFO)
	{
		Start(pField);
	}

	virtual ~CPDUInfo() {}

	// If GroupName is not null, Field is sub-field, GroupName is the name
	// of group.
	ret_ AddField(const TField &Field, 
				  const ch_1 *pszGroupName = null_v);

	// Get field
	ret_ GetField(const ch_1 *pszName, CField *&pField);

	// Get PDU structure
	ret_ GetStruct(CField *&pField);

protected:
	ret_ Start(const CField *pHeadField);
	ret_ Stop();

private:
    mapField m_FieldMap;

	CField *m_pField;
	CField *m_pCurField;
};

#endif // _C_PDU_INFO_H_
