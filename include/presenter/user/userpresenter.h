#ifndef USERPRESENTER_H
#define USERPRESENTER_H

#include "usergui.h"
#include "roomtable.h"
#include "usertable.h"

class UserPresenter 
{
    
public:
    UserPresenter(UserGUI *user_gui, RoomTable *room_table, UserTable *user_table);
    void HandleLogin();
    void HandleLogOut();
    void CreateRoom();
    void ReadRoom();
    void UpdateRoom();
    void DeleteRoom(); 
    void populateRoomData(); 
    void populateFacilities(); 
    void GetAvailableRooms();
    void DisplayRoomDetails();
    void LoadNextRoomDetails();
    void LoadPrevRoomDetails();
    void FilterRooms();

private:
    UserGUI *user_gui;     
    RoomTable *room_table; 
    UserTable *user_table; 
    int current_page = 0;
    std::vector<Room> current_rooms;
    std::string priv_hotel_name;
};

#endif // USERPRESENTER_H