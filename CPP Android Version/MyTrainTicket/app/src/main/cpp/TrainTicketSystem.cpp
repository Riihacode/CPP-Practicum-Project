#include "TrainTicketSystem.h"
#include <iostream>
using namespace std;

TrainTicketSystem::TrainTicketSystem() {
    arrayJenisKereta[0] = "Ekonomi";
    arrayJenisKereta[1] = "Bisnis";
    arrayJenisKereta[2] = "Eksekutif";

    arrayKotaAsal[0] = "Kota Yogyakarta";
    arrayKotaAsal[1] = "Kabupaten Sleman";
    arrayKotaAsal[2] = "Kabupaten Gunung Kidul";
    arrayKotaAsal[3] = "Kabupaten Bantul";
    arrayKotaAsal[4] = "Kabupaten Kulon Progo";

    arrayKotaTujuan[0] = "Kota Magelang";
    arrayKotaTujuan[1] = "Kabupaten Magelang";
    arrayKotaTujuan[2] = "Kabupaten Banjarnegara";
    arrayKotaTujuan[3] = "Kabupaten Boyolali";
    arrayKotaTujuan[4] = "Kabupaten Cilacap";
    arrayKotaTujuan[5] = "Kabupaten Brebes";
    arrayKotaTujuan[6] = "Kabupaten Demak";
    arrayKotaTujuan[7] = "Kabupaten Jepara";
    arrayKotaTujuan[8] = "Kota Semarang";
    arrayKotaTujuan[9] = "Kota Salatiga";

    for(int i=0; i<3; i++)
        for(int j=0; j<10; j++)
            kursi[i][j] = "";

}


void TrainTicketSystem::pesanTiket(
        int jenisKeretaIdx,
        int kotaAsalIdx,
        int kotaTujuanIdx,
        const string& nama,
        const string& nik,
        const string& alamat,
        int metodePemilihanKursi,
        int gerbong,
        int nomorKursi) {
    resetData();

    kereta.jenisKereta = arrayJenisKereta[jenisKeretaIdx];
    kereta.kotaAsal = arrayKotaAsal[kotaAsalIdx];
    kereta.kotaTujuan = arrayKotaTujuan[kotaTujuanIdx];

    penumpang.nama = nama;
    penumpang.nik = nik;
    penumpang.alamat = alamat;

    if(metodePemilihanKursi == 1) {
        if(gerbong >= 1 && gerbong <= 3 && nomorKursi >= 1 && nomorKursi <= 10) {
            kursi[gerbong-1][nomorKursi-1] = penumpang.nama;
        }
    } else {
        for(int i=0; i<3; i++) {
            for(int j=0; j<10; j++) {
                if(kursi[i][j].empty()) {
                    kursi[i][j] = penumpang.nama;
                    kursi[i][j] = penumpang.nik;
                    kursi[i][j] = penumpang.alamat;
                    return;
                }
            }
        }
    }
}

string TrainTicketSystem::lihatStatusKursi() {
    string result;
    for(int i=0; i<3; i++) {
        result += "Gerbong " + to_string(i+1) + ":\n";
        for(int j=0; j<10; j++) {
            result += "Kursi " + to_string(j+1) + ": ";
            result += kursi[i][j].empty() ? "Tersedia" : kursi[i][j];
            result += "\n";
        }
    }
    return result;
}

void TrainTicketSystem::resetData() {
    penumpang = Penumpang();
    kereta = Kereta();
}

void TrainTicketSystem::getDaftarJenisKereta(std::string* output, int& size) {
    size = 3;
    if (output != nullptr) {
        for(int i=0; i<size; i++) {
            output[i] = arrayJenisKereta[i];
        }
    }
}

void TrainTicketSystem::getDaftarKotaAsal(std::string* output, int& size) {
    size = 5;
    if (output != nullptr) {
        for(int i=0; i<size; i++) {
            output[i] = arrayKotaAsal[i];
        }
    }
}

void TrainTicketSystem::getDaftarKotaTujuan(std::string* output, int& size) {
    size = 10;
    if (output != nullptr) {
        for(int i=0; i<size; i++) {
            output[i] = arrayKotaTujuan[i];
        }
    }
}