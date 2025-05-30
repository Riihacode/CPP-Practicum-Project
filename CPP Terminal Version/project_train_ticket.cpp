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

// Searching
void searchByNIK();
void searchSeqNonSentinelBelumUrut(string *pointerNIK);
void searchSeqSentinelBelumUrut(string *pointerNIK);
void searchBinarySearch(Pemesanan *copyBinary, string *nikPointer);

// Sorting
void bubbleSortBerdasarNik(Pemesanan *copyBubleNik);
void bubbleSort(Pemesanan *copyBubble);
void straightInsertionSort(Pemesanan *copyInsertion);
void selectionSort(Pemesanan *copySelection);
void shellSort(Pemesanan *copyShell);
void quickSort(Pemesanan *copyQuick, int first, int last);
void tampilkanDataSetelahSorting(Pemesanan *dataSorting);

// File Opearation
void fileSave(Pemesanan bookings[], int totalData);
void fileSaveTiketSingle(Pemesanan bookings[], int totalData, string targetNIK);

void menuLoginDanPesanTiket();
void menuCariTiket();
void menuTampilkanSeluruhTiket();
void pilihMenu5();

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
        cout << "   6. Edit Tiket"                          << endl;
        cout << "   7. Hapus Tiket"                         << endl;
        cout << "   8. Exit"                                << endl;
        cout << "   Pilih Menu : ";
        cin >> pilihanMenu;
        cout << endl;

        switch (pilihanMenu) {
            case 1: { menuLoginDanPesanTiket();     break; }
            case 2: { menuCariTiket();              break; }
            case 3: { menuTampilkanSeluruhTiket();  break; }
            case 4: {     break;}
            case 5: { pilihMenu5();      break; }
            case 6: { cout << "   Exit..." << endl << endl; break; }
            default: {cout << "   Invalid Option! \n\n";break; }
        }

    } while (pilihanMenu != 8);
}

void menuLoginDanPesanTiket() {
    int pilihMenu;

    do {
        cout << "[PESAN TIKET ANDA]"                << endl;
        cout << "   1. Generate Data Customer"      << endl;
        cout << "   2. Manual Input Data Customer"  << endl;
        cout << "   3. Kembali ke Menu Utama"       << endl;
        cout << "   Pilih Menu : ";
        cin >> pilihMenu;
        cout << endl;

        switch (pilihMenu){
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
    } while (pilihMenu != 3);

    cout << endl;
}

void menuCariTiket(){
    int pilihMenu;
    do {
        cout << "\n[INFORMASI TIKET ANDA]"<< endl;
        cout << "   1. Searching Sequential Non Sentinel Belum Urut"    << endl;
        cout << "   2. Searching Sequential Sentinel Search Belum Urut" << endl;
        cout << "   3. Binary Search"                                   << endl;
        cout << "   4. Kembali ke Menu Utama"                           << endl;
        cout << "   Pilih Menu : ";
        cin >> pilihMenu;
        cout << endl;
        
        switch(pilihMenu) {
            case 1: {   
                string searchNIK;
                cout << "   Input NIK yang ingin anda cari : ";
                cin >> searchNIK;
                            
                searchSeqNonSentinelBelumUrut(&searchNIK); 
                cout << endl << endl; 
                break;  
            }
            case 2: {
                string searchNIK;
                cout << "   Input NIK yang ingin anda cari : ";
                cin >> searchNIK; 
                
                searchSeqSentinelBelumUrut(&searchNIK);      
                
                cout << endl << endl;
                break;  
            }
            
            case 3: {   
                Pemesanan copy[30];
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }

                string searchNIK;

                cout << "   Input NIK yang ingin anda cari : ";
                cin >> searchNIK; 

                searchBinarySearch(copy, &searchNIK);
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
    } while (pilihMenu != 4);
    cout << endl;
}

void menuTampilkanSeluruhTiket() {
    int pilihMenu3;
    do {
        cout << "[ALL TICKET INFORMATION]"    << endl;
        cout << "   1. Bubble Sort"                                    << endl;
        cout << "   2. Straight Insertion Sort"                        << endl;
        cout << "   3. Straight Selection Sort"                        << endl;
        cout << "   4. Shell Sort"                                     << endl;
        cout << "   5. Quick Sort"                                     << endl;
        cout << "   6. Back to main menu"                              << endl;
        cout << "   Choose your option: ";
        cin >> pilihMenu3;
        cout << endl;
        switch(pilihMenu3) {
            case 1: {
                Pemesanan copy[30];
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }
                bubbleSort(copy);
                tampilkanDataSetelahSorting(copy); 
                cout << endl;
                break;  
            }
            case 2: {   
                Pemesanan copy[30];
                
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }
                straightInsertionSort(copy);
                tampilkanDataSetelahSorting(copy);  

                cout << endl;

                break;  
            }
            case 3: {   
                Pemesanan copy[30];
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }
                
                selectionSort(copy);
                tampilkanDataSetelahSorting(copy);   
                
                cout << endl << endl;
                
                break;  
            }
            case 4: {   
                Pemesanan copy[30];
                
                for (int i = 0; i < indexKeberangkatan; i++) {
                    copy[i] = pemesanan[i];
                }

                shellSort(copy);
                tampilkanDataSetelahSorting(copy);     
                            
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
                tampilkanDataSetelahSorting(copy);

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
    } while (pilihMenu3 != 6);
}

void pilihMenu5() {
    int pilihMenu;
                
    do {
        cout << "[CETAK TIKET]" << endl;
        cout << "   1. Cetak Seluruh Tiket"     << endl;
        cout << "   2. Cetak Tiket Anda"        << endl;
        cout << "   3. Kembali ke Menu Utama"   << endl;
        cout << "   Pilih Menu : ";
        cin >> pilihMenu;
        cout << endl;

        switch (pilihMenu) {
            case 1: {
                fileSave (pemesanan, indexKeberangkatan);
                break;
            }
            case 2: {
                string inputNIK;
                
                cout << "   Input NIK anda : ";
                cin >> inputNIK;
                
                fileSaveTiketSingle(pemesanan, indexKeberangkatan, inputNIK);
                
                break;
            }
            case 3: {
                break;
            }
            default: {
                break;
            }
        }
    } while(pilihMenu != 3);
    
    cout << endl << endl;
}

void autoBookTicket() {
    if (indexKeberangkatan >= 30) {
        cout << "Seluruh Kursi Telah Dipesan!" << endl;
        return;
    }

    string sampelNama[]         = {"Budi", "Ani", "Citra", "Dedi", "Eka", "Fajar", "Gita", "Hana"};
    string sampelAlamat[]       = {"Yogyakarta", "Sleman", "Bantul", "Kulon Progo"};
    string kotaTujuan[]         = {"Semarang", "Jepara", "Magelang", "Cilacap", "Boyolali"};
    string metodePembayaran[]   = {"Transfer", "E-Wallet", "Cash"};

    srand(time(0));

    // Cari kursi kosong
    int gerbong = -1;
    int kursi = -1;
    bool foundKursi = false;

    for (int g = 0; g < nomorGerbong && !foundKursi; g++) {
        for (int s = 0; s < tempatDudukGerbong && !foundKursi; s++) {
            if (!kursiTiapGerbong[g][s]) {
                gerbong = g;
                kursi = s;
                foundKursi = true;
            }
        }
    }

    if (!foundKursi) {
        cout << "Tidak ada kursi kosong" << endl;
        return;
    }

    // Generate unique NIK
    string generatedNIK;
    bool terduplikat;
    do {
        terduplikat = false;
        int randomNIK = 100000000 + rand() % 900000000; // Random 9 digit
        generatedNIK = to_string(randomNIK);

        for (int i = 0; i < indexKeberangkatan; i++) {
            if (pemesanan[i].penumpang.nik == generatedNIK) {
                terduplikat = true;
                break;
            }
        }
    } while (terduplikat);

    // Generate unique Name
    string namaDasar = sampelNama[rand() % 8];
    string namaUnique = namaDasar + "-" + to_string(indexKeberangkatan + 1);

    // Assign data ke bookings
    kursiTiapGerbong[gerbong][kursi] = true;
    Pemesanan &booking = pemesanan[indexKeberangkatan];

    // b.passenger.name    = sampleNames[rand() % 8];
    booking.penumpang.nama    = namaUnique;
    booking.penumpang.nik     = generatedNIK;
    booking.penumpang.alamat  = sampelAlamat[rand() % 4];

    // b.tiket.asalKota     = kotaAsal[rand() % 5];
    booking.tiket.kotaTujuan            = kotaTujuan[rand() % 5];
    booking.tiket.nomorGerbong          = gerbong;
    booking.tiket.nomorTempatDuduk      = kursi;
    booking.tiket.tanggalKeberangkatan  = "2025-04-01";

    booking.pembayaran.metodePembayaran = metodePembayaran[rand() % 3];
    booking.pembayaran.sudahDibayar     = true;
    booking.pembayaran.totalHarga       = 100000;

    cout << "   [HASIL] Pemesanan otomatis berhasil untuk " << booking.penumpang.nama
         << " dengan NIK " << booking.penumpang.nik
         << " di kursi " << gerbong + 1
         << "-" << kursi + 1 << endl;

    indexKeberangkatan++;
}


void manualInput() {
    if (indexKeberangkatan >= 30) {
        cout << "   Semua kursi telah dipesan!" << endl;
        return;
    }

    // int chooseDepartureCity, chooseDestinationCity, chooseTrainClass, choosePayment;
    int pilihKotaTujuan, pilihPembayaran;
    int nomorGerbong, nomorKursi;

    cout << "[INPUT DATA PRIBADI]"<<endl;
    cout << "   Nama       : ";
    cin.ignore();
    getline(cin, pemesanan[indexKeberangkatan].penumpang.nama);
    cout << "   NIK        : ";
    getline(cin, pemesanan[indexKeberangkatan].penumpang.nik);
    cout << "   Alamat     : ";
    getline(cin, pemesanan[indexKeberangkatan].penumpang.alamat);
    cout << endl << endl;
    


    // cout << "[DEPARTURE CITY MENU]" << endl;
    // for (int i = 0; i < 5; i++) {
    //     cout << i + 1 << ". " << kotaAsal[i] <<endl;
    // }
    // cout << "   Choose your option: ";
    // cin >> chooseDepartureCity;
    // pemesanan[indexKeberangkatan].tiket.asalKota = kotaAsal[chooseDepartureCity - 1];



    cout << "\n[MENU KOTA TUJUAN]" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "   " << i + 1 << ". " << kotaTujuan[i] <<endl;
    }
    cout << "   Choose your option: ";
    cin >> pilihKotaTujuan;
    pemesanan[indexKeberangkatan].tiket.kotaTujuan = kotaTujuan[pilihKotaTujuan - 1];



    // Menampilkan kursi kosong
    cout << "\n[KURSI YANG TERSEDIA]" << endl;
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

    

    cout << "\n[PILIH KURSI]" << endl;
    cout << "   Pilih Gerbong Kereta (1 - 3) : ";
    cin >> nomorGerbong; nomorGerbong -= 1;
    cout << "   Pilih Nomor Kursi (1 - 10)   : ";
    cin >> nomorKursi;  nomorKursi  -= 1;

    if (kursiTiapGerbong[nomorGerbong][nomorKursi]) {
        cout << "       Nomor Kursi Telah Dipesan!";
        return;
    }

    kursiTiapGerbong[nomorGerbong][nomorKursi]    = true;
    pemesanan[indexKeberangkatan].tiket.nomorGerbong = nomorGerbong;
    pemesanan[indexKeberangkatan].tiket.nomorTempatDuduk  = nomorKursi;
    pemesanan[indexKeberangkatan].tiket.tanggalKeberangkatan  = "2025-04-01";  // Fixed dulu



    cout << "\n[PAYMENT METHOD]" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   " << i + 1 << ". " << metodePembayaran[i] << endl;
    }
    cout << "   Choose your option: ";
    cin >> pilihPembayaran;
    pemesanan[indexKeberangkatan].pembayaran.metodePembayaran  = metodePembayaran[pilihPembayaran - 1];
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

void searchSeqNonSentinelBelumUrut(string *pointerNIK){
    bool found = false;
    int i = 0;

    while (
        (i < indexKeberangkatan) && 
        (!found)
    ) {
        if (pemesanan[i].penumpang.nik == *pointerNIK) {
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

void searchSeqSentinelBelumUrut(string *pointerNIK) {
    Pemesanan cadanganData = pemesanan[indexKeberangkatan];
    
    pemesanan[indexKeberangkatan].penumpang.nik = *pointerNIK;

    int i = 0;
    // bool found = false;
    while (pemesanan[i].penumpang.nik != *pointerNIK) {
        i++;
    }

    // Kembalikan data terakhir ke semula
    pemesanan[indexKeberangkatan] = cadanganData;

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

void searchBinarySearch(Pemesanan *copyBinary, string *nikPointer) {
    bubbleSortBerdasarNik(copyBinary);

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

void bubbleSortBerdasarNik(Pemesanan *copyBubleNik) {
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

void quickSort(Pemesanan *pemesananQuick, int first, int last) {
    int low, high;

    low     = first;
    high    = last;

    Pemesanan listSeparator = pemesananQuick[(first + last) / 2];

    do {
        while (pemesananQuick[low].penumpang.nama < listSeparator.penumpang.nama) {
            low++;
        }
        while (pemesananQuick[high].penumpang.nama > listSeparator.penumpang.nama) {
            high--;
        }

        if (low <= high) {
            Pemesanan temp            = pemesananQuick[low];
            pemesananQuick[low++]    = pemesananQuick[high];
            pemesananQuick[high--]   = temp;
        }
    } while (low <= high);

    if (first < high)   { quickSort(pemesananQuick, first, high); };
    if (low < last)     { quickSort(pemesananQuick, low, last);   };
}

void tampilkanDataSetelahSorting(Pemesanan *dataSorting) {
    cout << "[SEMUA DATA PEMESANAN - SETELAH DIURUTKAN (A-Z)]\n";
    for (int i = 0; i < indexKeberangkatan; i++) {
        cout << "   " << i + 1  << ". Nama: "   << dataSorting[i].penumpang.nama 
                                << ", NIK: "    << dataSorting[i].penumpang.nik 
                                << ", Asal: "   << dataSorting[i].tiket.asalKota 
                                << ", Tujuan: " << dataSorting[i].tiket.kotaTujuan 
                                << endl;
    }
    cout << endl;
}

void fileSave(Pemesanan bookings[], int totalData) {
    FILE *fp;
    fp = fopen("ticket_data.txt", "w");

    if (fp == NULL) {
        cout << "Gagal Membuka File!" << endl;
        return;
    }

    for (int i = 0; i < totalData; i++) {
        fprintf(fp, "==============================\n");
        fprintf(fp, "         TIKET KERETA\n");
        fprintf(fp, "==============================\n");
        fprintf(fp, "Nama                   : %s\n", bookings[i].penumpang.nama.c_str());
        fprintf(fp, "NIK                    : %s\n", bookings[i].penumpang.nik.c_str());
        fprintf(fp, "Alamat                 : %s\n", bookings[i].penumpang.alamat.c_str());
        // fprintf(fp, "Departure City : %s\n", bookings[i].tiket.asalKota.c_str());
        fprintf(fp, "Kota Tujuan            : %s\n", bookings[i].tiket.kotaTujuan.c_str());
        fprintf(fp, "Gerbong - Kursi        : %d - %d\n", bookings[i].tiket.nomorGerbong + 1, bookings[i].tiket.nomorTempatDuduk + 1);
        fprintf(fp, "Tanggal Keberangkatan  : %s\n", bookings[i].tiket.tanggalKeberangkatan.c_str());
        fprintf(fp, "Metode Pembayaran      : %s\n", bookings[i].pembayaran.metodePembayaran.c_str());
        fprintf(fp, "Sudah Dibayar          : %s\n", bookings[i].pembayaran.sudahDibayar ? "Yes" : "No");
        fprintf(fp, "Total Harga            : Rp%d\n", bookings[i].pembayaran.totalHarga);
        fprintf(fp, "==============================\n\n");
    }

    fclose(fp);
    printf("    Seluruh tiket telah disimpan.\n");
}

void fileSaveTiketSingle(Pemesanan bookings[], int totalData, string targetNIK) {
    bool found = false;

    for (int i = 0; i < totalData; i++) {
        if (bookings[i].penumpang.nik == targetNIK) {
            string namaFile = targetNIK + "_ticket_data.txt";
            FILE *fp;
            fp = fopen(namaFile.c_str(), "w");

            if (fp == NULL) {
                cout << "   Failed to open ticket file!\n";
                return;
            }

            fprintf(fp, "==============================\n");
            fprintf(fp, "         TIKET KERETA\n");
            fprintf(fp, "==============================\n");
            fprintf(fp, "Nama                   : %s\n", bookings[i].penumpang.nama.c_str());
            fprintf(fp, "NIK                    : %s\n", bookings[i].penumpang.nik.c_str());
            fprintf(fp, "Alamat                 : %s\n", bookings[i].penumpang.alamat.c_str());
            // fprintf(fp, "Departure City : %s\n", bookings[i].tiket.asalKota.c_str());
            fprintf(fp, "Kota Tujuan            : %s\n", bookings[i].tiket.kotaTujuan.c_str());
            fprintf(fp, "Gerbong - Kursi        : %d - %d\n", bookings[i].tiket.nomorGerbong + 1, bookings[i].tiket.nomorTempatDuduk + 1);
            fprintf(fp, "Tanggal Keberangkatan  : %s\n", bookings[i].tiket.tanggalKeberangkatan.c_str());
            fprintf(fp, "Metode Pembayaran      : %s\n", bookings[i].pembayaran.metodePembayaran.c_str());
            fprintf(fp, "Sudah Dibayar          : %s\n", bookings[i].pembayaran.sudahDibayar ? "Yes" : "No");
            fprintf(fp, "Total Harga            : Rp%d\n", bookings[i].pembayaran.totalHarga);
            fprintf(fp, "==============================\n\n");

            fclose(fp);

            cout << "   Tiket telah disimpan: " << namaFile << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "   Data tidak ditemukan.\n";
    }
}