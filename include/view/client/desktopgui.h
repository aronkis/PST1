#ifndef DESKTOPGUI_H
#define DESKTOPGUI_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QLineEdit> // Include QLineEdit
#include <QString>
#include <vector>
#include <string>
#include "clientgui.h"
#include "roomtable.h"
#include "database.h"
#include "clientpresenter.h"

class DesktopGUI : public QMainWindow, public ClientGUI {
    Q_OBJECT

public:
    explicit DesktopGUI(QWidget *parent = nullptr);
    ~DesktopGUI();

    // Implementation of ClientGUI interface
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
    
    // Buttons for UserView
    QPushButton *loginButton;
    QPushButton *createRoomButton;
    QPushButton *readRoomButton;
    QPushButton *updateRoomButton;
    QPushButton *deleteRoomButton;
    QPushButton *logoutButton;

    // Buttons
    QPushButton *printAvailableButton;
    QPushButton *filterRoomsButton;
    QPushButton *nextButton; // Button to navigate to the next result
    QPushButton *prevButton; // Button to navigate to the previous result

    // Dropdown boxes for room attributes
    QComboBox *roomAvailabilityBox;
    QComboBox *roomPriceBox;
    QComboBox *roomLocationBox;
    QComboBox *roomPositionBox;
    QComboBox *hotelNameBox;

    // Output fields
    QLineEdit *hotelNameField;
    QLineEdit *roomNumberField;
    QLineEdit *priceField;
    QLineEdit *locationField;
    QLineEdit *positionField;
    QLineEdit *facilitiesField; // This will display facilities as a single line

    QListWidget *facilitiesListWidget;

    Database database;
    RoomTable roomTable;

    // Member variables for ClientGUI properties
    int roomId;
    int roomNumber;
    bool roomAvailability;
    double roomPrice;
    std::string hotelName;
    std::string roomLocation;
    std::string roomPosition;
    std::vector<std::string> roomFacilities;

    // For paging
    std::vector<Room> currentRooms;
    int currentPage;

    ClientPresenter *presenter; // Add a ClientPresenter member

    void populateRoomData();
    void populateFacilities();

private slots:
    void onPrintAvailableRoomsClicked();
    void onFilterRoomsClicked();
    void onNextButtonClicked(); // Slot for navigating to the next result
    void onPrevButtonClicked(); // Slot for navigating to the previous result
};

#endif // DESKTOPGUI_H