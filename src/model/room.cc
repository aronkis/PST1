#include "room.h"

Room::Room(int id, const std::string& location, int number, bool is_available, double price, const std::vector<std::string>& facilities)
{
    this->id = id;
    this->location = location;
    this->number = number;
    this->availability = is_available;
    this->price = price;
    this->facilities = facilities;
}

int Room::GetId() const
{
    return id;
}

int Room::GetNumber() const
{
    return number;
}

bool Room::GetAvailability() const
{
    return availability;
}

double Room::GetPrice() const
{
    return price;
}

std::string Room::GetLocation() const
{
    return location;
}

std::string Room::GetPosition() const
{
    return position;
}

std::vector<std::string> Room::GetFacilities() const
{
    return facilities;
}

std::string Room::GetHotelName() const
{
    return hotel_name;
}

void Room::SetId(int id)
{
    this->id = id;
}

void Room::SetNumber(int number)
{
    this->number = number;
}

void Room::SetLocation(const std::string& location)
{
    this->location = location;
}

void Room::SetPrice(double price)
{
    this->price = price;
}

void Room::SetAvailability(bool availability)
{
    this->availability = availability;
}

void Room::SetPosition(const std::string& position)
{
    this->position = position;
}

void Room::SetFacilities(const std::vector<std::string>& facilities)
{
    this->facilities = facilities;
}

void Room::SetHotelName(const std::string& hotel_name)
{
    this->hotel_name = hotel_name;
}

bool Room::MatchesFilter(const std::string& location, bool availability, double max_price, const std::vector<std::string>& required_facilities) const
{
    if ((location.empty() || this->location == location) && 
        (this->availability == availability) && 
        (this->price <= max_price))
    {
        for (const std::string& required_facility : required_facilities)
        {
            bool found = false;
            for (const std::string& facility : this->facilities)
            {
                if (facility == required_facility)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
