#include "usertable.h"
#include "user.h"
#include <iostream>
#include <sqlite3.h>

UserTable::UserTable(Database* database)
{
    this->db = database;
    this->table_name = "User";
}

bool UserTable::CreateUser(const User& user)
{
    std::string command = "INSERT INTO User (username, email, password, role) VALUES ('" + user.GetUsername() +
                          "', '" + user.GetEmail() + "', '" + user.GetPassword() + "', " + std::to_string(user.GetRole()) + ");";
    return db->ExecuteSQLCommand(command);
}

User UserTable::ReadUser(int user_id)
{
    std::string command = "SELECT * FROM User WHERE id = " + std::to_string(user_id);
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command);

    User user;
    if (!result.empty()) 
    {
        const auto& row = result[0]; 
        if (row.size() >= 5) 
        {
            user.SetId(std::stoi(row[0]));
            user.SetUsername(row[1]);
            user.SetEmail(row[2]);
            user.SetPassword(row[3]);
            user.SetRole(std::stoi(row[4]));
        }
    }

    return user;
}

bool UserTable::UpdateUser(int user_id, const User& user)
{
    std::string command = "UPDATE User SET username = '" + user.GetUsername() + "', email = '" + user.GetEmail() +
                          "', password = '" + user.GetPassword() + "', role = " + std::to_string(user.GetRole()) +
                          " WHERE id = " + std::to_string(user_id) + ";";
    return db->ExecuteSQLCommand(command);
}

bool UserTable::DeleteUser(int user_id)
{
    std::string command = "DELETE FROM User WHERE id = " + std::to_string(user_id);
    return db->ExecuteSQLCommand(command);
}

std::vector<User> UserTable::ListUsers()
{
    std::vector<User> users;
    std::string command = "SELECT * FROM User";
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command);
    for (const auto& row : result)
    {
        if (row.size() >= 5) 
        {
            User user;
            user.SetId(std::stoi(row[0]));
            user.SetUsername(row[1]);
            user.SetEmail(row[2]);
            user.SetPassword(row[3]);
            user.SetRole(std::stoi(row[4]));
            users.push_back(user);
        }
    }

    return users;
}

bool UserTable::CheckCredentials(std::string username, std::string password)
{
    std::string command = "SELECT * FROM User WHERE username = '" + username +  "' AND password = '" + password + "';";
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command);

    if (!result.empty()) 
    {
        return true;
    }

    return false;
}