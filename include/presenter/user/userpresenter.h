 #ifndef USERPRESENTER_H
#define USERPRESENTER_H

#include "usergui.h"
#include "roomtable.h"
#include "usertable.h"

class UserPresenter 
{
    
public:
    UserPresenter(UserGUI *user_gui, RoomTable *room_table, UserTable *user_table);
    bool HandleLogin(const std::string &username, const std::string &password);
    void CreateRoom();
    void ReadRoom();
    void UpdateRoom();
    void DeleteRoom(); 

private:
    UserGUI *user_gui;     
    RoomTable *room_table; 
    UserTable *user_table; 
};

#endif // USERPRESENTER_H