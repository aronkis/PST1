#ifndef USERGUI_H
#define USERGUI_H

#include <string>

class UserGUI 
{
public:
    virtual void SetDatabase(std::string path) = 0;
    virtual std::string GetHotelName() = 0;
    virtual void SetHotelName(const std::string &hotel_name) = 0;
    virtual int GetRoomId() = 0;
    virtual void SetRoomId(int id) = 0;
    virtual int GetRoomNumber() = 0;
    virtual void SetRoomNumber(int number) = 0;
    virtual std::string GetRoomAvailability() = 0;
    virtual void SetRoomAvailability(std::string availability) = 0;
    virtual double GetRoomPrice() = 0;
    virtual void SetRoomPrice(double price) = 0;
    virtual std::string GetRoomLocation() = 0;
    virtual void SetRoomLocation(const std::string &location) = 0;
    virtual std::string GetRoomPosition() = 0;
    virtual void SetRoomPosition(const std::string &position) = 0;
    virtual std::string GetFacilities() = 0;
    virtual void SetRoomFacilities(const std::string &facilities) = 0;
    virtual std::string GetUsername() = 0;
    virtual void SetHotelNameBox(const std::string &hotel_name) = 0;
    virtual std::string GetRoomAvailabilityBox() = 0;
    virtual void SetRoomAvailabilityBox(std::string availability) = 0;
    virtual double GetRoomPriceBox() = 0;
    virtual void SetRoomPriceBox(double price) = 0;
    virtual std::string GetRoomLocationBox() = 0;
    virtual void SetRoomLocationBox(const std::string &location) = 0;
    virtual std::string GetRoomPositionBox() = 0;
    virtual void SetRoomPositionBox(const std::string &position) = 0;
    virtual bool GetFacilitiesBoxItemState(int pos) = 0;
    virtual std::string GetFacilitiesBoxItemValue(int pos) = 0;
    virtual int GetFacilitiesCount() = 0;
    virtual void SetRoomFacilitiesBox(const std::string &facilities) = 0;
    virtual std::string GetUserPassword() = 0;
    virtual std::string GetHotelNameBox() = 0;
    virtual void SetLoggedIn(bool logged_in) = 0;
};

#endif // USERGUI_H
