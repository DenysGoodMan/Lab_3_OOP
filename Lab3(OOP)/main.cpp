#include "HotelBookingSystem.h"
#include <iostream>

void saveClientsToFile(const BookingRequest clients[], int size, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < size; i++) {
            outFile << clients[i].toFileFormat() << endl;
        }
        outFile.close();
        cout << "\n Clients saved to " << filename << "\n" << endl;
    }
    else {
        cerr << "Unable to open file " << filename << endl;
    }
}

int main() {
    // Створення об'єкта послуги
    Service breakfast("Breakfast in room", 15.0);
    // Отримання інформації про послугу
    cout << "Service Name: " << breakfast.getServiceName() << endl;
    cout << "Service Price: $" << breakfast.getPrice() << endl;
    cout << "Service Type: " << breakfast.getServiceType() << "\n" << endl;
    cout << "\n********************************" << endl;
    cout << "************11,12,13************" << endl;
    // Створення об'єктів Customer
    Customer customer("John Doe", "john@example.com");
    customer.displayCustomerInfo();

    // Створення об'єктів Room
    Room rooms1(2, "Standard", 50.0);
    Room rooms2(3, "Deluxe", 80.0);

    // Створення об'єкта Hotel та додавання кімнат
    Hotel hotel("Grand Hotel");
    hotel.addRoom(rooms1);
    hotel.addRoom(rooms2);
    hotel.displayRooms();

    // Створення запиту на бронювання
    BookingRequest bookingRequest("John Doe", 2, "Standard", 3, rooms1.calculateCost(3));
    Booking booking(bookingRequest, rooms1);

    // Додавання послуг до бронювання
    Service breakfast_t("Breakfast", 15.0);
    Service transfer_r("Airport Transfer", 30.0);

    booking.addService(breakfast_t);
    booking.addService(transfer_r);

    // Виведення деталей бронювання
    booking.displayBookingDetails();
    cout << "********************************\n" << endl;



    // Створюємо і повертаємо об'єкт Room за допомогою функції createDeluxeRoom
    Room myRoom = createDeluxeRoom();
    // Додатково викликаємо метод для перевірки
    if (!myRoom.checkAvailability()) {
        cout << "The room has been booked successfully" << endl;
    }
    cout << "\n---------Simple method---------" << endl;
    // 1. Простий спосіб
    Room simpleRoom(2, "Standard", 50.0);  // Просте створення об'єкта
    simpleRoom.displayRoomInfo();
    cout << "---------Explicit method---------" << endl;
    // 2. Явний спосіб
    Room explicitRoom = Room(3, "Deluxe", 80.0);  // Явний виклик конструктора
    explicitRoom.displayRoomInfo();
    cout << "---------Shorted method---------" << endl;
    // 3. Скорочений спосіб
    Room shortRoom{ 4, "Suite", 120.0 };  // Список ініціалізації
    shortRoom.displayRoomInfo();

    cout << "\n\n *|___System Hotel___|*" << endl;
    // Додаємо інформацію про кімнати
    Room room1(2, "Standard", 50.0);
    Room room2(3, "Deluxe", 80.0);
    Room room3(4, "Suite", 120.0);

    Service* services = new Service[5];
    services[0] = Service("Breakfast in room", 15.0);
    services[1] = Service("Transfer", 30.0);
    services[2] = Service("Pool Access", 20.0);
    services[3] = Service("Spa Treatment", 50.0);
    services[4] = Service("Dinner Package", 40.0);


    // Створюємо масив із 5 клієнтів
    BookingRequest static  clients[5] = {
        BookingRequest("Alice Smith", 2, "Standard", 3, room1.calculateCost(3)),
        BookingRequest("Bob Johnson", 3, "Deluxe", 4, room2.calculateCost(4)),
        BookingRequest("Charlie Brown", 2, "Standard", 2, room1.calculateCost(2)),
        BookingRequest("David Williams", 4, "Suite", 1, room3.calculateCost(1)),
        BookingRequest("Eve Miller", 3, "Deluxe", 5, room2.calculateCost(5))
    };
    //  Вивід загальної кількості бронювань
    cout << "------------------" << endl;
    cout << "Total Bookings: " << BookingRequest::getTotalBookings() << endl;
    cout << "------------------" << endl;
    // Виведіть підсумки бронювань
    for (int i = 0; i < 5; i++) {
        displayBookingSummary(clients[i]);
    }
    // Виклик перевантаженої функції з коефіцієнтом знижки
    for (int i = 0; i < 5; i++) {
        displayBookingSummary(clients[i], 0.15); // Наприклад, 15% знижка
    }
    // Копіюємо один з елементів масиву 
    BookingRequest copiedClient = clients[0];
    // Виводимо інформацію про оригінальний та скопійований запитити на бронювання
    cout << "__________________________________" << endl;
    cout << "Original Booking:" << endl;
    clients[0].displayBookingInfo();
    cout << "\nCopied Booking:" << endl;
    copiedClient.displayBookingInfo();
    cout << "__________________________________\n\n" << endl;



    // Виведення інформації про кожного клієнта до підтвердження бронювання
    cout << "Booking Requests Before Confirmation:\n" << endl;
    for (int i = 0; i < 5; i++) {
        clients[i].displayBookingInfo();
    }
    cout << endl;
    // Випадкове додавання послуг для кожного клієнта
    for (int i = 0; i < 5; i++) {
        int randomServiceCount = rand() % 5; // Випадкове число від 0 до 2 (кількість послуг для клієнта)

        if (randomServiceCount > 0) clients[i].addService(services[0]); // Додаємо breakfast, якщо > 0
        if (randomServiceCount > 1) clients[i].addService(services[1]); // Додаємо transfer, якщо > 1
        if (randomServiceCount > 3) clients[i].addService(services[3]); // Додаємо Spa Treatment якщо > 3
        if (randomServiceCount > 1) clients[i].addService(services[4]); // Додаємо Dinner Package якщо > 1
        if (rand() % 2 == 0) clients[i].addService(services[2]);        // Додаємо poolAccess випадково (50% шанс)
    }


    // Підтвердження бронювання для всіх клієнтів та виведення інформації після підтвердження
    cout << "Booking Requests After Confirmation:" << endl;
    for (int i = 0; i < 5; i++) {
        clients[i].confirmBooking();
    }

    // Збереження інформації у файл
    saveClientsToFile(clients, 5, "clients.txt");

    // Завантаження клієнтів з файлу та виведення інформації
    cout << "Loaded Booking Requests:" << endl;
    BookingRequest::loadClientsFromFile(clients, 5, "clients.txt");
    for (int i = 0; i < 5; i++) {
        clients[i].displayBookingInfo();
    }

    // Звільнення пам'яті
    delete[] services;

    return 0;
}
