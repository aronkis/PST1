#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class Room
{
private:
    int id;
    int number;
    std::string location;
    float price;
    bool availability;
    std::string position;
    std::vector<std::string> facilities; // List of facilities for the room
    std::string hotel_name;

public:
    Room(int id, const std::string& location, int number, bool is_available, double price, const std::vector<std::string>& facilities);

    // Getters
    int GetId() const;
    int GetNumber() const;
    bool GetAvailability() const;
    double GetPrice() const;
    std::string GetLocation() const;
    std::string GetPosition() const;
    std::vector<std::string> GetFacilities() const;
    std::string GetHotelName() const;

    // Setters
    void SetId(int id);
    void SetNumber(int number);
    void SetLocation(const std::string& location);
    void SetPrice(double price);
    void SetAvailability(bool availability);
    void SetPosition(const std::string& position);
    void SetFacilities(const std::vector<std::string>& facilities);
    void SetHotelName(const std::string& hotel_name);

    // Matches filter criteria
    bool MatchesFilter(const std::string& location, bool availability, double max_price, const std::vector<std::string>& required_facilities) const;
};

#endif // ROOM_H
