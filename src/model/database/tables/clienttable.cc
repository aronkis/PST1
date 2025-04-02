#include "clienttable.h"
#include "client.h"
#include <iostream>
#include <sqlite3.h>

ClientTable::ClientTable(Database* database)
{
    this->db = database;
    this->table_name = "Client";
}

void ClientTable::CreateClient(int client_id, const Client& client)
{
    std::string command = "INSERT INTO Client (id, name, email, phone_number) VALUES (" +
                          std::to_string(client_id) + ", '" + client.GetName() + "', '" + client.GetEmail() +
                          "', '" + client.GetPhoneNumber() + "');";
    db->ExecuteSQLCommand(command);
}

Client ClientTable::ReadClient(int client_id)
{
    std::string command = "SELECT * FROM Client WHERE id = " + std::to_string(client_id);
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command); 

    if (!result.empty())
    {
        const auto& row = result[0]; 
        if (row.size() >= 4) 
        {
            Client client(0, "", "", "");
            client.SetId(std::stoi(row[0]));
            client.SetName(row[1]);
            client.SetEmail(row[2]);
            client.SetPhoneNumber(row[3]);
            return client;
        }
    }
    return Client(0, "", "", "");
}

void ClientTable::UpdateClient(int client_id, const Client& client)
{
    std::string command = "UPDATE Client SET name = '" + client.GetName() + "', email = '" + client.GetEmail() +
                          "', phone_number = '" + client.GetPhoneNumber() + "' WHERE id = " + std::to_string(client_id) + ";";
    db->ExecuteSQLCommand(command);
}

void ClientTable::DeleteClient(int client_id)
{
    std::string command = "DELETE FROM Client WHERE id = " + std::to_string(client_id);
    db->ExecuteSQLCommand(command);
}

std::vector<Client> ClientTable::ListClients()
{
    std::vector<Client> clients;
    std::string command = "SELECT * FROM Client";
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command); 
    for (const auto& row : result)
    {
        if (row.size() >= 4)
        {
            Client client(0, "", "", "");
            client.SetId(std::stoi(row[0]));
            client.SetName(row[1]);
            client.SetEmail(row[2]);
            client.SetPhoneNumber(row[3]);
            clients.push_back(client);
        }
    }

    return clients;
}
