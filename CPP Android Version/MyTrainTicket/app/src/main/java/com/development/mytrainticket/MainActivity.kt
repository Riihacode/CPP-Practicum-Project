package com.development.mytrainticket

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.ArrayAdapter
import android.widget.Spinner
import androidx.activity.result.contract.ActivityResultContracts
import com.development.mytrainticket.databinding.ActivityMainBinding

//class MainActivity : AppCompatActivity() {
//
//    private lateinit var binding: ActivityMainBinding
//    private lateinit var ticketManager: TrainTicketManager
//
//    override fun onCreate(savedInstanceState: Bundle?) {
//        super.onCreate(savedInstanceState)
//        binding = ActivityMainBinding.inflate(layoutInflater)
//        setContentView(binding.root)
//
//        // Inisialisasi Ticket Manager
//        ticketManager = TrainTicketManager()
//
//        // Setup Spinner dengan data dari C++
//        setupSpinners()
//
//        // Tombol Pesan Tiket
//        binding.btnPesan.setOnClickListener {
//            handlePemesanan()
//        }
//
//        // Tombol Cek Kursi
//        binding.btnCekKursi.setOnClickListener {
//            showStatusKursi()
//        }
//    }
//
//    private fun setupSpinners() {
//        // Ambil data dari native code
//        val jenisKereta = ticketManager.getJenisKereta().toList()
//        val kotaAsal = ticketManager.getKotaAsal().toList()
//        val kotaTujuan = ticketManager.getKotaTujuan().toList()
//
//        // Debug: Pastikan data tidak kosong
//        if (jenisKereta.isEmpty() || kotaAsal.isEmpty() || kotaTujuan.isEmpty()) {
//            Log.e("SpinnerData", "Data spinner kosong!")
//            return
//        }
//
//        // Log data untuk debugging
//        Log.d("SpinnerData", "Jenis Kereta: $jenisKereta")
//        Log.d("SpinnerData", "Kota Asal: $kotaAsal")
//        Log.d("SpinnerData", "Kota Tujuan: $kotaTujuan")
//
//        // Setup masing-masing Spinner
//        setupSpinner(binding.spinJenisKereta, jenisKereta, "Pilih Jenis Kereta")
//        setupSpinner(binding.spinKotaAsal, kotaAsal, "Pilih Kota Asal")
//        setupSpinner(binding.spinKotaTujuan, kotaTujuan, "Pilih Kota Tujuan")
//    }
//
//    private fun setupSpinner(spinner: Spinner, data: List<String>, prompt: String) {
//        val adapter = ArrayAdapter(
//            this,
//            android.R.layout.simple_spinner_item,
//            data
//        ).apply {
//            setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
//        }
//
//        with(spinner) {
//            this.adapter = adapter
//            this.prompt = prompt
//        }
//    }
//
//    @SuppressLint("SetTextI18n")
//    private fun handlePemesanan() {
//        // Ambil data dari UI
//        val jenisKereta = binding.spinJenisKereta.selectedItemPosition
//        val kotaAsal = binding.spinKotaAsal.selectedItemPosition
//        val kotaTujuan = binding.spinKotaTujuan.selectedItemPosition
//
//        val nama = binding.etNama.text.toString()
//        val nik = binding.etNIK.text.toString()
//        val alamat = binding.etAlamat.text.toString()
//
//        val metodePemilihan = if (binding.rbManual.isChecked) 1 else 2
//        val gerbong = binding.etGerbong.text.toString().toIntOrNull() ?: 0
//        val nomorKursi = binding.etNomorKursi.text.toString().toIntOrNull() ?: 0
//
//        // Validasi input
//        if (nama.isEmpty() || nik.isEmpty() || alamat.isEmpty()) {
//            binding.tvStatusPemesanan.text = "Harap isi semua data diri!"
//            return
//        }
//
//        // Proses pemesanan
//        ticketManager.pesanTiket(
//            jenisKereta,
//            kotaAsal,
//            kotaTujuan,
//            nama,
//            nik,
//            alamat,
//            metodePemilihan,
//            gerbong,
//            nomorKursi
//        )
//
//        // Update status
//        binding.tvStatusPemesanan.text = """
//            Pemesanan Berhasil!
//            ${ticketManager.lihatStatusKursi()}
//        """.trimIndent()
//    }
//
//    @SuppressLint("SetTextI18n")
//    private fun showStatusKursi() {
//        binding.tvDetailKursi.text = """
//            Status Kursi Terkini:
//            ${ticketManager.lihatStatusKursi()}
//        """.trimIndent()
//    }
//}


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private val createFileLauncher = registerForActivityResult(
        ActivityResultContracts.CreateDocument("text/plain")
    ) { uri ->
        uri?.let {
            contentResolver.openOutputStream(it)?.use { output ->
//                val result = TrainTicketManager.autoBookTicketJNI() // atau fungsi hasil apa pun
//                output.write(result.toByteArray())
                val result = TrainTicketManager.fileOperationSaveToJNI(it.path ?: "")
                output.write(result.toByteArray())

            }
            binding.tvResult.text = "File saved successfully to: $uri"
        } ?: run {
            binding.tvResult.text = "File save cancelled."
        }
    }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.btnAutoBook.setOnClickListener {
            val result = TrainTicketManager.autoBookTicketJNI()
            binding.tvResult.text = result
        }

        binding.btnManualInput.setOnClickListener {
            val result = TrainTicketManager.manualInputJNI()
            binding.tvResult.text = result
        }

        binding.btnSearch.setOnClickListener {
            val nik = binding.etNIK.text.toString().trim()
            if (nik.isNotEmpty()) {
                val result = TrainTicketManager.binarySearchJNI(nik)
                binding.tvResult.text = result
            } else {
                binding.tvResult.text = "Please enter a NIK."
            }
        }

        binding.btnSort.setOnClickListener {
            val result = TrainTicketManager.sortingOutputShowJNI()
            binding.tvResult.text = result
        }

//        binding.btnSaveAll.setOnClickListener {
//            val result = TrainTicketManager.fileOperationSaveJNI()
//            binding.tvResult.text = result
//        }

        binding.btnSaveByNIK.setOnClickListener {
            val nik = binding.etNIK.text.toString().trim()
            if (nik.isNotEmpty()) {
                val result = TrainTicketManager.fileOperationSaveSingleJNI(nik)
                binding.tvResult.text = result
            } else {
                binding.tvResult.text = "Please enter a NIK to save."
            }
        }
//
//        // Tombol untuk save file ke lokasi aman (internal storage)
//        binding.btnSaveAll.setOnClickListener {
//            val path = getExternalFilesDir(null)?.absolutePath + "/ticket_data.txt"
//            val result = TrainTicketManager.fileOperationSaveToJNI(path ?: "")
//            binding.tvResult.text = result
//        }

        binding.btnSaveAll.setOnClickListener {
            createFileLauncher.launch("ticket_data.txt")  // ini akan memunculkan file picker Android
        }

    }
}