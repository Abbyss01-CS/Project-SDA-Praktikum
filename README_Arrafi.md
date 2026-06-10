
    # Sistem Manajemen Hotel — C++

Program manajemen hotel berbasis konsol yang dibuat menggunakan C++ dengan konsep **OOP (Object-Oriented Programming)**. Program ini mencakup sistem booking kamar, manajemen membership, serta panel admin untuk mengelola status kamar.


Identitas

| Keterangan | Detail |
|---|---|
| Nama | Arrafi |
| NIM | 2507071024 |
| Program Studi | Manajemen Informatika |
| Universitas | Universitas Lampung |
| Mata Kuliah | Struktur Data & Algoritma |


Deskripsi Program

Program ini mensimulasikan sistem manajemen hotel sederhana dengan fitur:
- Melihat daftar kamar beserta ketersediaan dan fasilitasnya
- Booking kamar dengan validasi input lengkap
- Sistem membership dengan diskon loyalitas
- Panel admin untuk mengubah status kamar

Struktur Program

Konsep OOP yang Digunakan

| Konsep | Implementasi |
|---|---|
| **Class & Object** | Class `Kamar`, `Standar`, `Deluxe`, `Executive`, `Vip`, `Premium` |
| **Inheritance** | Semua tipe kamar mewarisi class `Kamar` |
| **Polymorphism** | Virtual function `tampilInfo()` dan `hitungTotal()` |
| **Encapsulation** | Data kamar dilindungi dengan `protected`, diakses via getter/setter |

Struct yang Digunakan

Data Kamar

Total kamar: **10 kamar** (2 kamar per tipe)

| ID | Tipe | Nomor | Harga/Malam | Fasilitas Utama |
|---|---|---|---|---|
| 101, 102 | Standar | STD-1, STD-2 | Rp. 300.000 | AC, TV, WiFi |
| 201, 202 | Deluxe | DLX-1, DLX-2 | Rp. 500.000 | AC, TV, WiFi, Bathtub, Mini Bar |
| 301, 302 | Executive | EXC-1, EXC-2 | Rp. 750.000 | AC, TV, WiFi, Bathtub, Mini Bar, Living Room |
| 401, 402 | VIP | VIP-1, VIP-2 | Rp. 1.200.000 | AC, TV, WiFi, Jacuzzi, Living Room, Butler Service |
| 501, 502 | Premium | PRM-1, PRM-2 | Rp. 2.000.000 | AC, TV, WiFi, Private Pool, Private Chef |

---

Fitur Program

1. Lihat Daftar Kamar
Menampilkan semua kamar beserta tipe, harga, nomor kamar, dan status ketersediaan.

2. Booking Kamar
- Submenu: cek fasilitas dulu atau langsung booking
- Input: nama tamu (validasi huruf saja), tanggal (format dd/mm/yyyy), tipe kamar, durasi menginap
- Sistem otomatis memilih kamar yang tersedia sesuai tipe
- Mencetak struk booking setelah berhasil

3. Ubah Status Kamar (Admin)
- Dilindungi password: `12345`
- Admin dapat toggle status kamar antara **Tersedia** / **Tidak Tersedia**
- Hanya 1 kamar yang bisa diubah per sesi

4. Membership
- Daftar Member Baru** — mendapat kode membership 5 digit otomatis
- Booking dengan Membership** — harga menggunakan tarif kamar yang ada
- Diskon 10%** otomatis aktif setelah member menginap **5 kali**
- Cek Info Member** — lihat status diskon dan sisa menginap
- Lihat Semua Member** — tampilan tabel semua member aktif

Validasi Input

| Input | Validasi |
|---|---|
| Menu pilihan | Hanya angka, tidak loop jika input huruf |
| Nama tamu | Hanya huruf dan spasi |
| Tanggal booking | Format dd/mm/yyyy, tahun 2026, hari/bulan valid |
| Kode membership | Tepat 5 digit angka |
| Durasi menginap | Hanya angka |

Alur Program

Main Menu
├── 1. Lihat Daftar Kamar
├── 2. Booking Kamar
│   ├── 1. Cek Fasilitas Kamar Dulu
│   └── 2. Langsung Isi Form Booking
├── 3. Ubah Status Kamar (Admin) [password: 12345]
├── 4. Membership
│   ├── 1. Daftar Member Baru
│   ├── 2. Booking dengan Membership
│   ├── 3. Cek Info Member
│   └── 4. Lihat Semua Member
└── 5. Keluar

