#include "CIPFilter.h"

bool_ CIPFilter::AddIPGroup(const ch_1 *pszIP)
{
	if (!m_bIsWork)
		return false_v;

	if (!pszIP)
		return false_v;

	b_4		nLength		= (b_4)strlen(pszIP);
	b_4		m			= 0;
	ch_1	sSingleIP[16];

	memset(sSingleIP, 0, 16);

	for (b_4 n = 0; n <= nLength; n++)
	{
		if (' ' == pszIP[n] || '\0' == pszIP[n])
		{
			if (!m_IPSet.count(sSingleIP))
			{
				m_IPSet.insert(sSingleIP);
				memset(sSingleIP, 0, 16);
				m = 0;
			}
		}
		else
		{
			sSingleIP[m++] = pszIP[n];
		}
	}

	return true_v;
}

