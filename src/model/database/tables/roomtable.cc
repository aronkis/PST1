#include "roomtable.h"
#include "room.h"
#include <iostream>
#include <sqlite3.h>
#include <sstream> // For std::stringstream
#include <vector>
#include <string>
#include <algorithm> // For std::remove_if, std::isspace

// Helper function to trim spaces from a string
std::string trim(const std::string &str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Helper function to split a string by a delimiter and trim spaces
std::vector<std::string> splitString(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token)); // Trim spaces from each token
    }

    return tokens;
}
RoomTable::RoomTable(Database* database)
{
    this->db = database;
    this->table_name = "Room";
}

bool RoomTable::CreateRoom(const std::string& hotel_name, const Room& room)
{
    std::string command = "INSERT INTO Room (hotel_name, number, location, price, availability, position) VALUES ('" +
                          hotel_name + "', " + std::to_string(room.GetNumber()) + ", '" + room.GetLocation() + "', " +
                          std::to_string(room.GetPrice()) + ", " + (room.GetAvailability() ? "1" : "0") + ", '" + room.GetPosition() + "');";
    return db->ExecuteSQLCommand(command);
}

Room RoomTable::ReadRoom(const std::string& hotel_name, int room_number)
{
    std::string command = "SELECT * FROM Room WHERE hotel_name = '" + hotel_name + "' AND number = " + std::to_string(room_number);
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command);  

    Room room(0, "", 0, false, 0.0, {}); 

    if (!result.empty())
    {
        const auto& row = result[0];
        if (row.size() >= 7) 
        {
            room.SetId(std::stoi(row[0]));
            room.SetHotelName(row[1]);
            room.SetNumber(std::stoi(row[2]));
            room.SetLocation(row[3]);
            room.SetPrice(std::stod(row[4]));
            room.SetAvailability(row[5] == "1");
            room.SetPosition(row[6]);
        }
    }

    return room;
}

bool RoomTable::UpdateRoom(const std::string& hotel_name, int room_number, const Room& room)
{
    std::string command = "UPDATE Room SET location = '" + room.GetLocation() + "', price = " +
                          std::to_string(room.GetPrice()) + ", availability = " + (room.GetAvailability() ? "1" : "0") +
                          ", position = '" + room.GetPosition() + "' WHERE hotel_name = '" + hotel_name + "' AND number = " +
                          std::to_string(room_number) + ";";
    return db->ExecuteSQLCommand(command);
}

bool RoomTable::DeleteRoom(const std::string& hotel_name, int room_number)
{
    std::string command = "DELETE FROM Room WHERE hotel_name = '" + hotel_name + "' AND number = " + std::to_string(room_number);
    return db->ExecuteSQLCommand(command);
}

std::vector<Room> RoomTable::ListRooms()
{
    std::vector<Room> rooms;
    std::string command = "SELECT * FROM Room";
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command);  

    for (const auto& row : result)
    {
        if (row.size() >= 7) 
        {
            Room room(0, "", 0, false, 0.0, {});
            room.SetId(std::stoi(row[0]));
            room.SetHotelName(row[1]);
            room.SetNumber(std::stoi(row[2]));
            room.SetLocation(row[3]);
            room.SetPrice(std::stod(row[4]));
            room.SetAvailability(row[5] == "1");
            room.SetPosition(row[6]);
            std::vector<std::string> facilities = splitString(row[7], ',');
            room.SetFacilities(facilities);
            rooms.push_back(room);
        }
    }

    return rooms;
}

std::vector<Room> RoomTable::FilterRooms(const std::string& location, const std::string& position, bool availability, double max_price, const std::vector<std::string>& required_facilities)
{
    std::vector<Room> rooms;
    std::string command = "SELECT * FROM Room WHERE location LIKE '%" + location + "%' AND availability = " + (availability ? "1" : "0") +
                          " AND price <= " + std::to_string(max_price) + " AND position LIKE '%" + position + "%';";
    std::vector<std::vector<std::string>> result = db->ExecuteSQLQuery(command);

    for (const auto& row : result)
    {
        if (row.size() >= 7)
        {
            Room room(0, "", 0, false, 0.0, {});
            room.SetId(std::stoi(row[0]));
            room.SetHotelName(row[1]);
            room.SetNumber(std::stoi(row[2]));
            room.SetLocation(row[3]);
            room.SetPrice(std::stod(row[4]));
            room.SetAvailability(row[5] == "1");
            room.SetPosition(row[6]);
            std::vector<std::string> facilities = splitString(row[7], ',');
            bool hasAllFacilities = std::all_of(required_facilities.begin(), required_facilities.end(), [&](const std::string &facility) {
                return std::find(facilities.begin(), facilities.end(), facility) != facilities.end();
            });

            if (hasAllFacilities) {
                room.SetFacilities(facilities);
                rooms.push_back(room);
            }
        }
    }

    return rooms;
}
