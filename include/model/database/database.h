#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>
#include <vector>
#include <functional>

class Database {

public:
    Database() : db(nullptr) {}
    ~Database();

    sqlite3* GetConnection();
    void SetConnection(sqlite3* connection);

    bool OpenConnection(const std::string& path);
    void CloseConnection();

    bool ExecuteSQLCommand(const std::string& command);
    std::vector<std::vector<std::string>> ExecuteSQLQuery(const std::string& query);
    std::string GetTable(const std::string& table_name);

private:
    sqlite3* db;

};

#endif // DATABASE_H
