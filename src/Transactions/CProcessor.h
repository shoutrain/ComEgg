#ifndef CPROCESSOR_H
#define CPROCESSOR_H

#include "TransactionCommon.h"

class CNetworkHandle;

#include <string>
#include <map>
#include <set>

using namespace std;

typedef map<const CPDUInfo *, const CProgram *>	map_handle;

typedef set<string>								set_register;
typedef map<string, set_register *>				map_register;

class CProcessor: public CBaseClass
{
public:
	CProcessor();
	CProcessor(const CProcessor &Processor);
	const CProcessor &operator =(const CProcessor &Processor);

	virtual ~CProcessor()
	{
		Stop();
	}

	ret_ Reset();

	void SetData(const CData &Data)
	{
		m_OrnData	= Data;
		m_Data		= Data;
	}

	void SetNormalHandle(const CProgram &Program, ENormalHandle enh)
	{
		m_NormalHandle[enh] = Program;
	}

	ret_ SetMsgHandle(const CProgram &Program,
					  EDirection Direction,
					  const CPDUInfo *pPDUInfo);

	ret_ ExecNormalHandle(const TMsgInfo *pMsgInfo, ENormalHandle enh);
	ret_ ExecMsgHandle(const CPDUInfo *pPDUInfo,
					   const ub_1 *pMsg,
					   size_ nSize,
					   const TMsgInfo *pMsgInfo,
					   EDirection Direction);

	ret_ SetHandle(const CNetworkHandle *pHandle);

	ret_ Send(const CPDUInfo *pPDUInfo,
			  const ub_1 *pMsg,
			  size_ nSize,
			  const TMsgInfo *pMsgInfo);

	ret_ Register(const ch_1 *pszCategory,
				  const ch_1 *pszKey,
				  bool_ bIsCovered = false_v);
	ret_ Unregister(const ch_1 *pszCategory, const ch_1 *pszKey);

	CData &Data()
	{
		return m_Data;
	}

protected:
	ret_ Stop();

private:
	CData m_OrnData;
	CData m_Data;

	CProgram m_NormalHandle[NORMAL_HANDLE];

	map_handle m_HandleInMap;
	map_handle m_HandleOutMap;

	CNetworkHandle *m_pHandle;

	map_register m_RegisterMap;
};

#endif // CPROCESSOR_H

