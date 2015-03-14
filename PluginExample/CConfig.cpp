#include "CConfig.h"
#include "inifile.h"

#include <memory.h>

CConfig::CConfig() {
	memset(_server, 0, PARAMETER_MAX_LENGTH);
	memset(_user, 0, PARAMETER_MAX_LENGTH);
	memset(_password, 0, PARAMETER_MAX_LENGTH);
	memset(_database, 0, PARAMETER_MAX_LENGTH);
}

bool CConfig::init() {
	if (!read_profile_string("database", "server", _server,
			PARAMETER_MAX_LENGTH, "", CONFIGURE_FILE_NAME)) {
		return false;
	}

	if (!read_profile_string("database", "user", _user, PARAMETER_MAX_LENGTH,
			"", CONFIGURE_FILE_NAME)) {
		return false;
	}

	if (!read_profile_string("database", "password", _password,
			PARAMETER_MAX_LENGTH, "", CONFIGURE_FILE_NAME)) {
		return false;
	}

	if (!read_profile_string("database", "database", _database,
			PARAMETER_MAX_LENGTH, "", CONFIGURE_FILE_NAME)) {
		return false;
	}

	return true;
}

