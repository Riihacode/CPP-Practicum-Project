#include "TrainTicketSystem.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sstream>

bool seatsEachPortal[portalClass][portalClassSeat] = {false};

Booking bookings[30];

std::string departuresCity[5] = {
        "Yogyakarta", "Sleman", "Gunung Kidul", "Bantul", "Kulon Progo"
};

std::string destinationsCity[5] = {
        "Magelang", "Semarang", "Jepara", "Cilacap", "Boyolali"
};

std::string paymentMethods[3] = {
        "Transfer", "E-Wallet", "Cash"
};

int indexDeparture = 0;
// Fungsi booking otomatis
std::string autoBookTicket() {
    std::stringstream ss;
    if (indexDeparture >= 30) {
        ss << "All seats already booked";
        return ss.str();
    }

    std::string sampleNames[] = {"Budi", "Ani", "Citra", "Dedi", "Eka", "Fajar", "Gita", "Hana"};
    std::string sampleAddresses[] = {"Yogyakarta", "Sleman", "Bantul", "Kulon Progo"};

    srand(time(0));

    int coach = -1, seat = -1;
    bool foundSeat = false;

    for (int g = 0; g < portalClass && !foundSeat; g++) {
        for (int s = 0; s < portalClassSeat && !foundSeat; s++) {
            if (!seatsEachPortal[g][s]) {
                coach = g;
                seat = s;
                foundSeat = true;
            }
        }
    }

    if (!foundSeat) {
        ss << "Tidak ada kursi kosong";
        return ss.str();
    }

    std::string generatedNIK;
    bool isDuplicate;
    do {
        isDuplicate = false;
        int randomNIK = 100000000 + rand() % 900000000;
        generatedNIK = std::to_string(randomNIK);

        for (int i = 0; i < indexDeparture; i++) {
            if (bookings[i].passenger.nik == generatedNIK) {
                isDuplicate = true;
                break;
            }
        }
    } while (isDuplicate);

    std::string baseName = sampleNames[rand() % 8];
    std::string uniqueName = baseName + "-" + std::to_string(indexDeparture + 1);

    seatsEachPortal[coach][seat] = true;
    Booking &b = bookings[indexDeparture];
    b.passenger.name = uniqueName;
    b.passenger.nik = generatedNIK;
    b.passenger.address = sampleAddresses[rand() % 4];
    b.ticket.departureCity = departuresCity[rand() % 5];
    b.ticket.destinationCity = destinationsCity[rand() % 5];
    b.ticket.coachNumber = coach;
    b.ticket.seatNumber = seat;
    b.ticket.travelDate = "2025-04-01";
    b.payment.paymentMethod = paymentMethods[rand() % 3];
    b.payment.isPaid = true;
    b.payment.totalPrice = 100000;

    ss << "[RESULT] Pemesanan otomatis berhasil untuk " << b.passenger.name
       << " dengan NIK " << b.passenger.nik
       << " di kursi " << coach + 1 << "-" << seat + 1;

    indexDeparture++;
    return ss.str();
}

// Fungsi manual input booking
std::string manualInput(std::istream &in) {
    std::stringstream ss;

    if (indexDeparture >= 30) {
        ss << "   Semua kursi telah dipesan!";
        return ss.str();
    }

    int chooseDepartureCity, chooseDestinationCity, chooseTrainClass, choosePayment;
    int coachNumber, seatNumber;

    ss << "[INPUT PERSONAL DATA]";
    ss << "   Name       : ";
    in.ignore();
    getline(in, bookings[indexDeparture].passenger.name);
    ss << "   NIK        : ";
    getline(in, bookings[indexDeparture].passenger.nik);
    ss << "   Address    : ";
    getline(in, bookings[indexDeparture].passenger.address);
    ss << "";

    ss << "[DEPARTURE CITY MENU]";
    for (int i = 0; i < 5; i++) {
        ss << i + 1 << ". " << departuresCity[i] << "";
    }
    ss << "   Choose your option: ";
    in >> chooseDepartureCity;
    bookings[indexDeparture].ticket.departureCity = departuresCity[chooseDepartureCity - 1];

    ss << "[DESTINATION CITY MENU]";
    for (int i = 0; i < 5; i++) {
        ss << "   " << i + 1 << ". " << destinationsCity[i] << "";
    }
    ss << "   Choose your option: ";
    in >> chooseDestinationCity;
    bookings[indexDeparture].ticket.destinationCity = destinationsCity[chooseDestinationCity - 1];

    ss << "[AVAILABLE SEAT]";
    for (int i = 0; i < 3; i++) {
        ss << "   Coach Train-" << i + 1 << " = ";
        for (int j = 0; j < 10; j++) {
            if (seatsEachPortal[i][j] != false) {
                ss << "       [X] ";
            } else {
                ss << "       [" << std::to_string(j + 1) << "]";
            }
        }
        ss << "";
    }

    ss << "[CHOOSE SEAT]";
    ss << "   Choose Coach Train (1 - 3)     : ";
    in >> coachNumber;
    coachNumber -= 1;
    ss << "   Choose Seat Number (1 - 10)    : ";
    in >> seatNumber;
    seatNumber -= 1;

    if (seatsEachPortal[coachNumber][seatNumber]) {
        ss << "       The Seat Number already been booked!";
        return ss.str();
    }

    seatsEachPortal[coachNumber][seatNumber]    = true;
    bookings[indexDeparture].ticket.coachNumber = coachNumber;
    bookings[indexDeparture].ticket.seatNumber  = seatNumber;
    bookings[indexDeparture].ticket.travelDate  = "2025-04-01";

    ss << "[PAYMENT METHOD]";
    for (int i = 0; i < 3; i++) {
        ss << "   " << i + 1 << ". " << paymentMethods[i] << "";
    }
    ss << "   Choose your option: ";
    in >> choosePayment;
    bookings[indexDeparture].payment.paymentMethod  = paymentMethods[choosePayment - 1];
    bookings[indexDeparture].payment.isPaid         = true;
    bookings[indexDeparture].payment.totalPrice     = 100000;

    ss << "   [RESULT] Your ticket booking was successful!";
    indexDeparture++;

    return ss.str();
}

// Fungsi pencarian berdasarkan NIK
std::string searchByNIK() {
    std::stringstream ss;
    bool found = false;
    for (int i = 0; i < indexDeparture; ++i) {
        found = true;
        ss << "[FOUND - TICKET]";
        ss << "   Nama       : " << bookings[i].passenger.name << "";
        ss << "   NIK        : " << bookings[i].passenger.nik << "";
        ss << "   Asal       : " << bookings[i].ticket.departureCity << "";
        ss << "   Tujuan     : " << bookings[i].ticket.destinationCity << "";
        ss << "   Kursi      : " << bookings[i].ticket.coachNumber << "-" << bookings[i].ticket.seatNumber << "";
        ss << "   Total Bayar: Rp" << bookings[i].payment.totalPrice << "";
        break;
    }
    return ss.str();
}

// Fungsi sequential search tanpa sentinel
std::string seqNonSentinelNotYetSorted(std::string *nikPointer) {
    std::stringstream ss;
    bool found = false;
    int i = 0;

    while ((i < indexDeparture) && (!found)) {
        if (bookings[i].passenger.nik == *nikPointer) {
            found = true;
        } else {
            i++;
        }
    }

    if (found) {
        ss << "[FOUND - NIK]";
        ss << "   Nama       : " << bookings[i].passenger.name << "";
        ss << "   NIK        : " << bookings[i].passenger.nik << "";
        ss << "   Asal       : " << bookings[i].ticket.departureCity << "";
        ss << "   Tujuan     : " << bookings[i].ticket.destinationCity << "";
        ss << "   Kursi      : " << bookings[i].ticket.coachNumber + 1 << "-" << bookings[i].ticket.seatNumber + 1 << "";
        ss << "   Total Bayar: Rp" << bookings[i].payment.totalPrice << "";
    } else {
        ss << "   NIK not found! ";
    }

    return ss.str();
}

// Fungsi sequential search dengan sentinel
std::string seqSentinelNotYetSorted(std::string *nikPointer) {
    std::stringstream ss;
    Booking tempBackup = bookings[indexDeparture];
    bookings[indexDeparture].passenger.nik = *nikPointer;

    int i = 0;
    while (bookings[i].passenger.nik != *nikPointer) {
        i++;
    }

    bookings[indexDeparture] = tempBackup;

    if (i < indexDeparture) {
        ss << "[FOUND - NIK]";
        ss << "   Nama       : " << bookings[i].passenger.name << "";
        ss << "   NIK        : " << bookings[i].passenger.nik << "";
        ss << "   Asal       : " << bookings[i].ticket.departureCity << "";
        ss << "   Tujuan     : " << bookings[i].ticket.destinationCity << "";
        ss << "   Kursi      : " << bookings[i].ticket.coachNumber + 1 << "-" << bookings[i].ticket.seatNumber + 1 << "";
        ss << "   Total Bayar: Rp" << bookings[i].payment.totalPrice << "";
    } else {
        ss << "   NIK not found!";
    }

    return ss.str();
}

// Fungsi binary search setelah data disortir berdasarkan NIK
std::string binarySearch(Booking *copyBinary, std::string *nikPointer) {
    std::stringstream ss;
    bubbleSortByNik(copyBinary);

    int i = 0, j = indexDeparture - 1, k;
    bool found = false;

    while ((i <= j) && (!found)) {
        k = (i + j) / 2;
        if (*nikPointer == copyBinary[k].passenger.nik) {
            found = true;
        } else {
            if (*nikPointer < copyBinary[k].passenger.nik) {
                j = k - 1;
            } else {
                i = k + 1;
            }
        }
    }

    if (found) {
        ss << "[FOUND - NIK]";
        ss << "   Nama       : " << copyBinary[k].passenger.name << "";
        ss << "   NIK        : " << copyBinary[k].passenger.nik << "";
        ss << "   Asal       : " << copyBinary[k].ticket.departureCity << "";
        ss << "   Tujuan     : " << copyBinary[k].ticket.destinationCity << "";
        ss << "   Kursi      : " << copyBinary[k].ticket.coachNumber + 1 << "-" << copyBinary[k].ticket.seatNumber + 1 << "";
        ss << "   Total Bayar: Rp" << copyBinary[k].payment.totalPrice << "";
    } else {
        ss << "   NIK not found!";
    }

    return ss.str();
}


void bubbleSortByNik(Booking *copyBubleNik) {
    for (int i = 0; i < indexDeparture - 1; i++) {
        for (int j = 0; j < indexDeparture - 1 - i; j++) {
            if (copyBubleNik[j].passenger.nik > copyBubleNik[j + 1].passenger.nik) {
                Booking temp        = copyBubleNik[j];
                copyBubleNik[j]     = copyBubleNik[j + 1];
                copyBubleNik[j + 1] = temp;
            }
        }
    }
}

void bubbleSort(Booking *copyBubble) {
    for (int i = 0; i < indexDeparture - 1; i++) {
        for (int j = 0; j < indexDeparture - 1 - i; j++) {
            if (copyBubble[j].passenger.name > copyBubble[j + 1].passenger.name) {
                Booking temp      = copyBubble[j];
                copyBubble[j]     = copyBubble[j + 1];
                copyBubble[j + 1] = temp;
            }
        }
    }
}

// Fungsi straight insertion sort berdasarkan nama penumpang
void straightInsertionSort(Booking *copyInsertion) {
    int i, j;
    Booking temp;

    for (i = 1; i < indexDeparture; i++) {
        temp = copyInsertion[i];
        j = i - 1;
        while ((j >= 0) && (temp.passenger.name < copyInsertion[j].passenger.name)) {
            copyInsertion[j + 1] = copyInsertion[j];
            j = j - 1;
        }
        copyInsertion[j + 1] = temp;
    }
}

// Fungsi selection sort berdasarkan nama penumpang
void selectionSort(Booking *copySelection) {
    for (int current = 0; current < indexDeparture; current++) {
        for (int j = current + 1; j < indexDeparture; j++) {
            if (copySelection[current].passenger.name > copySelection[j].passenger.name) {
                Booking temp = copySelection[current];
                copySelection[current] = copySelection[j];
                copySelection[j] = temp;
            }
        }
    }
}

// Fungsi shell sort berdasarkan nama penumpang
void shellSort(Booking *copyShell) {
    for (int gap = indexDeparture / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < indexDeparture; i++) {
            Booking temp = copyShell[i];
            int j;
            for (j = i; j >= gap && copyShell[j - gap].passenger.name > temp.passenger.name; j -= gap) {
                copyShell[j] = copyShell[j - gap];
            }
            copyShell[j] = temp;
        }
    }
}

// Fungsi quick sort berdasarkan nama penumpang
void quickSort(Booking *bookingsQuick, int first, int last) {
    int low = first, high = last;
    Booking pivot = bookingsQuick[(first + last) / 2];

    do {
        while (bookingsQuick[low].passenger.name < pivot.passenger.name) {
            low++;
        }
        while (bookingsQuick[high].passenger.name > pivot.passenger.name) {
            high--;
        }
        if (low <= high) {
            Booking temp = bookingsQuick[low];
            bookingsQuick[low] = bookingsQuick[high];
            bookingsQuick[high] = temp;
            low++;
            high--;
        }
    } while (low <= high);

    if (first < high) quickSort(bookingsQuick, first, high);
    if (low < last) quickSort(bookingsQuick, low, last);
}


// Fungsi menampilkan hasil sorting booking
std::string sortingOutputShow(Booking *sortingShow) {
    std::stringstream ss;
    ss << "[ALL BOOKING DATA - AFTER SORTED (A-Z)]";
    for (int i = 0; i < indexDeparture; i++) {
        ss << "   " << i + 1 << ". Nama: " << sortingShow[i].passenger.name
           << ", NIK: " << sortingShow[i].passenger.nik
           << ", Asal: " << sortingShow[i].ticket.departureCity
           << ", Tujuan: " << sortingShow[i].ticket.destinationCity
           << "";
    }
    ss << "";
    return ss.str();
}

// Fungsi menyimpan seluruh tiket ke file
std::string fileOperationSave(Booking bookings[], int totalData) {
    std::stringstream ss;
    FILE *fp = fopen("ticket_data.txt", "w");
    if (fp == NULL) {
        ss << "Failed to open file!";
        return ss.str();
    }
    for (int i = 0; i < totalData; i++) {
        fprintf(fp, "==============================\n");
        fprintf(fp, "         TRAIN TICKET\n");
        fprintf(fp, "==============================\n");
        fprintf(fp, "Name           : %s\n", bookings[i].passenger.name.c_str());
        fprintf(fp, "NIK            : %s\n", bookings[i].passenger.nik.c_str());
        fprintf(fp, "Address        : %s\n", bookings[i].passenger.address.c_str());
        fprintf(fp, "Departure City : %s\n", bookings[i].ticket.departureCity.c_str());
        fprintf(fp, "Destination    : %s\n", bookings[i].ticket.destinationCity.c_str());
        fprintf(fp, "Coach - Seat   : %d - %d\n", bookings[i].ticket.coachNumber + 1, bookings[i].ticket.seatNumber + 1);
        fprintf(fp, "Travel Date    : %s\n", bookings[i].ticket.travelDate.c_str());
        fprintf(fp, "Payment Method : %s\n", bookings[i].payment.paymentMethod.c_str());
        fprintf(fp, "Paid           : %s\n", bookings[i].payment.isPaid ? "Yes" : "No");
        fprintf(fp, "Total Price    : Rp%d\n", bookings[i].payment.totalPrice);
        fprintf(fp, "==============================\n\n");
    }
    fclose(fp);
    ss << "All ticket has been saved successfully.";
    return ss.str();
}

std::string fileOperationSaveSingle(Booking bookings[], int totalData, const std::string &targetNIK) {
    std::stringstream ss;
    bool found = false;

    for (int i = 0; i < totalData; i++) {
        if (bookings[i].passenger.nik == targetNIK) {
            std::string fileName = targetNIK + "_ticket_data.txt";
            FILE *fp = fopen(fileName.c_str(), "w");

            if (fp == NULL) {
                ss << "Failed to open ticket file!";
                return ss.str();
            }

            fprintf(fp, "==============================\n");
            fprintf(fp, "         TRAIN TICKET\n");
            fprintf(fp, "==============================\n");
            fprintf(fp, "Name           : %s\n", bookings[i].passenger.name.c_str());
            fprintf(fp, "NIK            : %s\n", bookings[i].passenger.nik.c_str());
            fprintf(fp, "Address        : %s\n", bookings[i].passenger.address.c_str());
            fprintf(fp, "Departure City : %s\n", bookings[i].ticket.departureCity.c_str());
            fprintf(fp, "Destination    : %s\n", bookings[i].ticket.destinationCity.c_str());
            fprintf(fp, "Coach - Seat   : %d - %d\n", bookings[i].ticket.coachNumber + 1, bookings[i].ticket.seatNumber + 1);
            fprintf(fp, "Travel Date    : %s\n", bookings[i].ticket.travelDate.c_str());
            fprintf(fp, "Payment Method : %s\n", bookings[i].payment.paymentMethod.c_str());
            fprintf(fp, "Paid           : %s\n", bookings[i].payment.isPaid ? "Yes" : "No");
            fprintf(fp, "Total Price    : Rp%d\n", bookings[i].payment.totalPrice);
            fprintf(fp, "==============================\n");

            fclose(fp);

            ss << "Ticket has been saved successfully: " << fileName;
            found = true;
            break;
        }
    }

    if (!found) {
        ss << "Data not found.";
    }

    return ss.str();
}

std::string fileOperationSaveTo(const std::string& path) {
    FILE *fp = fopen(path.c_str(), "w");
    std::stringstream ss;

    if (fp == nullptr) {
        ss << "Failed to open file: " << path;
        return ss.str();
    }

    for (int i = 0; i < indexDeparture; ++i) {
        fprintf(fp, "==============================\n");
        fprintf(fp, "         TRAIN TICKET\n");
        fprintf(fp, "==============================\n");
        fprintf(fp, "Name           : %s\n", bookings[i].passenger.name.c_str());
        fprintf(fp, "NIK            : %s\n", bookings[i].passenger.nik.c_str());
        fprintf(fp, "Address        : %s\n", bookings[i].passenger.address.c_str());
        fprintf(fp, "Departure City : %s\n", bookings[i].ticket.departureCity.c_str());
        fprintf(fp, "Destination    : %s\n", bookings[i].ticket.destinationCity.c_str());
        fprintf(fp, "Coach - Seat   : %d - %d\n", bookings[i].ticket.coachNumber + 1, bookings[i].ticket.seatNumber + 1);
        fprintf(fp, "Travel Date    : %s\n", bookings[i].ticket.travelDate.c_str());
        fprintf(fp, "Payment Method : %s\n", bookings[i].payment.paymentMethod.c_str());
        fprintf(fp, "Paid           : %s\n", bookings[i].payment.isPaid ? "Yes" : "No");
        fprintf(fp, "Total Price    : Rp%d\n", bookings[i].payment.totalPrice);
        fprintf(fp, "==============================\n\n");
    }

    fclose(fp);
    ss << "Saved " << indexDeparture << " bookings to " << path;
    return ss.str();
}

