//
// Created by ACER on 21/02/2025.
//

#ifndef MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H
#define MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H

#include <iostream>

using namespace std;

string kursi[3][10];

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


#endif //MY_TRAIN_TICKET_TRAINTICKETSYSTEM_H
