#include "desktopgui.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QTextEdit> // Include QTextEdit
#include <set> // Include for std::set
#include "clientpresenter.h"

// Constructor
DesktopGUI::DesktopGUI(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      layout(new QVBoxLayout),
      label(new QLabel("Welcome to the Client GUI", this)),
      printAvailableButton(new QPushButton("Print Available Rooms", this)),
      filterRoomsButton(new QPushButton("Filter Rooms", this)),
      nextButton(new QPushButton("Next", this)),
      prevButton(new QPushButton("Previous", this)),
      roomPositionBox(new QComboBox(this)),
      roomAvailabilityBox(new QComboBox(this)),
      roomPriceBox(new QComboBox(this)),
      roomLocationBox(new QComboBox(this)),
      hotelNameBox(new QComboBox(this)),
      hotelNameField(new QLineEdit(this)), // Replace QTextEdit with QLineEdit
      roomNumberField(new QLineEdit(this)), // Replace QTextEdit with QLineEdit
      priceField(new QLineEdit(this)), // Replace QTextEdit with QLineEdit
      locationField(new QLineEdit(this)), // Replace QTextEdit with QLineEdit
      positionField(new QLineEdit(this)), // Replace QTextEdit with QLineEdit
      facilitiesField(new QLineEdit(this)), // Replace QTextEdit with QLineEdit
      facilitiesListWidget(new QListWidget(this)), // Initialize facilities list widget
      database(), // Initialize the database
      roomTable(&database), // Pass a pointer to the database instance to RoomTable
      presenter(new ClientPresenter(this, &roomTable)), // Initialize ClientPresenter
      currentPage(0) // Initialize current page to 0
{
    // Open the database connection
    if (!database.OpenConnection("/home/karon/Documents/Git/PST1/database/Hotels.db")) {
        QMessageBox::critical(this, "Database Error", "Failed to open the database connection.");
        qDebug() << "Database connection failed.";
        return;
    } else {
        qDebug() << "Database connection successful.";
    }

    // Set up the central widget and layout
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    // Center the label in the middle of the screen
    QSpacerItem *topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addItem(topSpacer); // Add spacer above the label
    layout->addWidget(label, 0, Qt::AlignCenter); // Center the label horizontally
    layout->addItem(bottomSpacer); // Add spacer below the label

    // Populate dropdowns dynamically
    populateRoomData();

    // Populate facilities list widget
    populateFacilities();

    layout->addWidget(new QLabel("Hotel Name:", this));
    layout->addWidget(hotelNameBox);

    layout->addWidget(new QLabel("Room Availability:", this));
    layout->addWidget(roomAvailabilityBox);

    layout->addWidget(new QLabel("Room Price:", this));
    layout->addWidget(roomPriceBox);

    layout->addWidget(new QLabel("Room Location:", this));
    layout->addWidget(roomLocationBox);

    layout->addWidget(new QLabel("Room Position:", this));
    layout->addWidget(roomPositionBox);
   
    // Add facilities list widget
    layout->addWidget(new QLabel("Facilities:", this));
    layout->addWidget(facilitiesListWidget);

    // Add buttons
    layout->addWidget(printAvailableButton);
    layout->addWidget(filterRoomsButton);

    // Add output fields
    layout->addWidget(new QLabel("Hotel Name:", this));
    layout->addWidget(hotelNameField);
    hotelNameField->setReadOnly(true);

    layout->addWidget(new QLabel("Room Number:", this));
    layout->addWidget(roomNumberField);
    roomNumberField->setReadOnly(true);

    layout->addWidget(new QLabel("Price:", this));
    layout->addWidget(priceField);
    priceField->setReadOnly(true);

    layout->addWidget(new QLabel("Location:", this));
    layout->addWidget(locationField);
    locationField->setReadOnly(true);

    layout->addWidget(new QLabel("Position:", this));
    layout->addWidget(positionField);
    positionField->setReadOnly(true);

    layout->addWidget(new QLabel("Facilities:", this));
    layout->addWidget(facilitiesField);
    facilitiesField->setReadOnly(true);

    // Add navigation buttons
    layout->addWidget(prevButton);
    layout->addWidget(nextButton);

    // Connect button signals to slots
    connect(printAvailableButton, &QPushButton::clicked, this, &DesktopGUI::onPrintAvailableRoomsClicked);
    connect(filterRoomsButton, &QPushButton::clicked, this, &DesktopGUI::onFilterRoomsClicked);
    connect(nextButton, &QPushButton::clicked, this, &DesktopGUI::onNextButtonClicked);
    connect(prevButton, &QPushButton::clicked, this, &DesktopGUI::onPrevButtonClicked);
}

// Destructor
DesktopGUI::~DesktopGUI() {
    database.CloseConnection();
}

bool DesktopGUI::GetRoomAvailability() {
    return roomAvailabilityBox->currentText() == "Available";
}

void DesktopGUI::SetRoomAvailability(bool availability) {
    roomAvailabilityBox->setCurrentText(availability ? "Available" : "Not Available");
}

double DesktopGUI::GetRoomPrice() {
    return roomPriceBox->currentText().toDouble();
}

void DesktopGUI::SetRoomPrice(double price) {
    roomPriceBox->setCurrentText(QString::number(price));
}

std::string DesktopGUI::GetRoomLocation() {
    return roomLocationBox->currentText().toStdString();
}

void DesktopGUI::SetRoomLocation(const std::string &location) {
    roomLocationBox->setCurrentText(QString::fromStdString(location));
}

std::string DesktopGUI::GetRoomPosition() {
    return roomPositionBox->currentText().toStdString();
}

void DesktopGUI::SetRoomPosition(const std::string &position) {
    roomPositionBox->setCurrentText(QString::fromStdString(position));
}

std::vector<std::string> DesktopGUI::GetFacilities() {
    std::vector<std::string> selectedFacilities;
    for (int i = 0; i < facilitiesListWidget->count(); ++i) {
        QListWidgetItem *item = facilitiesListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            selectedFacilities.push_back(item->text().toStdString());
        }
    }
    return selectedFacilities;
}

void DesktopGUI::SetRoomFacilities(const std::vector<std::string> &facilities) {
    for (int i = 0; i < facilitiesListWidget->count(); ++i) {
        QListWidgetItem *item = facilitiesListWidget->item(i);
        if (std::find(facilities.begin(), facilities.end(), item->text().toStdString()) != facilities.end()) {
            item->setCheckState(Qt::Checked);
        } else {
            item->setCheckState(Qt::Unchecked);
        }
    }
}

std::string DesktopGUI::GetHotelName() {
    return hotelNameBox->currentText().toStdString();
}

void DesktopGUI::SetHotelName(const std::string &hotel_name) {
    hotelNameBox->setCurrentText(QString::fromStdString(hotel_name));
}

// Function to populate dropdowns dynamically using RoomTable's ListRooms()
void DesktopGUI::populateRoomData() {
    std::vector<Room> rooms = roomTable.ListRooms();

    qDebug() << "Populating room data. Number of rooms:" << rooms.size();

    for (const Room &room : rooms) {
        roomAvailabilityBox->addItem(room.GetAvailability() ? "Available" : "Not Available");
        roomPriceBox->addItem(QString::number(room.GetPrice()));
        roomLocationBox->addItem(QString::fromStdString(room.GetLocation()));
        roomPositionBox->addItem(QString::fromStdString(room.GetPosition()));
        hotelNameBox->addItem(QString::fromStdString(room.GetHotelName()));

        qDebug() << "Added room:" << QString::fromStdString(room.GetHotelName());
    }
}

// Function to populate facilities list widget
void DesktopGUI::populateFacilities() {
    std::vector<Room> rooms = roomTable.ListRooms();

    std::set<std::string> uniqueFacilities;

    for (const Room &room : rooms) {
        std::vector<std::string> facilities = room.GetFacilities();
        uniqueFacilities.insert(facilities.begin(), facilities.end());
    }

    facilitiesListWidget->clear();
    for (const std::string &facility : uniqueFacilities) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(facility), facilitiesListWidget);
        item->setCheckState(Qt::Unchecked);

        qDebug() << "Added facility:" << QString::fromStdString(facility);
    }
}

// Slot for printing available rooms
void DesktopGUI::onPrintAvailableRoomsClicked() {
    // Delegate to ClientPresenter
    presenter->handlePrintAvailableRooms(hotelNameBox->currentText().toStdString());
}

// Slot for filtering rooms
void DesktopGUI::onFilterRoomsClicked() {
    // Get filter criteria from dropdowns
    double price = roomPriceBox->currentText().toDouble();
    std::string location = roomLocationBox->currentText().toStdString();
    std::string position = roomPositionBox->currentText().toStdString();
    bool availability = (roomAvailabilityBox->currentText() == "Available");

    // Get selected facilities
    std::vector<std::string> selectedFacilities;
    for (int i = 0; i < facilitiesListWidget->count(); ++i) {
        QListWidgetItem *item = facilitiesListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            selectedFacilities.push_back(item->text().toStdString());
        }
    }

    // Delegate to ClientPresenter
    presenter->handleFilterRooms(price, location, position, availability, selectedFacilities);
}

void DesktopGUI::onNextButtonClicked() {
    if (currentPage < currentRooms.size() - 1) {
        currentPage++;
        displayRoomDetails(currentPage);
    }
}

void DesktopGUI::onPrevButtonClicked() {
    if (currentPage > 0) {
        currentPage--;
        displayRoomDetails(currentPage);
    }
}

void DesktopGUI::setCurrentRooms(const std::vector<Room> &rooms) {
    currentRooms = rooms;
}

void DesktopGUI::displayRoomDetails(int index) {
    if (index < 0 || index >= currentRooms.size()) return;

    const Room &room = currentRooms[index];
    qDebug() << "Displaying room details for index:" << index;
    qDebug() << "Hotel Name:" << QString::fromStdString(room.GetHotelName());
    qDebug() << "Room Number:" << room.GetNumber();
    qDebug() << "Price:" << room.GetPrice();
    qDebug() << "Location:" << QString::fromStdString(room.GetLocation());
    qDebug() << "Position:" << QString::fromStdString(room.GetPosition());

    hotelNameField->setText(QString::fromStdString(room.GetHotelName()));
    roomNumberField->setText(QString::number(room.GetNumber()));
    priceField->setText(QString::number(room.GetPrice()));
    locationField->setText(QString::fromStdString(room.GetLocation()));
    positionField->setText(QString::fromStdString(room.GetPosition()));

    std::vector<std::string> facilities = room.GetFacilities();
    QString facilitiesText = QString::fromStdString(
        std::accumulate(facilities.begin(), facilities.end(), std::string(),
                        [](const std::string &a, const std::string &b) {
                            return a.empty() ? b : a + ", " + b;
                        }));
    facilitiesField->setText(facilitiesText);

    qDebug() << "Facilities:" << facilitiesText;
}

// Main entry point
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    // Create and show the main window
    DesktopGUI mainWindow(nullptr);
    mainWindow.setWindowTitle("Desktop Client Application");
    mainWindow.resize(400, 500);
    mainWindow.show();

    // Execute the application
    return app.exec();
}

////////////////////////////////////////////////////////////////////////////////////


#include "usergui.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QTextEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <set>
#include <iostream>
#include "userpresenter.h"

// Constructor
UserGUI::UserGUI(QWidget *parent)
    : QWidget(parent),
      usernameLabel(new QLabel("Username:", this)),
      userPasswordLabel(new QLabel("Password:", this)),
      usernameField(new QLineEdit(this)),
      userPasswordField(new QLineEdit(this)),
      loginButton(new QPushButton("Login", this)),
      createRoomButton(new QPushButton("Create Room", this)),
      readRoomButton(new QPushButton("Read Room", this)),
      updateRoomButton(new QPushButton("Update Room", this)),
      deleteRoomButton(new QPushButton("Delete Room", this)),
      logoutButton(new QPushButton("Logout", this)),
      roomId(0),
      roomNumber(0),
      roomAvailability(false),
      roomPrice(0.0) {
    // Set up layout
    QGridLayout *layout = new QGridLayout(this);

    // Add widgets to layout
    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameField, 0, 1);
    layout->addWidget(userPasswordLabel, 1, 0);
    layout->addWidget(userPasswordField, 1, 1);
    userPasswordField->setEchoMode(QLineEdit::Password);

    layout->addWidget(loginButton, 2, 0, 1, 2);
    layout->addWidget(createRoomButton, 3, 0, 1, 2);
    layout->addWidget(readRoomButton, 4, 0, 1, 2);
    layout->addWidget(updateRoomButton, 5, 0, 1, 2);
    layout->addWidget(deleteRoomButton, 6, 0, 1, 2);
    layout->addWidget(logoutButton, 7, 0, 1, 2);

    // Initially hide buttons for logged-in actions
    createRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);

    // Connect signals to slots
    connect(loginButton, &QPushButton::clicked, this, &UserGUI::onLogInClicked);
    connect(logoutButton, &QPushButton::clicked, this, &UserGUI::onLogOutClicked);
}

// Room-related methods
int UserGUI::GetRoomId() const {
    return roomId;
}

void UserGUI::SetRoomId(int id) {
    roomId = id;
}

int UserGUI::GetRoomNumber() const {
    return roomNumber;
}

void UserGUI::SetRoomNumber(int number) {
    roomNumber = number;
}

bool UserGUI::GetRoomAvailability() const {
    return roomAvailability;
}

void UserGUI::SetRoomAvailability(bool availability) {
    roomAvailability = availability;
}

double UserGUI::GetRoomPrice() const {
    return roomPrice;
}

void UserGUI::SetRoomPrice(double price) {
    roomPrice = price;
}

std::string UserGUI::GetRoomLocation() const {
    return roomLocation;
}

void UserGUI::SetRoomLocation(const std::string &location) {
    roomLocation = location;
}

std::string UserGUI::GetRoomPosition() const {
    return roomPosition;
}

void UserGUI::SetRoomPosition(const std::string &position) {
    roomPosition = position;
}

std::vector<std::string> UserGUI::GetFacilities() const {
    return facilities;
}

void UserGUI::SetRoomFacilities(const std::vector<std::string> &facilities) {
    this->facilities = facilities;
}

std::string UserGUI::GetHotelName() const {
    return hotelName;
}

void UserGUI::SetHotelName(const std::string &hotel_name) {
    hotelName = hotel_name;
}

// Handle login
void UserGUI::onLogInClicked() {
    std::string username = usernameField->text().toStdString();
    std::string password = userPasswordField->text().toStdString();

    // Simulate login validation
    if (username == "admin" && password == "password") {
        QMessageBox::information(this, "Login", "Login successful!");
        loginButton->setVisible(false);
        createRoomButton->setVisible(true);
        readRoomButton->setVisible(true);
        updateRoomButton->setVisible(true);
        deleteRoomButton->setVisible(true);
        logoutButton->setVisible(true);
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid username or password.");
    }
}

// Handle logout
void UserGUI::onLogOutClicked() {
    QMessageBox::information(this, "Logout", "Logged out successfully!");
    loginButton->setVisible(true);
    createRoomButton->setVisible(false);
    readRoomButton->setVisible(false);
    updateRoomButton->setVisible(false);
    deleteRoomButton->setVisible(false);
    logoutButton->setVisible(false);
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    UserGUI userWindow(nullptr);
    userWindow.setWindowTitle("User Management");
    userWindow.resize(400, 300);
    userWindow.show();

    return app.exec();
}