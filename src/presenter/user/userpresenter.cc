#include <QMessageBox>
#include <set>
#include "userpresenter.h"

UserPresenter::UserPresenter(UserGUI *user_gui, RoomTable *room_table, UserTable *user_table)
    : user_gui(user_gui), room_table(room_table), user_table(user_table) {}

bool UserPresenter::HandleLogin(const std::string &username, const std::string &password) 
{
    if (user_table->CheckCredentials(username, password)) 
    {
       return true;
    }
    
    return false;
}

void UserPresenter::CreateRoom() 
{
    Room room(user_gui->GetRoomId(), user_gui->GetRoomLocation(), user_gui->GetRoomPosition(),
              user_gui->GetRoomNumber(),user_gui->GetRoomAvailability(), user_gui->GetRoomPrice(),
              user_gui->GetFacilities());

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
        user_gui->SetRoomId(room.GetId());
        user_gui->SetRoomLocation(room.GetLocation());
        user_gui->SetRoomPrice(room.GetPrice());
        user_gui->SetRoomAvailability(room.GetAvailability());
        user_gui->SetRoomPosition(room.GetPosition());
        user_gui->SetRoomFacilities(room.GetFacilities());
    } 
    else 
    {
        QMessageBox::critical(nullptr, "Error", "Failed to read room.");
    }
}

void UserPresenter::UpdateRoom() 
{
    Room room(user_gui->GetRoomId(), user_gui->GetRoomLocation(), user_gui->GetRoomPosition(), 
              user_gui->GetRoomNumber(), user_gui->GetRoomAvailability(), user_gui->GetRoomPrice(),
              user_gui->GetFacilities());

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