#ifndef CCONFIG_H
#define CCONFIG_H

const unsigned int PARAMETER_MAX_LENGTH = 32;

const char CONFIGURE_FILE_NAME[] = "config.ini";

class CConfig
{
public:
	CConfig();

	bool Initialize();

	const char *GetServer() const
	{
		return m_szServer;
	}

	const char *GetUser() const
	{
		return m_szUser;
	}

	const char *GetPassword() const
	{
		return m_szPassword;
	}

	const char *GetDatabase() const
	{
		return m_szDatabase;
	}

private:
	char m_szServer[PARAMETER_MAX_LENGTH];
	char m_szUser[PARAMETER_MAX_LENGTH];
	char m_szPassword[PARAMETER_MAX_LENGTH];
	char m_szDatabase[PARAMETER_MAX_LENGTH];
};

#endif // CCONFIG_H
