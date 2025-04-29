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
void seqNonSentinelNotYetSorted(string *nikPointer);
void seqSentinelNotYetSorted(string *nikPointer);
void binarySearch(Booking *copyBinary, string *nikPointer);
void bubbleSortByNik(Booking *copyBubleNik);
void bubbleSort(Booking *copyBubble);
void straightInsertionSort(Booking *copyInsertion);
void selectionSort(Booking *copySelection);
void shellSort(Booking *copyShell);
void quickSort(Booking *copyQuick, int first, int last);
void sortingOutputShow(Booking *sortingShow);

int main() {
    int chooseMenu;

    do {   
        cout << "[MAIN MENU]"<< endl;
        cout << "   1. Book your ticket"                           << endl;
        cout << "   2. Show your ticket information (Searching)"   << endl;
        cout << "   3. Show all ticket information (Sorting)"      << endl;
        cout << "   4. Recursive"                                  << endl;
        cout << "   5. Exit"                                       << endl;
        cout << "   Choose your option : ";
        cin >> chooseMenu;
        cout << endl;

        switch (chooseMenu) {
            case 1: {
                int chooseMenuInMenu1;

                do {
                    cout << "[BOOK YOUR TICKET]"<< endl;
                    cout << "   1. Generate Data Customer"                     << endl;
                    cout << "   2. Manual Input Data Customer"                 << endl;
                    cout << "   3. Back to main menu"                          << endl;
                    cout << "   Choose Your Option: ";
                    cin >> chooseMenuInMenu1;
                    cout << endl;

                    switch (chooseMenuInMenu1){
                        case 1: {   
                            autoBookTicket();
                            cout << endl << endl;
                            break; 
                        }
                        case 2: {   
                            manualInput();
                            cout<< endl << endl; 
                            break; 
                        }
                        case 3: {   cout << "   Exit..."<< endl << endl; break; }
                        default:{   cout << "   Invalid"<< endl << endl; break; }
                    }
                } while (chooseMenuInMenu1 != 3);
                cout << endl;

                break;
            }
                
            case 2: {
                int chooseMenuInMenu2;
                do {
                    cout << "\n[YOUR TICKET INFORMATION]"<< endl;
                    cout << "   1. Sequential Non Sentinel Search Not Yet Sorted"  << endl;
                    cout << "   2. Sequential Sentinel Search Not Yet Sorted"      << endl;
                    cout << "   3. Binary Search"                                  << endl;
                    cout << "   4. Back to main menu"                              << endl;
                    cout << "   Choose your option: ";
                    cin >> chooseMenuInMenu2;
                    cout << endl;

                    switch(chooseMenuInMenu2) {
                        case 1: {   
                            string searchNIK;
                            cout << "   Input NIK you wanna search: ";
                            cin >> searchNIK;
                            
                            seqNonSentinelNotYetSorted(&searchNIK); 
                            cout << endl << endl; 

                            break;  
                        }
                        case 2: {
                            string searchNIK;

                            cout << "Input NIK you wanna search: ";
                            cin >> searchNIK; 

                            seqSentinelNotYetSorted(&searchNIK);      
                            cout << endl << endl;
                            break;  
                        }
                        case 3: {   
                            Booking copy[30];
                            for (int i = 0; i < indexDeparture; i++) {
                                copy[i] = bookings[i];
                            }

                            string searchNIK;

                            cout << "Input NIK you wanna search: ";
                            cin >> searchNIK; 

                            binarySearch(copy, &searchNIK);
                            cout << endl << endl;

                            break;                                  
                        }
                        case 4: {  
                            cout << "   Exit...";             
                            cout << endl << endl;
                            
                            break;  }
                        default:{   
                            cout << endl << endl;
                            break;                                  
                        }
                    }
                } while (chooseMenuInMenu2 != 4);
                cout << endl;

                break;
            }

            case 3: {
                int chooseMenuInMenu3;
                do {
                    cout << "[ALL TICKET INFORMATION]"    << endl;
                    cout << "   1. Bubble Sort"                                    << endl;
                    cout << "   2. Straight Insertion Sort"                        << endl;
                    cout << "   3. Straight Selection Sort"                        << endl;
                    cout << "   4. Shell Sort"                                     << endl;
                    cout << "   5. Quick Sort"                                     << endl;
                    cout << "   6. Back to main menu"                              << endl;
                    cout << "   Choose your option: ";
                    cin >> chooseMenuInMenu3;
                    cout << endl;

                    switch(chooseMenuInMenu3) {
                        case 1: {
                            Booking copy[30];

                            for (int i = 0; i < indexDeparture; i++) {
                                copy[i] = bookings[i];
                            }
                            
                            bubbleSort(copy);
                            sortingOutputShow(copy);  

                            cout << endl;

                            break;  
                        }
                        case 2: {   
                            Booking copy[30];

                            for (int i = 0; i < indexDeparture; i++) {
                                copy[i] = bookings[i];
                            }

                            straightInsertionSort(copy);
                            sortingOutputShow(copy);  
                            
                            cout << endl;

                            break;  
                        }
                        case 3: {   
                            Booking copy[30];
                            for (int i = 0; i < indexDeparture; i++) {
                                copy[i] = bookings[i];
                            }

                            selectionSort(copy);
                            sortingOutputShow(copy);      
                            
                            cout << endl << endl;

                            break;  
                        }
                        case 4: {   
                            Booking copy[30];

                            for (int i = 0; i < indexDeparture; i++) {
                                copy[i] = bookings[i];
                            }

                            shellSort(copy);
                            sortingOutputShow(copy);     
                            
                            cout << endl;

                            break;  
                        }
                        case 5: {   
                            Booking copy[30];

                            int i;
                            for (i = 0; i < indexDeparture; i++) {
                                copy[i] = bookings[i];
                            }

                            //Booking *copyPointer = &copy[i];

                            int first = 0;
                            int last = indexDeparture - 1;

                            quickSort(copy, first, last);
                            sortingOutputShow(copy);

                            cout << endl;

                            break;
                        }
                        case 6: {   
                            cout << "   Exit..." << endl; 
                            cout << endl;
                                    
                            break;  
                        }
                        default:{   break;  }
                    }
                } while (chooseMenuInMenu3 != 6);
                break;
            }
            
            case 4: {
                cout << endl << endl;
                break;
            }

            case 5: {
                cout << endl << endl;
                break;
            }

            default: {
                cout << "   Invalid Option!";
                cout << endl << endl;
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

/*
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
    //b.passenger.nik     = sampleNIKs[rand() % 4];
    int randomBaseNIK = 1000000000 + rand() % 900000000;
    b.passenger.nik = to_string(randomBaseNIK) + to_string(indexDeparture);
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

    cout << "   [RESULT] Pemesanan otomatis berhasil untuk " << b.passenger.name 
         << " dengan NIK " << b.passenger.nik
         << " di kursi " << coach + 1 
         << "-" << seat + 1;

    indexDeparture++;
}*/
void autoBookTicket() {
    if (indexDeparture >= 30) {
        cout << "All seats already booked" << endl;
        return;
    }

    string sampleNames[]      = {"Budi", "Ani", "Citra", "Dedi", "Eka", "Fajar", "Gita", "Hana"};
    string sampleAddresses[]  = {"Yogyakarta", "Sleman", "Bantul", "Kulon Progo"};
    string destinationsCity[] = {"Semarang", "Jepara", "Magelang", "Cilacap", "Boyolali"};
    string paymentMethods[]   = {"Transfer", "E-Wallet", "Cash"};

    srand(time(0));

    // Cari kursi kosong
    int coach = -1, seat = -1;
    bool foundSeat = false;

    for (int g = 0; g < portalClass && !foundSeat; g++) {
        for (int s = 0; s < portalClassSeat && !foundSeat; s++) {
            if (!seatsEachPortal[g][s]) {
                coach = g;
                seat = s;
                foundSeat = true;
            }
        }
    }

    if (!foundSeat) {
        cout << "Tidak ada kursi kosong" << endl;
        return;
    }

    // Generate unique NIK
    string generatedNIK;
    bool isDuplicate;
    do {
        isDuplicate = false;
        int randomNIK = 100000000 + rand() % 900000000; // Random 9 digit
        generatedNIK = to_string(randomNIK);

        for (int i = 0; i < indexDeparture; i++) {
            if (bookings[i].passenger.nik == generatedNIK) {
                isDuplicate = true;
                break;
            }
        }
    } while (isDuplicate);

    // Assign data ke bookings
    seatsEachPortal[coach][seat] = true;
    Booking& b = bookings[indexDeparture];

    b.passenger.name    = sampleNames[rand() % 8];
    b.passenger.nik     = generatedNIK;
    b.passenger.address = sampleAddresses[rand() % 4];

    b.ticket.departureCity     = departuresCity[rand() % 5];
    b.ticket.destinationCity   = destinationsCity[rand() % 5];
    b.ticket.coachNumber       = coach;
    b.ticket.seatNumber        = seat;
    b.ticket.travelDate        = "2025-04-01";

    b.payment.paymentMethod    = paymentMethods[rand() % 3];
    b.payment.isPaid           = true;
    b.payment.totalPrice       = 100000;

    cout << "   [RESULT] Pemesanan otomatis berhasil untuk " << b.passenger.name
         << " dengan NIK " << b.passenger.nik
         << " di kursi " << coach + 1
         << "-" << seat + 1 << endl;

    indexDeparture++;
}


void manualInput() {
    if (indexDeparture >= 30) {
        cout << "   Semua kursi telah dipesan!" << endl;
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
        cout << "   " << i + 1 << ". " << destinationsCity[i] <<endl;
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

    cout << "   [RESULT] Your ticket booking was successful!" << endl;
    indexDeparture++;
}

void searchByNIK() {
    bool found = false;
    for (int i = 0; i < indexDeparture; ++i) {
        found = true;
        cout << "\n[FOUND - TICKET]\n";
        cout << "   Nama       : " << bookings[i].passenger.name << endl;
        cout << "   NIK        : " << bookings[i].passenger.nik << endl;
        cout << "   Asal       : " << bookings[i].ticket.departureCity << endl;
        cout << "   Tujuan     : " << bookings[i].ticket.destinationCity << endl;
        cout << "   Kursi      : " << bookings[i].ticket.coachNumber << "-" << bookings[i].ticket.seatNumber << endl;
        cout << "   Total Bayar: Rp" << bookings[i].payment.totalPrice << endl;
        break;    
    }
}

void seqNonSentinelNotYetSorted(string *nikPointer){
    bool found = false;
    int i = 0;

    while (
        (i < indexDeparture) && 
        (!found)
    ) {
        if (bookings[i].passenger.nik == *nikPointer) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        cout << "\n[FOUND - NIK]\n";
        cout << "   Nama       : " << bookings[i].passenger.name << endl;
        cout << "   NIK        : " << bookings[i].passenger.nik << endl;
        cout << "   Asal       : " << bookings[i].ticket.departureCity << endl;
        cout << "   Tujuan     : " << bookings[i].ticket.destinationCity << endl;
        cout << "   Kursi      : " << bookings[i].ticket.coachNumber + 1 << "-" << bookings[i].ticket.seatNumber + 1 << endl;
        cout << "   Total Bayar: Rp" << bookings[i].payment.totalPrice << endl << endl;
    } else {
        cout << "   NIK not found!\n";
    }
}

void seqSentinelNotYetSorted(string *nikPointer) {
    Booking tempBackup = bookings[indexDeparture];
    
    bookings[indexDeparture].passenger.nik = *nikPointer;

    int i = 0;
    // bool found = false;
    while (bookings[i].passenger.nik != *nikPointer) {
        i++;
    }

    // Kembalikan data terakhir ke semula
    bookings[indexDeparture] = tempBackup;

    if (i < indexDeparture) {
        cout << "\n[FOUND - NIK]\n";
        cout << "   Nama       : " << bookings[i].passenger.name << endl;
        cout << "   NIK        : " << bookings[i].passenger.nik << endl;
        cout << "   Asal       : " << bookings[i].ticket.departureCity << endl;
        cout << "   Tujuan     : " << bookings[i].ticket.destinationCity << endl;
        cout << "   Kursi      : " << bookings[i].ticket.coachNumber + 1 << "-" << bookings[i].ticket.seatNumber + 1 << endl;
        cout << "   Total Bayar: Rp" << bookings[i].payment.totalPrice << endl << endl;
    } else {
        cout << "   NIK not found!\n";
    }
}

void binarySearch(Booking *copyBinary, string *nikPointer) {
    bubbleSortByNik(copyBinary);

    int i, j, k;
    bool found;

    found = false;
    i = 0;
    j = indexDeparture;

    while((i <= j) && (!found)){
        k  = (i + j) / 2;
        if (*nikPointer == copyBinary[k].passenger.nik) {
            found = true;
        } else {
            if (*nikPointer < copyBinary[k].passenger.nik) {
                j = k - 1;
            } else {
                i = k + 1;
            }
        }
    }

    if (found) {
        cout << "\n[FOUND - NIK]\n";
        cout << "   Nama       : " << copyBinary[k].passenger.name << endl;
        cout << "   NIK        : " << copyBinary[k].passenger.nik << endl;
        cout << "   Asal       : " << copyBinary[k].ticket.departureCity << endl;
        cout << "   Tujuan     : " << copyBinary[k].ticket.destinationCity << endl;
        cout << "   Kursi      : " << copyBinary[k].ticket.coachNumber + 1 << "-" << copyBinary[k].ticket.seatNumber + 1 << endl;
        cout << "   Total Bayar: Rp" << copyBinary[k].payment.totalPrice << endl << endl;
    } else {
        cout << "   NIK not found!\n";
    }
}

void bubbleSortByNik(Booking *copyBubleNik) {
    for (int i = 0; i < indexDeparture - 1; i++) {
        for (int j = 0; j < indexDeparture - 1 - i; j++) {    
            if (copyBubleNik[j].passenger.nik > copyBubleNik[j + 1].passenger.nik) {
                Booking temp        = copyBubleNik[j];
                copyBubleNik[j]     = copyBubleNik[j + 1];
                copyBubleNik[j + 1] = temp;
            }
        }
    }
}

void bubbleSort(Booking *copyBubble) {
    for (int i = 0; i < indexDeparture - 1; i++) {
        for (int j = 0; j < indexDeparture - 1 - i; j++) {
            if (copyBubble[j].passenger.name > copyBubble[j + 1].passenger.name) {
                Booking temp      = copyBubble[j];
                copyBubble[j]     = copyBubble[j + 1];
                copyBubble[j + 1] = temp;
            }
        }
    }
}

void straightInsertionSort(Booking *copyInsertion) {
    int i, j;
    Booking temp;

    for (i = 1; i < indexDeparture; i++) {
        temp = copyInsertion[i];
        j = i - 1;
        while ((j >= 0) && (temp.passenger.name < copyInsertion[j].passenger.name) ) {
            copyInsertion[j + 1] = copyInsertion[j];
            j                    = j - 1;
            copyInsertion[j + 1] = temp;
        }
    }
}

void selectionSort(Booking *copySelection) {
    for (int current = 0; current < indexDeparture; current++) {
        for (int j = current + 1; j < indexDeparture; j++) {
            if (copySelection[current].passenger.name > copySelection[j].passenger.name) {
                Booking temp            = copySelection[current];
                copySelection[current]  = copySelection[j];
                copySelection[j]        = temp;
            }
        }
    }
}

void shellSort(Booking *copyShell) {
    for (int k = indexDeparture / 2; k > 0; k /= 2) {
        for (int j = k; j < indexDeparture; j++) {
            for (int i = j - k; i >= 0; i -= k) {
                if (copyShell[i + k].passenger.name > copyShell[i].passenger.name) {
                    break;
                } else {
                    Booking mid      = copyShell[i];
                    copyShell[i]     = copyShell[i + k];
                    copyShell[i + k] = mid;
                }
            }
        } 
    }
}

void quickSort(Booking *bookingsQuick, int first, int last) {
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
}

void sortingOutputShow(Booking *sortingShow) {
    cout << "[ALL BOOKING DATA - AFTER SORTED (A-Z)]\n";
    for (int i = 0; i < indexDeparture; i++) {
        cout << "   " << i + 1  << ". Nama: "   << sortingShow[i].passenger.name 
                                << ", NIK: "    << sortingShow[i].passenger.nik 
                                << ", Asal: "   << sortingShow[i].ticket.departureCity 
                                << ", Tujuan: " << sortingShow[i].ticket.destinationCity 
                                << endl;
    }
    cout << endl;
}