#include "HotelBookingSystem.h"
// ����������� ���������� ����
int BookingRequest::totalBookings = 0;

BookingRequest::BookingRequest() : clientName(""), roomCapacity(0), roomClass(""),
stayDuration(0), isConfirmed(false), prepayment(0.0), totalCost(0.0)/*, bookingID(0),
bookedRoom(*(new Room(0, "", 0)))*/ {
    incrementBookings();
}
// ������������ �� ������ BookingRequest
BookingRequest::BookingRequest(string clientName, int roomCapacity, string roomClass, int stayDuration, double totalCost/*, int id, const Room& room*/)
    : clientName(clientName), roomCapacity(roomCapacity), roomClass(roomClass), stayDuration(stayDuration),
    isConfirmed(false), prepayment(0.0), totalCost(totalCost) {
    incrementBookings();
}

// ����������� ��������� ��� BookingRequest
BookingRequest::BookingRequest(const BookingRequest& other) : clientName(other.clientName), roomCapacity(other.roomCapacity), roomClass(other.roomClass),
stayDuration(other.stayDuration), isConfirmed(other.isConfirmed), prepayment(other.prepayment), totalCost(other.totalCost),
additionalServices(other.additionalServices)/*, bookingID(other.bookingID),
bookedRoom(other.bookedRoom)*/ {}  // ��������� ������� ������

//BookingRequest::BookingRequest(int id, const Room& room) : bookingID(id), bookedRoom(room) {}


// ���������� ����� BookingRequest, ���� ������� ��'��� clientName
BookingRequest::~BookingRequest() {
    cout << "Client " << clientName << " destructor" << endl;
}

int BookingRequest::getTotalBookings() {
    return totalBookings;
}

void BookingRequest::incrementBookings() {
    totalBookings++;
}

string BookingRequest::getClientName() const {
    return clientName;
}
int BookingRequest::getRoomCapacity() const {
    return roomCapacity;
}
string BookingRequest::getRoomClass() const {
    return roomClass;
}
int BookingRequest::getStayDuration() const {
    return stayDuration;
}
double BookingRequest::getPrepayment() const {
    return prepayment;
}
double BookingRequest::getTotalCost() const {
    return totalCost;
}
bool BookingRequest::getIsConfirmed() const {
    return isConfirmed;
}

//int BookingRequest::getBookingID() const {
//    return bookingID;
//}
//const Room& BookingRequest::getBookedRoom() const {
//    return bookedRoom;
//}
void BookingRequest::confirmBooking() {
    isConfirmed = true;
}
void BookingRequest::cancelBooking() {
    isConfirmed = false;
}

void BookingRequest::setPrepayment(double amount) {
    if (amount <= totalCost) {
        prepayment = amount;
    }
}

void BookingRequest::addService(const Service& service) {
    additionalServices.push_back(service);
    totalCost += service.getPrice();
}

void BookingRequest::displayBookingInfo() const {
    cout << "Client: " << clientName << endl;
    cout << "Room Capacity: " << roomCapacity << ", Class: " << roomClass << endl;
    cout << "Stay Duration: " << stayDuration << " nights" << endl;
    cout << "Total Cost: $" << totalCost << ", Prepayment: $" << prepayment << endl;
    cout << "Confirmed: " << (isConfirmed ? "Yes" : "No") << endl;

    if (!additionalServices.empty()) {
        cout << "\n Additional Services: " << endl;
        for (const auto& service : additionalServices) {
            cout << " - " << service.getServiceName() << " ($" << service.getPrice() << ")" << endl;
        }
    }
    cout << endl;
}
// ����� ��� ��������� ���� �� ����������.
void displayBookingSummary(const BookingRequest& booking) {
    cout << "Booking Summary:" << endl;
    cout << "Client Name: " << booking.getClientName() << endl;
    cout << "Room Capacity: " << booking.getRoomCapacity() << endl;
    cout << "Room Class: " << booking.getRoomClass() << endl;
    cout << "Stay Duration: " << booking.getStayDuration() << " nights" << endl;
    cout << "Total Cost: $" << booking.getTotalCost() << endl;
    cout << "Prepayment: $" << booking.getPrepayment() << endl;

    double remainingAmount = booking.getTotalCost() - booking.getPrepayment();
    cout << "Remaining Amount: $" << remainingAmount << endl;

    cout << "Booking Confirmed: " << (booking.getIsConfirmed() ? "Yes" : "No") << endl;
    cout << endl;
}
// ��� � �����, ��� ��� ��������� ���� � �������
void displayBookingSummary(const BookingRequest& booking, double discountRate) {
    cout << "Booking Summary with Discount:" << endl;
    cout << "Client Name: " << booking.getClientName() << endl;
    cout << "Room Capacity: " << booking.getRoomCapacity() << endl;
    cout << "Room Class: " << booking.getRoomClass() << endl;
    cout << "Stay Duration: " << booking.getStayDuration() << " nights" << endl;

    double discountedCost = booking.getTotalCost() * (1 - discountRate);
    cout << "Original Total Cost: $" << booking.getTotalCost() << endl;
    cout << "Discount Rate: " << discountRate * 100 << "%" << endl;
    cout << "Discounted Total Cost: $" << discountedCost << endl;
    cout << "Prepayment: $" << booking.getPrepayment() << endl;

    double remainingAmount = discountedCost - booking.getPrepayment();
    cout << "Remaining Amount after Discount: $" << remainingAmount << endl;

    cout << "Booking Confirmed: " << (booking.getIsConfirmed() ? "Yes" : "No") << endl;
    cout << endl;
}

string BookingRequest::toFileFormat() const {
    string result = clientName + "," + to_string(roomCapacity) + "," + roomClass + "," +
        to_string(stayDuration) + "," + to_string(totalCost) + "," +
        to_string(prepayment) + "," + (isConfirmed ? "Confirmed" : "Not Confirmed");
    for (const auto& service : additionalServices) {
        result += "," + service.getServiceName() + "($" + to_string(service.getPrice()) + ")";
    }
    return result;
}

void BookingRequest::loadClientsFromFile(BookingRequest clients[], int n, const string& filename) {
    ifstream readFile(filename);
    if (readFile.fail()) {
        cerr << "������� �������� �����!" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        string clientName;
        int roomCapacity;
        string roomClass;
        int stayDuration;
        double totalCost;
        //int bookingID; // ������� ID ����������
        //Room; room; // ����� �� ���������� ��'��� Room, �� �� ���� ���������

        if (readFile >> clientName >> roomCapacity >> roomClass >> stayDuration >> totalCost) {
            clients[i] = BookingRequest(clientName, roomCapacity, roomClass, stayDuration, totalCost);
        }
    }

    readFile.close();
}

// ������������ �� ������ Service
Service::Service() :serviceName(""), price(0.0) {}
Service::Service(string serviceName, double price) : serviceName(serviceName), price(price) {}
// ���������� ����� Service
Service::~Service() {
    //cout << "Services destructor" << endl;
}
// ����������� ��������� ��� Service
Service::Service(const Service& other) : serviceName(other.serviceName), price(other.price) {}

string Service::getServiceName() const {
    return serviceName;
}
double Service::getPrice() const {
    return price;
}
// ����� ��� ��������� ���� (�����) �������
string Service::getServiceType() const {
    return serviceName; // ������� ����� �������
}

//Room::Room() :roomCapacity(0), roomClass(""), pricePerNight(0.0), isAvailable(false) {}
// ������������ �� ������ Room
Room::Room(int roomCapacity, string roomClass, double pricePerNight) : roomCapacity(roomCapacity), roomClass(roomClass), pricePerNight(pricePerNight), isAvailable(true) {}
// ����������� ��������� ��� Room
Room::Room(const Room& other) : roomCapacity(other.roomCapacity), roomClass(other.roomClass),
pricePerNight(other.pricePerNight), isAvailable(other.isAvailable) {}

// ���������� ����� Room
Room::~Room() {
    /*  cout << "Rooms destructor" << endl;*/
}

bool Room::checkAvailability() const {
    return isAvailable;
}

double Room::calculateCost(int nights) const {
    return nights * pricePerNight;
}

void Room::bookRoom() {
    isAvailable = false;
}

void Room::releaseRoom() {
    isAvailable = true;
}

void Room::displayRoomInfo() const {
    cout << "Room Capacity: " << roomCapacity << ", Class: " << roomClass << endl;
    cout << "Price per Night: $" << pricePerNight << endl;
    cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
    cout << endl;
}

Room createDeluxeRoom() {
    // ��������� ��'���� Room � ����������� Deluxe
    Room deluxeRoom(2, "Deluxe", 100.0); // ̳������: 2 ������, ����: Deluxe, ���� �� ��: 100.0

    // ������������ ������ ����� ��� ���������� ������
    deluxeRoom.bookRoom();
    deluxeRoom.displayRoomInfo();

    // ��������� ��'��� Room
    return deluxeRoom;
}


Customer::Customer(string name, string contactInfo) : name(name), contactInfo(contactInfo) {}

void Customer::displayCustomerInfo() const {
    cout << "Customer Name: " << name << ", Contact Info: " << contactInfo << endl;
}

Hotel::Hotel(string hotelName) : hotelName(hotelName) {}

void Hotel::addRoom(const Room& room) {
    rooms.push_back(room);
}

void Hotel::displayRooms() const {
    cout << "Rooms in " << hotelName << ":" << endl;
    for (const auto& room : rooms) {
        room.displayRoomInfo();
    }
}

Booking::Booking(const BookingRequest& bookingRequest, const Room& room)
    : bookingRequest(bookingRequest), room(room) {}

void Booking::addService(const Service& service) {
    services.push_back(service);
}

void Booking::displayBookingDetails() const {
    bookingRequest.displayBookingInfo();
    room.displayRoomInfo();
    cout << "Services: " << endl;
    for (const auto& service : services) {
        cout << " - " << service.getServiceName() << " ($" << service.getPrice() << ")" << endl;
    }
}