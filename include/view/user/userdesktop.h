#ifndef USERDESKTOP_H
#define USERDESKTOP_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit> 
#include <QComboBox>
#include <QListWidget>
#include <vector>
#include <string>
#include "usergui.h"
#include "roomtable.h"
#include "database.h"
#include "userpresenter.h"

class UserDesktopGUI : public QMainWindow, public UserGUI 
{
    Q_OBJECT

public:
    explicit UserDesktopGUI(QWidget *parent = nullptr);
    ~UserDesktopGUI();
    int GetRoomId() override;
    void SetRoomId(int id) override;
    int GetRoomNumber() override;
    void SetRoomNumber(int number) override;
    std::string GetRoomAvailability() override;
    void SetRoomAvailability(std::string availability) override;
    double GetRoomPrice() override;
    void SetRoomPrice(double price) override;
    std::string GetRoomLocation() override;
    void SetRoomLocation(const std::string &location) override;
    std::string GetRoomPosition()  override;
    void SetRoomPosition(const std::string &position) override;
    std::string GetFacilities()  override;
    void SetRoomFacilities(const std::string &facilities) override;
    std::string GetHotelName() override;
    void SetHotelName(const std::string &hotel_name) override;
    std::string GetUsername() override;
    std::string GetUserPassword() override;
    std::string GetHotelNameBox() override;
    void SetHotelNameBox(const std::string &hotel_name) override;
    void SetRoomAvailabilityBox(std::string availability) override;
    void SetRoomPriceBox(double price) override;
    void SetRoomLocationBox(const std::string &location) override;
    void SetRoomPositionBox(const std::string &position) override;
    void SetRoomFacilitiesBox(const std::string &facilities) override;
    std::string GetRoomAvailabilityBox() override;
    double GetRoomPriceBox() override;
    std::string GetRoomLocationBox() override;
    std::string GetRoomPositionBox() override;
    std::string GetFacilitiesBox() override;
    void SetLoggedIn(bool logged_in) override;

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

    QPushButton *nextButton;
    QPushButton *prevButton;
    QPushButton *availableRoomsButton;
    QPushButton *showAvailableButton;
    QPushButton *filterRoomsButton;
    QPushButton *showFilterRoomsButton;

    QComboBox *hotelNameBox;
    QComboBox *roomAvailabilityBox;
    QComboBox *roomPriceBox;
    QComboBox *roomLocationBox;
    QComboBox *roomPositionBox;
    QListWidget *facilitiesListWidget;
    
    QWidget *centralWidget;
    QVBoxLayout *layout;

    QLabel *label;
    
    QLineEdit *hotelNameField;
    QLineEdit *roomIdField;
    QLineEdit *roomNumberField;
    QLineEdit *roomAvailabilityField;
    QLineEdit *priceField;
    QLineEdit *locationField;
    QLineEdit *positionField;
    QLineEdit *facilitiesField;
    QLineEdit *usernameField;
    QLineEdit *userPasswordField; 

    QLabel *outHotelNameLabel;
    QLabel *outRoomIdLabel;
    QLabel *outRoomNumberLabel;
    QLabel *outRoomAvailabilityLabel;
    QLabel *outPriceLabel;
    QLabel *outLocationLabel;
    QLabel *outPositionLabel;
    QLabel *outFacilitiesLabel;
    QLabel *usernameLabel;
    QLabel *userPasswordLabel;

    QLabel *roomAvailabilityBoxLabel;
    QLabel *roomPriceBoxLabel;
    QLabel *roomLocationBoxLabel;
    QLabel *roomPositionBoxLabel;
    QLabel *hotelNameBoxLabel;
    QLabel *facilitiesListWidgetLabel;

    UserPresenter *user_presenter; 
    Database database;
    RoomTable roomTable;
    UserTable userTable;
    bool is_logged_in = false;

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
    void onAvailableRoomsButtonClicked();
    void onShowAvailableButtonClicked();
    void onFilterRoomsButtonClicked(); 
    void onShowFilterRoomsButtonClicked();
    void onNextButtonClicked();
    void onPrevButtonClicked();

};

#endif // USERGUI_H
