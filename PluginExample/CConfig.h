#ifndef CCONFIG_H
#define CCONFIG_H

const unsigned int PARAMETER_MAX_LENGTH = 32;
const char CONFIGURE_FILE_NAME[] = "config.ini";

class CConfig {
public:
    CConfig();

    bool init();

    const char *getServer() const {
        return _server;
    }

    const char *getUser() const {
        return _user;
    }

    const char *getPassword() const {
        return _password;
    }

    const char *getDatabase() const {
        return _database;
    }

private:
    char _server[PARAMETER_MAX_LENGTH];
    char _user[PARAMETER_MAX_LENGTH];
    char _password[PARAMETER_MAX_LENGTH];
    char _database[PARAMETER_MAX_LENGTH];
};

#endif // CCONFIG_H
