package com.development.mytrainticket

class TrainTicketManager {
    // Native function declarations
    private external fun initSystem(): Long
    private external fun pesanTiket(
        handle: Long,
        jenisKereta: Int,
        kotaAsal: Int,
        kotaTujuan: Int,
        nama: String,
        nik: String,
        alamat: String,
        metodePemilihanKursi: Int,
        gerbong: Int,
        nomorKursi: Int
    )
    private external fun lihatStatusKursi(handle: Long): String
    private external fun destroySystem(handle: Long)
    private external fun getDaftarJenisKereta(handle: Long): Array<String>
    private external fun getDaftarKotaAsal(handle: Long): Array<String>
    private external fun getDaftarKotaTujuan(handle: Long): Array<String>

    // Native instance handle
    private var nativeHandle: Long = initSystem()

    /**
     * Public API untuk UI
     */

    fun pesanTiket(
        jenisKereta: Int,
        kotaAsal: Int,
        kotaTujuan: Int,
        nama: String,
        nik: String,
        alamat: String,
        metodePemilihanKursi: Int,
        gerbong: Int,
        nomorKursi: Int
    ) {
        pesanTiket(
            nativeHandle,
            jenisKereta,
            kotaAsal,
            kotaTujuan,
            nama,
            nik,
            alamat,
            metodePemilihanKursi,
            gerbong,
            nomorKursi
        )
    }

    fun lihatStatusKursi(): String {
        return lihatStatusKursi(nativeHandle) ?: "Error: Status kursi tidak tersedia"
    }

    fun getJenisKereta(): Array<String> {
        return getDaftarJenisKereta(nativeHandle) ?: emptyArray()
    }

    fun getKotaAsal(): Array<String> {
        return getDaftarKotaAsal(nativeHandle) ?: emptyArray()
    }

    fun getKotaTujuan(): Array<String> {
        return getDaftarKotaTujuan(nativeHandle) ?: emptyArray()
    }
    companion object {
        // Load native library
        init {
            System.loadLibrary("mytrainticket")
        }
    }
}