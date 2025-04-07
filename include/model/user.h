#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
    User();
    User(int id, const std::string& username, const std::string& email, const std::string& password);
    User(const std::string& username, const std::string& password);

    int GetId() const;
    std::string GetUsername() const;
    std::string GetEmail() const;
    std::string GetPassword() const;
    int GetRole() const;

    void SetId(int id);
    void SetUsername(const std::string& username);
    void SetEmail(const std::string& email);
    void SetPassword(const std::string& password);
    void SetRole(int role);

private:
    int id;
    std::string username;
    std::string email;
    std::string password;
    int role;
};

#endif // USER_H
