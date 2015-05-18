#ifndef CXML_LOADER_H
#define CXML_LOADER_H

#include "XMLParserCommon.h"

class CXMLLoader
{
protected:
	CXMLLoader(): m_pParser(null_v) {}

	void SetParser(XercesDOMParser *pParser)
	{
		m_pParser = pParser;
	}

	XercesDOMParser *GetParser() const
	{
		return m_pParser;
	}

	ret_ GetLastName(const ch_1 *pszFullName, ch_1 *&sLastName);
	ret_ GetFirstName(const ch_1 *pszFullName, ch_1 *sFirstName, size_ &nSize);
	ret_ GetDirection(const ch_1 *pszDirection, EDirection &Direction);
	ret_ GetFieldType(EFieldStyle Style, 
					  size_ nLength, 
					  bool_ bSign, 
					  EFieldType &Type);

	ret_ GetUnitaryOperator(const ch_1 *pszOperator,
			EUnitaryCalculate &Calculate);
	ret_ GetDualityOperator(const ch_1 *pszOperator,
			EDualityCalculate &Calculate);
	ret_ GetCompareOperator(const ch_1 *pszOperator,
			ECompareCalculate &Calculate);

private:
	CXMLLoader(const CXMLLoader &);
	const CXMLLoader &operator =(const CXMLLoader &);

	XercesDOMParser *m_pParser;
};

#endif // CXML_LOADER_H
