#include "clientpresenter.h"
#include <set>
#include <algorithm>    

ClientPresenter::ClientPresenter(ClientGUI *gui, RoomTable *roomTable)
    : client_gui(gui), rooms_table(roomTable) {}

void ClientPresenter::handlePrintAvailableRooms(const std::string &hotelName) 
{
    std::vector<Room> rooms = rooms_table->ListRooms();
    rooms.erase(std::remove_if(rooms.begin(), rooms.end(),
                               [hotelName](const Room &room) 
                               {
                                   return !room.GetAvailability() || room.GetHotelName() != hotelName;
                               }),
                rooms.end());
                client_gui->setCurrentRooms(rooms);
    if (!rooms.empty()) 
    {
        client_gui->displayRoomDetails(0);
    }
    else
    {
        client_gui->displayRoomDetails(-1);
    }
}

void ClientPresenter::handleFilterRooms(double price, const std::string &location, const std::string &position,
                                        bool availability, const std::vector<std::string> &facilities) 
{
    std::vector<Room> rooms = rooms_table->FilterRooms(location, position, availability, price, facilities);
    client_gui->setCurrentRooms(rooms);
    if (!rooms.empty()) 
    {
        client_gui->displayRoomDetails(0);
    }
    else
    {
        client_gui->displayRoomDetails(-1);
    }
}

void ClientPresenter::populateRoomData() 
{
    std::vector<Room> rooms = rooms_table->ListRooms();
    std::set<std::string> uniqueHotelNames;
    std::set<bool> uniqueAvailability;

    for (const Room &room : rooms) 
    {
        client_gui->SetRoomPrice(room.GetPrice());
        client_gui->SetRoomLocation(room.GetLocation());
        client_gui->SetRoomPosition(room.GetPosition());
        uniqueHotelNames.insert(room.GetHotelName());
        uniqueAvailability.insert(room.GetAvailability());
    }

    for (const std::string &hotelName : uniqueHotelNames) 
    {
        client_gui->SetHotelName(hotelName);
    }

    for (bool availability : uniqueAvailability) 
    {
        client_gui->SetRoomAvailability(availability);
    }
}

void ClientPresenter::populateFacilities() 
{
    std::vector<Room> rooms = rooms_table->ListRooms();
    std::set<std::string> uniqueFacilities;

    for (const Room &room : rooms) 
    {
        std::vector<std::string> facilities = room.GetFacilities();
        uniqueFacilities.insert(facilities.begin(), facilities.end());
    }

    std::vector<std::string> facilitiesList(uniqueFacilities.begin(), uniqueFacilities.end());
    client_gui->SetRoomFacilities(facilitiesList);
}
