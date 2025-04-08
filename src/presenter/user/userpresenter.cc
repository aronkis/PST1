#include <QMessageBox>
#include <set>
#include <vector>
#include "userpresenter.h"
#include <iostream>

std::string VecToStr(std::vector<std::string> vec)
{
    std::string facilitiesStr = vec[0];
    for (int i = 1; i < vec.size(); i++) 
    {
        facilitiesStr += ", " + vec[i];
    }

    return facilitiesStr;
}

UserPresenter::UserPresenter(UserGUI *user_gui, RoomTable *room_table, UserTable *user_table)
    : user_gui(user_gui), room_table(room_table), user_table(user_table) {}

void UserPresenter::HandleLogin() 
{
    std::string username = user_gui->GetUsername();
    std::string password = user_gui->GetUserPassword();

    if (username.empty() || password.empty()) 
    {
        QMessageBox::warning(nullptr, "Login Error", "Please enter both username and password.");
    }
    else if (!user_table->CheckCredentials(username, password)) 
    {
        QMessageBox::warning(nullptr, "Login Error", "Invalid username or password.");
    }
    else
    {
        user_gui->SetLoggedIn(true);
    }
}

void UserPresenter::HandleLogOut()
{
    user_gui->SetLoggedIn(false);
}

void UserPresenter::CreateRoom() 
{
    std::vector<std::string> facilities = room_table->splitString(user_gui->GetFacilities(), ',');
    bool availability = user_gui->GetRoomAvailability() == "Available";

    Room room(user_gui->GetRoomId(), user_gui->GetRoomLocation(), user_gui->GetRoomPosition(),
              user_gui->GetRoomNumber(),availability, user_gui->GetRoomPrice(), facilities);

    std::string hotel_name = user_gui->GetHotelName();
    if (room_table->CreateRoom(hotel_name, room)) 
    {
        QMessageBox::information(nullptr, "Success", "Room created successfully.");
    } 
    else 
    {
        QMessageBox::critical(nullptr, "Error", "Failed to create room.");
    }
}

void UserPresenter::ReadRoom() 
{
    std::string hotel_name = user_gui->GetHotelName();
    int room_number = user_gui->GetRoomNumber();

    Room room = room_table->ReadRoom(hotel_name, room_number);
    if (room.GetNumber() != 0) 
    {
        std::string facilitiesStr = VecToStr(room.GetFacilities());
        std::string availability = room.GetAvailability() ? "Available" : "Not Available";

        user_gui->SetRoomId(room.GetId());
        user_gui->SetRoomLocation(room.GetLocation());
        user_gui->SetRoomPrice(room.GetPrice());
        user_gui->SetRoomAvailability(availability);

        user_gui->SetRoomPosition(room.GetPosition());
        user_gui->SetRoomFacilities(facilitiesStr);
    } 
    else 
    {
        QMessageBox::critical(nullptr, "Error", "Failed to read room.");
    }
}

void UserPresenter::UpdateRoom() 
{
    std::vector<std::string> facilities = room_table->splitString(user_gui->GetFacilities(), ',');
    bool availability = user_gui->GetRoomAvailability() == "Available";

    Room room(user_gui->GetRoomId(), user_gui->GetRoomLocation(), user_gui->GetRoomPosition(), 
              user_gui->GetRoomNumber(), availability, user_gui->GetRoomPrice(), facilities);

    std::string hotel_name = user_gui->GetHotelName();
    if (room_table->UpdateRoom(hotel_name, room.GetNumber(), room)) 
    {
        QMessageBox::information(nullptr, "Success", "Room updated successfully.");
    } 
    else 
    {
        QMessageBox::critical(nullptr, "Error", "Failed to update room.");
    }
}

void UserPresenter::DeleteRoom() 
{
    std::string hotel_name = user_gui->GetHotelName();
    int room_number = user_gui->GetRoomNumber();

    if (room_table->DeleteRoom(hotel_name, room_number)) 
    {
        QMessageBox::information(nullptr, "Success", "Room deleted successfully.");
    } 
    else 
    {
        QMessageBox::critical(nullptr, "Error", "Failed to delete room.");
    }
}

void UserPresenter::populateRoomData() 
{
    printf("Populating room data at line: %d\n", __LINE__);
    std::vector<Room> rooms = room_table->ListRooms();
    std::set<std::string> uniqueHotelNames;
    std::set<bool> uniqueAvailability;
    std::set<double> uniquePrices;
    std::set<std::string> uniquePositions;
    std::set<std::string> uniqueLocations;

    for (const Room &room : rooms) 
    {
        uniqueHotelNames.insert(room.GetHotelName());
        uniqueAvailability.insert(room.GetAvailability());
        uniquePrices.insert(room.GetPrice());
        uniquePositions.insert(room.GetPosition());
        uniqueLocations.insert(room.GetLocation());
    }

    for (const std::string &hotelName : uniqueHotelNames) 
    {
        user_gui->SetHotelNameBox(hotelName);
    }

    for (bool availability : uniqueAvailability) 
    {
        user_gui->SetRoomAvailabilityBox(availability ? "Available" : "Not Available");
    }

    for (double price : uniquePrices) 
    {
        user_gui->SetRoomPriceBox(price);
    }

    for (const std::string &position : uniquePositions) 
    {
        user_gui->SetRoomPositionBox(position);
    }

    for (const std::string &location : uniqueLocations) 
    {
        user_gui->SetRoomLocationBox(location);
    }
}

void UserPresenter::populateFacilities() 
{
    std::vector<Room> rooms = room_table->ListRooms();
    std::set<std::string> uniqueFacilities;

    for (const Room &room : rooms) 
    {
        std::vector<std::string> facilities = room.GetFacilities();
        uniqueFacilities.insert(facilities.begin(), facilities.end());
    }

    std::vector<std::string> sortedFacilities(uniqueFacilities.begin(), uniqueFacilities.end());
    std::sort(sortedFacilities.begin(), sortedFacilities.end());

    for (const std::string &facility : sortedFacilities) 
    {
        user_gui->SetRoomFacilitiesBox(facility);
    }
}

void UserPresenter::GetAvailableRooms()
{
    std::string hotel_name = user_gui->GetHotelNameBox();

    if (priv_hotel_name != hotel_name)
    {
        priv_hotel_name = hotel_name;
        current_page = 0;
    }

    std::vector<Room> rooms = room_table->ListRooms();
    rooms.erase(std::remove_if(rooms.begin(), rooms.end(),
                               [hotel_name](const Room &room) 
                               {
                                   return !room.GetAvailability() || room.GetHotelName() != hotel_name;
                               }),
                rooms.end());

    current_rooms = rooms;
    if (current_rooms.empty())
    {
        current_page = -1;
    }
}

void UserPresenter::LoadNextRoomDetails()
{
    current_page++;
    if (current_page >= current_rooms.size()) 
    {
        current_page = 0;
    }
    DisplayRoomDetails();
}

void UserPresenter::LoadPrevRoomDetails()
{
    current_page--;
    if (current_page < 0) 
    {
        current_page = current_rooms.size() - 1;
    }
    DisplayRoomDetails();
}

void UserPresenter::DisplayRoomDetails()
{   
    if (current_page < 0 || current_rooms.size() <= 0) 
    {
        user_gui->SetHotelName("N/A");
        user_gui->SetRoomId(-1);
        user_gui->SetRoomAvailability("N/A");
        user_gui->SetRoomNumber(-1);
        user_gui->SetRoomPrice(-1.0);
        user_gui->SetRoomLocation("N/A");
        user_gui->SetRoomPosition("N/A");
        user_gui->SetRoomFacilities("N/A");
    }
    else if (current_rooms.empty())
    {
        user_gui->SetHotelName("N/A");
        user_gui->SetRoomId(-1);
        user_gui->SetRoomAvailability("N/A");
        user_gui->SetRoomNumber(-1);
        user_gui->SetRoomPrice(-1.0);
        user_gui->SetRoomLocation("N/A");
        user_gui->SetRoomPosition("N/A");
        user_gui->SetRoomFacilities("N/A");
    }
    else
    {
        const Room &room = current_rooms[current_page];
        std::string availability = room.GetAvailability() ? "Available" : "Not Available";
        std::string facilitiesStr = VecToStr(room.GetFacilities());

        user_gui->SetRoomId(room.GetId());
        user_gui->SetRoomAvailability(availability);
        user_gui->SetRoomNumber(room.GetNumber());
        user_gui->SetRoomPrice(room.GetPrice());
        user_gui->SetRoomLocation(room.GetLocation());
        user_gui->SetRoomPosition(room.GetPosition());
        user_gui->SetRoomFacilities(facilitiesStr);
    }
}
void UserPresenter::FilterRooms() 
{
    std::vector<std::string> facilities = room_table->splitString(user_gui->GetFacilitiesBox(), ',');
    bool availability = user_gui->GetRoomAvailabilityBox() == "Available";

    std::vector<Room> rooms = room_table->FilterRooms(user_gui->GetRoomLocationBox(), 
                                                      user_gui->GetRoomPositionBox(), 
                                                      availability, 
                                                      user_gui->GetRoomPriceBox(), 
                                                      facilities);
    current_rooms = rooms;
    if (current_rooms.empty())
    {
        current_page = -1;
    }
    else
    {
        current_page = 0;
    }
}