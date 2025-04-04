#ifndef USERDESKTOP_H
#define USERDESKTOP_H

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
#include "usergui.h"
#include "roomtable.h"
#include "database.h"
#include "userpresenter.h"

class UserDesktopGUI : public QMainWindow, public UserGUI {
    Q_OBJECT

public:
    explicit UserDesktopGUI(QWidget *parent = nullptr);
    ~UserDesktopGUI();

    // Implement IUserGUI methods
    int GetRoomId() override;
    void SetRoomId(int id) override;
    int GetRoomNumber() override;
    void SetRoomNumber(int number) override;
    bool GetRoomAvailability() override;
    void SetRoomAvailability(bool availability) override;
    double GetRoomPrice() override;
    void SetRoomPrice(double price) override;
    std::string GetRoomLocation() override;
    void SetRoomLocation(const std::string &location) override;
    std::string GetRoomPosition()  override;
    void SetRoomPosition(const std::string &position) override;
    std::vector<std::string> GetFacilities()  override;
    void SetRoomFacilities(const std::vector<std::string> &facilities) override;
    std::string GetHotelName() override;
    void SetHotelName(const std::string &hotel_name) override;

    std::string GetUsername() override;
    std::string GetUserPassword() override;

private:
  
    QPushButton *loginButton;
    QPushButton *createRoomButton;
    QPushButton *createButton;
    QPushButton *readRoomButton;
    QPushButton *findRoomButton;
    QPushButton *homeButton;
    QPushButton *updateRoomButton;
    QPushButton *updateButton;
    QPushButton *deleteRoomButton;
    QPushButton *deleteButton;
    QPushButton *logoutButton;

    // Authentication fields
    QLabel *usernameLabel;
    QLabel *userPasswordLabel;
    QLineEdit *usernameField;
    QLineEdit *userPasswordField;

    QWidget *centralWidget;
    QWidget *userViewWidget;
    QVBoxLayout *layout;

    QLabel *label;

    // Dropdown boxes for room attributes
    QComboBox *hotelNameBox;
    QComboBox *roomAvailabilityBox;
    QComboBox *roomPriceBox;
    QComboBox *roomLocationBox;
    QComboBox *roomPositionBox;
    
    //Room attributes labels
    QLabel *hotelNameLabel;
    QLabel *roomNumberLabel;
    QLabel *roomAvailabilityLabel;
    QLabel *priceLabel;
    QLabel *locationLabel;
    QLabel *positionLabel;
    QLabel *facilitiesLabel;
 
    // Output fields
    QLineEdit *hotelNameField;
    QLineEdit *roomIdField;
    QLineEdit *roomNumberField;
    QLineEdit *roomAvailabilityField;
    QLineEdit *priceField;
    QLineEdit *locationField;
    QLineEdit *positionField;
    QLineEdit *facilitiesField; // This will display facilities as a single line

    //Output labels
    QLabel *outHotelNameLabel;
    QLabel *outRoomIdLabel;
    QLabel *outRoomNumberLabel;
    QLabel *outRoomAvailabilityLabel;
    QLabel *outPriceLabel;
    QLabel *outLocationLabel;
    QLabel *outPositionLabel;
    QLabel *outFacilitiesLabel;

    QListWidget *facilitiesListWidget;

    // For paging
    std::vector<Room> currentRooms;
    int currentPage;

    UserPresenter *user_presenter; // Reference to the presenter
    Database database;
    RoomTable roomTable;
    UserTable userTable;

    // Room-related data
    int roomId;
    int roomNumber;
    bool roomAvailability;
    double roomPrice;
    std::string roomLocation;
    std::string roomPosition;
    std::vector<std::string> facilities;
    std::string hotelName;

private slots:
    void onLogInClicked();
    void onLogOutClicked();
    void onReadroomClicked();
    void onCreateRoomClicked();
    void onCreateClicked();
    void findRoomButtonClicked();
    void homeButtonClicked();
    void onUpdateroomClicked();
    void onUpdateButtonClicked();
    void onDeleteRoomClicked();
    void onDeleteClicked();
};

#endif // USERGUI_H