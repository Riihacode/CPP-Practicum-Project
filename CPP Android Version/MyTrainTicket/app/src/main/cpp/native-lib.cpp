#include <jni.h>
#include <string>
#include "TrainTicketSystem.h"

using namespace std;

extern "C" {

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_autoBookTicketJNI(JNIEnv *env, jobject /* this */) {
        std::string result = autoBookTicket();
        return env->NewStringUTF(result.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_manualInputJNI(JNIEnv *env, jobject) {
        std::string result = manualInput();
        return env->NewStringUTF(result.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_searchByNIKJNI(JNIEnv *env, jobject) {
        std::string result = searchByNIK();
        return env->NewStringUTF(result.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_seqNonSentinelNotYetSortedJNI(JNIEnv *env, jobject, jstring nik) {
        const char* nativeNik = env->GetStringUTFChars(nik, 0);
        std::string nikStr(nativeNik);
        env->ReleaseStringUTFChars(nik, nativeNik);

        std::string result = seqNonSentinelNotYetSorted(&nikStr);
        return env->NewStringUTF(result.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_seqSentinelNotYetSortedJNI(JNIEnv *env, jobject, jstring nik) {
        const char* nativeNik = env->GetStringUTFChars(nik, 0);
        std::string nikStr(nativeNik);
        env->ReleaseStringUTFChars(nik, nativeNik);

        std::string result = seqSentinelNotYetSorted(&nikStr);
        return env->NewStringUTF(result.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_binarySearchJNI(JNIEnv *env, jobject, jstring nik) {
        const char* nativeNik = env->GetStringUTFChars(nik, 0);
        std::string nikStr(nativeNik);
        env->ReleaseStringUTFChars(nik, nativeNik);

        Booking copy[30];
        for (int i = 0; i < indexDeparture; i++) {
            copy[i] = bookings[i];
        }

        std::string result = binarySearch(copy, &nikStr);
        return env->NewStringUTF(result.c_str());
    }


    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_sortingOutputShowJNI(JNIEnv *env, jobject) {
        Booking copy[30];
        for (int i = 0; i < indexDeparture; i++) {
            copy[i] = bookings[i];
        }

        bubbleSort(copy); // atau quickSort/cara lain jika diinginkan
        std::string result = sortingOutputShow(copy);
        return env->NewStringUTF(result.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_fileOperationSaveJNI(JNIEnv *env, jobject) {
        std::string result = fileOperationSave(bookings, indexDeparture);
        return env->NewStringUTF(result.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_fileOperationSaveSingleJNI(JNIEnv *env, jobject, jstring nik) {
        const char* nativeNik = env->GetStringUTFChars(nik, 0);
        std::string nikStr(nativeNik);
        env->ReleaseStringUTFChars(nik, nativeNik);

        std::string result = fileOperationSaveSingle(bookings, indexDeparture, nikStr);
        return env->NewStringUTF(result.c_str());
    }

//    JNIEXPORT jstring JNICALL
//    Java_com_development_mytrainticket_TrainTicketManager_fileOperationSaveToJNI(JNIEnv *env, jobject, jstring jpath) {
//        const char* path = env->GetStringUTFChars(jpath, nullptr);
//
//        FILE* fp = fopen(path, "w");
//        std::string message;
//        if (fp) {
//            // misalnya kita hanya testing:
//            fprintf(fp, "INI ADALAH FILE TEST DARI JNI\n");
//            fclose(fp);
//            message = "Saved to: " + std::string(path);
//        } else {
//            message = "Failed to write: " + std::string(path);
//        }
//
//        env->ReleaseStringUTFChars(jpath, path);
//        return env->NewStringUTF(message.c_str());
//    }

    JNIEXPORT jstring JNICALL
    Java_com_development_mytrainticket_TrainTicketManager_fileOperationSaveToJNI(JNIEnv *env, jobject, jstring jpath) {
        const char *path = env->GetStringUTFChars(jpath, nullptr);
        std::string result = fileOperationSaveTo(path);
        env->ReleaseStringUTFChars(jpath, path);
        return env->NewStringUTF(result.c_str());
    }

} // extern "C"
