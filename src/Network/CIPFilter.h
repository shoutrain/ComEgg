#ifndef CIP_FILTER_H
#define CIP_FILTER_H

#include "NetworkCommon.h"

#include <set>
#include <string>

using namespace std;

typedef set<string> set_string;

class CIPFilter
{
public:
	CIPFilter() 
	{
		m_bIsForbid = false_v;
		m_bIsWork	= false_v;
	}

	virtual ~CIPFilter()
	{
		m_IPSet.clear();
	}

    none_ SetForbid(bool_ bIsForbid = true_v)
	{
		m_bIsForbid = bIsForbid;
		m_bIsWork	= true_v;
	}

	bool_ AddIP(const ch_1 *pszIP)
	{
		if (!m_bIsWork)
			return false_v;

		if (!pszIP)
			return false_v;

		if (!m_IPSet.count(pszIP))
			m_IPSet.insert(pszIP);

		return true_v;
	}

	bool_ AddIPGroup(const ch_1 *pszIP);

	bool_ IPPermit(const ch_1 *pszIP)
	{
		if (!pszIP)
			return false_v;

		if (!m_bIsWork)
			return true_v;

		if (m_bIsForbid)
		{
			if (m_IPSet.count(pszIP))
				return false_v;
			else
				return true_v;
		}
		else
		{
			if (m_IPSet.count(pszIP))
				return true_v;
			else
				return false_v;
		}
	}

private:
	CIPFilter(const CIPFilter &);
	const CIPFilter &operator =(const CIPFilter &);

	bool_ m_bIsWork;
	bool_ m_bIsForbid;

	set_string m_IPSet;
};

#endif // CIP_FILTER_H
