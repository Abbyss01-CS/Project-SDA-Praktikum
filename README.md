Kode ini adalah sistem manajemen kamar hotel sederhana menggunakan C++ dengan konsep OOP. Ada dua bagian utama: struct Booking sebagai wadah data pemesanan, dan hierarki class Kamar beserta turunannya.

Struct Booking hanya berfungsi sebagai formulir data menyimpan nama tamu, tanggal, ID kamar, tipe, durasi, total harga, dan field aktif sebagai penanda apakah booking sedang berjalan atau tidak.

Class Kamar adalah base class (abstract) yang menjadi induk semua tipe kamar. Atributnya protected agar bisa diakses child class. Ada dua method pure virtual (tampilInfo dan hitungTotal) yang wajib di-override, plus cetakStruk() yang sudah punya implementasi lengkap untuk mencetak struk ke console.
Lima kelas anakannya (Standar, Deluxe, Executive, Vip, Premium) semuanya mewarisi Kamar dan melakukan hal yang sama:

- Constructor menerima ID, nomor kamar, harga per malam, dan array fasilitas
- Override tampilInfo() untuk menampilkan detail kamar
- Override hitungTotal() untuk menghitung hpMalam × durasi

Alur kerjanya secara singkat:

Buat objek kamar sesuai tipe
Panggil tampilInfo() untuk lihat detail
Panggil hitungTotal() untuk estimasi biaya
Isi data booking lalu setBooking() + setTersedia(false)
Panggil cetakStruk() untuk print struk akhir

MATERI YANG DIGUNAKAN DI KODE INI :

- Struct

- OOP (Object Oriented Programming)

Encapsulation : atribut disimpan di protected/private, akses lewat getter & setter
Inheritance : Standar, Deluxe, Executive, Vip, Premium semuanya mewarisi class Kamar
Polymorphism : tampilInfo() dan hitungTotal() di-override di setiap child class
Abstraction : Kamar adalah abstract class karena punya pure virtual method (= 0)

- Virtual Function & Pure Virtual

virtual void tampilInfo() = 0 dan virtual void hitungTotal() = 0 menjadikan Kamar tidak bisa diinstansiasi langsung

- Array

string fasilitas[15] array statis di dalam class

- Tipe Data & Variable

Penggunaan string, int, float, bool

- Input/Output & Formatting

cout, fixed, setprecision(0), setw(20), left dari library

- Constructor

Setiap class punya constructor untuk inisialisasi atribut saat objek dibuat