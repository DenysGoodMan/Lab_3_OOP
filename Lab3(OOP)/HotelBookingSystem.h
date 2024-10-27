#pragma once
#ifndef HOTELBOOKINGSYSTEM_H
#define HOTELBOOKINGSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Room;
class Service;

// Запит на бронювання
class BookingRequest {
private:
    string clientName;
    int roomCapacity; // Кількість місць у кімнаті
    string roomClass; // Клас кімнати
    int stayDuration; // Тривальсть перебування
    bool isConfirmed; // Підтвердження бронювання
    double prepayment; // Передоплата
    double totalCost; // Загальна вартість
    vector<Service> additionalServices; // Додаткові послуги

    static int totalBookings;
    //const int bookingID;         // Константне поле для ID бронювання
    ////static Room defaultRoom;   // Статичний об'єкт Room за замовчуванням
    //const Room& bookedRoom;      // Поле-посилання на об'єкт Room


public:
    BookingRequest(); // Конструктор без параметрів
    BookingRequest(string clientName, int roomCapacity, string roomClass, int stayDuration, double totalCost/*, int id, const Room& room*/); // Конструктор з параметрами
    BookingRequest(const BookingRequest& other); // Конструктор копіювання
    /* BookingRequest(int id, const Room& room);*/
    ~BookingRequest();

    string getClientName() const;
    int getRoomCapacity() const;
    string getRoomClass() const;
    int getStayDuration() const;
    double getPrepayment() const;
    double getTotalCost() const;
    bool  getIsConfirmed() const;

    static int getTotalBookings(); // Статичний метод для отримання кількості бронювань
    static void incrementBookings(); // Статичний метод для збільшення кількості бронювань



    //int getBookingID() const;             // Геттер для bookingID
    //const Room& getBookedRoom() const;    // Геттер для bookedRoom

    void confirmBooking(); // Підтвердити бронювання
    void cancelBooking(); // Відхилити бронювання
    void setPrepayment(double amount); // Встановити предоплату
    void addService(const Service& service); // Додати послугу
    void displayBookingInfo() const; // Відображення інформації про бронювання
    string toFileFormat() const;  // Новий метод для форматування інформації у вигляді рядка

    /* void loadClientsFromFile(BookingRequest clients[], int n, const string& filename);*/
    static void loadClientsFromFile(BookingRequest clients[], int size, const string& filename);
};

class Service {
private:
    string serviceName;
    double price;

public:
    Service();
    Service(string serviceName, double price);
    Service(const Service& other);  // Конструктор копіювання
    ~Service();

    string getServiceName() const; // Отримати ім'я послуги
    double getPrice() const; // Отримати ціну послуги 
    string getServiceType() const;  // Метод для отримання типу (назви) послуги
};

class Room {
private:
    int roomCapacity; // Місткість кімнати
    string roomClass; // Клас кімнати
    double pricePerNight; // Ціна за добу
    bool isAvailable; // Метод, який показує чи є в наявності така кімната

public:
    /*  Room();*/
    Room(int roomCapacity, string roomClass, double pricePerNight);
    Room(const Room& other);  // Конструктор копіювання
    ~Room();
    bool checkAvailability() const; // Перевірити наявність
    double calculateCost(int nights) const; // Розрахунок вартості
    void bookRoom(); // 
    void releaseRoom();
    void displayRoomInfo() const; // Метод для відображення інформації про кімнату
};
Room createDeluxeRoom();  // Функція, яка створює і повертає об'єкт Room
void displayBookingSummary(const BookingRequest& booking);

// Додаємо знижку
void displayBookingSummary(const BookingRequest& booking, double discountRate);  // Перевантаження





// 1. Ассоціація
class Customer {
private:
    string name;
    string contactInfo;

public:
    Customer(string name, string contactInfo);
    void displayCustomerInfo() const;
};

// 2. Агрегація
class Hotel {
private:
    string hotelName;
    vector<Room> rooms; // Агрегація: Hotel має Rooms

public:
    Hotel(string hotelName);
    void addRoom(const Room& room);
    void displayRooms() const;
};

// 3. Композиція
class Booking {
private:
    BookingRequest bookingRequest; // Композиція: Booking містить BookingRequest
    Room room;
    vector<Service> services;

public:
    Booking(const BookingRequest& bookingRequest, const Room& room);
    void addService(const Service& service);
    void displayBookingDetails() const;
};

#endif // HOTELBOOKINGSYSTEM_H