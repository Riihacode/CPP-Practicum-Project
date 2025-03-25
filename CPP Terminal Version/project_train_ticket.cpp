#include <iostream>
#include <string>

using namespace std;

bool seatsEachPortal[3][10];

struct Passenger {
    string 
        name,
        nik,
        address;
};

struct TicketInfo{
    string 
        departureCity,
        destinationCity,
        trainClass;
    int 
        coachNumber,
        seatNumber;
    string travelDate;
};

struct PaymentInfo {
    string paymentMethod;
    bool isPaid;
    int totalPrice;
};

struct Booking {
    Passenger passenger;
    TicketInfo ticket;
    PaymentInfo payment;
};

Booking bookings[30];

string departuresCity[] = {
    "Yogyakarta", 
    "Sleman", 
    "Gunung Kidul", 
    "Bantul", 
    "Kulon Progo"
};

string destinationsCity[] = {
    "Magelang", 
    "Semarang", 
    "Jepara", 
    "Cilacap", 
    "Boyolali"
};

string trainClass[] = {
    "Ekonomi", 
    "Bisnis", 
    "Eksekutif"
};

string paymentMethods[] = {
    "Transfer", "E-Wallet", "Cash"
};

int indexDeparture = 0;
                            
int main() {
    int chooseMenu;

    do {   
        cout << "=================== MAIN MENU ================"<< endl;
        cout << "1. Book your ticket"                           << endl;
        cout << "2. Show your ticket information"               << endl;
        cout << "3. Exit"                                       <<endl;
        cout << "=============================================="<< endl;
        cout << "Choose your option : ";
        cin >> chooseMenu;
        cout << endl;

        switch (chooseMenu) {
            case 1: {
                if (indexDeparture >= 30) {
                    cout << "Semua kursi telah dipesan!" << endl;
                    break;
                }

                int chooseDepartureCity, chooseDestinationCity, chooseTrainClass, choosePayment;
                int coachNumber, seatNumber;

                cout << "=================== INPUT PERSONAL DATA ================"<<endl;
                cout << "Name       : ";
                cin.ignore();
                getline(cin, bookings[indexDeparture].passenger.name);
                cout << "NIK        : ";
                getline(cin, bookings[indexDeparture].passenger.nik);
                cout << "Address    : ";
                getline(cin, bookings[indexDeparture].passenger.address);
                cout << "========================================================" << endl << endl;
                


                cout << "=================== DEPARTURE CITY MENU ================" << endl;
                for (int i = 0; i < 5; i++) {
                    cout << i + 1 << ". " << departuresCity[i] <<endl;
                }
                cout << "========================================================" << endl;
                cout << "Choose your option: ";
                cin >> chooseDepartureCity;
                bookings[indexDeparture].ticket.departureCity;


                cout << "\n================== DESTINATION CITY MENU ===============" << endl;
                for (int i = 0; i < 5; i++) {
                    cout << i + 1 << ". " << destinationsCity[i] <<endl;
                }
                cout << "========================================================" << endl;
                cout << "Choose your option: ";
                cin >> chooseDestinationCity;
                bookings[indexDeparture].ticket.destinationCity;


                cout << "\n==================== TRAIN CLASS MENU ==================" << endl;
                for (int i = 0; i < 3; i++) {
                    cout << i + 1 << ". " << trainClass[i] <<endl;
                }
                cout << "========================================================" << endl;
                cout << "Choose your option: ";
                cin >> chooseTrainClass;
                bookings[indexDeparture].ticket.trainClass;


                // Menampilkan kursi kosong
                cout << "\n==================== AVAILABLE SEAT ==================" << endl;
                for (int i = 0; i < 3; i++) {
                    cout << "Coach Train-" << i + 1 << " =" << endl;
                    for (int j = 0; j < 10; j++) {
                        if (seatsEachPortal[i][j] != false) {
                            cout << "   [X]" << " ";
                        } else {
                            cout << "   [" << to_string(j + 1) << "]";
                        }
         
                    }
                    cout << endl;
                }
                cout << "========================================================" << endl;


                cout << "\n===================== CHOOSE SEAT ===================" << endl;
                cout << "Choose Coach Train (1 - 3)     : ";
                cin >> coachNumber; coachNumber -= 1;
                cout << "Choose Seat Number (1 - 10)    : ";
                cin >> seatNumber;  seatNumber  -= 1;

                if (seatsEachPortal[coachNumber][seatNumber]) {
                    cout << "The Seat Number already been booked!";
                    break;
                }

                seatsEachPortal[coachNumber][seatNumber]    = true;
                bookings[indexDeparture].ticket.coachNumber = coachNumber;
                bookings[indexDeparture].ticket.seatNumber  = seatNumber;
                bookings[indexDeparture].ticket.travelDate  = "2025-04-01";  // Fixed dulu
                cout << "======================================================" << endl;



                cout << "\n=================== PAYMENT METHOD =================" << endl;
                for (int i = 0; i < 3; i++) {
                    cout << i + 1 << ". " << paymentMethods[i] << endl;
                }
                cout << "===================================================="<< endl;
                cout << "Choose your option: ";
                cin >> choosePayment;
                bookings[indexDeparture].payment.paymentMethod  = paymentMethods[choosePayment - 1];
                bookings[indexDeparture].payment.isPaid         = true;
                bookings[indexDeparture].payment.totalPrice     = 100000;   // isi flat dulu


                cout << "Your ticket booking was successful!" << endl;
                indexDeparture++;

                break;
            }
                
            case 2: {
                
                break;
            }

            case 3: {
                cout << "Thank you!";
                break;
            }
            
            default: {
                cout << "Invalid Option!"<<endl;
                break;
            }
        }

    } while (chooseMenu != 3);
}