#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include "userdesktop.h"
#include "userpresenter.h" 

UserDesktopGUI::UserDesktopGUI(QWidget *parent)
    : QMainWindow(parent), 
      centralWidget(new QWidget(this)),
      layout(new QVBoxLayout),
      label(new QLabel("Welcome to the User GUI", this)),
      loginButton(new QPushButton("Login", this)),
      createRoomButton(new QPushButton("Create Room", this)),
      createButton(new QPushButton("Create", this)),
      readRoomButton(new QPushButton("Read Room", this)),
      findRoomButton(new QPushButton("Find", this)),
      homeButton(new QPushButton("Home", this)),
      updateRoomButton(new QPushButton("Update Room", this)),
      updateButton(new QPushButton("Update", this)),
      deleteRoomButton(new QPushButton("Delete Room", this)),
      deleteButton(new QPushButton("Delete", this)),
      logoutButton(new QPushButton("Logout", this)),
      hotelNameField(new QLineEdit(this)), 
      roomIdField(new QLineEdit(this)), 
      roomNumberField(new QLineEdit(this)), 
      priceField(new QLineEdit(this)), 
      locationField(new QLineEdit(this)),
      roomAvailabilityField(new QLineEdit(this)),
      positionField(new QLineEdit(this)), 
      facilitiesField(new QLineEdit(this)), 
      roomPositionBox(new QComboBox(this)),
      roomAvailabilityBox(new QComboBox(this)),
      roomPriceBox(new QComboBox(this)),
      roomLocationBox(new QComboBox(this)),
      hotelNameBox(new QComboBox(this)),
      facilitiesListWidget(new QListWidget(this)),
      nextButton(new QPushButton("Next", this)),
      prevButton(new QPushButton("Previous", this)),
      availableRoomsButton(new QPushButton("Available Rooms", this)),
      showAvailableButton(new QPushButton("Show Available Rooms", this)),
      filterRoomsButton(new QPushButton("Filter Rooms", this)),
      showFilterRoomsButton(new QPushButton("Show Filtered Rooms", this)),
      database(),
      roomTable(&database),
      userTable(&database),
      user_presenter(new UserPresenter(this, &roomTable, &userTable)) 
{
    user_presenter->OpenDatabase();
    
    user_presenter->PopulateRoomData();
    user_presenter->PopulateFacilities();
    
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
    this->adjustSize();

    layout->addWidget(label, 0, Qt::AlignCenter | Qt::AlignHCenter);

    outHotelNameLabel = new QLabel("Hotel Name:", this);
    outRoomIdLabel = new QLabel("Room Id:", this);
    outRoomNumberLabel = new QLabel("Room Number:", this);
    outRoomAvailabilityLabel = new QLabel("Room Availability:", this);
    outPriceLabel = new QLabel("Room Price:", this);
    outLocationLabel = new QLabel("Room Location:", this);
    outPositionLabel = new QLabel("Room Position:", this);
    outFacilitiesLabel = new QLabel("Facilities:", this);

    hotelNameBoxLabel = new QLabel("Hotel Name:", this);
    roomAvailabilityBoxLabel = new QLabel("Room Availability:", this);
    roomPriceBoxLabel = new QLabel("Room Price:", this);
    roomLocationBoxLabel = new QLabel("Room Location:", this);
    roomPositionBoxLabel = new QLabel("Room Position:", this);
    facilitiesListWidgetLabel = new QLabel("Facilities:", this);

    layout->addWidget(hotelNameBoxLabel);
    layout->addWidget(hotelNameBox);
    hotelNameBoxLabel->setVisible(false);
    hotelNameBox->setVisible(false);

    layout->addWidget(roomAvailabilityBoxLabel);
    layout->addWidget(roomAvailabilityBox);
    roomAvailabilityBoxLabel->setVisible(false);
    roomAvailabilityBox->setVisible(false);

    layout->addWidget(roomPriceBoxLabel);
    layout->addWidget(roomPriceBox);
    roomPriceBoxLabel->setVisible(false);
    roomPriceBox->setVisible(false);

    layout->addWidget(roomLocationBoxLabel);
    layout->addWidget(roomLocationBox);
    roomLocationBoxLabel->setVisible(false);
    roomLocationBox->setVisible(false);

    layout->addWidget(roomPositionBoxLabel);
    layout->addWidget(roomPositionBox);
    roomPositionBoxLabel->setVisible(false);
    roomPositionBox->setVisible(false);

    layout->addWidget(facilitiesListWidgetLabel);
    layout->addWidget(facilitiesListWidget);
    facilitiesListWidgetLabel->setVisible(false);
    facilitiesListWidget->setVisible(false);

    layout->addWidget(outHotelNameLabel);
    layout->addWidget(hotelNameField);
    outHotelNameLabel->setVisible(false);
    hotelNameField->setVisible(false);
    hotelNameField->setReadOnly(true);

    layout->addWidget(outRoomNumberLabel);
    layout->addWidget(roomNumberField);
    roomNumberField->setValidator(new QIntValidator(0, 999999, this));
    outRoomNumberLabel->setVisible(false);
    roomNumberField->setVisible(false);
    roomNumberField->setReadOnly(true);

    layout->addWidget(outRoomIdLabel);
    layout->addWidget(roomIdField);
    roomIdField->setValidator(new QIntValidator(0, 999999, this));
    outRoomIdLabel->setVisible(false);
    roomIdField->setVisible(false);
    roomIdField->setReadOnly(true);

    layout->addWidget(outRoomAvailabilityLabel);
    layout->addWidget(roomAvailabilityField);
    outRoomAvailabilityLabel->setVisible(false);
    roomAvailabilityField->setVisible(false);
    roomAvailabilityField->setReadOnly(true);

    layout->addWidget(outPriceLabel);
    layout->addWidget(priceField);
    priceField->setValidator(new QDoubleValidator(0, 99999.99, 2, this));
    outPriceLabel->setVisible(false);
    priceField->setVisible(false);
    priceField->setReadOnly(true);

    layout->addWidget(outLocationLabel);
    layout->addWidget(locationField);
    outLocationLabel->setVisible(false);
    locationField->setVisible(false);
    locationField->setReadOnly(true);

    layout->addWidget(outPositionLabel);
    layout->addWidget(positionField);
    outPositionLabel->setVisible(false);
    positionField->setVisible(false);
    positionField->setReadOnly(true);
 
    layout->addWidget(outFacilitiesLabel);
    layout->addWidget(facilitiesField);
    outFacilitiesLabel->setVisible(false);
    facilitiesField->setVisible(false);
    facilitiesField->setReadOnly(true);

    usernameLabel = new QLabel("Username:", this);
    userPasswordLabel = new QLabel("Password:", this);
    usernameField = new QLineEdit(this);
    userPasswordField = new QLineEdit(this);
    userPasswordField->setEchoMode(QLineEdit::Password);
    
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameField);
    layout->addWidget(userPasswordLabel);
    layout->addWidget(userPasswordField);
    layout->addWidget(loginButton);
    loginButton->setVisible(true);

    layout->addWidget(createRoomButton);
    layout->addWidget(createButton);
    layout->addWidget(readRoomButton);
    layout->addWidget(findRoomButton);
    layout->addWidget(updateButton);
    layout->addWidget(deleteButton);
    layout->addWidget(updateRoomButton);
    layout->addWidget(deleteRoomButton);

    layout->addWidget(availableRoomsButton);
    layout->addWidget(showAvailableButton);
    layout->addWidget(showFilterRoomsButton);
    layout->addWidget(filterRoomsButton);
    layout->addWidget(nextButton);
    layout->addWidget(prevButton);

    layout->addWidget(homeButton);
    layout->addWidget(logoutButton);

    createRoomButton->setVisible(false);
    createButton->setVisible(false);
    findRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    homeButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);
    updateButton->setVisible(false);
    deleteButton->setVisible(false);

    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);
    nextButton->setVisible(false);
    prevButton->setVisible(false);
    showAvailableButton->setVisible(false);
    showFilterRoomsButton->setVisible(false);

    connect(loginButton, &QPushButton::clicked, this, &UserDesktopGUI::onLogInClicked);
    connect(logoutButton, &QPushButton::clicked, this, &UserDesktopGUI::onLogOutClicked);
    connect(readRoomButton, &QPushButton::clicked, this, &UserDesktopGUI::onReadroomClicked);
    connect(createRoomButton, &QPushButton::clicked, this, &UserDesktopGUI::onCreateRoomClicked);
    connect(createButton, &QPushButton::clicked, this, &UserDesktopGUI::onCreateClicked);
    connect(findRoomButton, &QPushButton::clicked, this, &UserDesktopGUI::findRoomButtonClicked);
    connect(homeButton, &QPushButton::clicked, this, &UserDesktopGUI::homeButtonClicked);
    connect(updateRoomButton, &QPushButton::clicked, this, &UserDesktopGUI::onUpdateroomClicked);
    connect(updateButton, &QPushButton::clicked, this, &UserDesktopGUI::onUpdateButtonClicked);
    connect(deleteRoomButton, &QPushButton::clicked, this, &UserDesktopGUI::onDeleteRoomClicked);
    connect(deleteButton, &QPushButton::clicked, this, &UserDesktopGUI::onDeleteClicked);
    
    connect(availableRoomsButton, &QPushButton::clicked, this, &UserDesktopGUI::onAvailableRoomsButtonClicked);
    connect(showAvailableButton, &QPushButton::clicked, this, &UserDesktopGUI::onShowAvailableButtonClicked);
    connect(filterRoomsButton, &QPushButton::clicked, this, &UserDesktopGUI::onFilterRoomsButtonClicked);
    connect(showFilterRoomsButton, &QPushButton::clicked, this, &UserDesktopGUI::onShowFilterRoomsButtonClicked);
    connect(nextButton, &QPushButton::clicked, this, &UserDesktopGUI::onNextButtonClicked);
    connect(prevButton, &QPushButton::clicked, this, &UserDesktopGUI::onPrevButtonClicked);
}

UserDesktopGUI::~UserDesktopGUI() {}

void UserDesktopGUI::onNextButtonClicked()
{
    user_presenter->LoadNextRoomDetails();
}

void UserDesktopGUI::onPrevButtonClicked()
{
    user_presenter->LoadPrevRoomDetails();
}

void UserDesktopGUI::onShowFilterRoomsButtonClicked()
{
    this->adjustSize();

    outRoomIdLabel->setVisible(true);
    roomIdField->setVisible(true);
    outRoomAvailabilityLabel->setVisible(true);
    roomAvailabilityField->setVisible(true);
    outPriceLabel->setVisible(true);
    priceField->setVisible(true);
    outLocationLabel->setVisible(true);
    locationField->setVisible(true);
    outPositionLabel->setVisible(true);
    positionField->setVisible(true);
    outFacilitiesLabel->setVisible(true);
    facilitiesField->setVisible(true);
    nextButton->setVisible(true);
    prevButton->setVisible(true);

    user_presenter->FilterRooms();
    user_presenter->DisplayRoomDetails();
}

void UserDesktopGUI::onFilterRoomsButtonClicked()
{
    this->adjustSize();

    roomAvailabilityBoxLabel->setVisible(true);
    roomAvailabilityBox->setVisible(true);
    roomPriceBoxLabel->setVisible(true);
    roomPriceBox->setVisible(true);
    roomLocationBoxLabel->setVisible(true);
    roomLocationBox->setVisible(true);
    roomPositionBoxLabel->setVisible(true);
    roomPositionBox->setVisible(true);
    facilitiesListWidgetLabel->setVisible(true);
    facilitiesListWidget->setVisible(true);
    homeButton->setVisible(true);
    showFilterRoomsButton->setVisible(true);
    createRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);
    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);
}

void UserDesktopGUI::onShowAvailableButtonClicked()
{
    this->adjustSize();

    outRoomIdLabel->setVisible(true);
    roomIdField->setVisible(true);
    outRoomAvailabilityLabel->setVisible(true);
    roomAvailabilityField->setVisible(true);
    outPriceLabel->setVisible(true);
    priceField->setVisible(true);
    outLocationLabel->setVisible(true);
    locationField->setVisible(true);
    outPositionLabel->setVisible(true);
    positionField->setVisible(true);
    outFacilitiesLabel->setVisible(true);
    facilitiesField->setVisible(true);
    nextButton->setVisible(true);
    prevButton->setVisible(true);

    user_presenter->GetAvailableRooms();
    user_presenter->DisplayRoomDetails();
}

void UserDesktopGUI::onAvailableRoomsButtonClicked()
{
    this->adjustSize();

    hotelNameBoxLabel->setVisible(true);
    hotelNameBox->setVisible(true);
    homeButton->setVisible(true);
    showAvailableButton->setVisible(true);
    createRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);
    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);
}

void UserDesktopGUI::findRoomButtonClicked()
{
    this->adjustSize();

    outRoomIdLabel->setVisible(true);
    roomIdField->setVisible(true);
    outRoomAvailabilityLabel->setVisible(true);
    roomAvailabilityField->setVisible(true);
    outPriceLabel->setVisible(true);
    priceField->setVisible(true);
    outLocationLabel->setVisible(true);
    locationField->setVisible(true);
    outPositionLabel->setVisible(true);
    positionField->setVisible(true);
    outFacilitiesLabel->setVisible(true);
    facilitiesField->setVisible(true);

    user_presenter->ReadRoom();
}

void UserDesktopGUI::homeButtonClicked()
{
    this->adjustSize();

    label->setText("User Menu");

    createRoomButton->setVisible(true);
    readRoomButton->setVisible(true);
    updateRoomButton->setVisible(true);
    deleteRoomButton->setVisible(true);
    logoutButton->setVisible(true);
    availableRoomsButton->setVisible(true);
    filterRoomsButton->setVisible(true);
    loginButton->setVisible(false);
    usernameLabel->setVisible(false);
    usernameField->setVisible(false);
    userPasswordLabel->setVisible(false);
    userPasswordField->setVisible(false);
    outHotelNameLabel->setVisible(false);
    hotelNameField->setVisible(false);
    outRoomNumberLabel->setVisible(false);
    roomNumberField->setVisible(false);
    outRoomAvailabilityLabel->setVisible(false);
    roomAvailabilityField->setVisible(false);
    outPriceLabel->setVisible(false);
    priceField->setVisible(false);
    outLocationLabel->setVisible(false);
    locationField->setVisible(false);
    outPositionLabel->setVisible(false);
    positionField->setVisible(false);
    outFacilitiesLabel->setVisible(false);
    facilitiesField->setVisible(false);
    homeButton->setVisible(false);
    findRoomButton->setVisible(false);
    roomIdField->setVisible(false);
    outRoomIdLabel->setVisible(false);
    createButton->setVisible(false);
    updateButton->setVisible(false);
    deleteButton->setVisible(false);
    nextButton->setVisible(false);
    prevButton->setVisible(false);
    showAvailableButton->setVisible(false);
    hotelNameBoxLabel->setVisible(false);
    hotelNameBox->setVisible(false);
    roomAvailabilityBoxLabel->setVisible(false);
    roomAvailabilityBox->setVisible(false);
    roomPriceBoxLabel->setVisible(false);
    roomPriceBox->setVisible(false);
    roomLocationBoxLabel->setVisible(false);
    roomLocationBox->setVisible(false);
    roomPositionBoxLabel->setVisible(false);
    roomPositionBox->setVisible(false);
    facilitiesListWidgetLabel->setVisible(false);
    facilitiesListWidget->setVisible(false);
    showFilterRoomsButton->setVisible(false);
}

void UserDesktopGUI::onReadroomClicked()
{
    this->adjustSize();

    label->setText("Read Room");

    hotelNameBoxLabel->setVisible(true);
    hotelNameBox->setVisible(true);

    outRoomNumberLabel->setVisible(true);
    roomNumberField->setVisible(true);
    roomNumberField->setReadOnly(false);
    roomNumberField->clear();

    findRoomButton->setVisible(true);
    homeButton->setVisible(true);

    createRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);
    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);
}

void UserDesktopGUI::onUpdateButtonClicked()
{
    this->adjustSize();

    user_presenter->UpdateRoom();
    user_presenter->PopulateRoomData();
    user_presenter->PopulateFacilities();
}

void UserDesktopGUI::onUpdateroomClicked()
{
    this->adjustSize();

    onReadroomClicked();
    
    label->setText("Update Room");
    
    hotelNameField->setReadOnly(false);
    roomNumberField->setReadOnly(false);
    roomIdField->setReadOnly(false);
    roomAvailabilityField->setReadOnly(false);
    priceField->setReadOnly(false);
    locationField->setReadOnly(false);
    positionField->setReadOnly(false);
    facilitiesField->setReadOnly(false);
    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);

    updateButton->setVisible(true);
}

void UserDesktopGUI::onDeleteClicked()
{
    user_presenter->DeleteRoom();
}

void UserDesktopGUI::onDeleteRoomClicked()
{
    this->adjustSize();

    onReadroomClicked();
    
    label->setText("Delete Room");
    findRoomButton->setVisible(false);
    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);
    deleteButton->setVisible(true);
}

void UserDesktopGUI::onCreateClicked()
{
    user_presenter->CreateRoom();
    user_presenter->PopulateRoomData();
    user_presenter->PopulateFacilities();
}

void UserDesktopGUI::onCreateRoomClicked()
{
    this->adjustSize();

    label->setText("Create Room");

    outHotelNameLabel->setVisible(true);
    hotelNameField->setVisible(true);
    hotelNameField->setReadOnly(false);
    hotelNameField->clear();

    outRoomNumberLabel->setVisible(true);
    roomNumberField->setVisible(true);
    roomNumberField->setReadOnly(false);
    roomNumberField->clear();

    outRoomIdLabel->setVisible(true);
    roomIdField->setVisible(true);
    roomIdField->setReadOnly(false);
    roomIdField->clear();
    outRoomAvailabilityLabel->setVisible(true);
    roomAvailabilityField->setVisible(true);
    roomAvailabilityField->setReadOnly(false);
    roomAvailabilityField->clear();

    outPriceLabel->setVisible(true);
    priceField->setVisible(true);
    priceField->setReadOnly(false);
    priceField->clear();

    outLocationLabel->setVisible(true);
    locationField->setVisible(true);
    locationField->setReadOnly(false);
    locationField->clear();

    outPositionLabel->setVisible(true);
    positionField->setVisible(true);
    positionField->setReadOnly(false);
    positionField->clear();

    outFacilitiesLabel->setVisible(true);
    facilitiesField->setVisible(true);
    facilitiesField->setReadOnly(false);
    facilitiesField->clear();

    createButton->setVisible(true);
    homeButton->setVisible(true);

    createRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);
    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);
}

void UserDesktopGUI::onLogInClicked() 
{
    this->adjustSize();

    user_presenter->HandleLogin();
    
    if (is_logged_in)
    {
        label->setText("User Menu");

        loginButton->setVisible(false);
        usernameLabel->setVisible(false);
        usernameField->setVisible(false);
        userPasswordLabel->setVisible(false);
        userPasswordField->setVisible(false);
        createRoomButton->setVisible(true);
        readRoomButton->setVisible(true);
        updateRoomButton->setVisible(true);
        deleteRoomButton->setVisible(true);
        logoutButton->setVisible(true);
        availableRoomsButton->setVisible(true);
        filterRoomsButton->setVisible(true);
    }
}

void UserDesktopGUI::onLogOutClicked() 
{
    this->adjustSize();
    label->setText("You've been logged out!\n         Login in again!");

    loginButton->setVisible(true);
    usernameLabel->setVisible(true);
    usernameField->setVisible(true);
    userPasswordLabel->setVisible(true);
    userPasswordField->setVisible(true);
    
    userPasswordField->clear();

    createRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);
    availableRoomsButton->setVisible(false);
    filterRoomsButton->setVisible(false);
    showAvailableButton->setVisible(false);

    user_presenter->HandleLogOut();
}

void UserDesktopGUI::SetDatabase(std::string path)
{
    database.OpenConnection(path);
}

void UserDesktopGUI::SetHotelName(const std::string &hotel_name) 
{
    hotelNameField->setText(QString::fromStdString(hotel_name));
}

std::string UserDesktopGUI::GetHotelName() 
{
    return hotelNameField->text().toStdString();
}

int UserDesktopGUI::GetRoomId() 
{
    return roomIdField->text().toInt(); 
}

void UserDesktopGUI::SetRoomId(int id) 
{
    roomIdField->setText(QString::number(id)); 
}

int UserDesktopGUI::GetRoomNumber() 
{
    return roomNumberField->text().toInt(); 
}

void UserDesktopGUI::SetRoomNumber(int number) 
{
    roomNumberField->setText(QString::number(number)); 
}

std::string UserDesktopGUI::GetRoomAvailability() 
{

    return roomAvailabilityField->text().toStdString();
}

void UserDesktopGUI::SetRoomAvailability(std::string availability)
{
    roomAvailabilityField->setText(QString::fromStdString(availability));
}

double UserDesktopGUI::GetRoomPrice() 
{
    return priceField->text().toDouble(); 
}

void UserDesktopGUI::SetRoomPrice(double price) 
{
    priceField->setText(QString::number(price));
}

std::string UserDesktopGUI::GetRoomLocation() 
{
    return locationField->text().toStdString();
}

void UserDesktopGUI::SetRoomLocation(const std::string &location) 
{
    locationField->setText(QString::fromStdString(location));
}

std::string UserDesktopGUI::GetRoomPosition() 
{
    return positionField->text().toStdString();
}

void UserDesktopGUI::SetRoomPosition(const std::string &position) 
{
    positionField->setText(QString::fromStdString(position));
}

std::string UserDesktopGUI::GetFacilities() 
{
    return facilitiesField->text().toStdString();
}

void UserDesktopGUI::SetRoomFacilities(const std::string &facilities) 
{
    facilitiesField->setText(QString::fromStdString(facilities));
}

std::string UserDesktopGUI::GetUsername() 
{
    return usernameField->text().toStdString(); 
}

std::string UserDesktopGUI::GetUserPassword() 
{
    return userPasswordField->text().toStdString(); 
}

std::string UserDesktopGUI::GetHotelNameBox()
{
    return hotelNameBox->currentText().toStdString();
}

void UserDesktopGUI::SetHotelNameBox(const std::string &hotel_name)
{
    hotelNameBox->addItem(QString::fromStdString(hotel_name));
}

void UserDesktopGUI::SetRoomAvailabilityBox(std::string availability)
{
    roomAvailabilityBox->addItem(QString::fromStdString(availability));
}

void UserDesktopGUI::SetRoomPriceBox(double price)
{
    roomPriceBox->addItem(QString::number(price));
}

void UserDesktopGUI::SetRoomLocationBox(const std::string &location)
{
    roomLocationBox->addItem(QString::fromStdString(location));
}

void UserDesktopGUI::SetRoomPositionBox(const std::string &position)
{
    roomPositionBox->addItem(QString::fromStdString(position));
}

void UserDesktopGUI::SetRoomFacilitiesBox(const std::string &facility)
{
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(facility), facilitiesListWidget);
    item->setCheckState(Qt::Unchecked);
}

std::string UserDesktopGUI::GetRoomAvailabilityBox()
{
    return roomAvailabilityBox->currentText().toStdString();
}

double UserDesktopGUI::GetRoomPriceBox()
{
    return roomPriceBox->currentText().toDouble();
}

std::string UserDesktopGUI::GetRoomLocationBox()
{
    return roomLocationBox->currentText().toStdString();
}

std::string UserDesktopGUI::GetRoomPositionBox()
{
    return roomPositionBox->currentText().toStdString();
}

bool UserDesktopGUI::GetFacilitiesBoxItemState(int pos)
{
   return facilitiesListWidget->item(pos)->checkState() == Qt::Checked;
}

std::string UserDesktopGUI::GetFacilitiesBoxItemValue(int pos)
{
   return facilitiesListWidget->item(pos)->text().toStdString();
}

int UserDesktopGUI::GetFacilitiesCount()
{
    return facilitiesListWidget->count();
}

void UserDesktopGUI::SetLoggedIn(bool logged_in)
{
    is_logged_in = logged_in;
}

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    UserDesktopGUI mainWindow(nullptr);
    mainWindow.setWindowTitle("Desktop User Application");
    mainWindow.show();

    return app.exec();
}