#ifndef MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H
#define MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>  // untuk rand()
#include <ctime>    // untuk time()

const int portalClass = 3;
const int portalClassSeat = 10;

// Struktur dan konstanta eksternal
//extern const int portalClass;
//extern const int portalClassSeat;

struct Passenger {
    std::string name, nik, address;
};

struct TicketInfo {
    std::string departureCity, destinationCity;
    int coachNumber, seatNumber;
    std::string travelDate;
};

struct PaymentInfo {
    std::string paymentMethod;
    bool isPaid;
    int totalPrice;
};

struct Booking {
    Passenger passenger;
    TicketInfo ticket;
    PaymentInfo payment;
};

extern Booking bookings[30];
extern std::string departuresCity[];
extern std::string destinationsCity[];
extern std::string paymentMethods[];
//extern bool seatsEachPortal[3][10];
extern bool seatsEachPortal[portalClass][portalClassSeat];
extern int indexDeparture;

// Fungsi-fungsi
std::string autoBookTicket();
std::string manualInput(std::istream &in = std::cin);
std::string searchByNIK();
std::string seqNonSentinelNotYetSorted(std::string *nikPointer);
std::string seqSentinelNotYetSorted(std::string *nikPointer);
std::string binarySearch(Booking *copyBinary, std::string *nikPointer);
std::string sortingOutputShow(Booking *sortingShow);
std::string fileOperationSave(Booking bookings[], int totalData);
std::string fileOperationSaveSingle(Booking bookings[], int totalData, const std::string &targetNIK);
std::string fileOperationSaveTo(const std::string& path);

// Sorting
void bubbleSortByNik(Booking *copyBubleNik);
void bubbleSort(Booking *copyBubble);
void straightInsertionSort(Booking *copyInsertion);
void selectionSort(Booking *copySelection);
void shellSort(Booking *copyShell);
void quickSort(Booking *bookingsQuick, int first, int last);


#endif //MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H
