#include <jni.h>
#include <string>
#include "TrainTicketSystem.h"

using namespace std;

extern "C" {
    JNIEXPORT jlong JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_initSystem(
            JNIEnv *env,
            jobject thiz) {
        return reinterpret_cast<jlong>(new TrainTicketSystem());
    }

    JNIEXPORT void JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_pesanTiket(
            JNIEnv *env,
            jobject thiz,
            jlong handle,
            jint jenisKereta,
            jint kotaAsal,
            jint kotaTujuan,
            jstring nama,
            jstring nik,
            jstring alamat,
            jint metodePemilihanKursi,
            jint gerbong,
            jint nomorKursi
    ) {
        auto* system = reinterpret_cast<TrainTicketSystem*>(handle);

        const char *c_nama = env->GetStringUTFChars(nama, nullptr);
        const char *c_nik = env->GetStringUTFChars(nik, nullptr);
        const char *c_alamat = env->GetStringUTFChars(alamat, nullptr);

        system->pesanTiket(
                jenisKereta,
                kotaAsal,
                kotaTujuan,
                c_nama,
                c_nik,
                c_alamat,
                metodePemilihanKursi,
                gerbong,
                nomorKursi
        );

        env->ReleaseStringUTFChars(nama, c_nama);
        env->ReleaseStringUTFChars(nik, c_nik);
        env->ReleaseStringUTFChars(alamat, c_alamat);
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_lihatStatusKursi(
            JNIEnv *env,
            jobject thiz,
            jlong handle
    ) {
        auto* system = reinterpret_cast<TrainTicketSystem*>(handle);
        return env->NewStringUTF(system->lihatStatusKursi().c_str());
    }

    JNIEXPORT void JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_destroySystem(
            JNIEnv *env,
            jobject thiz,
            jlong handle
    ) {
        delete reinterpret_cast<TrainTicketSystem*>(handle);
    }


    JNIEXPORT jobjectArray JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_getDaftarJenisKereta(
            JNIEnv *env,
            jobject thiz,
            jlong handle
    ) {
        auto* system = reinterpret_cast<TrainTicketSystem*>(handle);

        // 1. Dapatkan ukuran array
        int size;
        system->getDaftarJenisKereta(nullptr, size);

        // 2. Alokasi array dinamis
        std::string* data = new std::string[size];
        system->getDaftarJenisKereta(data, size);

        // 3. Konversi ke Java array
        jobjectArray result = env->NewObjectArray(
                size,
                env->FindClass("java/lang/String"),
                env->NewStringUTF("")
        );

        for(int i=0; i<size; i++) {
            env->SetObjectArrayElement(
                    result,
                    i,
                    env->NewStringUTF(data[i].c_str())
            );
        }

        // 4. Hapus memori
        delete[] data;

        return result;
    }

    JNIEXPORT jobjectArray JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_getDaftarKotaTujuan(
            JNIEnv *env,
            jobject thiz,
            jlong handle
    ) {
        auto* system = reinterpret_cast<TrainTicketSystem*>(handle);

        // 1. Dapatkan ukuran array
        int size;
        system->getDaftarKotaTujuan(nullptr, size);

        // 2. Alokasi array dinamis
        std::string* data = new std::string[size];
        system->getDaftarKotaTujuan(data, size);

        // 3. Konversi ke Java array
        jobjectArray result = env->NewObjectArray(
                size,
                env->FindClass("java/lang/String"),
                env->NewStringUTF("")
        );

        for(int i=0; i<size; i++) {
            env->SetObjectArrayElement(
                    result,
                    i,
                    env->NewStringUTF(data[i].c_str())
            );
        }

        // 4. Hapus memori
        delete[] data;

        return result;
    }

    JNIEXPORT jobjectArray JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_getDaftarKotaAsal(
            JNIEnv *env,
            jobject thiz,
            jlong handle
    ) {
        auto* system = reinterpret_cast<TrainTicketSystem*>(handle);

        // 1. Dapatkan ukuran array
        int size;
        system->getDaftarKotaAsal(nullptr, size); // Hanya ambil ukuran

        // 2. Alokasi array dinamis
        std::string* data = new std::string[size];
        system->getDaftarKotaAsal(data, size); // Ambil data

        // 3. Konversi ke Java array
        jobjectArray result = env->NewObjectArray(
                size,
                env->FindClass("java/lang/String"),
                env->NewStringUTF("")
        );

        for(int i=0; i<size; i++) {
            env->SetObjectArrayElement(
                    result,
                    i,
                    env->NewStringUTF(data[i].c_str())
            );
        }

        // 4. Hapus memori
        delete[] data;

        return result;
    }
}