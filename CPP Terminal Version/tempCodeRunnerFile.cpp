#include <iostream>
#include <string>
#include <cstdlib>  // untuk rand()
#include <ctime>    // untuk time()

using namespace std;

const int nomorGerbong = 3;
const int tempatDudukGerbong = 10;

bool kursiTiapGerbong[nomorGerbong][tempatDudukGerbong];

struct Penumpang {
    string 
        nama,
        nik,
        alamat;
};

struct InfoTiket{
    string 
        asalKotaStatsiun,
        kotaTujuan;
    int 
        nomorGerbong,
        nomorTempatDuduk;
    string tanggalKeberangkatan;
};

struct InfoPembayaran {
    string metodePembayaran;
    bool sudahDibayar;
    int totalHarga;
};

struct Pemesanan {
    Penumpang penumpang;
    InfoTiket tiket;
    InfoPembayaran pembayaran;
};

Pemesanan pemesanan[30];

string kotaAsal[] = {
    "Yogyakarta", 
    "Sleman", 
    "Gunung Kidul", 
    "Bantul", 
    "Kulon Progo"
};

string kotaTujuan[] = {
    "Magelang", 
    "Semarang", 
    "Jepara",   
    "Cilacap", 
    "Boyolali"
};

string metodePembayaran[] = {
    "Transfer", 
    "E-Wallet", 
    "Cash"
};

int indexKeberangkatan = 0;


//###################
void autoBookTicket();
void manualInput();
void searchByNIK();
void seqNonSentinelNotYetSorted();
void seqSentinelNotYetSorted();
void bubbleSort(Pemesanan *copyBubble);
void straightInsertionSort();
void selectionSort();
void shellSort();
void quickSort(Pemesanan *bookingsQuick, int first, int last);
void sortingOutputShow(Pemesanan *sortingShow);

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
                        case 1: {
                            Pemesanan copy[30];

                            int i;
                            for (i = 0; i < indexKeberangkatan; i++) {
                                copy[i] = pemesanan[i];
                            }
                            
                            Pemesanan *copyPointerBubble = &copy[i];
                            bubbleSort(copyPointerBubble);
                            sortingOutputShow(copyPointerBubble);               
                            break;  
                        }
                        case 2: {   
                            straightInsertionSort();    
                            break;  
                        }
                        case 3: {   
                            selectionSort();            
                            break;  
                        }
                        case 4: {   
                            shellSort();                
                            break;  
                        }
                        case 5: {   
                            Pemesanan copy[30];

                            int i;
                            for (i = 0; i < indexKeberangkatan; i++) {
                                copy[i] = pemesanan[i];
                            }

                            Pemesanan *copyPointer = &copy[i];

                            int first = 0;
                            int last = indexKeberangkatan - 1;

                            quickSort(copyPointer, first, last);
                            sortingOutputShow(copyPointer);

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
        pemesanan[i].penumpang.nama      = "Passenger Number - " + to_string(i + 1);
        pemesanan[i].penumpang.nik       = "1232100 - " + to_string(i + 1);
        pemesanan[i].penumpang.alamat   = "Indonesia, Regency Code Number - " + to_string(i + 1);

        // TicketInfo
        pemesanan[i].tiket.asalKotaStatsiun    = "Yogyakarta";
        pemesanan[i].tiket.kotaTujuan  = "Magelang";
        //bookings[i].ticket.trainClass       = "Ekonomi";
        pemesanan[i].tiket.nomorGerbong      = 1 ;
        pemesanan[i].tiket.nomorTempatDuduk       = i ;
        pemesanan[i].tiket.tanggalKeberangkatan       = "2025-04-01";

        // PaymentInfo
        pemesanan[i].pembayaran.metodePembayaran   = "E-Wallet";
        pemesanan[i].pembayaran.sudahDibayar          = true;
        pemesanan[i].pembayaran.totalHarga      = 100000;

        indexKeberangkatan++;
    }

    cout << endl;
}

void autoBookTicket() {
    if (indexKeberangkatan >= 30) {
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

    for (int g = 0; g < nomorGerbong && !found; g++) {
        for (int s = 0; s < tempatDudukGerbong && !found; s++) {
            if (!kursiTiapGerbong[g][s]) {
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

    kursiTiapGerbong[coach][seat]= true;
    Pemesanan& b                  = pemesanan[indexKeberangkatan];

    b.penumpang.nama    = sampleNames[rand() % 8];
    b.penumpang.nik     = sampleNIKs[rand() % 4];
    b.penumpang.alamat = sampleAddresses[rand() % 4];

    b.tiket.asalKotaStatsiun  = kotaAsal[rand() % 5];
    b.tiket.kotaTujuan= destinationsCity[rand() % 5];
    //b.ticket.trainClass     = trainClass[rand() % 3];
    b.tiket.nomorGerbong    = coach;
    b.tiket.nomorTempatDuduk     = seat;
    b.tiket.tanggalKeberangkatan     = "2025-04-01";

    b.pembayaran.metodePembayaran = paymentMethods[rand() % 3];
    b.pembayaran.sudahDibayar        = true;
    b.pembayaran.totalHarga    = 100000;

    cout << "Pemesanan otomatis berhasil untuk " << b.penumpang.nama 
         << " dengan NIK " << b.penumpang.nik
         << " di kursi " << coach + 1 
         << "-" << seat + 1 
         << endl;

    indexKeberangkatan++;
}

void manualInput() {
    if (indexKeberangkatan >= 30) {
        cout << "Semua kursi telah dipesan!" << endl;
        return;
    }

    int chooseDepartureCity, chooseDestinationCity, chooseTrainClass, choosePayment;
    int coachNumber, seatNumber;

    cout << "[INPUT PERSONAL DATA]"<<endl;
    cout << "   Name       : ";
    cin.ignore();
    getline(cin, pemesanan[indexKeberangkatan].penumpang.nama);
    cout << "   NIK        : ";
    getline(cin, pemesanan[indexKeberangkatan].penumpang.nik);
    cout << "   Address    : ";
    getline(cin, pemesanan[indexKeberangkatan].penumpang.alamat);
    cout << endl << endl;
    


    cout << "[DEPARTURE CITY MENU]" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << kotaAsal[i] <<endl;
    }
    cout << "   Choose your option: ";
    cin >> chooseDepartureCity;
    pemesanan[indexKeberangkatan].tiket.asalKotaStatsiun = kotaAsal[chooseDepartureCity - 1];


    cout << "\n[DESTINATION CITY MENU]" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "   " << i + 1 << ". " << kotaTujuan[i] <<endl;
    }
    cout << "   Choose your option: ";
    cin >> chooseDestinationCity;
    pemesanan[indexKeberangkatan].tiket.kotaTujuan = kotaTujuan[chooseDestinationCity - 1];


    // Menampilkan kursi kosong
    cout << "\n[AVAILABLE SEAT]" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   Coach Train-" << i + 1 << " =" << endl;
        for (int j = 0; j < 10; j++) {
            if (kursiTiapGerbong[i][j] != false) {
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

    if (kursiTiapGerbong[coachNumber][seatNumber]) {
        cout << "       The Seat Number already been booked!";
        return;
    }

    kursiTiapGerbong[coachNumber][seatNumber]    = true;
    pemesanan[indexKeberangkatan].tiket.nomorGerbong = coachNumber;
    pemesanan[indexKeberangkatan].tiket.nomorTempatDuduk  = seatNumber;
    pemesanan[indexKeberangkatan].tiket.tanggalKeberangkatan  = "2025-04-01";  // Fixed dulu



    cout << "\n[PAYMENT METHOD]" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   " << i + 1 << ". " << metodePembayaran[i] << endl;
    }
    cout << "   Choose your option: ";
    cin >> choosePayment;
    pemesanan[indexKeberangkatan].pembayaran.metodePembayaran  = metodePembayaran[choosePayment - 1];
    pemesanan[indexKeberangkatan].pembayaran.sudahDibayar         = true;
    pemesanan[indexKeberangkatan].pembayaran.totalHarga     = 100000;   // isi flat dulu

    cout << "[FINAL RESULT]"<< endl;
    cout << "   Your ticket booking was successful!" << endl;
    indexKeberangkatan++;
}

void searchByNIK() {
    bool found = false;
    for (int i = 0; i < indexKeberangkatan; ++i) {
        found = true;
        cout << "\n=== Tiket Ditemukan ===\n";
        cout << "Nama       : " << pemesanan[i].penumpang.nama << endl;
        cout << "NIK        : " << pemesanan[i].penumpang.nik << endl;
        cout << "Asal       : " << pemesanan[i].tiket.asalKotaStatsiun << endl;
        cout << "Tujuan     : " << pemesanan[i].tiket.kotaTujuan << endl;
        cout << "Kursi      : " << pemesanan[i].tiket.nomorGerbong << "-" << pemesanan[i].tiket.nomorTempatDuduk << endl;
        cout << "Total Bayar: Rp" << pemesanan[i].pembayaran.totalHarga << endl;
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
        (i < indexKeberangkatan) && 
        (!found)
    ) {
        if (pemesanan[i].penumpang.nik == searchNIK) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        cout << "\n====== NIK ditemukan =======\n";
        cout << "Nama       : " << pemesanan[i].penumpang.nama << endl;
        cout << "NIK        : " << pemesanan[i].penumpang.nik << endl;
        cout << "Asal       : " << pemesanan[i].tiket.asalKotaStatsiun << endl;
        cout << "Tujuan     : " << pemesanan[i].tiket.kotaTujuan << endl;
        cout << "Kursi      : " << pemesanan[i].tiket.nomorGerbong + 1 << "-" << pemesanan[i].tiket.nomorTempatDuduk + 1 << endl;
        cout << "Total Bayar: Rp" << pemesanan[i].pembayaran.totalHarga << endl << endl;
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
    Pemesanan tempBackup = pemesanan[indexKeberangkatan];
    
    // isi index terakhir dengan inputan NIK yang ingin dicari (ibaratnya menganggap index terakhir sebaga sentinel)
    pemesanan[indexKeberangkatan].penumpang.nik = searchNIK;

    int i = 0;
    // bool found = false;
    while (pemesanan[i].penumpang.nik != searchNIK) {
        i++;
    }

    // Kembalikan data terakhir ke semula
    pemesanan[indexKeberangkatan] = tempBackup;

    if (i < indexKeberangkatan) {
        cout << "\n====== NIK FOUND =======\n";
        cout << "Nama       : " << pemesanan[i].penumpang.nama << endl;
        cout << "NIK        : " << pemesanan[i].penumpang.nik << endl;
        cout << "Asal       : " << pemesanan[i].tiket.asalKotaStatsiun << endl;
        cout << "Tujuan     : " << pemesanan[i].tiket.kotaTujuan << endl;
        cout << "Kursi      : " << pemesanan[i].tiket.nomorGerbong + 1 << "-" << pemesanan[i].tiket.nomorTempatDuduk + 1 << endl;
        cout << "Total Bayar: Rp" << pemesanan[i].pembayaran.totalHarga << endl << endl;
    } else {
        cout << "NIK not found!\n";
    }
}

void bubbleSort(Pemesanan *copyBubble) {
    for (int i = 0; i < indexKeberangkatan - 1; i++) {
        for (int j = 0; j < indexKeberangkatan - 1 - i; j++) {
            if (copyBubble[j].penumpang.nama > copyBubble[j + 1].penumpang.nama) {
                Pemesanan temp    = copyBubble[j];
                copyBubble[j]         = copyBubble[j + 1];
                copyBubble[j + 1]     = temp;
            }
        }
    }
}

void straightInsertionSort() {
    Pemesanan copy[30];
    for (int i = 0; i < indexKeberangkatan; i++) {
        copy[i] = pemesanan[i];
    }

    int j;

    for (int i = 1; i < indexKeberangkatan; i++) {
        Pemesanan temp = copy[i];
        j = i - 1;
        while ((temp.penumpang.nama < copy[j].penumpang.nama) & (j >= 0)) {
            copy[j + 1] = copy[j];
            j           = j - 1;
            copy[j + 1] = temp;
        }
    }

    sortingOutputShow(copy);
}

void selectionSort() {
    Pemesanan copy[30];
    for (int i = 0; i < indexKeberangkatan; i++) {
        copy[i] = pemesanan[i];
    }

    for (int current = 0; current < indexKeberangkatan; current++) {
        for (int j = current + 1; j < indexKeberangkatan; j++) {
            if (copy[current].penumpang.nama > copy[j].penumpang.nama) {
                Pemesanan temp    = copy[current];
                copy[current]   = copy[j];
                copy[j]         = temp;
            }
        }
    }

    sortingOutputShow(copy);
}

void shellSort() {
    Pemesanan copy[30];
    for (int i = 0; i < indexKeberangkatan; i++) {
        copy[i] = pemesanan[i];
    }

    for (int k = indexKeberangkatan / 2; k > 0; k /= 2) {
        for (int j = k; j < indexKeberangkatan; j++) {
            for (int i = j - k; i >= 0; i -= k) {
                if (copy[i + k].penumpang.nama > copy[i].penumpang.nama) {
                    break;
                } else {
                    Pemesanan mid = copy[i];
                    copy[i]     = copy[i + k];
                    copy[i + k] = mid;
                }
            }
        } 
    }

    sortingOutputShow(copy);
}

void quickSort(Pemesanan *bookingsQuick, int first, int last) {
    int low, high;

    low     = first;
    high    = last;

    Pemesanan listSeparator = bookingsQuick[(first + last) / 2];

    do {
        while (bookingsQuick[low].penumpang.nama < listSeparator.penumpang.nama) {
            low++;
        }
        while (bookingsQuick[high].penumpang.nama > listSeparator.penumpang.nama) {
            high--;
        }

        if (low <= high) {
            Pemesanan temp            = bookingsQuick[low];
            bookingsQuick[low++]    = bookingsQuick[high];
            bookingsQuick[high--]   = temp;
        }
    } while (low <= high);

    if (first < high)   { quickSort(bookingsQuick, first, high); };
    if (low < last)     { quickSort(bookingsQuick, low, last);   };

    //Booking *bookingsQuickPointer = bookingsQuick;
    //sortingOutputShow(bookingsQuickPointer);
    //sortingOutputShow(bookingsQuick);
}

void sortingOutputShow(Pemesanan *sortingShow) {
    cout << "====== Data Booking Setelah Sorting (A-Z Nama) ======\n";
    for (int i = 0; i < indexKeberangkatan; i++) {
        cout << i + 1   << ". Nama: "   << sortingShow[i].penumpang.nama 
                        << ", NIK: "    << sortingShow[i].penumpang.nik 
                        << ", Asal: "   << sortingShow[i].tiket.asalKotaStatsiun 
                        << ", Tujuan: " << sortingShow[i].tiket.kotaTujuan 
                        << endl;
    }
    cout << endl;
}