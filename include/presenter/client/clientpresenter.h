// clientpresenter.h
#ifndef CLIENTPRESENTER_H
#define CLIENTPRESENTER_H

#include <string>
#include <vector>
#include "roomtable.h"
#include "clientgui.h"

class ClientPresenter 
{
public:
    ClientPresenter(ClientGUI* gui, RoomTable* table);

    void populateRoomData();       
    void populateFacilities();    
    void handlePrintAvailableRooms(const std::string &hotelName); 
    void handleFilterRooms(double price, const std::string &location, const std::string &position,
                           bool availability, const std::vector<std::string> &facilities); 

private:
    ClientGUI* client_gui; 
    RoomTable* rooms_table;
};

#endif // CLIENTPRESENTER_H
