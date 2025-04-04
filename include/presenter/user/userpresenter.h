 #ifndef USERPRESENTER_H
#define USERPRESENTER_H

#include "usergui.h"
#include "roomtable.h"
#include "usertable.h"

class UserPresenter {
    
public:
    // Constructor
    UserPresenter(UserGUI *user_gui, RoomTable *room_table, UserTable *user_table);
    bool HandleLogin(const std::string &username, const std::string &password);
    void CreateRoom();
    void ReadRoom();
    void UpdateRoom();
    void DeleteRoom();
    void populateRoomData();       // Populate room data
    void populateFacilities();    // Populate facilities

private:
    UserGUI *user_gui;       // Reference to the UserGUI interface
    RoomTable *room_table;   // Reference to the RoomTable for database operations
    UserTable *user_table;   // Reference to the RoomTable for database operations
};

#endif // USERPRESENTER_H