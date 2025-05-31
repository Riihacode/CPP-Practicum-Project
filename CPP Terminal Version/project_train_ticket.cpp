#include <iostream>
#include <string>
#include <cstdlib>  // untuk rand()
#include <ctime>    // untuk time()
#include <fstream>

using namespace std;

const int nomorGerbong = 3;
const int tempatDudukGerbong = 10;
const int maxTanggal = 10; // Jumlah maksimum tanggal simulasi
const int maksPemesananPerTanggal = 30; // Kuota per tanggal

bool kursiTiapGerbong[nomorGerbong][tempatDudukGerbong];

struct GuestAccount {
    string email = "guestaccount@gmail.com";
    string password = "12345678";
};

struct Tujuan {
    string kota;
    int harga;
};

// struct Penumpang {
//     string nama;
//     string nik;
//     string alamat;
// };
struct Penumpang {
    string nama;      // Nama lengkap penumpang
    string nik;       // Nomor Induk Kependudukan (atau passport)
    string alamat;    // Alamat domisili
    int umur;         // Umur penumpang
    string noHp;      // Nomor telepon aktif
};

struct InfoTiket{
    string asalKota;
    string kotaTujuan;
    int nomorGerbong;
    int nomorTempatDuduk;
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
GuestAccount guest;

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

string daftarTanggal[maxTanggal] = {
    "30-01-2025", "31-01-2025", "01-02-2025", "02-02-2025", "03-02-2025",
    "04-02-2025", "05-02-2025", "06-02-2025", "07-02-2025", "08-02-2025"
};

Tujuan daftarTujuan[] = {
    {"Solo Balapan", 30000},
    {"Kutoarjo",      30000},
    {"Purwokerto",    60000},
    {"Madiun",        60000},
    {"Semarang",      50000},
    {"Cilacap",       80000},
    {"Tegal",         90000},
    {"Magelang",      25000}
};

const int jumlahTujuan = sizeof(daftarTujuan) / sizeof(daftarTujuan[0]);


bool kursiTerpakai[maxTanggal][nomorGerbong][tempatDudukGerbong] = {};
Pemesanan semuaPemesanan[maxTanggal][maksPemesananPerTanggal];
int jumlahPemesanan[maxTanggal] = {};

int indexKeberangkatan = 0;

//###################
// void autoBookTicket();
// void autoBookTicket(int indexTanggal, string kotaTujuanDipilih);
void autoBookTicket(int indexTanggal, int indexKotaTujuan);
// void manualInput();
// void manualInput(int indexTanggal, string kotaTujuanDipilih);
void manualInput(int indexTanggal, int indexKotaTujuan);

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
void fileSaveTiketSemua(Pemesanan bookings[], int totalData);
void fileSaveTiketSingle(Pemesanan bookings[], int totalData, string targetNIK);

void menuLoginDanPesanTiket();
void menuCariTiket();
void menuTampilkanSeluruhTiket();
void pilihMenu5();

void tampilkanSeluruhDataPemesanan();

// void simpanSemuaTiketKeFile(bool append);
// void simpanTiketPerPenumpang();
// void menuCreateTiket();
void simpanTiketBerdasarkanNIK();
void bacaTiketDariFile();
void updateTiketDariFile();

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
        cout << "   8. Tampilkan Data Tiket (untuk development) \n";
        cout << "   9. Exit"                                << endl;
        cout << "   Pilih Menu : ";
        cin >> pilihanMenu;
        cout << endl;

        switch (pilihanMenu) {
            case 1: { menuLoginDanPesanTiket();     break; }
            case 2: { menuCariTiket();              break; }
            case 3: { menuTampilkanSeluruhTiket();  break; }
            // case 4: { menuCreateTiket(); break; }
            // case 4: { simpanTiketPerPenumpang(); break; }
            case 4: { simpanTiketBerdasarkanNIK(); break; }
            case 5: { bacaTiketDariFile();      break; }
            case 6: { updateTiketDariFile(); break; }
            case 7: { break; }
            case 8: { tampilkanSeluruhDataPemesanan(); break; }
            case 9: { cout << "   Exit..." << endl << endl; break; }
            default: {cout << "   Invalid Option! \n\n";break; }
        }

    } while (pilihanMenu != 9);
}

// void menuCreateTiket() {
//     int pilihMode;
//     cout << "\n[MENU CETAK TIKET]" << endl;
//     cout << "   1. Tulis ulang semua tiket (overwrite)" << endl;
//     cout << "   2. Tambahkan ke file lama (append)" << endl;
//     cout << "   3. Kembali ke menu utama" << endl;
//     cout << "   Pilih mode: ";
//     cin >> pilihMode;

//     switch(pilihMode) {
//         case 1: { simpanSemuaTiketKeFile(false); break; }
//         case 2: { simpanSemuaTiketKeFile(true); break; }
//         case 3: { cout << "    Exit ... "; break; }
//         default: { cout << "   Invalid input" << endl; break; }
//     }
// }

// void menuLoginDanPesanTiket() {
//     int pilihMenu;

//     do {
//         cout << "[PESAN TIKET ANDA]"                << endl;
//         cout << "   1. Generate Data Customer"      << endl;
//         cout << "   2. Manual Input Data Customer"  << endl;
//         cout << "   3. Kembali ke Menu Utama"       << endl;
//         cout << "   Pilih Menu : ";
//         cin >> pilihMenu;
//         cout << endl;

//         switch (pilihMenu){
//             case 1: {   
//                 int indexTanggal;
//                 cout << "\n[PILIH TANGGAL KEBERANGKATAN]" << endl;

//                 for (int i = 0; i < maxTanggal; i++) {
//                     cout << "   " << i + 1 << ". " << daftarTanggal[i] << endl;
//                 }

//                 cout << "   Pilih (1 - " << maxTanggal << "): ";
//                 cin >> indexTanggal;
//                 indexTanggal -= 1; // ubah ke index array

//                 // autoBookTicket();
//                 autoBookTicket(indexTanggal);
//                 cout << endl << endl;
//                 break; 
//             }

//             case 2: {   
//                 manualInput();
//                 cout<< endl << endl; 
//                 break; 
//             }

//             case 3: {   
//                 cout << "   Exit..."<< endl << endl; 
//                 break; 
//             }

//             default:{   
//                 cout << "   Invalid"<< endl << endl; 
//                 break; 
//             }
//         }
//     } while (pilihMenu != 3);

//     cout << endl;
// }

void menuLoginDanPesanTiket() {
    // [1] LOGIN
    string inputEmail, inputPassword;
    cout << "[LOGIN GUEST ACCOUNT]" << endl;
    cout << "   Email    : "; cin >> inputEmail;
    cout << "   Password : "; cin >> inputPassword;

    if (inputEmail != guest.email || inputPassword != guest.password) {
        cout << "   Login gagal! Kembali ke menu utama.\n";
        return;
    }

    cout << "   Login berhasil! Selamat datang, Guest.\n\n";

    // [2] PILIH KOTA TUJUAN
    // cout << "[PILIH KOTA TUJUAN]" << endl;
    // for (int i = 0; i < 5; i++) {
    //     cout << "   " << i + 1 << ". " << kotaTujuan[i] << endl;
    // }
    // int indexKotaTujuan;
    // cout << "   Pilih (1 - 5): ";
    // cin >> indexKotaTujuan;
    // indexKotaTujuan -= 1;
    cout << "[PILIH KOTA TUJUAN]" << endl;
    for (int i = 0; i < jumlahTujuan; i++) {
        cout << "   " << i + 1 << ". " << daftarTujuan[i].kota << " - Rp" << daftarTujuan[i].harga << endl;
    }
    int indexKotaTujuan;
    cout << "   Pilih (1 - " << jumlahTujuan << "): ";
    cin >> indexKotaTujuan;
    indexKotaTujuan -= 1;


    // [3] PILIH TANGGAL
    cout << "\n[PILIH TANGGAL KEBERANGKATAN]" << endl;
    for (int i = 0; i < maxTanggal; i++) {
        cout << "   " << i + 1 << ". " << daftarTanggal[i] << endl;
    }
    int indexTanggal;
    cout << "   Pilih (1 - " << maxTanggal << "): ";
    cin >> indexTanggal;
    indexTanggal -= 1;

    // [4] MASUK SUBMENU
    int pilihMenu;
    do {
        cout << "\n[PESAN TIKET ANDA]" << endl;
        cout << "   1. Generate Data Customer (Auto)" << endl;
        cout << "   2. Manual Input Data Customer" << endl;
        cout << "   3. Kembali ke Menu Utama" << endl;
        cout << "   Pilih Menu : ";
        cin >> pilihMenu;
        cout << endl;

        switch (pilihMenu){
            case 1:
                // autoBookTicket(indexTanggal, kotaTujuan[indexKotaTujuan]);
                autoBookTicket(indexTanggal, indexKotaTujuan);
                break;
            case 2:
                // manualInput(indexTanggal, kotaTujuan[indexKotaTujuan]);
                manualInput(indexTanggal, indexKotaTujuan);
                break;
            case 3:
                cout << "   Kembali ke menu utama..." << endl;
                break;
            default:
                cout << "   Invalid option!\n";
        }
    } while (pilihMenu != 3);
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
                fileSaveTiketSemua (pemesanan, indexKeberangkatan);
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

// void autoBookTicket() {
//     if (indexKeberangkatan >= 30) {
//         cout << "Seluruh Kursi Telah Dipesan!" << endl;
//         return;
//     }

//     string sampelNama[]         = {"Budi", "Ani", "Citra", "Dedi", "Eka", "Fajar", "Gita", "Hana"};
//     string sampelAlamat[]       = {"Yogyakarta", "Sleman", "Bantul", "Kulon Progo"};
//     string kotaTujuan[]         = {"Semarang", "Jepara", "Magelang", "Cilacap", "Boyolali"};
//     string metodePembayaran[]   = {"Transfer", "E-Wallet", "Cash"};

//     srand(time(0));

//     // Cari kursi kosong
//     int gerbong = -1;
//     int kursi = -1;
//     bool foundKursi = false;

//     for (int g = 0; g < nomorGerbong && !foundKursi; g++) {
//         for (int s = 0; s < tempatDudukGerbong && !foundKursi; s++) {
//             if (!kursiTiapGerbong[g][s]) {
//                 gerbong = g;
//                 kursi = s;
//                 foundKursi = true;
//             }
//         }
//     }

//     if (!foundKursi) {
//         cout << "Tidak ada kursi kosong" << endl;
//         return;
//     }

//     // Generate unique NIK
//     string generatedNIK;
//     bool terduplikat;
//     do {
//         terduplikat = false;
//         int randomNIK = 100000000 + rand() % 900000000; // Random 9 digit
//         generatedNIK = to_string(randomNIK);

//         for (int i = 0; i < indexKeberangkatan; i++) {
//             if (pemesanan[i].penumpang.nik == generatedNIK) {
//                 terduplikat = true;
//                 break;
//             }
//         }
//     } while (terduplikat);

//     // Generate unique Name
//     string namaDasar = sampelNama[rand() % 8];
//     string namaUnique = namaDasar + "-" + to_string(indexKeberangkatan + 1);

//     // Assign data ke bookings
//     kursiTiapGerbong[gerbong][kursi] = true;
//     Pemesanan &booking = pemesanan[indexKeberangkatan];

//     // b.passenger.name    = sampleNames[rand() % 8];
//     booking.penumpang.nama    = namaUnique;
//     booking.penumpang.nik     = generatedNIK;
//     booking.penumpang.alamat  = sampelAlamat[rand() % 4];

//     // b.tiket.asalKota     = kotaAsal[rand() % 5];
//     booking.tiket.kotaTujuan            = kotaTujuan[rand() % 5];
//     booking.tiket.nomorGerbong          = gerbong;
//     booking.tiket.nomorTempatDuduk      = kursi;
//     booking.tiket.tanggalKeberangkatan  = "2025-04-01";

//     booking.pembayaran.metodePembayaran = metodePembayaran[rand() % 3];
//     booking.pembayaran.sudahDibayar     = true;
//     booking.pembayaran.totalHarga       = 100000;

//     cout << "   [HASIL] Pemesanan otomatis berhasil untuk " << booking.penumpang.nama
//          << " dengan NIK " << booking.penumpang.nik
//          << " di kursi " << gerbong + 1
//          << "-" << kursi + 1 << endl;

//     indexKeberangkatan++;
// }
// void autoBookTicket(int indexTanggal, string kotaTujuanDipilih) {
void autoBookTicket(int indexTanggal, int indexKotaTujuan) {
    if (jumlahPemesanan[indexTanggal] >= maksPemesananPerTanggal) {
        cout << "   Semua tiket pada tanggal ini telah habis!\n";
        return;
    }

    string sampelNama[]       = {"Budi", "Ani", "Citra", "Dedi", "Eka", "Fajar", "Gita", "Hana"};
    string sampelAlamat[]     = {"Yogyakarta", "Sleman", "Bantul", "Kulon Progo"};
    string metodePembayaran[] = {"Transfer", "E-Wallet", "Cash"};

    srand(time(0));

    int gerbong = -1;
    int kursi = -1;
    bool foundKursi = false;

    // Cari kursi kosong pada tanggal yang dipilih
    for (int g = 0; g < nomorGerbong && !foundKursi; g++) {
        for (int s = 0; s < tempatDudukGerbong && !foundKursi; s++) {
            if (!kursiTerpakai[indexTanggal][g][s]) {
                gerbong = g;
                kursi = s;
                foundKursi = true;
            }
        }
    }

    if (!foundKursi) {
        cout << "   Tidak ada kursi kosong pada tanggal ini\n";
        return;
    }

    // Generate unique NIK
    string generatedNIK;
    bool terduplikat;
    do {
        terduplikat = false;
        int randomNIK = 100000000 + rand() % 900000000;
        generatedNIK = to_string(randomNIK);

        for (int i = 0; i < jumlahPemesanan[indexTanggal]; i++) {
            if (semuaPemesanan[indexTanggal][i].penumpang.nik == generatedNIK) {
                terduplikat = true;
                break;
            }
        }
    } while (terduplikat);

    // Generate nama unik
    string namaDasar  = sampelNama[rand() % 8];
    string namaUnique = namaDasar + "-" + to_string(jumlahPemesanan[indexTanggal] + 1);

    // Simpan data ke struct
    Pemesanan &booking = semuaPemesanan[indexTanggal][jumlahPemesanan[indexTanggal]];

    kursiTerpakai[indexTanggal][gerbong][kursi] = true;

    booking.penumpang.nama     = namaUnique;
    booking.penumpang.nik      = generatedNIK;
    booking.penumpang.alamat   = sampelAlamat[rand() % 4];
    // Tambahan untuk melengkapi data struct Penumpang
    booking.penumpang.umur  = 17 + rand() % 40; // Umur acak 17 - 56 tahun
    // Simulasi No HP unik acak
    string noHpAwal = "08";
    for (int i = 0; i < 10; i++) {
        noHpAwal += to_string(rand() % 10);
    }
    booking.penumpang.noHp = noHpAwal;


    booking.tiket.asalKota               = "Yogyakarta";
    // booking.tiket.kotaTujuan             = kotaTujuanDipilih;
    booking.tiket.kotaTujuan             = daftarTujuan[indexKotaTujuan].kota;
    booking.tiket.nomorGerbong           = gerbong;
    booking.tiket.nomorTempatDuduk       = kursi;
    booking.tiket.tanggalKeberangkatan   = daftarTanggal[indexTanggal];

    booking.pembayaran.metodePembayaran  = metodePembayaran[rand() % 3];
    booking.pembayaran.sudahDibayar      = true;
    // booking.pembayaran.totalHarga        = 100000;
    booking.pembayaran.totalHarga        = daftarTujuan[indexKotaTujuan].harga;

    cout << "   [AUTO-PESAN] Berhasil dipesan oleh " << booking.penumpang.nama
         << " (NIK: " << booking.penumpang.nik << ") pada " << daftarTanggal[indexTanggal]
         << ", Kursi " << gerbong + 1 << "-" << kursi + 1 << endl;

    jumlahPemesanan[indexTanggal]++;
}

// void manualInput() {
//     if (indexKeberangkatan >= 30) {
//         cout << "   Semua kursi telah dipesan!" << endl;
//         return;
//     }

//     // int chooseDepartureCity, chooseDestinationCity, chooseTrainClass, choosePayment;
//     int pilihKotaTujuan, pilihPembayaran;
//     int nomorGerbong, nomorKursi;

//     cout << "[INPUT DATA PRIBADI]"<<endl;
//     cout << "   Nama       : ";
//     cin.ignore();
//     getline(cin, pemesanan[indexKeberangkatan].penumpang.nama);
//     cout << "   NIK        : ";
//     getline(cin, pemesanan[indexKeberangkatan].penumpang.nik);
//     cout << "   Alamat     : ";
//     getline(cin, pemesanan[indexKeberangkatan].penumpang.alamat);
//     cout << endl << endl;
    


//     // cout << "[DEPARTURE CITY MENU]" << endl;
//     // for (int i = 0; i < 5; i++) {
//     //     cout << i + 1 << ". " << kotaAsal[i] <<endl;
//     // }
//     // cout << "   Choose your option: ";
//     // cin >> chooseDepartureCity;
//     // pemesanan[indexKeberangkatan].tiket.asalKota = kotaAsal[chooseDepartureCity - 1];



//     cout << "\n[MENU KOTA TUJUAN]" << endl;
//     for (int i = 0; i < 5; i++) {
//         cout << "   " << i + 1 << ". " << kotaTujuan[i] <<endl;
//     }
//     cout << "   Choose your option: ";
//     cin >> pilihKotaTujuan;
//     pemesanan[indexKeberangkatan].tiket.kotaTujuan = kotaTujuan[pilihKotaTujuan - 1];



//     // Menampilkan kursi kosong
//     cout << "\n[KURSI YANG TERSEDIA]" << endl;
//     for (int i = 0; i < 3; i++) {
//         cout << "   Coach Train-" << i + 1 << " =" << endl;
//         for (int j = 0; j < 10; j++) {
//             if (kursiTiapGerbong[i][j] != false) {
//                 cout << "       [X]" << " ";
//             } else {
//                 cout << "       [" << to_string(j + 1) << "]";
//             }

//         }
//         cout << endl;
//     }

    

//     cout << "\n[PILIH KURSI]" << endl;
//     cout << "   Pilih Gerbong Kereta (1 - 3) : ";
//     cin >> nomorGerbong; nomorGerbong -= 1;
//     cout << "   Pilih Nomor Kursi (1 - 10)   : ";
//     cin >> nomorKursi;  nomorKursi  -= 1;

//     if (kursiTiapGerbong[nomorGerbong][nomorKursi]) {
//         cout << "       Nomor Kursi Telah Dipesan!";
//         return;
//     }

//     kursiTiapGerbong[nomorGerbong][nomorKursi]    = true;
//     pemesanan[indexKeberangkatan].tiket.nomorGerbong = nomorGerbong;
//     pemesanan[indexKeberangkatan].tiket.nomorTempatDuduk  = nomorKursi;
//     pemesanan[indexKeberangkatan].tiket.tanggalKeberangkatan  = "2025-04-01";  // Fixed dulu



//     cout << "\n[PAYMENT METHOD]" << endl;
//     for (int i = 0; i < 3; i++) {
//         cout << "   " << i + 1 << ". " << metodePembayaran[i] << endl;
//     }
//     cout << "   Choose your option: ";
//     cin >> pilihPembayaran;
//     pemesanan[indexKeberangkatan].pembayaran.metodePembayaran  = metodePembayaran[pilihPembayaran - 1];
//     pemesanan[indexKeberangkatan].pembayaran.sudahDibayar         = true;
//     pemesanan[indexKeberangkatan].pembayaran.totalHarga     = 100000;   // isi flat dulu

//     cout << "   [RESULT] Your ticket booking was successful!" << endl;
//     indexKeberangkatan++;
// }

// void manualInput(int indexTanggal, string kotaTujuanDipilih) {
void manualInput(int indexTanggal, int indexKotaTujuan) {
    if (jumlahPemesanan[indexTanggal] >= maksPemesananPerTanggal) {
        cout << "   Semua kursi telah dipesan untuk tanggal ini!\n";
        return;
    }

    int jumlah;
    cout << "\n[INPUT JUMLAH PENUMPANG]" << endl;
    cout << "   Berapa tiket yang ingin dipesan? ";
    cin >> jumlah;

    int sisaKursi = maksPemesananPerTanggal - jumlahPemesanan[indexTanggal];
    if (jumlah > sisaKursi) {
        cout << "   Maaf, hanya tersedia " << sisaKursi << " kursi pada tanggal ini.\n";
        return;
    }

    cin.ignore();
    // int hargaPerTiket = 100000;
    int hargaPerTiket = daftarTujuan[indexKotaTujuan].harga;
    int totalHargaAkun = 0;

    for (int i = 0; i < jumlah; i++) {
        cout << "\n===================================" << endl;
        cout << "[DATA PENUMPANG KE-" << i + 1 << "]" << endl;

        Pemesanan &booking = semuaPemesanan[indexTanggal][jumlahPemesanan[indexTanggal]];

        cout << "   Nama    : ";
        getline(cin, booking.penumpang.nama);
        cout << "   NIK     : ";
        getline(cin, booking.penumpang.nik);
        cout << "   Alamat  : ";
        getline(cin, booking.penumpang.alamat);
        cout << "   Umur    : ";
        cin >> booking.penumpang.umur;
        cin.ignore();
        cout << "   No HP   : ";
        getline(cin, booking.penumpang.noHp);

        // Visualisasi kursi terbaru
        cout << "\n[KURSI TERSEDIA - " << daftarTanggal[indexTanggal] << "]\n";
        for (int g = 0; g < nomorGerbong; g++) {
            cout << "   Gerbong " << g + 1 << " : ";
            for (int k = 0; k < tempatDudukGerbong; k++) {
                if (kursiTerpakai[indexTanggal][g][k]) {
                    cout << "[X] ";
                } else {
                    cout << "[" << k + 1 << "] ";
                }
            }
            cout << endl;
        }

        int pilihGerbong, pilihKursi;
        cout << "\n[PILIH KURSI UNTUK PENUMPANG " << i + 1 << "]" << endl;
        cout << "   Pilih Gerbong (1 - 3): "; 
        cin >> pilihGerbong; pilihGerbong -= 1;
        cout << "   Pilih Nomor Kursi (1 - 10): "; 
        cin >> pilihKursi; pilihKursi -= 1;

        if (kursiTerpakai[indexTanggal][pilihGerbong][pilihKursi]) {
            cout << "   Kursi sudah terisi! Tiket ke-" << i + 1 << " dibatalkan.\n";
            continue; // skip iterasi dan tidak menambah index
        }

        kursiTerpakai[indexTanggal][pilihGerbong][pilihKursi] = true;

        // Tiket
        booking.tiket.asalKota = "Yogyakarta";
        // booking.tiket.kotaTujuan = kotaTujuanDipilih;
        booking.tiket.kotaTujuan = daftarTujuan[indexKotaTujuan].kota;
        booking.tiket.nomorGerbong = pilihGerbong;
        booking.tiket.nomorTempatDuduk = pilihKursi;
        booking.tiket.tanggalKeberangkatan = daftarTanggal[indexTanggal];

        // Pembayaran per individu
        booking.pembayaran.metodePembayaran = "Ditanggung Akun Guest";
        booking.pembayaran.sudahDibayar = true;
        booking.pembayaran.totalHarga = hargaPerTiket;

        jumlahPemesanan[indexTanggal]++;
        totalHargaAkun += hargaPerTiket;

        cout << "   [BERHASIL] Tiket ke-" << i + 1 << " telah dicatat.\n";
        cin.ignore();
    }

    cout << "\n===================================" << endl;
    cout << "[TOTAL PEMBAYARAN]" << endl;
    cout << "   Total tiket berhasil dipesan : " << jumlahPemesanan[indexTanggal] << endl;
    cout << "   Total pembayaran oleh Guest  : Rp" << totalHargaAkun << endl;
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

void fileSaveTiketSemua(Pemesanan bookings[], int totalData) {
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

void tampilkanSeluruhDataPemesanan() {
    cout << "\n========== DAFTAR SELURUH PEMESANAN ==========\n";

    for (int t = 0; t < maxTanggal; t++) {
        if (jumlahPemesanan[t] == 0) continue;

        cout << "\n     Tanggal Keberangkatan: " << daftarTanggal[t] << endl;
        cout << "---------------------------------------------" << endl;

        for (int i = 0; i < jumlahPemesanan[t]; i++) {
            Pemesanan &p = semuaPemesanan[t][i];
            cout << i + 1 << ". Nama    : " << p.penumpang.nama << endl;
            cout << "   NIK     : " << p.penumpang.nik << endl;
            cout << "   Asal    : " << p.tiket.asalKota << endl;
            cout << "   Tujuan  : " << p.tiket.kotaTujuan << endl;
            cout << "   Kursi   : Gerbong " << p.tiket.nomorGerbong + 1
                 << " - Kursi " << p.tiket.nomorTempatDuduk + 1 << endl;
            cout << "   Harga   : Rp" << p.pembayaran.totalHarga << endl;
            cout << "---------------------------------------------" << endl;
        }
    }

    cout << "\n==============================================" << endl;
}

// void simpanSemuaTiketKeFile(bool append = false) {
//     ofstream file;

//     if (append) {
//         file.open("semua_tiket.txt", ios::app);  // Tambah di akhir
//     } else {
//         file.open("semua_tiket.txt", ios::out);  // Timpa isi lama
//     }

//     if (!file.is_open()) {
//         cout << "Gagal membuka file untuk menulis!" << endl;
//         return;
//     }

//     for (int t = 0; t < maxTanggal; t++) {
//         if (jumlahPemesanan[t] == 0) continue;

//         file << "======================" << endl;
//         file << "Tanggal: " << daftarTanggal[t] << endl;
//         file << "======================" << endl;

//         for (int i = 0; i < jumlahPemesanan[t]; i++) {
//             Pemesanan &p = semuaPemesanan[t][i];
//             file << "Nama       : " << p.penumpang.nama << endl;
//             file << "NIK        : " << p.penumpang.nik << endl;
//             file << "Alamat     : " << p.penumpang.alamat << endl;
//             file << "Umur       : " << p.penumpang.umur << endl;
//             file << "No HP      : " << p.penumpang.noHp << endl;
//             file << "Asal       : " << p.tiket.asalKota << endl;
//             file << "Tujuan     : " << p.tiket.kotaTujuan << endl;
//             file << "Gerbong    : " << p.tiket.nomorGerbong + 1 << endl;
//             file << "Kursi      : " << p.tiket.nomorTempatDuduk + 1 << endl;
//             file << "Harga      : Rp" << p.pembayaran.totalHarga << endl;
//             file << "----------------------" << endl;
//         }
//     }

//     file.close();

//     if (append)
//         cout << "✅ Tiket berhasil ditambahkan ke 'semua_tiket.txt'\n";
//     else
//         cout << "✅ Semua tiket ditimpa & disimpan ulang ke 'semua_tiket.txt'\n";
// }

// void simpanTiketPerPenumpang() {
//     for (int t = 0; t < maxTanggal; t++) {
//         if (jumlahPemesanan[t] == 0) continue;

//         for (int i = 0; i < jumlahPemesanan[t]; i++) {
//             Pemesanan &p = semuaPemesanan[t][i];

//             string namaFile = "tiket_" + p.penumpang.nik + "_" + daftarTanggal[t] + ".txt";
//             fstream file;
//             file.open(namaFile, ios::out | ios::trunc);

//             if (!file.is_open()) {
//                 cout << "❌ Gagal membuka file untuk: " << p.penumpang.nik << endl;
//                 continue;
//             }

//             file << "======= TIKET KERETA =======\n";
//             file << "Tanggal     : " << daftarTanggal[t] << "\n";
//             file << "Nama        : " << p.penumpang.nama << "\n";
//             file << "NIK         : " << p.penumpang.nik << "\n";
//             file << "Alamat      : " << p.penumpang.alamat << "\n";
//             file << "Umur        : " << p.penumpang.umur << "\n";
//             file << "No HP       : " << p.penumpang.noHp << "\n";
//             file << "Asal        : " << p.tiket.asalKota << "\n";
//             file << "Tujuan      : " << p.tiket.kotaTujuan << "\n";
//             file << "Gerbong     : " << p.tiket.nomorGerbong + 1 << "\n";
//             file << "Kursi       : " << p.tiket.nomorTempatDuduk + 1 << "\n";
//             file << "Harga       : Rp" << p.pembayaran.totalHarga << "\n";
//             file << "=============================\n";

//             file.close();
//         }
//     }

//     cout << "✅ Semua tiket berhasil disimpan dalam file terpisah per penumpang.\n";
// }

void simpanTiketBerdasarkanNIK() {
    string inputNIK, inputTanggal;
    cout << "\n[MENU CETAK TIKET PER PENUMPANG]\n";
    cout << "   Masukkan NIK: ";
    cin >> inputNIK;
    cin.ignore();
    cout << "   Masukkan tanggal keberangkatan (dd-mm-yyyy): ";
    getline(cin, inputTanggal);

    // Cari index tanggal yang sesuai
    int indexTanggal = -1;
    for (int i = 0; i < maxTanggal; i++) {
        if (daftarTanggal[i] == inputTanggal) {
            indexTanggal = i;
            break;
        }
    }

    if (indexTanggal == -1) {
        cout << "   Tanggal tidak ditemukan dalam sistem.\n";
        return;
    }

    // Cari pemesanan dengan NIK yang cocok
    bool found = false;
    for (int i = 0; i < jumlahPemesanan[indexTanggal]; i++) {
        Pemesanan &p = semuaPemesanan[indexTanggal][i];
        if (p.penumpang.nik == inputNIK) {
            found = true;

            string namaFile = "tiket_" + p.penumpang.nik + "_" + daftarTanggal[indexTanggal] + ".txt";
            fstream file(namaFile, ios::out | ios::trunc);

            if (!file.is_open()) {
                cout << "   Gagal membuka file untuk NIK: " << p.penumpang.nik << endl;
                return;
            }

            file << "======= TIKET KERETA =======\n";
            file << "Tanggal Keberangkatan  : " << daftarTanggal[indexTanggal] << "\n";
            file << "Nama                   : " << p.penumpang.nama << "\n";
            file << "NIK                    : " << p.penumpang.nik << "\n";
            file << "Alamat                 : " << p.penumpang.alamat << "\n";
            file << "Umur                   : " << p.penumpang.umur << "\n";
            file << "No HP                  : " << p.penumpang.noHp << "\n";
            file << "Asal                   : " << p.tiket.asalKota << "\n";
            file << "Tujuan                 : " << p.tiket.kotaTujuan << "\n";
            file << "Gerbong                : " << p.tiket.nomorGerbong + 1 << "\n";
            file << "Kursi                  : " << p.tiket.nomorTempatDuduk + 1 << "\n";
            file << "Harga                  : Rp" << p.pembayaran.totalHarga << "\n";
            file << "=============================\n";

            file.close();

            cout << "   Tiket berhasil dicetak ke file: " << namaFile << "\n";
            return;
        }
    }

    if (!found) {
        cout << "   Tiket dengan NIK tersebut tidak ditemukan pada tanggal yang dimasukkan.\n";
    }
}

void bacaTiketDariFile() {
    string inputNIK, inputTanggal;

    cout << "\n[MENU LIHAT TIKET PER PENUMPANG]\n";
    cout << "   Masukkan NIK: ";
    cin >> inputNIK;
    cin.ignore();
    cout << "   Masukkan tanggal keberangkatan (dd-mm-yyyy): ";
    getline(cin, inputTanggal);

    // Bentuk nama file tiket
    string namaFile = "tiket_" + inputNIK + "_" + inputTanggal + ".txt";

    fstream file;
    file.open(namaFile, ios::in);

    if (!file.is_open()) {
        cout << "   Tiket tidak ditemukan untuk NIK dan tanggal tersebut.\n";
        return;
    }

    cout << "\n[ISI TIKET]\n";
    string baris;
    while (getline(file, baris)) {
        cout << "   " << baris << endl;
    }

    file.close();
    cout << endl;
}

// Perlu diperbaiki terutama daklam penginputan ulanmg
void updateTiketDariFile() {
    string inputNIK, inputTanggal;

    cout << "\n[MENU UPDATE TIKET]\n";
    cout << "   Masukkan NIK: ";
    cin >> inputNIK;
    cin.ignore();
    cout << "   Masukkan tanggal keberangkatan (dd-mm-yyyy): ";
    getline(cin, inputTanggal);

    string namaFile = "tiket_" + inputNIK + "_" + inputTanggal + ".txt";

    // Cek apakah file tiket ada
    fstream file;

    file.open(namaFile, ios::in);
    if (!file.is_open()) {
        cout << "   File tiket tidak ditemukan.\n";
        return;
    }

    // Tampilkan isi lama
    cout << "\n[ISI TIKET LAMA]:\n";
    string baris;

    while (getline(file, baris)) {
        cout << baris << endl;
    }
    file.close();

    // Input data baru
    Pemesanan p;
    p.penumpang.nik = inputNIK;
    cout << "\nSilakan masukkan data baru:\n";
    cout << "Nama                   : "; getline(cin, p.penumpang.nama);
    cout << "Alamat                 : "; getline(cin, p.penumpang.alamat);
    cout << "Umur                   : "; cin >> p.penumpang.umur; cin.ignore();
    cout << "No HP                  : "; getline(cin, p.penumpang.noHp);

    // Untuk sekarang kita tidak ubah kursi, gerbong, dll.
    cout << "Kota Asal              : "; getline(cin, p.tiket.asalKota);
    cout << "Kota Tujuan            : "; getline(cin, p.tiket.kotaTujuan);
    cout << "Nomor Gerbong (1-3)    : "; cin >> p.tiket.nomorGerbong;
    cout << "Nomor Kursi   (1-10)   : "; cin >> p.tiket.nomorTempatDuduk;
    cout << "Harga Tiket            : "; cin >> p.pembayaran.totalHarga;
    cin.ignore();

    // Tanggal tetap sama
    p.tiket.tanggalKeberangkatan = inputTanggal;

    // Simpan ulang
    fstream fileEdit;
    file.open(namaFile, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "   Gagal membuka file untuk update.\n";
        return;
    }

    file << "======= TIKET KERETA (UPDATED) =======\n";
    file << "Tanggal Keberangkatan : " << p.tiket.tanggalKeberangkatan << "\n";
    file << "Nama                  : " << p.penumpang.nama << "\n";
    file << "NIK                   : " << p.penumpang.nik << "\n";
    file << "Alamat                : " << p.penumpang.alamat << "\n";
    file << "Umur                  : " << p.penumpang.umur << "\n";
    file << "No HP                 : " << p.penumpang.noHp << "\n";
    file << "Asal                  : " << p.tiket.asalKota << "\n";
    file << "Tujuan                : " << p.tiket.kotaTujuan << "\n";
    file << "Gerbong               : " << p.tiket.nomorGerbong << "\n";
    file << "Kursi                 : " << p.tiket.nomorTempatDuduk << "\n";
    file << "Harga                 : Rp" << p.pembayaran.totalHarga << "\n";
    file << "======================================\n";

    file.close();
    cout << "   Tiket berhasil diperbarui.\n";
}
