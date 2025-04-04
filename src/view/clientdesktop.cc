#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include "clientdesktop.h"

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

ClientDesktopGIO::ClientDesktopGIO(QWidget *parent)
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
      hotelNameField(new QLineEdit(this)), 
      roomNumberField(new QLineEdit(this)), 
      priceField(new QLineEdit(this)), 
      locationField(new QLineEdit(this)), 
      positionField(new QLineEdit(this)), 
      facilitiesField(new QLineEdit(this)), 
      facilitiesListWidget(new QListWidget(this)),
      database(),
      roomTable(&database),
      presenter(new ClientPresenter(this, &roomTable)),
      currentPage(0)
{
    std::string fileName;
    if (!openFileDlg(fileName)) 
    {
        QMessageBox::critical(this, "Database Error", "No database selected!");
        exit(0);
        return;
    }

    if (!database.OpenConnection(fileName)) 
    {
        QMessageBox::critical(this, "Database Error", "Failed to open the database connection.");
        exit(0);
        return;
    }

    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    QSpacerItem *topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addItem(topSpacer); 
    layout->addWidget(label, 0, Qt::AlignCenter); 
    layout->addItem(bottomSpacer); 

    presenter->populateRoomData();
    presenter->populateFacilities();

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

    layout->addWidget(new QLabel("Facilities:", this));
    layout->addWidget(facilitiesListWidget);

    layout->addWidget(printAvailableButton);
    layout->addWidget(filterRoomsButton);

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

    layout->addWidget(prevButton);
    layout->addWidget(nextButton);

    connect(printAvailableButton, &QPushButton::clicked, this, &ClientDesktopGIO::onPrintAvailableRoomsClicked);
    connect(filterRoomsButton, &QPushButton::clicked, this, &ClientDesktopGIO::onFilterRoomsClicked);
    connect(nextButton, &QPushButton::clicked, this, &ClientDesktopGIO::onNextButtonClicked);
    connect(prevButton, &QPushButton::clicked, this, &ClientDesktopGIO::onPrevButtonClicked);
}

ClientDesktopGIO::~ClientDesktopGIO() 
{
    database.CloseConnection();
}

bool ClientDesktopGIO::GetRoomAvailability() 
{
    return roomAvailabilityBox->currentText() == "Available";
}

void ClientDesktopGIO::SetRoomAvailability(bool availability) 
{
    roomAvailabilityBox->addItem(availability ? "Available" : "Not Available");
}

double ClientDesktopGIO::GetRoomPrice() 
{
    return roomPriceBox->currentText().toDouble();
}

void ClientDesktopGIO::SetRoomPrice(double price) 
{
    roomPriceBox->addItem(QString::number(price));
}

std::string ClientDesktopGIO::GetRoomLocation() 
{
    return roomLocationBox->currentText().toStdString();
}

void ClientDesktopGIO::SetRoomLocation(const std::string &location) 
{
    roomLocationBox->addItem(QString::fromStdString(location));
}

std::string ClientDesktopGIO::GetRoomPosition() 
{
    return roomPositionBox->currentText().toStdString();
}

void ClientDesktopGIO::SetRoomPosition(const std::string &position) 
{
    roomPositionBox->addItem(QString::fromStdString(position));
}

std::vector<std::string> ClientDesktopGIO::GetFacilities() 
{
    std::vector<std::string> selectedFacilities;
    for (int i = 0; i < facilitiesListWidget->count(); ++i) 
    {
        QListWidgetItem *item = facilitiesListWidget->item(i);
        if (item->checkState() == Qt::Checked) 
        {
            selectedFacilities.push_back(item->text().toStdString());
        }
    }
    return selectedFacilities;
}

void ClientDesktopGIO::SetRoomFacilities(const std::vector<std::string> &facilities) 
{
    for (const std::string &facility : facilities) 
    {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(facility), facilitiesListWidget);
        item->setCheckState(Qt::Unchecked);
    }
}

std::string ClientDesktopGIO::GetHotelName() 
{
    return hotelNameBox->currentText().toStdString();
}

void ClientDesktopGIO::SetHotelName(const std::string &hotel_name) 
{
    hotelNameBox->addItem(QString::fromStdString(hotel_name));
}

void ClientDesktopGIO::onPrintAvailableRoomsClicked() 
{
    presenter->handlePrintAvailableRooms(hotelNameBox->currentText().toStdString());
}

void ClientDesktopGIO::onFilterRoomsClicked() 
{
    double price = roomPriceBox->currentText().toDouble();
    std::string location = roomLocationBox->currentText().toStdString();
    std::string position = roomPositionBox->currentText().toStdString();
    bool availability = (roomAvailabilityBox->currentText() == "Available");

    std::vector<std::string> selectedFacilities;
    for (int i = 0; i < facilitiesListWidget->count(); ++i)
     {
        QListWidgetItem *item = facilitiesListWidget->item(i);
        if (item->checkState() == Qt::Checked) 
        {
            selectedFacilities.push_back(item->text().toStdString());
        }
    }

    presenter->handleFilterRooms(price, location, position, availability, selectedFacilities);
}

void ClientDesktopGIO::onNextButtonClicked() 
{
    if (currentPage < currentRooms.size() - 1) 
    {
        currentPage++;
        displayRoomDetails(currentPage);
    }
}

void ClientDesktopGIO::onPrevButtonClicked() 
{
    if (currentPage > 0) 
    {
        currentPage--;
        displayRoomDetails(currentPage);
    }
}

void ClientDesktopGIO::setCurrentRooms(const std::vector<Room> &rooms) 
{
    currentRooms = rooms;
}

void ClientDesktopGIO::displayRoomDetails(int index) 
{
    if (index < 0 || index >= currentRooms.size())
    {
        hotelNameField->setText("N/A");
        roomNumberField->setText("N/A");
        priceField->setText("N/A");
        locationField->setText("N/A");
        positionField->setText("N/A");
        facilitiesField->setText("N/A");
        return; 
    };

    const Room &room = currentRooms[index];
    hotelNameField->setText(QString::fromStdString(room.GetHotelName()));
    roomNumberField->setText(QString::number(room.GetNumber()));
    priceField->setText(QString::number(room.GetPrice()));
    locationField->setText(QString::fromStdString(room.GetLocation()));
    positionField->setText(QString::fromStdString(room.GetPosition()));

    std::vector<std::string> facilities = room.GetFacilities();
    QString facilitiesText = QString::fromStdString(
        std::accumulate(facilities.begin(), facilities.end(), std::string(),
                        [](const std::string &a, const std::string &b) 
                        {
                            return a.empty() ? b : a + ", " + b;
                        }));
    facilitiesField->setText(facilitiesText);
}

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);


    ClientDesktopGIO mainWindow(nullptr);
    mainWindow.setWindowTitle("Desktop Client Application");
    mainWindow.resize(400, 500);
    mainWindow.show();

    return app.exec();
}