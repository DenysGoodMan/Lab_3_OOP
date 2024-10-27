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

// ����� �� ����������
class BookingRequest {
private:
    string clientName;
    int roomCapacity; // ʳ������ ���� � �����
    string roomClass; // ���� ������
    int stayDuration; // ���������� �����������
    bool isConfirmed; // ϳ����������� ����������
    double prepayment; // �����������
    double totalCost; // �������� �������
    vector<Service> additionalServices; // �������� �������

    static int totalBookings;
    //const int bookingID;         // ���������� ���� ��� ID ����������
    ////static Room defaultRoom;   // ��������� ��'��� Room �� �������������
    //const Room& bookedRoom;      // ����-��������� �� ��'��� Room


public:
    BookingRequest(); // ����������� ��� ���������
    BookingRequest(string clientName, int roomCapacity, string roomClass, int stayDuration, double totalCost/*, int id, const Room& room*/); // ����������� � �����������
    BookingRequest(const BookingRequest& other); // ����������� ���������
    /* BookingRequest(int id, const Room& room);*/
    ~BookingRequest();

    string getClientName() const;
    int getRoomCapacity() const;
    string getRoomClass() const;
    int getStayDuration() const;
    double getPrepayment() const;
    double getTotalCost() const;
    bool  getIsConfirmed() const;

    static int getTotalBookings(); // ��������� ����� ��� ��������� ������� ���������
    static void incrementBookings(); // ��������� ����� ��� ��������� ������� ���������



    //int getBookingID() const;             // ������ ��� bookingID
    //const Room& getBookedRoom() const;    // ������ ��� bookedRoom

    void confirmBooking(); // ϳ��������� ����������
    void cancelBooking(); // ³������� ����������
    void setPrepayment(double amount); // ���������� ����������
    void addService(const Service& service); // ������ �������
    void displayBookingInfo() const; // ³���������� ���������� ��� ����������
    string toFileFormat() const;  // ����� ����� ��� ������������ ���������� � ������ �����

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
    Service(const Service& other);  // ����������� ���������
    ~Service();

    string getServiceName() const; // �������� ��'� �������
    double getPrice() const; // �������� ���� ������� 
    string getServiceType() const;  // ����� ��� ��������� ���� (�����) �������
};

class Room {
private:
    int roomCapacity; // ̳������ ������
    string roomClass; // ���� ������
    double pricePerNight; // ֳ�� �� ����
    bool isAvailable; // �����, ���� ������ �� � � �������� ���� ������

public:
    /*  Room();*/
    Room(int roomCapacity, string roomClass, double pricePerNight);
    Room(const Room& other);  // ����������� ���������
    ~Room();
    bool checkAvailability() const; // ��������� ��������
    double calculateCost(int nights) const; // ���������� �������
    void bookRoom(); // 
    void releaseRoom();
    void displayRoomInfo() const; // ����� ��� ����������� ���������� ��� ������
};
Room createDeluxeRoom();  // �������, ��� ������� � ������� ��'��� Room
void displayBookingSummary(const BookingRequest& booking);

// ������ ������
void displayBookingSummary(const BookingRequest& booking, double discountRate);  // ��������������





// 1. ����������
class Customer {
private:
    string name;
    string contactInfo;

public:
    Customer(string name, string contactInfo);
    void displayCustomerInfo() const;
};

// 2. ���������
class Hotel {
private:
    string hotelName;
    vector<Room> rooms; // ���������: Hotel �� Rooms

public:
    Hotel(string hotelName);
    void addRoom(const Room& room);
    void displayRooms() const;
};

// 3. ����������
class Booking {
private:
    BookingRequest bookingRequest; // ����������: Booking ������ BookingRequest
    Room room;
    vector<Service> services;

public:
    Booking(const BookingRequest& bookingRequest, const Room& room);
    void addService(const Service& service);
    void displayBookingDetails() const;
};

#endif // HOTELBOOKINGSYSTEM_H