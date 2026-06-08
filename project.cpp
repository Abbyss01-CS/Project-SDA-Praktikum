#include <iostream>
using namespace std;

class Kamar {
protected:
    string idKamar;
    string nomor;
    string tipe;
    float hpMalam;
    bool tersedia;
    string fasilitas[15];
    Booking bookingData;

public:
    Kamar() {
        idKamar = "";
        nomor = "";
        tipe = "";
        hpMalam = 0.0;
        tersedia = true;
        for (int i = 0; i < 15; i++) fasilitas[i] = "";
        bookingData.aktif = false;
    }

    string getIdKamar() { return idKamar; }
    string getTipe() { return tipe; }
    bool isTersedia() { return tersedia; }
    float getHarga() { return hpMalam; }

    void setTersedia(bool status) { tersedia = status; }
    void setBooking(Booking b) { bookingData = b; }

    virtual void tampilInfo() = 0;
    virtual void hitungTotal(int durasi) = 0;

    void cetakStruk() {
        if (!bookingData.aktif) {
            cout << "Tidak ada booking aktif untuk kamar ini." << endl;
            return;
        }
        cout << "\n";
        cout << "========================================" << endl;
        cout << "         STRUK BOOKING HOTEL            " << endl;
        cout << "========================================" << endl;
        cout << left << setw(20) << "Nama Tamu"   << ": " << bookingData.namaGuest << endl;
        cout << left << setw(20) << "ID Kamar"    << ": " << bookingData.idKamar << endl;
        cout << left << setw(20) << "Tipe Kamar"  << ": " << bookingData.tipeKamar << endl;
        cout << left << setw(20) << "Nomor Kamar" << ": " << nomor << endl;
        cout << left << setw(20) << "Tanggal"     << ": " << bookingData.tanggal << endl;
        cout << left << setw(20) << "Durasi"      << ": " << bookingData.durasi << " Malam" << endl;
        cout << left << setw(20) << "Harga/Malam" << ": Rp. " << fixed << setprecision(0) << hpMalam << endl;
        cout << "----------------------------------------" << endl;
        cout << left << setw(20) << "TOTAL HARGA" << ": Rp. " << fixed << setprecision(0) << bookingData.totalHarga << endl;
        cout << "========================================" << endl;
        cout << "     Terima kasih telah menginap!       " << endl;
        cout << "========================================" << endl;
    }
};

// ===================== STANDAR =====================
class Standar : public Kamar {
public:
    Standar(string id, string nomor, float hpMalam, string fas[]) {
        this->idKamar = id;
        this->nomor = nomor;
        this->tipe = "Standar";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) this->fasilitas[i] = fas[i];
    }

    void tampilInfo() {
        cout << "ID Kamar    : " << idKamar << endl;
        cout << "Nomor Kamar : " << nomor << endl;
        cout << "Tipe        : " << tipe << endl;
        cout << "Harga/Malam : Rp. " << fixed << setprecision(0) << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas   : ";
        for (int i = 0; i < 15; i++) if (fasilitas[i] != "") cout << fasilitas[i] << " ";
        cout << endl;
    }

    void hitungTotal(int durasi) {
        cout << "Durasi : " << durasi << " Malam | Total : Rp. " << fixed << setprecision(0) << hpMalam * durasi << endl;
    }
};

// ===================== DELUXE =====================
class Deluxe : public Kamar {
public:
    Deluxe(string id, string nomor, float hpMalam, string fas[]) {
        this->idKamar = id;
        this->nomor = nomor;
        this->tipe = "Deluxe";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) this->fasilitas[i] = fas[i];
    }

    void tampilInfo() {
        cout << "ID Kamar    : " << idKamar << endl;
        cout << "Nomor Kamar : " << nomor << endl;
        cout << "Tipe        : " << tipe << endl;
        cout << "Harga/Malam : Rp. " << fixed << setprecision(0) << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas   : ";
        for (int i = 0; i < 15; i++) if (fasilitas[i] != "") cout << fasilitas[i] << " ";
        cout << endl;
    }

    void hitungTotal(int durasi) {
        cout << "Durasi : " << durasi << " Malam | Total : Rp. " << fixed << setprecision(0) << hpMalam * durasi << endl;
    }
};

// ===================== EXECUTIVE =====================
class Executive : public Kamar {
public:
    Executive(string id, string nomor, float hpMalam, string fas[]) {
        this->idKamar = id;
        this->nomor = nomor;
        this->tipe = "Executive";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) this->fasilitas[i] = fas[i];
    }

    void tampilInfo() {
        cout << "ID Kamar    : " << idKamar << endl;
        cout << "Nomor Kamar : " << nomor << endl;
        cout << "Tipe        : " << tipe << endl;
        cout << "Harga/Malam : Rp. " << fixed << setprecision(0) << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas   : ";
        for (int i = 0; i < 15; i++) if (fasilitas[i] != "") cout << fasilitas[i] << " ";
        cout << endl;
    }

    void hitungTotal(int durasi) {
        cout << "Durasi : " << durasi << " Malam | Total : Rp. " << fixed << setprecision(0) << hpMalam * durasi << endl;
    }
};

// ===================== VIP =====================
class Vip : public Kamar {
public:
    Vip(string id, string nomor, float hpMalam, string fas[]) {
        this->idKamar = id;
        this->nomor = nomor;
        this->tipe = "VIP";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) this->fasilitas[i] = fas[i];
    }

    void tampilInfo() {
        cout << "ID Kamar    : " << idKamar << endl;
        cout << "Nomor Kamar : " << nomor << endl;
        cout << "Tipe        : " << tipe << endl;
        cout << "Harga/Malam : Rp. " << fixed << setprecision(0) << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas   : ";
        for (int i = 0; i < 15; i++) if (fasilitas[i] != "") cout << fasilitas[i] << " ";
        cout << endl;
    }

    void hitungTotal(int durasi) {
        cout << "Durasi : " << durasi << " Malam | Total : Rp. " << fixed << setprecision(0) << hpMalam * durasi << endl;
    }
};

// ===================== PREMIUM =====================
class Premium : public Kamar {
public:
    Premium(string id, string nomor, float hpMalam, string fas[]) {
        this->idKamar = id;
        this->nomor = nomor;
        this->tipe = "Premium";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) this->fasilitas[i] = fas[i];
    }

    void tampilInfo() {
        cout << "ID Kamar    : " << idKamar << endl;
        cout << "Nomor Kamar : " << nomor << endl;
        cout << "Tipe        : " << tipe << endl;
        cout << "Harga/Malam : Rp. " << fixed << setprecision(0) << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas   : ";
        for (int i = 0; i < 15; i++) if (fasilitas[i] != "") cout << fasilitas[i] << " ";
        cout << endl;
    }

    void hitungTotal(int durasi) {
        cout << "Durasi : " << durasi << " Malam | Total : Rp. " << fixed << setprecision(0) << hpMalam * durasi << endl;
    }
};