#include <iostream>
#include <string>
#include <cstdlib>  // untuk rand()
#include <ctime>    // untuk time()
using namespace std;

const int nomorGerbong = 3;
const int tempatDudukGerbong = 10;

bool seatsEachPortal[nomorGerbong][tempatDudukGerbong];

struct Penumpang {
    string nama,
        nik,
        alamat;
};
struct InfoTiket{
    string 
        asalKota,
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

// string kotaAsal[] = {
//     "Yogyakarta", 
//     "Sleman", 
//     "Gunung Kidul", 
//     "Bantul", 
//     "Kulon Progo"
// };

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
void seqNonSentinelNotYetSorted(string *nikPointer);
void seqSentinelNotYetSorted(string *nikPointer);
void binarySearch(Pemesanan *copyBinary, string *nikPointer);
void bubbleSortByNik(Pemesanan *copyBubleNik);
void bubbleSort(Pemesanan *copyBubble);
void straightInsertionSort(Pemesanan *copyInsertion);
void selectionSort(Pemesanan *copySelection);
void shellSort(Pemesanan *copyShell);
void quickSort(Pemesanan *copyQuick, int first, int last);
void sortingOutputShow(Pemesanan *sortingShow);
void fileOperationSave (Pemesanan bookings[], int totalData);
void fileOperationSaveSingle(Pemesanan bookings[], int totalData, string targetNIK);

void chooseMenuInMenu1();
void chooseMenuInMenu2();
void chooseMenuInMenu3();
void chooseMenuInMenu5();

int main() {
    cout << "Hello word";
    cout << "casting";
    int pilihanMenu;

    do {   
        // cout << "[MAIN MENU]"<< endl;
        // cout << "   1. Book your ticket"                           << endl;
        // cout << "   2. Show your ticket information (Searching)"   << endl;
        // cout << "   3. Show all ticket information (Sorting)"      << endl;
        // cout << "   4. Recursive"                                  << endl;
        // cout << "   5. Print ticket"                               << endl;
        // cout << "   6. Exit"                                       << endl;
        // cout << "   Choose your option : ";
        // cin >> chooseMenu;
        // cout << endl;
        cout << "[MENU UTAMA]"<< endl;
        cout << "   1. Login Akun dan Pesan Tiket"          << endl;
        cout << "   2. Cari Tiket (Searching)"              << endl;
        cout << "   3. Tampilkan Seluruh Tiket (Sorting)"   << endl;
        cout << "   4. Cetak Tiket"                         << endl;
        cout << "   5. Lihat Tiket"                         << endl;
        cout << "   5. Edit Tiket"                          << endl;
        cout << "   6. Hapus Tiket"                         << endl;
        cout << "   7. Exit"                                << endl;
        cout << "   Pilih Menu Anda your option : ";
        cin >> pilihanMenu;
        cout << endl;

        switch (pilihanMenu) {
            case 1: { chooseMenuInMenu1();      break; }
            case 2: { chooseMenuInMenu2();      break; }
            case 3: { chooseMenuInMenu3();      break; }
            case 4: { cout << endl << endl;     break;}
            case 5: { chooseMenuInMenu5();      break; }
            case 6: { cout << "   Exit..." << endl << endl; break; }
            default: {cout << "   Invalid Option! \n\n";break; }
        }

    } while (pilihanMenu != 6);
}

void chooseMenuInMenu1() {
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
            case 3: {   
                cout << "   Exit..."<< endl << endl; 
                break; 
            }

            default:{   
                cout << "   Invalid"<< endl << endl; 
                break; 
            }
        }
    } while (chooseMenuInMenu1 != 3);

    cout << endl;
}

void chooseMenuInMenu2(){
    int chooseMenuInMenu2;
    do {
        cout << "\n[YOUR TICKET INFORMATION]"<< endl;
        cout << "   1. Sequential Non Sentinel Search Not Yet Sorted"  << endl;
        cout << "   2. Sequential Sentinel Search Not Yet Sorted"      << endl;
        cout << "   3. Binary Search"                                  << endl;
        cout << "   4. Back to main menu"                              << endl;
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
                Pemesanan copy[30];
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
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
}

void chooseMenuInMenu3() {
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
                Pemesanan copy[30];
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }
                bubbleSort(copy);
                sortingOutputShow(copy); 
                cout << endl;
                break;  
            }
            case 2: {   
                Pemesanan copy[30];
                
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }
                straightInsertionSort(copy);
                sortingOutputShow(copy);  

                cout << endl;

                break;  
            }
            case 3: {   
                Pemesanan copy[30];
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }
                
                selectionSort(copy);
                sortingOutputShow(copy);   
                
                cout << endl << endl;
                
                break;  
            }
            case 4: {   
                Pemesanan copy[30];
                
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }

                shellSort(copy);
                sortingOutputShow(copy);     
                            
                cout << endl;

                break;  
            }
            case 5: {   
                Pemesanan copy[30];

                int i;
                for (i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }

                //Booking *copyPointer = &copy[i];
                
                int first = 0;
                int last = indexKeberangkatan - 1;
                
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
}

void chooseMenuInMenu5() {
    int chooseMenuInMenu5;
                
    do {
        cout << "[PRINT TICKET]" << endl;
        cout << "   1. Print all ticket"    << endl;
        cout << "   2. Print your ticket"   << endl;
        cout << "   3. Back to main menu"   << endl;
        cout << "   Choose your option : ";
        cin >> chooseMenuInMenu5;
        cout << endl;

        switch (chooseMenuInMenu5) {
            case 1: {
                fileOperationSave (pemesanan, indexKeberangkatan);
                break;
            }
            case 2: {
                string inputNIK;
                
                cout << "   Input your NIK : ";
                cin >> inputNIK;
                
                fileOperationSaveSingle(pemesanan, indexKeberangkatan, inputNIK);
                
                break;
            }
            case 3: {
                break;
            }
            default: {
                break;
            }
        }
    } while(chooseMenuInMenu5 != 3);
    
    cout << endl << endl;
}

void autoBookTicket() {
    if (indexKeberangkatan >= 30) {
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

    for (int g = 0; g < nomorGerbong && !foundSeat; g++) {
        for (int s = 0; s < tempatDudukGerbong && !foundSeat; s++) {
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

        for (int i = 0; i < indexKeberangkatan; i++) {
            if (pemesanan[i].penumpang.nik == generatedNIK) {
                isDuplicate = true;
                break;
            }
        }
    } while (isDuplicate);

    // Generate unique Name
    string baseName = sampleNames[rand() % 8];
    string uniqueName = baseName + "-" + to_string(indexKeberangkatan + 1);

    // Assign data ke bookings
    seatsEachPortal[coach][seat] = true;
    Pemesanan &b = pemesanan[indexKeberangkatan];

    // b.passenger.name    = sampleNames[rand() % 8];
    b.penumpang.nama    = uniqueName;
    b.penumpang.nik     = generatedNIK;
    b.penumpang.alamat = sampleAddresses[rand() % 4];

    // b.tiket.asalKota     = kotaAsal[rand() % 5];
    b.tiket.kotaTujuan   = destinationsCity[rand() % 5];
    b.tiket.nomorGerbong       = coach;
    b.tiket.nomorTempatDuduk        = seat;
    b.tiket.tanggalKeberangkatan        = "2025-04-01";

    b.pembayaran.metodePembayaran    = paymentMethods[rand() % 3];
    b.pembayaran.sudahDibayar           = true;
    b.pembayaran.totalHarga       = 100000;

    cout << "   [RESULT] Pemesanan otomatis berhasil untuk " << b.penumpang.nama
         << " dengan NIK " << b.penumpang.nik
         << " di kursi " << coach + 1
         << "-" << seat + 1 << endl;

    indexKeberangkatan++;
}


void manualInput() {
    if (indexKeberangkatan >= 30) {
        cout << "   Semua kursi telah dipesan!" << endl;
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
    


    // cout << "[DEPARTURE CITY MENU]" << endl;
    // for (int i = 0; i < 5; i++) {
    //     cout << i + 1 << ". " << kotaAsal[i] <<endl;
    // }
    // cout << "   Choose your option: ";
    // cin >> chooseDepartureCity;
    // pemesanan[indexKeberangkatan].tiket.asalKota = kotaAsal[chooseDepartureCity - 1];



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

    cout << "   [RESULT] Your ticket booking was successful!" << endl;
    indexKeberangkatan++;
}

void searchByNIK() {
    bool found = false;
    for (int i = 0; i < indexKeberangkatan; ++i) {
        found = true;
        cout << "\n[FOUND - TICKET]\n";
        cout << "   Nama       : " << pemesanan[i].penumpang.nama << endl;
        cout << "   NIK        : " << pemesanan[i].penumpang.nik << endl;
        cout << "   Asal       : " << pemesanan[i].tiket.asalKota << endl;
        cout << "   Tujuan     : " << pemesanan[i].tiket.kotaTujuan << endl;
        cout << "   Kursi      : " << pemesanan[i].tiket.nomorGerbong << "-" << pemesanan[i].tiket.nomorTempatDuduk << endl;
        cout << "   Total Bayar: Rp" << pemesanan[i].pembayaran.totalHarga << endl;
        break;    
    }
}

void seqNonSentinelNotYetSorted(string *nikPointer){
    bool found = false;
    int i = 0;

    while (
        (i < indexKeberangkatan) && 
        (!found)
    ) {
        if (pemesanan[i].penumpang.nik == *nikPointer) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        cout << "\n[FOUND - NIK]\n";
        cout << "   Nama       : " << pemesanan[i].penumpang.nama << endl;
        cout << "   NIK        : " << pemesanan[i].penumpang.nik << endl;
        cout << "   Asal       : " << pemesanan[i].tiket.asalKota << endl;
        cout << "   Tujuan     : " << pemesanan[i].tiket.kotaTujuan << endl;
        cout << "   Kursi      : " << pemesanan[i].tiket.nomorGerbong + 1 << "-" << pemesanan[i].tiket.nomorTempatDuduk + 1 << endl;
        cout << "   Total Bayar: Rp" << pemesanan[i].pembayaran.totalHarga << endl << endl;
    } else {
        cout << "   NIK not found!\n";
    }
}

void seqSentinelNotYetSorted(string *nikPointer) {
    Pemesanan tempBackup = pemesanan[indexKeberangkatan];
    
    pemesanan[indexKeberangkatan].penumpang.nik = *nikPointer;

    int i = 0;
    // bool found = false;
    while (pemesanan[i].penumpang.nik != *nikPointer) {
        i++;
    }

    // Kembalikan data terakhir ke semula
    pemesanan[indexKeberangkatan] = tempBackup;

    if (i < indexKeberangkatan) {
        cout << "\n[FOUND - NIK]\n";
        cout << "   Nama       : " << pemesanan[i].penumpang.nama << endl;
        cout << "   NIK        : " << pemesanan[i].penumpang.nik << endl;
        cout << "   Asal       : " << pemesanan[i].tiket.asalKota << endl;
        cout << "   Tujuan     : " << pemesanan[i].tiket.kotaTujuan << endl;
        cout << "   Kursi      : " << pemesanan[i].tiket.nomorGerbong + 1 << "-" << pemesanan[i].tiket.nomorTempatDuduk + 1 << endl;
        cout << "   Total Bayar: Rp" << pemesanan[i].pembayaran.totalHarga << endl << endl;
    } else {
        cout << "   NIK not found!\n";
    }
}

void binarySearch(Pemesanan *copyBinary, string *nikPointer) {
    bubbleSortByNik(copyBinary);

    int i, j, k;
    bool found;

    found = false;
    i = 0;
    j = indexKeberangkatan;

    while((i <= j) && (!found)){
        k  = (i + j) / 2;
        if (*nikPointer == copyBinary[k].penumpang.nik) {
            found = true;
        } else {
            if (*nikPointer < copyBinary[k].penumpang.nik) {
                j = k - 1;
            } else {
                i = k + 1;
            }
        }
    }

    if (found) {
        cout << "\n[FOUND - NIK]\n";
        cout << "   Nama       : " << copyBinary[k].penumpang.nama << endl;
        cout << "   NIK        : " << copyBinary[k].penumpang.nik << endl;
        cout << "   Asal       : " << copyBinary[k].tiket.asalKota << endl;
        cout << "   Tujuan     : " << copyBinary[k].tiket.kotaTujuan << endl;
        cout << "   Kursi      : " << copyBinary[k].tiket.nomorGerbong + 1 << "-" << copyBinary[k].tiket.nomorTempatDuduk + 1 << endl;
        cout << "   Total Bayar: Rp" << copyBinary[k].pembayaran.totalHarga << endl << endl;
    } else {
        cout << "   NIK not found!\n";
    }
}

void bubbleSortByNik(Pemesanan *copyBubleNik) {
    for (int i = 0; i < indexKeberangkatan - 1; i++) {
        for (int j = 0; j < indexKeberangkatan - 1 - i; j++) {    
            if (copyBubleNik[j].penumpang.nik > copyBubleNik[j + 1].penumpang.nik) {
                Pemesanan temp        = copyBubleNik[j];
                copyBubleNik[j]     = copyBubleNik[j + 1];
                copyBubleNik[j + 1] = temp;
            }
        }
    }
}

void bubbleSort(Pemesanan *copyBubble) {
    for (int i = 0; i < indexKeberangkatan - 1; i++) {
        for (int j = 0; j < indexKeberangkatan - 1 - i; j++) {
            if (copyBubble[j].penumpang.nama > copyBubble[j + 1].penumpang.nama) {
                Pemesanan temp      = copyBubble[j];
                copyBubble[j]     = copyBubble[j + 1];
                copyBubble[j + 1] = temp;
            }
        }
    }
}

void straightInsertionSort(Pemesanan *copyInsertion) {
    int i, j;
    Pemesanan temp;

    for (i = 1; i < indexKeberangkatan; i++) {
        temp = copyInsertion[i];
        j = i - 1;
        while ((j >= 0) && (temp.penumpang.nama < copyInsertion[j].penumpang.nama) ) {
            copyInsertion[j + 1] = copyInsertion[j];
            j                    = j - 1;
            copyInsertion[j + 1] = temp;
        }
    }
}

void selectionSort(Pemesanan *copySelection) {
    for (int current = 0; current < indexKeberangkatan; current++) {
        for (int j = current + 1; j < indexKeberangkatan; j++) {
            if (copySelection[current].penumpang.nama > copySelection[j].penumpang.nama) {
                Pemesanan temp            = copySelection[current];
                copySelection[current]  = copySelection[j];
                copySelection[j]        = temp;
            }
        }
    }
}

void shellSort(Pemesanan *copyShell) {
    for (int k = indexKeberangkatan / 2; k > 0; k /= 2) {
        for (int j = k; j < indexKeberangkatan; j++) {
            for (int i = j - k; i >= 0; i -= k) {
                if (copyShell[i + k].penumpang.nama > copyShell[i].penumpang.nama) {
                    break;
                } else {
                    Pemesanan mid      = copyShell[i];
                    copyShell[i]     = copyShell[i + k];
                    copyShell[i + k] = mid;
                }
            }
        } 
    }
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
}

void sortingOutputShow(Pemesanan *sortingShow) {
    cout << "[ALL BOOKING DATA - AFTER SORTED (A-Z)]\n";
    for (int i = 0; i < indexKeberangkatan; i++) {
        cout << "   " << i + 1  << ". Nama: "   << sortingShow[i].penumpang.nama 
                                << ", NIK: "    << sortingShow[i].penumpang.nik 
                                << ", Asal: "   << sortingShow[i].tiket.asalKota 
                                << ", Tujuan: " << sortingShow[i].tiket.kotaTujuan 
                                << endl;
    }
    cout << endl;
}

void fileOperationSave(Pemesanan bookings[], int totalData) {
    FILE *fp;
    fp = fopen("ticket_data.txt", "w");

    if (fp == NULL) {
        cout << "Failed to open file!" << endl;
        return;
    }

    for (int i = 0; i < totalData; i++) {
        fprintf(fp, "==============================\n");
        fprintf(fp, "         TRAIN TICKET\n");
        fprintf(fp, "==============================\n");
        fprintf(fp, "Name           : %s\n", bookings[i].penumpang.nama.c_str());
        fprintf(fp, "NIK            : %s\n", bookings[i].penumpang.nik.c_str());
        fprintf(fp, "Address        : %s\n", bookings[i].penumpang.alamat.c_str());
        fprintf(fp, "Departure City : %s\n", bookings[i].tiket.asalKota.c_str());
        fprintf(fp, "Destination    : %s\n", bookings[i].tiket.kotaTujuan.c_str());
        fprintf(fp, "Coach - Seat   : %d - %d\n", bookings[i].tiket.nomorGerbong + 1, bookings[i].tiket.nomorTempatDuduk + 1);
        fprintf(fp, "Travel Date    : %s\n", bookings[i].tiket.tanggalKeberangkatan.c_str());
        fprintf(fp, "Payment Method : %s\n", bookings[i].pembayaran.metodePembayaran.c_str());
        fprintf(fp, "Paid           : %s\n", bookings[i].pembayaran.sudahDibayar ? "Yes" : "No");
        fprintf(fp, "Total Price    : Rp%d\n", bookings[i].pembayaran.totalHarga);
        fprintf(fp, "==============================\n\n");
    }

    fclose(fp);
    printf("    All ticket has been saved successfully.\n");
}

void fileOperationSaveSingle(Pemesanan bookings[], int totalData, string targetNIK) {
    bool found = false;

    for (int i = 0; i < totalData; i++) {
        if (bookings[i].penumpang.nik == targetNIK) {
            string fileName = targetNIK + "_ticket_data.txt";
            FILE *fp;
            fp = fopen(fileName.c_str(), "w");

            if (fp == NULL) {
                cout << "   Failed to open ticket file!\n";
                return;
            }

            fprintf(fp, "==============================\n");
            fprintf(fp, "         TRAIN TICKET\n");
            fprintf(fp, "==============================\n");
            fprintf(fp, "Name           : %s\n", bookings[i].penumpang.nama.c_str());
            fprintf(fp, "NIK            : %s\n", bookings[i].penumpang.nik.c_str());
            fprintf(fp, "Address        : %s\n", bookings[i].penumpang.alamat.c_str());
            fprintf(fp, "Departure City : %s\n", bookings[i].tiket.asalKota.c_str());
            fprintf(fp, "Destination    : %s\n", bookings[i].tiket.kotaTujuan.c_str());
            fprintf(fp, "Coach - Seat   : %d - %d\n", bookings[i].tiket.nomorGerbong + 1, bookings[i].tiket.nomorTempatDuduk + 1);
            fprintf(fp, "Travel Date    : %s\n", bookings[i].tiket.tanggalKeberangkatan.c_str());
            fprintf(fp, "Payment Method : %s\n", bookings[i].pembayaran.metodePembayaran.c_str());
            fprintf(fp, "Paid           : %s\n", bookings[i].pembayaran.sudahDibayar ? "Yes" : "No");
            fprintf(fp, "Total Price    : Rp%d\n", bookings[i].pembayaran.totalHarga);
            fprintf(fp, "==============================\n");

            fclose(fp);

            cout << "   Ticket has been saved successfully: " << fileName << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "   Data not found.\n";
    }
}