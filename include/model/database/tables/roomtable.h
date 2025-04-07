#ifndef ROOMTABLE_H
#define ROOMTABLE_H

#include "database.h"
#include "room.h"
#include <vector>
#include <string>

class RoomTable
{
public:
    RoomTable(Database* database);

    bool CreateRoom(const std::string& hotel_name, const Room& room);
    Room ReadRoom(const std::string& hotel_name, int room_number);
    bool UpdateRoom(const std::string& hotel_name, int room_number, const Room& room);
    bool DeleteRoom(const std::string& hotel_name, int room_number);
    std::vector<Room> ListRooms();
    std::vector<Room> FilterRooms(const std::string& location, const std::string& position, bool availability, double max_price, const std::vector<std::string>& required_facilities);
    std::vector<std::string> splitString(const std::string &str, char delimiter);


private:
    Database* db;
    std::string table_name;

};

#endif // ROOMTABLE_H
