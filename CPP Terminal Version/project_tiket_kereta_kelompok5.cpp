#include <iostream>
#include <string>
using namespace std;

//####################################
// Array 2 Dimensi
string kursi[3][10];

//####################################
// Array 1 Dimensi untuk menampilkan menu
string arrayJenisKereta[3] = {
    "Ekonomi",
    "Bisnis",
    "Eksekutif"
};

string arrayKotaAsal[5] = {
    "Kota Yogyakarta",
    "Kabupaten Sleman",
    "Kabupaten Gunung Kidul",
    "Kabupaten Bantul",
    "Kabupaten Kulon Progo"
};

string arrayKotaTujuan[10] = {
    "Kota Magelang",
    "Kabupaten Magelang",
    "Kabupaten Banjarnegara",
    "Kabupaten Boyolali",
    "Kabupaten Cilacap",
    "Kabupaten Brebes",
    "Kabupaten Demak",
    "Kabupaten Jepara",
    "Kota Semarang",
    "Kota Salatiga"
};

//####################################
// Struct atau Record
struct Penumpang {
    string 
        nama, 
        nik, 
        alamat;
};

struct Kereta {
    string 
        jenisKereta, 
        kotaAsal, 
        kotaTujuan, 
        metodePembayaran;
};

Kereta kereta;
Penumpang penumpang;

//####################################
// Deklarasi function
void tampilkanMenu();
void tampilkanKursi();
void inputDataKereta();
void inputDataPenumpang();
void tampilkanJenisKereta();
void tampilkanDataKotaAsal();
void tampilkanDataKotaTujuan();
void resetData();

//####################################
// Function main (dieksekusi paling utama)
int main() {
    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1 :
                inputDataKereta();
                inputDataPenumpang();
                break;
            
            case 2 :
                tampilkanKursi();
                break;
            
            case 3 :
                cout << "Terima kasih telah menggunakan layanan kami!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silahkan coba lagi." << endl;
                break;
        }

    } while (pilihan != 3);

    return 0;
}

//####################################
// Function untuk User Interface
void tampilkanMenu(){
    cout << "\n=== Menu Utama ===" << endl;
    cout << "1. Pesan Tiket" << endl;
    cout << "2. Lihat Status Kursi" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilihan: ";
}

void tampilkanKursi() {
    cout << "\n=== Status Kursi ===" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Gerbong " << i + 1 << ":" << endl;
        for (int j = 0; j < 10; j++) {
            cout << " Kursi " << j + 1 << ": ";
            if (kursi[i][j].empty()) {
                cout << "Tersedia" << endl;
            } else {
                cout << "Dipesan oleh " << kursi[i][j] << endl;
            }
        }

        cout << endl;
    }
    cout << "====================" << endl;
}

void inputDataKereta() {
    int pilih;
    cout << "\nPilih jenis kereta: " << endl;
    tampilkanJenisKereta();
    cout << "Pilihan    : ";
    cin >> pilih;
    cin.ignore(); // Membersihkan buffer
    cout << endl;

    switch (pilih) {
        case 1:
            kereta.jenisKereta = arrayJenisKereta[0];
            break;
        case 2:
            kereta.jenisKereta = arrayJenisKereta[1];
            break;
        case 3:
            kereta.jenisKereta = arrayJenisKereta[2];
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }

    cout << "\nPilih kota asal: " << endl;
    tampilkanDataKotaAsal();
    cout << "Pilihan    : ";
    cin >> pilih;
    cin.ignore(); // Membersihkan buffer
    cout << endl;

    if (pilih >= 1 && pilih <= 5) {
        kereta.kotaAsal = arrayKotaAsal[pilih - 1];     // `- 1` karena array itu dimulai dari 0
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    cout << "\nPilih kota tujuan: " << endl;
    tampilkanDataKotaTujuan();
    cout << "Pilihan    : ";
    cin >> pilih;
    cin.ignore(); // Membersihkan buffer
    if (pilih >= 1 && pilih <= 10) {
        kereta.kotaTujuan = arrayKotaTujuan[pilih - 1]; // `- 1` karena array itu dimulai dari 0
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }
}

void inputDataPenumpang() {
    resetData();    // Reset data sebelum mengisi yang baru

    cout << "\nInputkan data diri Anda: " << endl;
    cout << "Nama   : ";
    getline(cin, penumpang.nama);
    cout << "NIK    : ";
    getline(cin, penumpang.nik);
    cout << "Alamat : ";
    getline(cin, penumpang.alamat);

    int pilihan;
    bool kursiDitemukan = false;

    cout << "\nPilih metode pemilihan kursi : "<<endl;
    cout << "1. Pilih kursi sendiri"<<endl;
    cout << "2. Biarkan sistem memilihkan kursi"<<endl;
    cout << "Pilihan : ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1 :
            int gerbong, nomorKursi;

            do {
                cout << "\nPilih gerbong (1-3): ";
                cin >> gerbong;
                cout << "Pilih nomor kursi (1-10): ";
                cin >> nomorKursi;
                cin.ignore(); // Membersihkan buffer

                if (gerbong < 1 || gerbong > 3 || nomorKursi < 1 || nomorKursi > 10) {
                    cout << "Pilihan gerbong atau kursi tidak valid!" << endl;
                    // return;
                }
            } while (gerbong < 1  || gerbong > 3 || nomorKursi < 1 || nomorKursi > 10);

            
            if (kursi[gerbong - 1][nomorKursi - 1].empty()) {
                kursi[gerbong - 1][nomorKursi - 1] = penumpang.nama;
                cout << "Kursi berhasil dipesan!" << endl;
            } else {
                cout << "Maaf, kursi sudah dipesan." << endl;
            }

            break;

        
        case 2 :
            // Opsi 2: Sistem memilihkan kursi
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 10; j++) {
                    if (kursi[i][j].empty()) {
                        kursi[i][j] = penumpang.nama;
                        cout    << "Kursi dipilihkan oleh sistem: Gerbong" << i + 1 
                                << ", Kursi " << j +1 <<endl;
                        
                        kursiDitemukan = true;
                        break;
                    }
                }

                if (kursiDitemukan) { break;}            
            }

            if (!kursiDitemukan) { 
                cout << "Maaf, tidak ada kursi tersedia. Apakah Anda ingin mencoba lagi (Y/y)" << endl; 
                
                char cobaLagi;

                cin >> cobaLagi;
                cin.ignore();

                if (cobaLagi == 'Y' || cobaLagi == 'y') {
                    inputDataPenumpang(); // Coba lagi
                } else {
                    cout << "Pemesanan dibatalkan. " << endl;
                }
            }
            
            break;


        default :
            cout << "Pilihan tidak valid!"<< endl;
            break;
    }
}

//####################################
// Function pendukung untuk mengurangi redundansi (penggunaan berulang-ulang)
void resetData(){
    penumpang = Penumpang();    // Reset data penumpang
    kereta = Kereta();          // Reset data kereta
}

void tampilkanJenisKereta() {
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << arrayJenisKereta[i] << endl;
    }
}

void tampilkanDataKotaAsal() {
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << arrayKotaAsal[i] << endl;
    }
}

void tampilkanDataKotaTujuan() {
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << ". " << arrayKotaTujuan[i] << endl;
    }
}