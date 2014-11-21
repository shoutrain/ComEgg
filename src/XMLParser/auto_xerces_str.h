#ifndef AUTO_XERCES_STR
#define AUTO_XERCES_STR

#include "XMLParserCommon.h"

// Can only be used after called XMLPlatformUtils::init();
class auto_xerces_str
{
public:
	auto_xerces_str(const ch_1 *psz)
	{
		m_ws	= XMLString::transcode(psz);
		m_s		= null_v;
	}

	auto_xerces_str(const XMLCh *pxs)
	{
		m_s		= XMLString::transcode(pxs);
		m_ws	= null_v;
	}

	~auto_xerces_str()
	{
		if (null_v != m_s)
			XMLString::release(&m_s);

		if (null_v != m_ws)
			XMLString::release(&m_ws);
	}

	operator const ch_1 *() const
	{
		return m_s;
	}

	operator const XMLCh *() const
	{
		return m_ws;
	}

protected:
	auto_xerces_str();

private:

	ch_1 	*m_s;
	XMLCh	*m_ws;
};

#endif // AUTO_XERCES_STR
