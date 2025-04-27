#include <iostream>
#include <string>
#include <cstdlib>  // untuk rand()
#include <ctime>    // untuk time()

using namespace std;

const int portalClass = 3;
const int portalClassSeat = 10;

bool seatsEachPortal[portalClass][portalClassSeat];

struct Passenger {
    string 
        name,
        nik,
        address;
};

struct TicketInfo{
    string 
        departureCity,
        destinationCity;
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

string paymentMethods[] = {
    "Transfer", 
    "E-Wallet", 
    "Cash"
};

int indexDeparture = 0;


//###################
void autoBookTicket();
void manualInput();
void searchByNIK();
void seqNonSentinelNotYetSorted();
void seqSentinelNotYetSorted();
void bubbleSort();
void straightInsertionSort();
void selectionSort();
void shellSort();
void quickSort(Booking bookingsQuick[], int first, int last);
void sortingOutputShow(Booking *sortingShow);

int main() {
    int chooseMenu;

    do {   
        cout << "=================== MAIN MENU ================"<< endl;
        cout << "1. Book your ticket"                           << endl;
        cout << "2. Show your ticket information (Searching)"   << endl;
        cout << "3. Show all ticket information (Sorting)"      << endl;
        cout << "4. Recursive"                                  << endl;
        cout << "5. Exit"                                       << endl;
        cout << "=============================================="<< endl;
        cout << "Choose your option : ";
        cin >> chooseMenu;
        cout << endl;

        switch (chooseMenu) {
            case 1: {
                int chooseMenuInMenu1;

                do {
                    cout << "=================== MAIN MENU ================"<< endl;
                    cout << "1. Generate Data Customer"                     << endl;
                    cout << "2. Manual Input Data Customer"                 << endl;
                    cout << "3. Back to main menu"                          << endl;
                    cout << "=============================================="<< endl;
                    cout << "Choose Your Option: ";
                    cin >> chooseMenuInMenu1;

                    switch (chooseMenuInMenu1){
                        case 1: {   autoBookTicket()    ;break; }
                        case 2: {   manualInput()       ;break; }
                        case 3: {   cout << "Exit..."   ;break; }
                        default:{   cout << "Invalid"   ;break; }
                    }
                } while (chooseMenuInMenu1 != 3);

                break;
            }
                
            case 2: {
                int chooseMenuInMenu2;
                do {
                    cout << "=================== MAIN MENU ================"    << endl;
                    cout << "1. Sequential Non Sentinel Search Not Yet Sorted"  << endl;
                    cout << "2. Sequential Sentinel Search Not Yet Sorted"      << endl;
                    cout << "3. Manual Input Data Customer"                     << endl;
                    cout << "4. Back to main menu"                              << endl;
                    cout << "=============================================="    << endl;
                    cout << "Choose your option: ";
                    cin >> chooseMenuInMenu2;
                    cout << endl;

                    switch(chooseMenuInMenu2) {
                        case 1: {   seqNonSentinelNotYetSorted();   break;  }
                        case 2: {   seqSentinelNotYetSorted();      break;  }
                        case 3: {   break;                                  }
                        case 4: {   cout << "Exit...";              break;  }
                        default:{   break;                                  }
                    }
                } while (chooseMenuInMenu2 != 4);
                break;
            }

            case 3: {
                int chooseMenuInMenu3;
                do {
                    cout << "=================== MAIN MENU ================"    << endl;
                    cout << "1. Bubble Sort"                                    << endl;
                    cout << "2. Straight Insertion Sort"                        << endl;
                    cout << "3. Straight Selection Sort"                        << endl;
                    cout << "4. Shell Sort"                                     << endl;
                    cout << "5. Quick Sort"                                     << endl;
                    cout << "6. Back to main menu"                              << endl;
                    cout << "=============================================="    << endl;
                    cout << "Choose your option: ";
                    cin >> chooseMenuInMenu3;
                    cout << endl;

                    switch(chooseMenuInMenu3) {
                        case 1: {   bubbleSort();               break;  }
                        case 2: {   straightInsertionSort();    break;  }
                        case 3: {   selectionSort();            break;  }
                        case 4: {   shellSort();                break;  }
                        case 5: {   
                            Booking copy[30];
                            for (int i = 0; i < indexDeparture; i++) {
                                copy[i] = bookings[i];
                            }

                            int first = 0;
                            int last = indexDeparture - 1; 
                            quickSort(bookings, first, last);
                            break;
                        }
                        case 6: {   cout << "Exit...";          break;  }
                        default:{   break;  }
                        
                    }
                } while (chooseMenuInMenu3 != 6);
                break;
            }
            
            case 4: {
                
                break;
            }

            case 5: {

                break;
            }

            default: {
                cout << "Invalid Option!"<<endl;
                break;
            }
        }

    } while (chooseMenu != 5);
}

void generateDataPassanger(){
    for (int i = 0; i < 10; i++) {
        // Passenger
        bookings[i].passenger.name      = "Passenger Number - " + to_string(i + 1);
        bookings[i].passenger.nik       = "1232100 - " + to_string(i + 1);
        bookings[i].passenger.address   = "Indonesia, Regency Code Number - " + to_string(i + 1);

        // TicketInfo
        bookings[i].ticket.departureCity    = "Yogyakarta";
        bookings[i].ticket.destinationCity  = "Magelang";
        //bookings[i].ticket.trainClass       = "Ekonomi";
        bookings[i].ticket.coachNumber      = 1 ;
        bookings[i].ticket.seatNumber       = i ;
        bookings[i].ticket.travelDate       = "2025-04-01";

        // PaymentInfo
        bookings[i].payment.paymentMethod   = "E-Wallet";
        bookings[i].payment.isPaid          = true;
        bookings[i].payment.totalPrice      = 100000;

        indexDeparture++;
    }

    cout << endl;
}

void autoBookTicket() {
    if (indexDeparture >= 30) {
        cout << "All seats already booked";
        return;
    }

    string sampleNames[]        = {"Budi", "Ani", "Citra", "Dedi", "Eka", "Fajar", "Gita", "Hana"};
    string sampleNIKs[]         = {"1234567890", "2345678901", "3456789012", "4567890123"};
    string sampleAddresses[]    = {"Yogyakarta", "Sleman", "Bantul", "Kulon Progo"};

    string destinationsCity[]   = {"Semarang", "Jepara", "Magelang", "Cilacap", "Boyolali"};
    string trainClass[]         = {"Ekonomi", "Bisnis", "Eksekutif"};
    string paymentMethods[]     = {"Transfer", "E-Wallet", "Cash"};

    srand(time(0));

    // Cari kursi kosong
    //int coach = -1, seat = -1;
    int coach, seat;
    bool found = false;

    for (int g = 0; g < portalClass && !found; g++) {
        for (int s = 0; s < portalClassSeat && !found; s++) {
            if (!seatsEachPortal[g][s]) {
                coach   = g;
                seat    = s;
                found   = true;
            }
        }
    }

    if (!found) {
        cout << "Tidak ada kursi kosong \n";
        return;
    }

    seatsEachPortal[coach][seat]= true;
    Booking& b                  = bookings[indexDeparture];

    b.passenger.name    = sampleNames[rand() % 8];
    b.passenger.nik     = sampleNIKs[rand() % 4];
    b.passenger.address = sampleAddresses[rand() % 4];

    b.ticket.departureCity  = departuresCity[rand() % 5];
    b.ticket.destinationCity= destinationsCity[rand() % 5];
    //b.ticket.trainClass     = trainClass[rand() % 3];
    b.ticket.coachNumber    = coach;
    b.ticket.seatNumber     = seat;
    b.ticket.travelDate     = "2025-04-01";

    b.payment.paymentMethod = paymentMethods[rand() % 3];
    b.payment.isPaid        = true;
    b.payment.totalPrice    = 100000;

    cout << "Pemesanan otomatis berhasil untuk " << b.passenger.name 
         << " dengan NIK " << b.passenger.nik
         << " di kursi " << coach + 1 
         << "-" << seat + 1 
         << endl;

    indexDeparture++;
}

void manualInput() {
    if (indexDeparture >= 30) {
        cout << "Semua kursi telah dipesan!" << endl;
        return;
    }

    int chooseDepartureCity, chooseDestinationCity, chooseTrainClass, choosePayment;
    int coachNumber, seatNumber;

    cout << "[INPUT PERSONAL DATA]"<<endl;
    cout << "   Name       : ";
    cin.ignore();
    getline(cin, bookings[indexDeparture].passenger.name);
    cout << "   NIK        : ";
    getline(cin, bookings[indexDeparture].passenger.nik);
    cout << "   Address    : ";
    getline(cin, bookings[indexDeparture].passenger.address);
    cout << endl << endl;
    


    cout << "[DEPARTURE CITY MENU]" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << departuresCity[i] <<endl;
    }
    cout << "   Choose your option: ";
    cin >> chooseDepartureCity;
    bookings[indexDeparture].ticket.departureCity = departuresCity[chooseDepartureCity - 1];


    cout << "\n[DESTINATION CITY MENU]" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << destinationsCity[i] <<endl;
    }
    cout << "   Choose your option: ";
    cin >> chooseDestinationCity;
    bookings[indexDeparture].ticket.destinationCity = destinationsCity[chooseDestinationCity - 1];


    // Menampilkan kursi kosong
    cout << "\n[AVAILABLE SEAT]" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   Coach Train-" << i + 1 << " =" << endl;
        for (int j = 0; j < 10; j++) {
            if (seatsEachPortal[i][j] != false) {
                cout << "       [X]" << " ";
            } else {
                cout << "       [" << to_string(j + 1) << "]";
            }

        }
        cout << endl;
    }


    cout << "\n[CHOOSE SEAT]" << endl;
    cout << "   Choose Coach Train (1 - 3)     : ";
    cin >> coachNumber; coachNumber -= 1;
    cout << "   Choose Seat Number (1 - 10)    : ";
    cin >> seatNumber;  seatNumber  -= 1;

    if (seatsEachPortal[coachNumber][seatNumber]) {
        cout << "       The Seat Number already been booked!";
        return;
    }

    seatsEachPortal[coachNumber][seatNumber]    = true;
    bookings[indexDeparture].ticket.coachNumber = coachNumber;
    bookings[indexDeparture].ticket.seatNumber  = seatNumber;
    bookings[indexDeparture].ticket.travelDate  = "2025-04-01";  // Fixed dulu



    cout << "\n[PAYMENT METHOD]" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   " << i + 1 << ". " << paymentMethods[i] << endl;
    }
    cout << "   Choose your option: ";
    cin >> choosePayment;
    bookings[indexDeparture].payment.paymentMethod  = paymentMethods[choosePayment - 1];
    bookings[indexDeparture].payment.isPaid         = true;
    bookings[indexDeparture].payment.totalPrice     = 100000;   // isi flat dulu


    cout << "Your ticket booking was successful!" << endl;
    indexDeparture++;
}

void searchByNIK() {
    bool found = false;
    for (int i = 0; i < indexDeparture; ++i) {
        found = true;
        cout << "\n=== Tiket Ditemukan ===\n";
        cout << "Nama       : " << bookings[i].passenger.name << endl;
        cout << "NIK        : " << bookings[i].passenger.nik << endl;
        cout << "Asal       : " << bookings[i].ticket.departureCity << endl;
        cout << "Tujuan     : " << bookings[i].ticket.destinationCity << endl;
        cout << "Kursi      : " << bookings[i].ticket.coachNumber << "-" << bookings[i].ticket.seatNumber << endl;
        cout << "Total Bayar: Rp" << bookings[i].payment.totalPrice << endl;
        break;    
    }
}

void seqNonSentinelNotYetSorted(){
    string searchNIK;
    cout << "Input NIK you wanna search: ";
    cin >> searchNIK;

    bool found = false;
    int i = 0;

    while (
        (i < indexDeparture) && 
        (!found)
    ) {
        if (bookings[i].passenger.nik == searchNIK) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        cout << "\n====== NIK ditemukan =======\n";
        cout << "Nama       : " << bookings[i].passenger.name << endl;
        cout << "NIK        : " << bookings[i].passenger.nik << endl;
        cout << "Asal       : " << bookings[i].ticket.departureCity << endl;
        cout << "Tujuan     : " << bookings[i].ticket.destinationCity << endl;
        cout << "Kursi      : " << bookings[i].ticket.coachNumber + 1 << "-" << bookings[i].ticket.seatNumber + 1 << endl;
        cout << "Total Bayar: Rp" << bookings[i].payment.totalPrice << endl << endl;
    } else {
        cout << "NIK not found!\n";
    }
}

void seqSentinelNotYetSorted() {
    string searchNIK;

    cout << "Input NIK you wanna search: ";
    cin >> searchNIK;

    // Buat backup untuk menghentikan looping dan menukar nilai nya dengan backup mula-mula setelah looping berakhir (trik utamanya ini)
    // Buat backup data dari struknya langsung (bukan hanya fieldnya saja)
    Booking tempBackup = bookings[indexDeparture];
    
    // isi index terakhir dengan inputan NIK yang ingin dicari (ibaratnya menganggap index terakhir sebaga sentinel)
    bookings[indexDeparture].passenger.nik = searchNIK;

    int i = 0;
    // bool found = false;
    while (bookings[i].passenger.nik != searchNIK) {
        i++;
    }

    // Kembalikan data terakhir ke semula
    bookings[indexDeparture] = tempBackup;

    if (i < indexDeparture) {
        cout << "\n====== NIK FOUND =======\n";
        cout << "Nama       : " << bookings[i].passenger.name << endl;
        cout << "NIK        : " << bookings[i].passenger.nik << endl;
        cout << "Asal       : " << bookings[i].ticket.departureCity << endl;
        cout << "Tujuan     : " << bookings[i].ticket.destinationCity << endl;
        cout << "Kursi      : " << bookings[i].ticket.coachNumber + 1 << "-" << bookings[i].ticket.seatNumber + 1 << endl;
        cout << "Total Bayar: Rp" << bookings[i].payment.totalPrice << endl << endl;
    } else {
        cout << "NIK not found!\n";
    }
}

void bubbleSort() {
    Booking copy[30];
    for (int i = 0; i < indexDeparture; i++) {
        copy[i] = bookings[i];
    }

    for (int i = 0; i < indexDeparture - 1; i++) {
        for (int j = 0; j < indexDeparture - 1 - i; j++) {
            if (copy[j].passenger.name > copy[j + 1].passenger.name) {
                Booking temp    = copy[j];
                copy[j]         = copy[j + 1];
                copy[j + 1]     = temp;
            }
        }
    }

    sortingOutputShow(copy);
}

void straightInsertionSort() {
    Booking copy[30];
    for (int i = 0; i < indexDeparture; i++) {
        copy[i] = bookings[i];
    }

    int j;

    for (int i = 1; i < indexDeparture; i++) {
        Booking temp = copy[i];
        j = i - 1;
        while ((temp.passenger.name < copy[j].passenger.name) & (j >= 0)) {
            copy[j + 1] = copy[j];
            j           = j - 1;
            copy[j + 1] = temp;
        }
    }

    sortingOutputShow(copy);
}

void selectionSort() {
    Booking copy[30];
    for (int i = 0; i < indexDeparture; i++) {
        copy[i] = bookings[i];
    }

    for (int current = 0; current < indexDeparture; current++) {
        for (int j = current + 1; j < indexDeparture; j++) {
            if (copy[current].passenger.name > copy[j].passenger.name) {
                Booking temp    = copy[current];
                copy[current]   = copy[j];
                copy[j]         = temp;
            }
        }
    }

    sortingOutputShow(copy);
}

void shellSort() {
    Booking copy[30];
    for (int i = 0; i < indexDeparture; i++) {
        copy[i] = bookings[i];
    }

    for (int k = indexDeparture / 2; k > 0; k /= 2) {
        for (int j = k; j < indexDeparture; j++) {
            for (int i = j - k; i >= 0; i -= k) {
                if (copy[i + k].passenger.name > copy[i].passenger.name) {
                    break;
                } else {
                    Booking mid = copy[i];
                    copy[i]     = copy[i + k];
                    copy[i + k] = mid;
                }
            }
        } 
    }

    sortingOutputShow(copy);
}

void quickSort(Booking bookingsQuick[], int first, int last) {
    int low, high;

    low     = first;
    high    = last;
    Booking listSeparator = bookingsQuick[(first + last) / 2];

    do {
        while (bookingsQuick[low].passenger.name < listSeparator.passenger.name) {
            low++;
        }
        while (bookingsQuick[high].passenger.name > listSeparator.passenger.name) {
            high--;
        }

        if (low <= high) {
            Booking temp            = bookingsQuick[low];
            bookingsQuick[low++]    = bookingsQuick[high];
            bookingsQuick[high--]   = temp;
        }
    } while (low <= high);

    if (first < high)   { quickSort(bookingsQuick, first, high); };
    if (low < last)     { quickSort(bookingsQuick, low, last);   };

    sortingOutputShow(bookingsQuick);
}

void sortingOutputShow(Booking *sortingShow) {
    cout << "====== Data Booking Setelah Sorting (A-Z Nama) ======\n";
    for (int i = 0; i < indexDeparture; i++) {
        cout << i + 1   << ". Nama: "   << sortingShow[i].passenger.name 
                        << ", NIK: "    << sortingShow[i].passenger.nik 
                        << ", Asal: "   << sortingShow[i].ticket.departureCity 
                        << ", Tujuan: " << sortingShow[i].ticket.destinationCity 
                        << endl;
    }
    cout << endl;
}