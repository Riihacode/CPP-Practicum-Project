#include <iostream>
#include <string>
#include <cstdlib>  // untuk rand()
#include <ctime>    // untuk time()
#include <fstream>

using namespace std;

// ######################## CONSTRAINT VARIABLE #########################
// Konstanta tetap
const int nomorGerbong            = 3;
const int tempatDudukGerbong      = 10;
const int maxTanggal              = 10; // Jumlah maksimum tanggal simulasi
const int maksPemesananPerTanggal = 30; // Kuota per tanggal
const string DEFAULT_ASAL_KOTA    = "Yogyakarta";  // Untuk template pengisian field asal kota karena harusnya tidak hanya satu stasion asal saja

// ############################### STRUCT #################################
// Deklarasi Struct
struct GuestAccount {
    string email = "guestaccount@gmail.com";
    string password = "12345678";
};

struct Tujuan {
    string kota;
    int harga;
};

struct Penumpang {
    string nama;      // Nama lengkap penumpang
    string nik;       // Nomor Induk Kependudukan (atau passport)
    string alamat;    // Alamat domisili
    int umur;         // Umur penumpang
    string noHp;      // Nomor telepon aktif
};

struct InfoTiket{
    string asalKotaStasiun;
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

// ############################ ARRAY 1D ####################################
// ARRAY untuk pemilihan input
string metodePembayaran[] = {
    "BRI", 
    "Seabank", 
    "BCA"
};

string daftarTanggal[maxTanggal] = {
    "30-01-2025", 
    "31-01-2025", 
    "01-02-2025", 
    "02-02-2025", 
    "03-02-2025",
    "04-02-2025", 
    "05-02-2025", 
    "06-02-2025", 
    "07-02-2025", 
    "08-02-2025"
};

Tujuan daftarTujuan[] = {
    {"Klaten",        20000},
    {"Solo Balapan",  30000},
    {"Sragen",        35000},
    {"Ngawi",         45000},
    {"Madiun",        60000},
    {"Nganjuk",       70000},
    {"Kediri",        80000},
    {"Jombang",       85000},
    {"Surabaya",     100000}
};

// ################# STRUCT VARIABLE & GLOBAL VARIABLE ###################
// Deklarasi Variable Struct, array kursi yang hendak dipesan, dan variabel bantuan
GuestAccount guest;
Pemesanan semuaPemesanan[maxTanggal][maksPemesananPerTanggal];

bool kursiTerpakai[maxTanggal][nomorGerbong][tempatDudukGerbong] = {};

int jumlahPemesanan[maxTanggal] = {};
const int jumlahTujuan          = sizeof(daftarTujuan) / sizeof(daftarTujuan[0]);

// ####################### RE-DECLARATION FUNCTION #######################
// Menu User Interface
void menuLoginDanPesanTiket();
void menuCariTiket();
void menuTampilkanSeluruhTiket();

// Input Data
void autoBookTicket(int indexTanggal, int indexKotaTujuan);
void manualInput(int indexTanggal, int indexKotaTujuan);

// Searching
void searchSeqNonSentinelBelumUrut(string *pointerNIK);
void searchSeqSentinelBelumUrut(string *pointerNIK);
void searchBinarySearch(string *nikPointer);
void printPemesanan(const Pemesanan &p, const string &tanggal, int nomor);
int flattenDataSorting(Pemesanan *copy, string *tanggalKeberangkatan);

// Sorting
void bubbleSortByNIK(Pemesanan *copy, string *tanggalKeberangkatan, int total);
void bubbleSortByNama(Pemesanan *copy, string *tanggal, int total);
void insertionSortByNama(Pemesanan *copy, string *tanggal, int total);
void selectionSortByNama(Pemesanan *copy, string *tanggal, int total);
void shellSortByNama(Pemesanan *copy, string *tanggal, int total);
void quickSortByNama(Pemesanan *copy, string *tanggal, int left, int right);
void tampilkanDataSetelahSorting(Pemesanan *dataSorting, string *tanggal, int total);

// File Operation
void fileCreateTiketDenganNIK();
void fileReadTiket();
void fileUpdateTiket();
void fileDeleteTiket();

// Untuk bahan cek
void tampilkanSeluruhDataPemesanan();

// ########################## USER INTERFACE #############################
// MAIN UI
int main() {
    int pilihanMenu;

    do { 
        cout << "[MENU UTAMA]"<< endl;
        cout << "   1. Login Akun dan Pesan Tiket"          << endl;
        cout << "   2. Cari Tiket (Searching)"              << endl;
        cout << "   3. Tampilkan Seluruh Tiket (Sorting)"   << endl;
        cout << "   4. Cetak Tiket (Create)"                << endl;
        cout << "   5. Lihat Tiket (Read)"                  << endl;
        cout << "   6. Edit Tiket (Update)"                 << endl;
        cout << "   7. Hapus Tiket (Delete)"                << endl;
        cout << "   8. Tampilkan Data Tiket (untuk development) \n";
        cout << "   9. Exit"                                << endl;
        cout << "   Pilih Menu : ";
        cin >> pilihanMenu;
        cout << endl;

        switch (pilihanMenu) {
            case 1: { menuLoginDanPesanTiket();         break; }
            case 2: { menuCariTiket();                  break; }
            case 3: { menuTampilkanSeluruhTiket();      break; }
            case 4: { fileCreateTiketDenganNIK();       break; }
            case 5: { fileReadTiket();                  break; }
            case 6: { fileUpdateTiket();                break; }
            case 7: { fileDeleteTiket();                break; }
            case 8: { tampilkanSeluruhDataPemesanan();  break; }
            case 9: { cout << "   Exit... \n\n";        break; }
            default: {cout << "   Invalid Option! \n\n";break; }
        }
    } while (pilihanMenu != 9);
}

// SUB UI
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

    // [2] KOTA TUJUAN
    cout << "[PILIH KOTA TUJUAN]" << endl;
    for (int i = 0; i < jumlahTujuan; i++) {
        cout << "   " << i + 1 << ". " << daftarTujuan[i].kota 
                               << " - Rp" << daftarTujuan[i].harga << endl;
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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "   Input tidak valid! Masukkan angka 1 - 3.\n\n";
            continue;
        }
        cout << endl;

        switch (pilihMenu){
            case 1:  { autoBookTicket(indexTanggal, indexKotaTujuan);   break; }
            case 2:  { manualInput(indexTanggal, indexKotaTujuan);      break; }
            case 3:  { cout << "    Kembali ke menu utama... \n\n";     break; }
            default: { cout << "    Invalid option!\n\n";               break; }
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

        bool dataKosong = true;
        
        for (int i = 0; i < maxTanggal; i++) {
            if (jumlahPemesanan[i] > 0) {
                dataKosong = false;
                break;
            }
        }

        if (dataKosong) {
            cout << "   [!] Data pemesanan kosong! Silakan input data terlebih dahulu.\n\n";
            break;
        }

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
                string searchNIK;

                cout << "   Input NIK yang ingin anda cari : ";
                cin >> searchNIK; 

                searchBinarySearch(&searchNIK);
                cout << endl << endl;

                break;                                  
            }
            
            case 4: { cout << "    Exit... \n\n";       break;  }
            default:{ cout << "    Invalid input\n\n";  break;  }
        }
    } while (pilihMenu != 4);
}

void menuTampilkanSeluruhTiket() {
    int pilihMenu;
    do {
        // Cek apakah data kosong
        bool isEmpty = true;
        for (int i = 0; i < maxTanggal; i++) {
            if (jumlahPemesanan[i] > 0) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
            cout << "   [!] Data pemesanan kosong. Silakan input data terlebih dahulu!\n\n";
            return;
        }

        cout << "[ALL TICKET INFORMATION]\n";
        cout << "   1. Bubble Sort\n";
        cout << "   2. Straight Insertion Sort\n";
        cout << "   3. Straight Selection Sort\n";
        cout << "   4. Shell Sort\n";
        cout << "   5. Quick Sort\n";
        cout << "   6. Back to main menu\n";
        cout << "   Choose your option: ";
        cin >> pilihMenu;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "   Input tidak valid! Masukkan angka 1 - 6.\n\n";
            continue;
        }

        switch (pilihMenu) {
            case 1: {
                Pemesanan copy[maxTanggal * maksPemesananPerTanggal];
                string tanggal[maxTanggal * maksPemesananPerTanggal];
                int total = flattenDataSorting(copy, tanggal);
                
                bubbleSortByNama(copy, tanggal, total);
                tampilkanDataSetelahSorting(copy, tanggal, total);
                break;
            }

            case 2: {
                Pemesanan copy[maxTanggal * maksPemesananPerTanggal];
                string tanggal[maxTanggal * maksPemesananPerTanggal];
                int total = flattenDataSorting(copy, tanggal);

                insertionSortByNama(copy, tanggal, total);
                tampilkanDataSetelahSorting(copy, tanggal, total);
                break;
            }
                
            case 3: {
                Pemesanan copy[maxTanggal * maksPemesananPerTanggal];
                string tanggal[maxTanggal * maksPemesananPerTanggal];
                int total = flattenDataSorting(copy, tanggal);

                selectionSortByNama(copy, tanggal, total);
                tampilkanDataSetelahSorting(copy, tanggal, total);
                break;
            }

            case 4: {
                Pemesanan copy[maxTanggal * maksPemesananPerTanggal];
                string tanggal[maxTanggal * maksPemesananPerTanggal];
                int total = flattenDataSorting(copy, tanggal);

                shellSortByNama(copy, tanggal, total);
                tampilkanDataSetelahSorting(copy, tanggal, total);
                break;
            }
            case 5: {
                Pemesanan copy[maxTanggal * maksPemesananPerTanggal];
                string tanggal[maxTanggal * maksPemesananPerTanggal];
                int total = flattenDataSorting(copy, tanggal);

                quickSortByNama(copy, tanggal, 0, total - 1);
                tampilkanDataSetelahSorting(copy, tanggal, total);
                break;
            }

            case 6: { cout << "   Kembali ke menu utama...\n\n"; break; }
            default: { cout << "   Invalid option.\n\n";         break; }
        }
    } while (pilihMenu != 6);
}

// ############################# INPUT DATA #############################
void autoBookTicket(int indexTanggal, int indexKotaTujuan) {
    if (jumlahPemesanan[indexTanggal] >= maksPemesananPerTanggal) {
        cout << "   Semua tiket pada tanggal ini telah habis!\n";
        return;
    }

    string sampelNama[]       = {"Budi", "Ani", "Citra", "Dedi", "Eka", "Fajar", "Gita", "Hana"};
    string sampelAlamat[]     = {"Yogyakarta", "Sleman", "Bantul", "Kulon Progo"};
    string metodePembayaran[] = {"BRI", "Seabank", "BCA"};

    srand(time(0));

    int gerbong = -1;
    int kursi = -1;
    bool foundKursi = false;

    // Cari kursi kosong pada tanggal yang dipilih
    for (int grbg = 0; grbg < nomorGerbong && !foundKursi; grbg++) {
        for (int krsi = 0; krsi < tempatDudukGerbong && !foundKursi; krsi++) {
            if (!kursiTerpakai[indexTanggal][grbg][krsi]) {
                gerbong     = grbg;
                kursi       = krsi;
                foundKursi  = true;
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

    booking.penumpang.nama              = namaUnique;
    booking.penumpang.nik               = generatedNIK;
    booking.penumpang.alamat            = sampelAlamat[rand() % 4];
    // Tambahan untuk melengkapi data struct Penumpang
    booking.penumpang.umur  = 17 + rand() % 40; // Umur acak 17 - 56 tahun
    // Simulasi No HP unik acak
    string noHpAwal = "08";
    for (int i = 0; i < 10; i++) {
        noHpAwal += to_string(rand() % 10);
    }
    booking.penumpang.noHp              = noHpAwal;

    booking.tiket.asalKotaStasiun       = DEFAULT_ASAL_KOTA;
    booking.tiket.kotaTujuan            = daftarTujuan[indexKotaTujuan].kota;
    booking.tiket.nomorGerbong          = gerbong;
    booking.tiket.nomorTempatDuduk      = kursi;
    booking.tiket.tanggalKeberangkatan  = daftarTanggal[indexTanggal];

    booking.pembayaran.metodePembayaran = metodePembayaran[rand() % 3];
    booking.pembayaran.sudahDibayar     = true;
    booking.pembayaran.totalHarga       = daftarTujuan[indexKotaTujuan].harga;

    cout << "   [AUTO-PESAN] Berhasil dipesan oleh " << booking.penumpang.nama
         << " (NIK: " << booking.penumpang.nik << ") pada " << daftarTanggal[indexTanggal]
         << ", Kursi " << gerbong + 1 << "-" << kursi + 1 << endl;

    jumlahPemesanan[indexTanggal]++;
}

void manualInput(int indexTanggal, int indexKotaTujuan) {
    if (jumlahPemesanan[indexTanggal] >= maksPemesananPerTanggal) {
        cout << "   Semua kursi telah dipesan untuk tanggal ini!\n";
        return;
    }

    int jumlah;
    cout << "[INPUT JUMLAH PENUMPANG]" << endl;
    cout << "   Berapa tiket yang ingin dipesan? ";
    cin >> jumlah;

    int sisaKursi = maksPemesananPerTanggal - jumlahPemesanan[indexTanggal];
    if (jumlah > sisaKursi) {
        cout << "   Maaf, hanya tersedia " << sisaKursi << " kursi pada tanggal ini.\n";
        return;
    }

    cin.ignore();
    
    int hargaPerTiket   = daftarTujuan[indexKotaTujuan].harga;
    int totalHargaAkun  = 0;
    int totalBerhasil   = 0;

    for (int i = 0; i < jumlah; i++) {
        cout << "\n===================================" << endl;
        cout << "[DATA PENUMPANG KE-" << i + 1 << "]" << endl;

        Pemesanan &booking = semuaPemesanan[indexTanggal][jumlahPemesanan[indexTanggal]];

        cout << "   Nama    : ";
        getline(cin, booking.penumpang.nama);
        
        do {
            cout << "   NIK     : ";
            getline(cin, booking.penumpang.nik);
            if (booking.penumpang.nik.empty()) {
                cout << "   [ERROR] NIK tidak boleh kosong.\n";
                continue;
            }

            // Cek apakah NIK sudah digunakan di tanggal ini
            bool nikDuplikat = false;
            for (int j = 0; j < jumlahPemesanan[indexTanggal]; j++) {
                if (semuaPemesanan[indexTanggal][j].penumpang.nik == booking.penumpang.nik) {
                    nikDuplikat = true;
                    break;
                }
            }

            if (nikDuplikat) {
                cout << "   [ERROR] NIK sudah digunakan untuk tanggal ini! Tiket ke-" << i + 1 << " dibatalkan.\n";
                booking.penumpang.nik = ""; // kosongkan agar tidak digunakan
                break; // batalkan loop input
            }
        } while (booking.penumpang.nik.empty());
        if (booking.penumpang.nik.empty()) { continue; }

        cout << "   Alamat  : ";
        getline(cin, booking.penumpang.alamat);
        cout << "   Umur    : ";
        cin >> booking.penumpang.umur;
        cin.ignore();
        cout << "   No HP   : ";
        getline(cin, booking.penumpang.noHp);

        // Visualisasi kursi terbaru
        cout << "\n[KURSI TERSEDIA - " << daftarTanggal[indexTanggal] << "]\n";
        for (int grbg = 0; grbg < nomorGerbong; grbg++) {
            cout << "   Gerbong " << grbg + 1 << " : ";
            for (int krsi = 0; krsi < tempatDudukGerbong; krsi++) {
                if (kursiTerpakai[indexTanggal][grbg][krsi]) {
                    cout << "[X] ";
                } else {
                    cout << "[" << krsi + 1 << "] ";
                }
            }
            cout << endl;
        }

        int pilihGerbong, pilihKursi;
        cout << "\n[PILIH KURSI UNTUK PENUMPANG " << i + 1 << "]" << endl;
        cout << "   Pilih Gerbong (1 - 3): "; 
        cin >> pilihGerbong; 
        cout << "   Pilih Nomor Kursi (1 - 10): "; 
        cin >> pilihKursi;
        cin.ignore();

        pilihGerbong -= 1;
        pilihKursi   -= 1;

        if (pilihGerbong < 0 || pilihGerbong >= nomorGerbong || 
            pilihKursi < 0 || pilihKursi >= tempatDudukGerbong) {
            cout << "   [ERROR] Pilihan kursi tidak valid! Tiket ke-" << i + 1 << " dibatalkan.\n";
            continue;
        }

        if (kursiTerpakai[indexTanggal][pilihGerbong][pilihKursi]) {
            cout << "   Kursi sudah terisi! Tiket ke-" << i + 1 << " dibatalkan.\n";
            continue; // skip iterasi dan tidak menambah index
        }

        kursiTerpakai[indexTanggal][pilihGerbong][pilihKursi] = true;

        // Tiket
        booking.tiket.asalKotaStasiun       = DEFAULT_ASAL_KOTA;
        booking.tiket.kotaTujuan            = daftarTujuan[indexKotaTujuan].kota;
        booking.tiket.nomorGerbong          = pilihGerbong;
        booking.tiket.nomorTempatDuduk      = pilihKursi;
        booking.tiket.tanggalKeberangkatan  = daftarTanggal[indexTanggal];

        // Pembayaran per individu
        cout << "\n[PILIH METODE PEMBAYARAN UNTUK PENUMPANG " << i + 1 << "]" << endl;
        for (int metodePem = 0; metodePem < 3; metodePem++) {
            cout << "   " << metodePem + 1 << ". " << metodePembayaran[metodePem] << endl;
        }

        int pilihMetode;
        do {
            cout << "   Pilihan (1 - 3): ";
            cin >> pilihMetode;
            if (pilihMetode < 1 || pilihMetode > 3) {
                cout << "   Pilihan tidak valid! Ulangi.\n";
            }
        } while (pilihMetode < 1 || pilihMetode > 3);
        cin.ignore();

        booking.pembayaran.metodePembayaran = metodePembayaran[pilihMetode - 1];
        booking.pembayaran.sudahDibayar     = true;
        booking.pembayaran.totalHarga       = hargaPerTiket;

        jumlahPemesanan[indexTanggal]++;
        totalHargaAkun += hargaPerTiket;

        cout << "   [BERHASIL] Tiket ke-" << i + 1 << " telah dicatat.\n";
    }

    cout << "\n===================================" << endl;
    cout << "[TOTAL PEMBAYARAN]" << endl;
    cout << "   Total tiket berhasil dipesan : " << jumlahPemesanan[indexTanggal] << endl;
    cout << "   Total pembayaran oleh Guest  : Rp" << totalHargaAkun << endl;
}

// ########################## SEARCHING ################################
void searchSeqNonSentinelBelumUrut(string* pointerNIK) {
    bool found = false;
    int tanggal = 0;

    cout << "\n[HASIL PENCARIAN BERDASARKAN NIK - SEQUENTIAL NON SENTINEL]:\n";

    while (tanggal < maxTanggal) {
        bool tanggalSudahDitampilkan = false;
        int nomor = 1;
        int i = 0;

        while (i < jumlahPemesanan[tanggal]) {
            Pemesanan& p = semuaPemesanan[tanggal][i];

            if (p.penumpang.nik == *pointerNIK) {
                found = true;

                if (!tanggalSudahDitampilkan) {
                    cout << "\nTanggal Keberangkatan : " << daftarTanggal[tanggal] << "\n";
                    cout << "====================================\n";
                    tanggalSudahDitampilkan = true;
                }

                printPemesanan(p, daftarTanggal[tanggal], nomor);
                nomor++;
            }

            i++;
        }

        tanggal++;
    }

    if (!found) {
        cout << "   [!] Data dengan NIK tersebut tidak ditemukan.\n";
    }
}

void searchSeqSentinelBelumUrut(string *pointerNIK) {
    bool found = false;
    int tanggal = 0;

    cout << "\n[HASIL PENCARIAN BERDASARKAN NIK]:\n";

    while (tanggal < maxTanggal) {
        if (jumlahPemesanan[tanggal] == 0) {
            tanggal++;
            continue;
        }

        // Tambahkan sentinel
        Pemesanan cadangan = semuaPemesanan[tanggal][jumlahPemesanan[tanggal]];
        semuaPemesanan[tanggal][jumlahPemesanan[tanggal]].penumpang.nik = *pointerNIK;

        int i = 0;
        while (semuaPemesanan[tanggal][i].penumpang.nik != *pointerNIK) {
            i++;
        }

        // Pulihkan cadangan
        semuaPemesanan[tanggal][jumlahPemesanan[tanggal]] = cadangan;

        // Tampilkan semua hasil pencarian dari tanggal ini
        if (i < jumlahPemesanan[tanggal]) {
            int nomor = 1;
            bool tanggalSudahDitampilkan = false;

            while (i < jumlahPemesanan[tanggal]) {
                Pemesanan& p = semuaPemesanan[tanggal][i];

                if (p.penumpang.nik == *pointerNIK) {
                    found = true;

                    if (!tanggalSudahDitampilkan) {
                        cout << "\nTanggal Keberangkatan : " << daftarTanggal[tanggal] << "\n";
                        cout << "====================================\n";
                        tanggalSudahDitampilkan = true;
                    }
                    
                    printPemesanan(p, daftarTanggal[tanggal], nomor);
                    nomor++;
                }

                i++;
            }
        }

        tanggal++;
    }

    if (!found) {
        cout << "   [!] NIK tidak ditemukan!\n";
    }
}

void searchBinarySearch(string *nikPointer) {
    Pemesanan copy[maxTanggal * maksPemesananPerTanggal];
    string tanggal[maxTanggal * maksPemesananPerTanggal];
    int total = flattenDataSorting(copy, tanggal);

    bubbleSortByNIK(copy, tanggal, total);

    int left = 0, right = total - 1, mid;
    bool found = false;

    while (left <= right) {
        mid = (left + right) / 2;
        if (copy[mid].penumpang.nik == *nikPointer) {
            found = true;
            break;
        } else if (*nikPointer < copy[mid].penumpang.nik) {
            right = mid - 1;
        } else {
            left  = mid + 1;
        }
    }

    if (!found) {
        cout << "   [!] NIK tidak ditemukan!\n";
        return;
    }

    int kiri = mid;
    while (kiri > 0          && copy[kiri - 1].penumpang.nik == *nikPointer)  { kiri--;  }
    int kanan = mid;
    while (kanan < total - 1 && copy[kanan + 1].penumpang.nik == *nikPointer) { kanan++; }
    cout << "\n[HASIL PENCARIAN BERDASARKAN NIK]:\n";

    string lastTanggal = "";
    int nomor = 1;

    for (int i = kiri; i <= kanan; i++) {
        if (tanggal[i] != lastTanggal) {
            lastTanggal = tanggal[i];
            nomor = 1;
            cout << "\nTanggal Keberangkatan: " << lastTanggal << "\n";
            cout << "====================================\n";
        }

        printPemesanan(copy[i], tanggal[i], nomor);
        nomor++;
    }
}

// Fungsi untuk mencetak 1 tiket dengan tanggal
void printPemesanan(const Pemesanan &p, const string &tanggal, int nomor) {
    cout << "-----------------------------\n";
    cout << nomor << ". Nama                  : " << p.penumpang.nama << "\n";
    cout << "   Tanggal Keberangkatan : " << tanggal << "\n";
    cout << "   NIK                   : " << p.penumpang.nik << "\n";
    cout << "   Alamat                : " << p.penumpang.alamat << "\n";
    cout << "   Umur                  : " << p.penumpang.umur << "\n";
    cout << "   No HP                 : " << p.penumpang.noHp << "\n";
    cout << "   Asal Kota Stasiun     : " << p.tiket.asalKotaStasiun << "\n";
    cout << "   Tujuan                : " << p.tiket.kotaTujuan << "\n";
    cout << "   Gerbong               : " << p.tiket.nomorGerbong + 1 << "\n";
    cout << "   Kursi                 : " << p.tiket.nomorTempatDuduk + 1 << "\n";
    cout << "   Metode Pembayaran     : " << p.pembayaran.metodePembayaran << "\n";
    if (p.pembayaran.sudahDibayar == true) {
        cout << "   Status Pembayaran     : " << "Sudah Dibayar" << endl;
    } else {
        cout << "   Status Pembayaran     : " << "Belum Dibayar" << endl;
    }
    cout << "   Harga                 : Rp" << p.pembayaran.totalHarga << "\n";
    cout << "-----------------------------\n";
}

// ############################ SORTING #################################
int flattenDataSorting(Pemesanan *copy, string *tanggalKeberangkatan) {
    int total = 0;
    for (int i = 0; i < maxTanggal; i++) {
        for (int j = 0; j < jumlahPemesanan[i]; j++) {
            copy[total]                 = semuaPemesanan[i][j];
            tanggalKeberangkatan[total] = daftarTanggal[i];
            total++;
        }
    }
    return total;
}

void bubbleSortByNIK(Pemesanan *copy, string *tanggalKeberangkatan, int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (copy[j].penumpang.nik > copy[j + 1].penumpang.nik) {
                // Tukar data pemesanan
                Pemesanan tempP = copy[j];
                copy[j]         = copy[j + 1];
                copy[j + 1]     = tempP;

                // Tukar tanggal juga
                string tempTgl              = tanggalKeberangkatan[j];
                tanggalKeberangkatan[j]     = tanggalKeberangkatan[j + 1];
                tanggalKeberangkatan[j + 1] = tempTgl;
            }
        }
    }
}

void bubbleSortByNama(Pemesanan *copy, string *tanggal, int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (copy[j].penumpang.nama > copy[j + 1].penumpang.nama) {
                // Tukar data
                Pemesanan temp  = copy[j];
                copy[j]         = copy[j + 1];
                copy[j + 1]     = temp;

                // Tukar tanggal juga agar tidak tertukar
                string tempTgl  = tanggal[j];
                tanggal[j]      = tanggal[j + 1];
                tanggal[j + 1]  = tempTgl;
            }
        }
    }
}

void insertionSortByNama(Pemesanan *copy, string *tanggal, int total) {
    for (int i = 1; i < total; i++) {
        Pemesanan tempPemesanan = copy[i];
        string tempTanggal      = tanggal[i];

        int j = i - 1;
        while (j >= 0 && tempPemesanan.penumpang.nama < copy[j].penumpang.nama) {
            copy[j + 1]     = copy[j];
            tanggal[j + 1]  = tanggal[j];
            j--;
        }

        copy[j + 1]     = tempPemesanan;
        tanggal[j + 1]  = tempTanggal;
    }
}

void selectionSortByNama(Pemesanan *copy, string *tanggal, int total) {
    for (int i = 0; i < total - 1; i++) {
        int indexMin = i;

        for (int j = i + 1; j < total; j++) {
            if (copy[j].penumpang.nama < copy[indexMin].penumpang.nama) {
                indexMin = j;
            }
        }

        if (indexMin != i) {
            Pemesanan tempPemesanan = copy[i];
            string tempTanggal      = tanggal[i];

            copy[i]     = copy[indexMin];
            tanggal[i]  = tanggal[indexMin];

            copy[indexMin]      = tempPemesanan;
            tanggal[indexMin]   = tempTanggal;
        }
    }
}

void shellSortByNama(Pemesanan *copy, string *tanggal, int total) {
    for (int gap = total / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < total; i++) {
            Pemesanan tempPemesanan = copy[i];
            string tempTanggal      = tanggal[i];
            int j                   = i;

            while (
                j >= gap 
                && copy[j - gap].penumpang.nama > tempPemesanan.penumpang.nama
            ) {
                copy[j]     = copy[j - gap];
                tanggal[j]  = tanggal[j - gap];
                j -= gap;
            }

            copy[j]     = tempPemesanan;
            tanggal[j]  = tempTanggal;
        }
    }
}

void quickSortByNama(Pemesanan *copy, string *tanggal, int left, int right) {
    if (left >= right) return;

    int i = left, j = right;
    Pemesanan pivot = copy[(left + right) / 2];
    string pivotTanggal = tanggal[(left + right) / 2];

    while (i <= j) {
        while (copy[i].penumpang.nama < pivot.penumpang.nama) { i++; }
        while (copy[j].penumpang.nama > pivot.penumpang.nama) { j--; }
        if (i <= j) {
            // Tukar isi copy[i] <-> copy[j]
            Pemesanan tempPemesanan = copy[i];
            string tempTanggal      = tanggal[i];

            copy[i]     = copy[j];
            tanggal[i]  = tanggal[j];

            copy[j]     = tempPemesanan;
            tanggal[j]  = tempTanggal;

            i++;
            j--;
        }
    }

    // Rekursif kiri dan kanan
    if (left < j)  { quickSortByNama(copy, tanggal, left, j);   }
    if (i < right) { quickSortByNama(copy, tanggal, i, right);  }
}

void tampilkanDataSetelahSorting(Pemesanan *dataSorting, string *tanggal, int total) {
    if (total == 0) {
        cout << "[!] Tidak ada data pemesanan untuk ditampilkan.\n\n";
        return;
    }

    cout << "[SEMUA DATA PEMESANAN - SETELAH DIURUTKAN (A-Z)]\n";
    cout << "==================================================\n";

    for (int i = 0; i < total; i++) {
        Pemesanan &p = dataSorting[i];
        cout << i + 1 << ". ====== TIKET KERETA ======" << "\n";
        cout << "   Tanggal Keberangkatan : " << tanggal[i] << "\n";
        cout << "   Nama                  : " << p.penumpang.nama << "\n";
        cout << "   NIK                   : " << p.penumpang.nik << "\n";
        cout << "   Alamat                : " << p.penumpang.alamat << "\n";
        cout << "   Umur                  : " << p.penumpang.umur << "\n";
        cout << "   No HP                 : " << p.penumpang.noHp << "\n";
        cout << "   Asal Kota Stasiun     : " << p.tiket.asalKotaStasiun << "\n";
        cout << "   Tujuan                : " << p.tiket.kotaTujuan << "\n";
        cout << "   Gerbong               : " << p.tiket.nomorGerbong + 1 << "\n";
        cout << "   Kursi                 : " << p.tiket.nomorTempatDuduk + 1 << "\n";
        cout << "   Metode Pembayaran     : " << p.pembayaran.metodePembayaran << "\n";
        
        if (p.pembayaran.sudahDibayar == true) {
            cout << "   Status Pembayaran     : Sudah Dibayar\n";
        } else {
            cout << "   Status Pembayaran     : Belum Dibayar\n";
        }

        cout << "   Harga                 : Rp" << p.pembayaran.totalHarga << "\n";
        cout << "===============================\n";
    }

    cout << endl;
}

void tampilkanSeluruhDataPemesanan() {
    cout << "\n========== DAFTAR SELURUH PEMESANAN ==========\n";

    for (int t = 0; t < maxTanggal; t++) {
        if (jumlahPemesanan[t] == 0) { continue; }

        cout << "\n     Tanggal Keberangkatan: " << daftarTanggal[t] << endl;
        cout << "=============================================\n";

        for (int i = 0; i < jumlahPemesanan[t]; i++) {
            Pemesanan &p = semuaPemesanan[t][i];
            cout << i + 1 << ". Nama                  : " << p.penumpang.nama << "\n";
            cout << "   NIK                   : " << p.penumpang.nik << "\n";
            cout << "   Alamat                : " << p.penumpang.alamat << "\n";
            cout << "   Umur                  : " << p.penumpang.umur << "\n";
            cout << "   No HP                 : " << p.penumpang.noHp << "\n";
            cout << "   Asal Kota Stasiun     : " << p.tiket.asalKotaStasiun << "\n";
            cout << "   Tujuan                : " << p.tiket.kotaTujuan << "\n";
            cout << "   Gerbong               : " << p.tiket.nomorGerbong + 1 << "\n";
            cout << "   Kursi                 : " << p.tiket.nomorTempatDuduk + 1 << "\n";
            cout << "   Metode Pembayaran     : " << p.pembayaran.metodePembayaran << "\n";
            if (p.pembayaran.sudahDibayar == true) {
                cout << "   Status Pembayaran     : " << "Sudah Dibayar" << endl;
            } else {
                cout << "   Status Pembayaran     : " << "Belum Dibayar" << endl;
            }
            cout << "   Harga                 : Rp" << p.pembayaran.totalHarga << "\n";
            cout << "   ------------------------------------------\n";
        }
    }

    cout << "\n==============================================" << endl;
}

// ########################## FILE OPERATION #############################
void fileCreateTiketDenganNIK() {
    string inputNIK, inputTanggal;
    cout << "[MENU CETAK TIKET PER PENUMPANG]\n";
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
            
            fstream file;
            file.open(namaFile, ios::out | ios::trunc);

            if (!file.is_open()) {
                cout << "   Gagal membuka file untuk NIK: " << p.penumpang.nik << endl;
                return;
            }

            file << "======= TIKET KERETA =======\n";
            file << "Tanggal Keberangkatan : " << daftarTanggal[indexTanggal] << "\n";
            file << "Nama                  : " << p.penumpang.nama << "\n";
            file << "NIK                   : " << p.penumpang.nik << "\n";
            file << "Alamat                : " << p.penumpang.alamat << "\n";
            file << "Umur                  : " << p.penumpang.umur << "\n";
            file << "No HP                 : " << p.penumpang.noHp << "\n";
            file << "Asal Kota Stasiun     : " << p.tiket.asalKotaStasiun << "\n";
            file << "Tujuan                : " << p.tiket.kotaTujuan << "\n";
            file << "Gerbong               : " << p.tiket.nomorGerbong + 1 << "\n";
            file << "Kursi                 : " << p.tiket.nomorTempatDuduk + 1 << "\n";
            file << "Metode Pembayaran     : " << p.pembayaran.metodePembayaran << "\n";
            if (p.pembayaran.sudahDibayar == true) {
                file << "Status Pembayaran     : " << "Sudah Dibayar" << endl;
            } else {
                file << "Status Pembayaran     : " << "Belum Dibayar" << endl;
            }
            file << "Harga                 : Rp" << p.pembayaran.totalHarga << "\n";
            file << "=============================\n";

            file.close();

            cout << "   Tiket berhasil dicetak ke file: " << namaFile << "\n\n";
            return;
        }
    }

    if (!found) {
        cout << "   Tiket dengan NIK tersebut tidak ditemukan pada tanggal yang dimasukkan.\n\n";
    }
}

void fileReadTiket() {
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
void fileUpdateTiket() {
    string inputNIK, inputTanggal;

    cout << "\n[MENU UPDATE TIKET]\n";
    cout << "   Masukkan NIK: ";
    cin >> inputNIK;
    cin.ignore();
    cout << "   Masukkan tanggal keberangkatan (dd-mm-yyyy): ";
    getline(cin, inputTanggal);

    // Cari index tanggal
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

    // Cari NIK di array
    bool found = false;
    for (int i = 0; i < jumlahPemesanan[indexTanggal]; i++) {
        Pemesanan &p = semuaPemesanan[indexTanggal][i];
        if (p.penumpang.nik == inputNIK) {
            found = true;

            // Tampilkan data lama
            cout << "\n[DATA LAMA]:\n";
            cout << "   Nama    : " << p.penumpang.nama << endl;
            cout << "   Alamat  : " << p.penumpang.alamat << endl;
            cout << "   Umur    : " << p.penumpang.umur << endl;
            cout << "   No HP   : " << p.penumpang.noHp << endl;

            cout << "\n (Catatan: NIK, tanggal keberangkatan, tujuan, kursi, dan pembayaran tidak bisa diubah)\n";
            
            // Minta input baru untuk data pribadi
            cout << "\n[DATA BARU]:\n";
            cout << "\n Masukkan data baru:\n";
            cout << "   Nama baru   : "; getline(cin, p.penumpang.nama);
            cout << "   Alamat baru : "; getline(cin, p.penumpang.alamat);
            cout << "   Umur baru   : "; cin >> p.penumpang.umur; cin.ignore();
            cout << "   No HP baru  : "; getline(cin, p.penumpang.noHp);

            // Tulis ulang ke file
            string namaFile = "tiket_" + p.penumpang.nik + "_" + p.tiket.tanggalKeberangkatan + ".txt";

            fstream file;
            file.open(namaFile, ios::out | ios::trunc);

            if (!file.is_open()) {
                cout << "   Gagal membuka file: " << namaFile << endl;
                return;
            }

            file << "======= TIKET KERETA (UPDATED) =======\n";
            file << "Tanggal Keberangkatan : " << p.tiket.tanggalKeberangkatan << "\n";
            file << "Nama                  : " << p.penumpang.nama << "\n";
            file << "NIK                   : " << p.penumpang.nik << "\n";
            file << "Alamat                : " << p.penumpang.alamat << "\n";
            file << "Umur                  : " << p.penumpang.umur << "\n";
            file << "No HP                 : " << p.penumpang.noHp << "\n";
            file << "Asal Kota Stasiun     : " << p.tiket.asalKotaStasiun << "\n";
            file << "Tujuan                : " << p.tiket.kotaTujuan << "\n";
            file << "Gerbong               : " << p.tiket.nomorGerbong + 1 << "\n";
            file << "Kursi                 : " << p.tiket.nomorTempatDuduk + 1 << "\n";
            file << "Metode Pembayaran     : " << p.pembayaran.metodePembayaran << "\n";
            if (p.pembayaran.sudahDibayar == true) {
                file << "Status Pembayaran     : " << "Sudah Dibayar" << endl;
            } else {
                file << "Status Pembayaran     : " << "Belum Dibayar" << endl;
            }
            file << "Harga                 : Rp" << p.pembayaran.totalHarga << "\n";
            file << "======================================\n";

            file.close();
            cout << "   Tiket berhasil diperbarui.\n";
            break;
        }
    }

    if (!found) {
        cout << "   Tiket dengan NIK tersebut tidak ditemukan pada tanggal itu.\n";
    }
}

void fileDeleteTiket() {
    string inputNIK, inputTanggal;

    cout << "\n[MENU HAPUS TIKET]\n";
    cout << "   Masukkan NIK: ";
    cin >> inputNIK;
    cin.ignore();
    cout << "   Masukkan tanggal keberangkatan (dd-mm-yyyy): ";
    getline(cin, inputTanggal);

    // Cari index tanggal
    int indexTanggal = -1;
    for (int i = 0; i < maxTanggal; i++) {
        if (daftarTanggal[i] == inputTanggal) {
            indexTanggal = i;
            break;
        }
    }

    if (indexTanggal == -1) {
        cout << "   Tanggal tidak ditemukan dalam sistem. \n";
        return;
    }

    // Cari data pemesanan di memori
    int indexDitemukan = -1;
    for (int i = 0; i < jumlahPemesanan[indexTanggal]; i++) {
        if (semuaPemesanan[indexTanggal][i].penumpang.nik == inputNIK) {
            indexDitemukan = i;
            break;
        }
    }

    if ( indexDitemukan == -1 ) {
        cout << "   Tiket dengan NIK tersebut tidak ditemukan pada tanggal itu.\n";
        return;
    }

    Pemesanan &p = semuaPemesanan[indexTanggal][indexDitemukan];

    // Kembalikan kursi jadi kosong
    kursiTerpakai[indexTanggal][p.tiket.nomorGerbong][p.tiket.nomorTempatDuduk] = false;

    // Hapus file tiket
    string namaFile = "tiket_" + inputNIK + "_" + inputTanggal + ".txt";
    if (remove(namaFile.c_str()) == 0) {
        cout << "   File tiket berhasil dihapus: " << namaFile << endl;
    } else {
        cout << "   File tidak ditemukan, tapi data tetap dihapus dari memori.\n";
    }

    // Geser array
    for (int j = indexDitemukan; j < jumlahPemesanan[indexTanggal] - 1; j++) {
        semuaPemesanan[indexTanggal][j] = semuaPemesanan[indexTanggal][j + 1];
    }
    jumlahPemesanan[indexTanggal]--;  // kurangi jumlah

    cout << "   Data tiket di memori juga telah dihapus.\n";
}