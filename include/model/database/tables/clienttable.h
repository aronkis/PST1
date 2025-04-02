#ifndef CLIENTTABLE_H
#define CLIENTTABLE_H

#include "database.h"
#include "client.h"
#include <vector>

class ClientTable
{
private:
    Database* db;
    std::string table_name;

public:
    ClientTable(Database* database);

    void CreateClient(int client_id, const Client& client);
    Client ReadClient(int client_id);
    void UpdateClient(int client_id, const Client& client);
    void DeleteClient(int client_id);
    std::vector<Client> ListClients();
};

#endif // CLIENTTABLE_H
