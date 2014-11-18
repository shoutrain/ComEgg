#ifndef CPROTOCOL_INFO_H
#define CPROTOCOL_INFO_H

#include "ProtocolCommon.h"

#include "../Data/CData.h"

#include <string>
#include <map>

using namespace std;

class CPDUInfo;

typedef map<string, const CPDUInfo *> map_pdu;

class CProtocolInfo: public CBaseClass
{
public:
	CProtocolInfo(): CBaseClass(CPROTOCOLINFO)
	{
		m_pField = null_v;
		m_pCurField = null_v;
	}

	virtual ~CProtocolInfo()
	{
		Stop();
	}

	// If GroupName is not null, Field is sub-field, GroupName is the name
	// of group.
	ret_ AddHeadField(const TField &Field, 
					  const ch_1 *pszGroupName = null_v);

	// Get field
	ret_ GetHeadField(const ch_1 *pszName, CField *&pField);

	ret_ AddPDU(const ch_1 *pszName, CPDUInfo *&pPDUInfo);
	ret_ GetPDU(const ch_1 *pszName, CPDUInfo *&pPDUInfo);

	CData &Data()
	{
		return m_Data;
	}

	bool_ IsPDUReady(const ch_1 *pszName)
	{
		if (m_PDUInfoMap.end() != m_PDUInfoMap.find(pszName))
			return true_v;

		return false_v;
	}

protected:
	ret_ Stop();

private:
	map_field m_HeadFieldMap;
	map_pdu	m_PDUInfoMap;

	CField *m_pField;
	CField *m_pCurField;

	CData m_Data;
};

#endif // CPROTOCOL_INFO_H
