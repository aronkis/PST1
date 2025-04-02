// clientpresenter.h
#ifndef CLIENTPRESENTER_H
#define CLIENTPRESENTER_H

#include <string>
#include <vector>
#include "roomtable.h"
#include "clientgui.h"

class ClientPresenter {
public:
    ClientPresenter(ClientGUI* gui, RoomTable* table);

    void populateRoomData();       // Populate room data
    void populateFacilities();    // Populate facilities
    void handlePrintAvailableRooms(const std::string &hotelName); // Declare this method
    void handleFilterRooms(double price, const std::string &location, const std::string &position,
                           bool availability, const std::vector<std::string> &facilities); // Declare this method

private:
    ClientGUI* client_gui;  // Accept ClientGUI pointer, which can point to ClientView
    RoomTable* rooms_table;
};

#endif // CLIENTPRESENTER_H
