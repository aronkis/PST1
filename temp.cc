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