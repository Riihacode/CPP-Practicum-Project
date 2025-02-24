package com.development.mytrainticket

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.ArrayAdapter
import android.widget.Spinner
import com.development.mytrainticket.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private lateinit var ticketManager: TrainTicketManager

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Inisialisasi Ticket Manager
        ticketManager = TrainTicketManager()

        // Setup Spinner dengan data dari C++
        setupSpinners()

        // Tombol Pesan Tiket
        binding.btnPesan.setOnClickListener {
            handlePemesanan()
        }

        // Tombol Cek Kursi
        binding.btnCekKursi.setOnClickListener {
            showStatusKursi()
        }
    }

    private fun setupSpinners() {
        // Ambil data dari native code
        val jenisKereta = ticketManager.getJenisKereta().toList()
        val kotaAsal = ticketManager.getKotaAsal().toList()
        val kotaTujuan = ticketManager.getKotaTujuan().toList()

        // Debug: Pastikan data tidak kosong
        if (jenisKereta.isEmpty() || kotaAsal.isEmpty() || kotaTujuan.isEmpty()) {
            Log.e("SpinnerData", "Data spinner kosong!")
            return
        }

        // Log data untuk debugging
        Log.d("SpinnerData", "Jenis Kereta: $jenisKereta")
        Log.d("SpinnerData", "Kota Asal: $kotaAsal")
        Log.d("SpinnerData", "Kota Tujuan: $kotaTujuan")

        // Setup masing-masing Spinner
        setupSpinner(binding.spinJenisKereta, jenisKereta, "Pilih Jenis Kereta")
        setupSpinner(binding.spinKotaAsal, kotaAsal, "Pilih Kota Asal")
        setupSpinner(binding.spinKotaTujuan, kotaTujuan, "Pilih Kota Tujuan")
    }

    private fun setupSpinner(spinner: Spinner, data: List<String>, prompt: String) {
        val adapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_item,
            data
        ).apply {
            setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        }

        with(spinner) {
            this.adapter = adapter
            this.prompt = prompt
        }
    }

    @SuppressLint("SetTextI18n")
    private fun handlePemesanan() {
        // Ambil data dari UI
        val jenisKereta = binding.spinJenisKereta.selectedItemPosition
        val kotaAsal = binding.spinKotaAsal.selectedItemPosition
        val kotaTujuan = binding.spinKotaTujuan.selectedItemPosition

        val nama = binding.etNama.text.toString()
        val nik = binding.etNIK.text.toString()
        val alamat = binding.etAlamat.text.toString()

        val metodePemilihan = if (binding.rbManual.isChecked) 1 else 2
        val gerbong = binding.etGerbong.text.toString().toIntOrNull() ?: 0
        val nomorKursi = binding.etNomorKursi.text.toString().toIntOrNull() ?: 0

        // Validasi input
        if (nama.isEmpty() || nik.isEmpty() || alamat.isEmpty()) {
            binding.tvStatusPemesanan.text = "Harap isi semua data diri!"
            return
        }

        // Proses pemesanan
        ticketManager.pesanTiket(
            jenisKereta,
            kotaAsal,
            kotaTujuan,
            nama,
            nik,
            alamat,
            metodePemilihan,
            gerbong,
            nomorKursi
        )

        // Update status
        binding.tvStatusPemesanan.text = """
            Pemesanan Berhasil!
            ${ticketManager.lihatStatusKursi()}
        """.trimIndent()
    }

    @SuppressLint("SetTextI18n")
    private fun showStatusKursi() {
        binding.tvDetailKursi.text = """
            Status Kursi Terkini:
            ${ticketManager.lihatStatusKursi()}
        """.trimIndent()
    }
}