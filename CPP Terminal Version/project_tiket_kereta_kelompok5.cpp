//////////////////////////////////////////////////////////////////////////////////////
// Yang bakal dipake
/*
#include <iostream>
#include <string>

using namespace std;

string kursi[3][10];     // Array 2D untuk kursi (baris = gerbong dan kolom = nomor kursi)

string arrayJenisKereta[3] = {  "Ekonomi",
                                "Bisnis",
                                "Eksekutif"
                                };

string arrayKotaAsal[5] = { "1. Kota Yogyakarta",
                            "2. Kabupaten Sleman",
                            "3. Kabupaten Gunung Kidul",
                            "4. Kabupaten Basntul",
                            "5. Kabupaten Kulon Progo" 
                            };

string arrayKotaTujuan[10] = {  "1. Kota Magelang",
                                "2. Kabupaten Magelang",
                                "3. Kabupaten Banjarnegara",
                                "4. Kabupaten Boyolali",
                                "5. Kabupaten Cilacap",
                                "6. Kabupaten Brebes",
                                "7. Kabupaten Demak",
                                "8. Kabupaten Jepara",
                                "9. Kota Semarang",
                                "10. Kota Salatiga"
                                };

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

void tampilkanKursi();
void inputDataKereta();
void inputDataPenumpang();

int main () {
    inputDataKereta();
    inputDataPenumpang();
    
}

void tampilkanKursi(){
    cout << "Status kursi";
}

void inputDataKereta() {
    int pilih;
    cout << "Pilih jenis kereta : " << endl;
    tampilkanJenisKereta();
    cout << endl;
    cin >> pilih;
    switch (pilih)
    {
    case 1:
        kereta.jenisKereta = arrayJenisKereta[1];
        break;
    
    case 2:
        kereta.jenisKereta = arrayJenisKereta[2];
        break;
    
    case 3:
        kereta.jenisKereta = arrayJenisKereta[3];
        break;
    
    default:
        cout << "Pilihan tidak valid";
        break;
    }
}

void inputDataPenumpang() {
    // Pengecekan posisi nomor kursi yang sudah diisi agar tidak ditempati

    // Penempatan posisi nomor kursi yang belum diisi untuk ditempati
    for (int i = 0; i < 3 ; i++) {
        for (int j = 0; j < 10; j++) {
            getline(cin, penumpang.nama);
            kursi[i][j] = penumpang.nama;
            break;
        }
    }


    cout << "Inputkan data diri anda : ";
    cout << "Nama   : ";
    getline(cin, penumpang.nama);
    cout << "NIK    : ";
    getline(cin, penumpang.nik);
    cout << "Alamat : ";
}

void tampilkanJenisKereta() {
    for (int i = 0; i < 3; i++) {
        cout << arrayJenisKereta[i];
    }
}

void tampilkanDataKotaAsal() {
    for (int i = 0; i < 5; i++) {
        cout << arrayKotaAsal[i] << endl;
    }
}

void tampilkanDataKotaTujuan() {
    for (int i = 0; i < 10; i++) {
        cout << arrayKotaTujuan[i] << endl;
    }
}
*/


///////////////////////////////////////////////////////////////////////////////////////
// Referensi
#include <iostream>
#include <string>
using namespace std;

string kursi[3][10];

string arrayJenisKereta[3] = {
    "Ekonomi",
    "Bisnis",
    "Eksekutif"
};

string arrayKotaAsal[5] = {
    "1. Kota Yogyakarta",
    "2. Kabupaten Sleman",
    "3. Kabupaten Gunung Kidul",
    "4. Kabupaten Bantul",
    "5. Kabupaten Kulon Progo"
};

string arrayKotaTujuan[10] = {
    "1. Kota Magelang",
    "2. Kabupaten Magelang",
    "3. Kabupaten Banjarnegara",
    "4. Kabupaten Boyolali",
    "5. Kabupaten Cilacap",
    "6. Kabupaten Brebes",
    "7. Kabupaten Demak",
    "8. Kabupaten Jepara",
    "9. Kota Semarang",
    "10. Kota Salatiga"
};

struct Penumpang {
    string nama, nik, alamat;
};

struct Kereta {
    string jenisKereta, kotaAsal, kotaTujuan, metodePembayaran;
};

Kereta kereta;
Penumpang penumpang;

void tampilkanKursi();
void inputDataKereta();
void inputDataPenumpang();
void tampilkanJenisKereta();
void tampilkanDataKotaAsal();
void tampilkanDataKotaTujuan();

int main() {
    inputDataKereta();
    inputDataPenumpang();
    tampilkanKursi();
    return 0;
}

void tampilkanKursi() {
    cout << "\n=== Status Kursi ===" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            cout << "Gerbong " << i + 1 << ", Kursi " << j + 1 << ": ";
            if (kursi[i][j].empty()) {
                cout << "Tersedia" << endl;
            } else {
                cout << "Dipesan oleh " << kursi[i][j] << endl;
            }
        }
    }
    cout << "====================" << endl;
}

void inputDataKereta() {
    int pilih;
    cout << "Pilih jenis kereta: " << endl;
    tampilkanJenisKereta();
    cin >> pilih;
    cin.ignore(); // Membersihkan buffer

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
    cin >> pilih;
    cin.ignore(); // Membersihkan buffer
    if (pilih >= 1 && pilih <= 5) {
        kereta.kotaAsal = arrayKotaAsal[pilih - 1];
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    cout << "\nPilih kota tujuan: " << endl;
    tampilkanDataKotaTujuan();
    cin >> pilih;
    cin.ignore(); // Membersihkan buffer
    if (pilih >= 1 && pilih <= 10) {
        kereta.kotaTujuan = arrayKotaTujuan[pilih - 1];
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }
}

void inputDataPenumpang() {
    cout << "\nInputkan data diri Anda: " << endl;
    cout << "Nama   : ";
    getline(cin, penumpang.nama);
    cout << "NIK    : ";
    getline(cin, penumpang.nik);
    cout << "Alamat : ";
    getline(cin, penumpang.alamat);

    int pilihan;
    cout << "\nPilih metode pemilihan kursi : "<<endl;
    cout << "1. Pilih kursi sendiri"<<endl;
    cout << "2. Biarkan sistem memilihkan kursi"<<endl;
    cout << "Pilihan : " << endl;
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        int gerbong, nomorKursi;
        cout << "\nPilih gerbong (1-3): ";
        cin >> gerbong;
        cout << "Pilih nomor kursi (1-10): ";
        cin >> nomorKursi;
        cin.ignore(); // Membersihkan buffer

        if (gerbong < 1 || gerbong > 3 || nomorKursi < 1 || nomorKursi > 10) {
            cout << "Pilihan gerbong atau kursi tidak valid!" << endl;
            return;
        }

        if (kursi[gerbong - 1][nomorKursi - 1].empty()) {
            kursi[gerbong - 1][nomorKursi - 1] = penumpang.nama;
            cout << "Kursi berhasil dipesan!" << endl;
        } else {
            cout << "Maaf, kursi sudah dipesan." << endl;
        }
    } else if (pilihan == 2) {
        // Opsi 2: Sistem memilihkan kursi
        bool kursiDitemukan = false;
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

        if (!kursiDitemukan) { cout << "Maaf, tidak ada kursi tersedia." << endl; }
    } else {
        cout << "Pilihan tidak valid!"<< endl;
    }
}

void tampilkanJenisKereta() {
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << arrayJenisKereta[i] << endl;
    }
}

void tampilkanDataKotaAsal() {
    for (int i = 0; i < 5; i++) {
        cout << arrayKotaAsal[i] << endl;
    }
}

void tampilkanDataKotaTujuan() {
    for (int i = 0; i < 10; i++) {
        cout << arrayKotaTujuan[i] << endl;
    }
}