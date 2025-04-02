#include "user.h"

User::User() 
{
    id = 0;
    logged_in = false;
    role = 0;
}

User::User(int id, const std::string& username, const std::string& email, const std::string& password)
{
    this->id = id;
    this->username = username;
    this->email = email;
    this->password = password;
    logged_in = false;
    role = 0;
}

User::User(const std::string& username, const std::string& password)
{
    this->username = username;
    this->password = password;
    logged_in = false;
    role = 0;
}

int User::GetId() const
{
    return id;
}

std::string User::GetUsername() const
{
    return username;
}

std::string User::GetEmail() const
{
    return email;
}

std::string User::GetPassword() const
{
    return password;
}

bool User::GetLoggedIn() const
{
    return logged_in;
}

int User::GetRole() const
{
    return role;
}

void User::SetId(int id)
{
    this->id = id;
}

void User::SetUsername(const std::string& username)
{
    this->username = username;
}

void User::SetEmail(const std::string& email)
{
    this->email = email;
}

void User::SetPassword(const std::string& password)
{
    this->password = password;
}

void User::SetLoggedIn(bool is_logged_in)
{
    this->logged_in = is_logged_in;
}

void User::SetRole(int role)
{
    this->role = role;
}

void User::Login()
{
    logged_in = true;
}

void User::Logout()
{
    logged_in = false;
}
