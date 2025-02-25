#ifndef MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H
#define MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H

#include <iostream>

using namespace std;

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

class TrainTicketSystem {
private:
    string kursi[3][10];

    string arrayJenisKereta[3];
    string arrayKotaAsal[5];
    string arrayKotaTujuan[10];
    /*
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
     */
    Kereta kereta;
    Penumpang penumpang;

public:
    TrainTicketSystem();
    void pesanTiket(
            int jenisKereta,
            int kotaAsal,
            int kotaTujuan,
            const string& nama,
            const string& nik,
            const string& alamat,
            int metodePemilihanKursi,
            int gerbong,
            int nomorKursi);
    string lihatStatusKursi();
    void resetData();

    void getDaftarJenisKereta(string* output, int& size);
    void getDaftarKotaAsal(string* output, int& size);
    void getDaftarKotaTujuan(string* output, int& size);
};

#endif //MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H
