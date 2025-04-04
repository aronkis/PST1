#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <string>
#include <vector>
#include "room.h"

class ClientGUI 
{
public:
    virtual bool GetRoomAvailability() = 0;
    virtual void SetRoomAvailability(bool availability) = 0;
    virtual double GetRoomPrice() = 0;
    virtual void SetRoomPrice(double price) = 0;
    virtual std::string GetRoomLocation() = 0;
    virtual void SetRoomLocation(const std::string& location) = 0;
    virtual std::string GetRoomPosition() = 0;
    virtual void SetRoomPosition(const std::string& position) = 0;
    virtual std::vector<std::string> GetFacilities() = 0;
    virtual void SetRoomFacilities(const std::vector<std::string>& facilities) = 0;
    virtual std::string GetHotelName() = 0;
    virtual void SetHotelName(const std::string& hotel_name) = 0;
    virtual void setCurrentRooms(const std::vector<Room> &rooms) = 0;
    virtual void displayRoomDetails(int index) = 0;
};

#endif // CLIENTGUI_H
