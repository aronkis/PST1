#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    int id;
    std::string username;
    std::string email;
    std::string password;
    bool logged_in;
    int role;

public:
    User();
    User(int id, const std::string& username, const std::string& email, const std::string& password);
    User(const std::string& username, const std::string& password);

    // Getters
    int GetId() const;
    std::string GetUsername() const;
    std::string GetEmail() const;
    std::string GetPassword() const;
    bool GetLoggedIn() const;
    int GetRole() const;

    // Setters
    void SetId(int id);
    void SetUsername(const std::string& username);
    void SetEmail(const std::string& email);
    void SetPassword(const std::string& password);
    void SetLoggedIn(bool is_logged_in);
    void SetRole(int role);

    // Login and Logout methods
    void Login();
    void Logout();
};

#endif // USER_H
