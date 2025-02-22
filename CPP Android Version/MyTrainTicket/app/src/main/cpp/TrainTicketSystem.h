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
    Kereta kereta;
    Penumpang penumpang;

public:
    TrainTicketSystem();
    void pesanTiket(int jenisKereta, int kotaAsal, int kotaTujuan,
                    const string& nama, const string& nik, const string& alamat,
                    int metodePemilihanKursi, int gerbong, int nomorKursi);
    string lihatStatusKursi();
    void resetData();

    void getDaftarJenisKereta(string* output, int& size);
    void getDaftarKotaAsal(string* output, int& size);
    void getDaftarKotaTujuan(string* output, int& size);
};

#endif //MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H
