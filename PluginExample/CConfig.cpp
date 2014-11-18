#include "CConfig.h"
#include "inifile.h"
#include <memory.h>

CConfig::CConfig()
{
	memset(m_szServer, 0, PARAMETER_MAX_LENGTH);
	memset(m_szUser, 0, PARAMETER_MAX_LENGTH);
	memset(m_szPassword, 0, PARAMETER_MAX_LENGTH);
	memset(m_szDatabase, 0, PARAMETER_MAX_LENGTH);
}

bool CConfig::Initialize()
{
	if (!read_profile_string("database", 
							 "server", 
							 m_szServer, 
							 PARAMETER_MAX_LENGTH, 
							 "", 
							 CONFIGURE_FILE_NAME))
	{
		return false;
	}

	if (!read_profile_string("database", 
							 "user", 
							 m_szUser, 
							 PARAMETER_MAX_LENGTH, 
							 "", 
							 CONFIGURE_FILE_NAME))
	{
		return false;
	}

	if (!read_profile_string("database", 
							 "password", 
							 m_szPassword, 
							 PARAMETER_MAX_LENGTH, 
							 "", 
							 CONFIGURE_FILE_NAME))
	{
		return false;
	}

	if (!read_profile_string("database", 
							 "database", 
							 m_szDatabase, 
							 PARAMETER_MAX_LENGTH, 
							 "", 
							 CONFIGURE_FILE_NAME))
	{
		return false;
	}

	return true;
}


