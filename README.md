
Hotel Management System 
Program manajemen hotel berbasis konsol menggunakan C++ dengan pendekatan Object-Oriented Programming (OOP). Program ini merupakan hasil kolaborasi kelompok yang menggabungkan sistem booking kamar, manajemen fasilitas, panel admin, dan sistem membership dengan diskon loyalitas.

Anggota Kelompok
NoNama1Revalia2Abbas3Carlen4Arrafi

Deskripsi Program
Sistem ini mensimulasikan operasional hotel sederhana secara digital, mencakup:

Manajemen kamar dengan 5 tipe berbeda (total 10 kamar)
Proses booking dengan validasi input lengkap
Sistem membership berbasis loyalitas dengan diskon otomatis
Panel admin untuk mengelola status ketersediaan kamar
Tampilan fasilitas detail per kamar


File Program
FileKeteranganproject.cppSource code awal / versi dasarproject1.cppSource code final lengkap (booking + membership + admin)README.mdDokumentasi proyek

Data Kamar
Total: 10 kamar (2 per tipe)
IDTipeNomorHarga/MalamFasilitas Utama101, 102StandarSTD-1, STD-2Rp 300.000AC, TV, WiFi201, 202DeluxeDLX-1, DLX-2Rp 500.000+ Bathtub, Mini Bar301, 302ExecutiveEXC-1, EXC-2Rp 750.000+ Living Room401, 402VIPVIP-1, VIP-2Rp 1.200.000+ Jacuzzi, Butler Service501, 502PremiumPRM-1, PRM-2Rp 2.000.000+ Private Pool, Private Chef

Fitur Program
1. Lihat Daftar Kamar
Menampilkan semua kamar beserta ID, tipe, nomor, harga, dan status ketersediaan.
2. Booking Kamar

Submenu: cek fasilitas dulu atau langsung booking
Input nama tamu, tanggal (dd/mm/yyyy), tipe kamar, durasi menginap
Sistem otomatis assign kamar tersedia sesuai tipe yang dipilih
Cetak struk booking lengkap setelah transaksi berhasil

3. Ubah Status Kamar (Admin)

Dilindungi password: 12345
Toggle status kamar: Tersedia / Tidak Tersedia
Hanya 1 kamar yang dapat diubah per sesi

4. Sistem Membership
Sub-fiturKeteranganDaftar Member BaruGenerate kode membership 5 digit otomatisBooking dengan MembershipHarga mengikuti tarif kamar yang dipilihDiskon LoyalitasDiskon 10% aktif otomatis setelah 5x menginapCek Info MemberLihat status diskon dan progress menginapLihat Semua MemberTabel seluruh member aktif

Materi yang Digunakan
1. Class dan Object
Class digunakan sebagai blueprint untuk membuat objek kamar. Setiap kamar dibuat sebagai object dari class turunannya masing-masing.
cppclass Kamar { ... };         // base class
Kamar* daftarKamar[10];      // array of object
daftarKamar[0] = new Standar("101", "STD-1", 300000, fasStandar);
2. Inheritance (Pewarisan)
Lima class turunan mewarisi semua atribut dan method dari class Kamar, sehingga tidak perlu menulis ulang kode yang sama.
cppclass Standar   : public Kamar { ... };
class Deluxe    : public Kamar { ... };
class Executive : public Kamar { ... };
class Vip       : public Kamar { ... };
class Premium   : public Kamar { ... };
3. Polymorphism
Virtual function memungkinkan setiap subclass punya implementasi tampilInfo() dan hitungTotal() yang berbeda, namun bisa dipanggil lewat pointer base class.
cppvirtual void tampilInfo()            = 0;  // pure virtual
virtual void hitungTotal(int durasi) = 0;
4. Encapsulation
Atribut kamar disimpan di akses protected agar tidak bisa diakses langsung dari luar, melainkan melalui getter dan setter.
cppprotected:
    string idKamar, nomor, tipe;
    float  hpMalam;
    bool   tersedia;

public:
    string getIdKamar() { return idKamar; }
    void   setTersedia(bool status) { tersedia = status; }
5. Abstract Class
Class Kamar tidak bisa dibuat objeknya secara langsung karena memiliki pure virtual function. Hanya subclass-nya yang bisa diinstansiasi.
6. Struct
Digunakan untuk menyimpan data transaksi dan data member secara terstruktur.
cppstruct Booking {
    string namaGuest, tanggal, idKamar, tipeKamar;
    int durasi;
    float totalHarga;
    bool aktif;
};

struct Member {
    string kodeMember, nama, noHp;
    int jumlahMenginap;
    bool aktif;
};
7. Dynamic Memory Allocation
Objek kamar dibuat secara dinamis di heap menggunakan new, dan dibersihkan di akhir program dengan delete.
cppdaftarKamar[0] = new Standar("101", "STD-1", 300000, fasStandar);
// ...
for (int i = 0; i < TOTAL_KAMAR; i++) delete daftarKamar[i];
8. Array of Pointers
Semua kamar disimpan dalam array pointer bertipe Kamar*, memungkinkan polimorfisme saat iterasi.
cppconst int TOTAL_KAMAR = 10;
Kamar* daftarKamar[TOTAL_KAMAR];
9. Input Validation
Fungsi helper khusus untuk memastikan input dari pengguna selalu valid sebelum diproses.
cppint    inputInt(const string& prompt);   // validasi input angka
string inputNama(const string& prompt);  // validasi hanya huruf & spasi
string inputTanggal();                   // validasi format dd/mm/yyyy
10. Modular Function
Program dibagi menjadi fungsi-fungsi kecil yang masing-masing punya tanggung jawab spesifik: prosesBooking(), ubahStatusKamar(), bookingDenganMembership(), menuMembership(), dan sebagainya.

Struktur OOP
Kamar  (Abstract Base Class)
├── Standar
├── Deluxe
├── Executive
├── Vip
└── Premium

Alur Program
Menu Utama
├── 1. Lihat Daftar Kamar
├── 2. Booking Kamar
│   ├── 1. Cek Fasilitas Kamar Dulu
│   └── 2. Langsung Isi Form Booking
├── 3. Ubah Status Kamar (Admin)  [Password: 12345]
├── 4. Membership
│   ├── 1. Daftar Member Baru
│   ├── 2. Booking dengan Membership
│   ├── 3. Cek Info Member
│   └── 4. Lihat Semua Member
└── 5. Keluar

Cara Kompilasi
Dev-C++ (TDM-GCC)

Buka project1.cpp di Dev-C++
Tools → Compiler Options → centang "Add the following commands..." → isi -std=c++11 → OK
Execute → Compile & Run (F11)

VS Code / Terminal
bashg++ -std=c++11 -o hotel project1.cpp
./hotel
