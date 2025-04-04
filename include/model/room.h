#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class Room
{
public:
    Room(int id, const std::string& location, std::string position, int number, bool is_available, 
        double price, const std::vector<std::string>& facilities);

    int GetId() const;
    int GetNumber() const;
    bool GetAvailability() const;
    double GetPrice() const;
    std::string GetLocation() const;
    std::string GetPosition() const;
    std::vector<std::string> GetFacilities() const;
    std::string GetHotelName() const;

    void SetId(int id);
    void SetNumber(int number);
    void SetLocation(const std::string& location);
    void SetPrice(double price);
    void SetAvailability(bool availability);
    void SetPosition(const std::string& position);
    void SetFacilities(const std::vector<std::string>& facilities);
    void SetHotelName(const std::string& hotel_name);

    bool MatchesFilter(const std::string& location, bool availability, double max_price, const std::vector<std::string>& required_facilities) const;

private:
    int id;
    int number;
    std::string location;
    float price;
    bool availability;
    std::string position;
    std::vector<std::string> facilities; 
    std::string hotel_name;

};

#endif // ROOM_H
