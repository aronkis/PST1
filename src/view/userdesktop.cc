#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include "userdesktop.h"
#include "userpresenter.h"

int openFileDlg(std::string& fname) 
{
    QString fileName = QFileDialog::getOpenFileName(
        nullptr, "Open File", "../", "*"
    );

    if (!fileName.isEmpty()) 
    {
        fname = fileName.toStdString();
        return 1; 
    }

    return 0; 
}

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
      database(),
      roomTable(&database),
      userTable(&database),
      user_presenter(new UserPresenter(this, &roomTable, &userTable)) 
{
    std::string fileName;
    if (!openFileDlg(fileName)) 
    {
        QMessageBox::critical(this, "Database Error", "No database selected!");
        exit(0);
        return;
    }
    if (!database.OpenConnection("/home/karon/Documents/Git/PST1/database/Hotels.db")) 
    {
        QMessageBox::critical(this, "Database Error", "Failed to open the database connection.");
        exit(0);
        return;
    }

    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    layout->addWidget(label, 0, Qt::AlignCenter | Qt::AlignHCenter);

    outHotelNameLabel = new QLabel("Hotel Name:", this);
    outRoomIdLabel = new QLabel("Room Id:", this);
    outRoomNumberLabel = new QLabel("Room Number:", this);
    outRoomAvailabilityLabel = new QLabel("Room Availability:", this);
    outPriceLabel = new QLabel("Room Price:", this);
    outLocationLabel = new QLabel("Room Location:", this);
    outPositionLabel = new QLabel("Room Position:", this);
    outFacilitiesLabel = new QLabel("Facilities:", this);

    layout->addWidget(outHotelNameLabel);
    layout->addWidget(hotelNameField);
    outHotelNameLabel->setVisible(false);
    hotelNameField->setVisible(false);
    hotelNameField->setReadOnly(true);

    layout->addWidget(outRoomNumberLabel);
    layout->addWidget(roomNumberField);
    outRoomNumberLabel->setVisible(false);
    roomNumberField->setVisible(false);
    roomNumberField->setReadOnly(true);

    layout->addWidget(outRoomIdLabel);
    layout->addWidget(roomIdField);
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
    layout->addWidget(homeButton);
    layout->addWidget(updateRoomButton);
    layout->addWidget(deleteRoomButton);
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

    adjustSize();
}

UserDesktopGUI::~UserDesktopGUI() {}

void UserDesktopGUI::findRoomButtonClicked()
{
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
    label->setText("Room Menu");
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
    outRoomIdLabel->setVisible(false);;
    createButton->setVisible(false);
    updateButton->setVisible(false);
    deleteButton->setVisible(false);

    adjustSize();
}

void UserDesktopGUI::onReadroomClicked()
{
    label->setText("Read Room");
    outHotelNameLabel->setVisible(true);
    hotelNameField->setVisible(true);
    hotelNameField->setReadOnly(false);
    hotelNameField->clear();

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
}

void UserDesktopGUI::onUpdateButtonClicked()
{
    user_presenter->UpdateRoom();
}

void UserDesktopGUI::onUpdateroomClicked()
{
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

    updateButton->setVisible(true);
}

void UserDesktopGUI::onDeleteClicked()
{
    user_presenter->DeleteRoom();
}

void UserDesktopGUI::onDeleteRoomClicked()
{
    onReadroomClicked();
    label->setText("Delete Room");
    findRoomButton->setVisible(false);
    deleteButton->setVisible(true);
}

void UserDesktopGUI::onCreateClicked()
{
    user_presenter->CreateRoom();
}

void UserDesktopGUI::onCreateRoomClicked()
{
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
}

void UserDesktopGUI::onLogInClicked() 
{
    
    std::string username = this->GetUsername();
    std::string password = this->GetUserPassword();
    if (username.empty() || password.empty()) 
    {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }
    
    if (!user_presenter->HandleLogin(username, password)) 
    {
        QMessageBox::warning(this, "Login Error", "Invalid username or password.");
        return;
    }
        
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
    label->setText("Room Menu");
     
    adjustSize();
}

void UserDesktopGUI::onLogOutClicked() 
{

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

    adjustSize();
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

std::string UserDesktopGUI::GetUsername() 
{
    return usernameField->text().toStdString(); 
}

std::string UserDesktopGUI::GetUserPassword() 
{
    return userPasswordField->text().toStdString(); 
}

bool UserDesktopGUI::GetRoomAvailability() 
{
    return roomAvailabilityField->text() == "Available";
}

void UserDesktopGUI::SetRoomAvailability(bool availability)
{
    roomAvailabilityField->setText(availability ? "Available" : "Not Available");
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

std::vector<std::string> UserDesktopGUI::GetFacilities() 
{
    std::vector<std::string> facilities;

    QString facilitiesText = facilitiesField->text();

    for (const QString& facility : facilitiesText.split(',')) 
    {
        facilities.push_back(facility.trimmed().toStdString()); 
    }
    
    return facilities;
}

void UserDesktopGUI::SetRoomFacilities(const std::vector<std::string> &facilities) 
{
    std::string facilitiesStr = facilities[0];
    for (int i = 1; i < facilities.size(); i++) 
    {
        facilitiesStr += ", " + facilities[i];
    }
    facilitiesField->setText(QString::fromStdString(facilitiesStr));
}

std::string UserDesktopGUI::GetHotelName() {
    return hotelNameField->text().toStdString();
}

void UserDesktopGUI::SetHotelName(const std::string &hotel_name) 
{
    hotelNameField->setText(QString::fromStdString(hotel_name));
}

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);


    UserDesktopGUI mainWindow(nullptr);
    mainWindow.setWindowTitle("Desktop User Application");
    mainWindow.show();

    return app.exec();
}