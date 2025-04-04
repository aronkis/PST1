#ifndef USERTABLE_H
#define USERTABLE_H

#include "database.h"
#include "user.h"
#include <vector>

class UserTable
{
private:
    Database* db;
    std::string table_name;

public:
    UserTable(Database* database);

    bool CreateUser(const User& user);
    User ReadUser(int user_id);
    bool UpdateUser(int user_id, const User& user);
    bool DeleteUser(int user_id);
    std::vector<User> ListUsers();
    bool CheckCredentials(std::string username, std::string password);

};

#endif // USERTABLE_H
