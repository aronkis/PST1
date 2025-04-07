#ifndef CLIENTDESKTOP_H
#define CLIENTDESKTOP_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QLineEdit> 
#include <vector>
#include <string>
#include "clientgui.h"
#include "roomtable.h"
#include "database.h"
#include "clientpresenter.h"

class ClientDesktopGUI : public QMainWindow, public ClientGUI 
{
    Q_OBJECT

public:
    explicit ClientDesktopGUI(QWidget *parent = nullptr);
    ~ClientDesktopGUI();

    bool GetRoomAvailability() override;
    void SetRoomAvailability(bool availability) override;
    double GetRoomPrice() override;
    void SetRoomPrice(double price) override;
    std::string GetRoomLocation() override;
    void SetRoomLocation(const std::string &location) override;
    std::string GetRoomPosition() override;
    void SetRoomPosition(const std::string &position) override;
    std::vector<std::string> GetFacilities() override;
    void SetRoomFacilities(const std::vector<std::string> &facilities) override;
    std::string GetHotelName() override;
    void SetHotelName(const std::string &hotel_name) override;
    void setCurrentRooms(const std::vector<Room> &rooms) override;
    void displayRoomDetails(int index) override;

private:
    QWidget *centralWidget;
    QWidget *clientViewWidget;
    QWidget *userViewWidget;
    QVBoxLayout *layout;
    QLabel *label;
    
    QPushButton *loginButton;
    QPushButton *createRoomButton;
    QPushButton *readRoomButton;
    QPushButton *updateRoomButton;
    QPushButton *deleteRoomButton;
    QPushButton *logoutButton;
    
    QPushButton *printAvailableButton;
    QPushButton *filterRoomsButton;
    QPushButton *nextButton; 
    QPushButton *prevButton; 
    
    QComboBox *roomAvailabilityBox;
    QComboBox *roomPriceBox;
    QComboBox *roomLocationBox;
    QComboBox *roomPositionBox;
    QComboBox *hotelNameBox;

    QLineEdit *hotelNameField;
    QLineEdit *roomNumberField;
    QLineEdit *priceField;
    QLineEdit *locationField;
    QLineEdit *positionField;
    QLineEdit *facilitiesField; 

    QListWidget *facilitiesListWidget;

    Database database;
    RoomTable roomTable;

    std::vector<Room> currentRooms;
    int currentPage;

    ClientPresenter *presenter; 

    void populateRoomData();
    void populateFacilities();

private slots:
    void onPrintAvailableRoomsClicked();
    void onFilterRoomsClicked();
    void onNextButtonClicked(); 
    void onPrevButtonClicked(); 
};

#endif // DESKTOPGUI_H