#ifndef USERGUI_H
#define USERGUI_H

#include <string>
#include <vector>
#include "room.h"

class UserGUI 
{
public:
    virtual int GetRoomId() = 0;
    virtual void SetRoomId(int id) = 0;
    virtual int GetRoomNumber() = 0;
    virtual void SetRoomNumber(int number) = 0;
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
    virtual std::string GetUsername() = 0;
    virtual std::string GetUserPassword() = 0;
};

#endif // USERGUI_H
