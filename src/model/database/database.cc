#include "database.h"
#include <iostream>
#include <sstream>

Database::~Database() 
{
    if (db) 
    {
        CloseConnection();
    }
}

sqlite3* Database::GetConnection() 
{
    return db;
}

void Database::SetConnection(sqlite3* connection) 
{
    if (db) 
    {
        CloseConnection();  
    }
    db = connection;  

    std::cout << "Database connection set." << std::endl;
}

bool Database::OpenConnection(const std::string& path) 
{
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) 
    {
        return 0;
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    } 
    else 
    {
        return 1;
        std::cout << "Opened database successfully: " << path << std::endl;
    }
}

void Database::CloseConnection() 
{
    if (db) 
    {
        sqlite3_close(db);
        db = nullptr;
        std::cout << "Database connection closed." << std::endl;
    }
}

bool Database::ExecuteSQLCommand(const std::string& command) {
    char* errMsg = nullptr;  
    int result = sqlite3_exec(db, command.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);  
        return false;  
    }

    return true;
}

int callback(void* data, int argc, char** argv, char** azColName)
{
    std::vector<std::vector<std::string>>* result = static_cast<std::vector<std::vector<std::string>>*>(data);
    std::vector<std::string> row;

    for (int i = 0; i < argc; i++)
    {
        row.push_back(argv[i] ? argv[i] : "NULL");
    }

    result->push_back(row);
    return 0;
}

std::vector<std::vector<std::string>> Database::ExecuteSQLQuery(const std::string& query)
{
    std::vector<std::vector<std::string>> result;
    char* errorMessage = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), callback, &result, &errorMessage);

    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

    return result;
}

std::string Database::GetTable(const std::string& table_name) 
{
    std::string query = "SELECT * FROM " + table_name;
    sqlite3_stmt* stmt;
    std::ostringstream oss;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) 
    {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    int columnCount = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        for (int i = 0; i < columnCount; ++i) 
        {
            const char* colValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            oss << (colValue ? colValue : "NULL") << "\t";
        }
        oss << "\n";
    }

    sqlite3_finalize(stmt);
    return oss.str();
}
