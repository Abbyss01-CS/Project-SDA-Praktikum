#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

int inputInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[!] Input tidak valid. Masukkan angka.\n";
        } else {
            return val;
        }
    }
}


string inputNama(const string& prompt) {
    string nama;
    while (true) {
        cout << prompt;
        getline(cin, nama);
        bool valid = true;
        if (nama.empty()) { valid = false; }
        for (char c : nama) {
            if (!isalpha(c) && c != ' ') { valid = false; break; }
        }
        if (valid) return nama;
        cout << "[!] Nama hanya boleh berisi huruf dan spasi.\n";
    }
}

const int MAX_MEMBER      = 100;
const float DISKON_PERSEN = 0.10f;

struct Member {
    string kodeMember;
    string nama;
    string noHp;
    int jumlahMenginap;
    bool aktif;
};

Member daftarMember[MAX_MEMBER];
int totalMember  = 0;
int kodeCounter  = 10001;

string generateKode() {
    return to_string(kodeCounter++);
}

int cariMember(const string& kode) {
    for (int i = 0; i < totalMember; i++) {
        if (daftarMember[i].kodeMember == kode && daftarMember[i].aktif)
            return i;
    }
    return -1;
}

bool cekDiskon(int idx) {
    return daftarMember[idx].jumlahMenginap >= 5;
}

float hitungHargaMember(float hargaNormal, int idx) {
    return cekDiskon(idx) ? hargaNormal * (1.0f - DISKON_PERSEN) : hargaNormal;
}

void tambahMenginap(int idx) {
    daftarMember[idx].jumlahMenginap++;
    int jml = daftarMember[idx].jumlahMenginap;
    cout << "\n[INFO] Riwayat menginap member '" << daftarMember[idx].nama
         << "' sekarang: " << jml << "x\n";
    if (jml == 5)
        cout << "[SELAMAT] Member ini sekarang berhak mendapat DISKON 10% untuk booking berikutnya!\n";
}

void daftarMemberBaru() {
    if (totalMember >= MAX_MEMBER) {
        cout << "[!] Database member penuh.\n";
        return;
    }
    Member m;
    cin.ignore(1000, '\n');
    cout << "\n========== PENDAFTARAN MEMBERSHIP ==========\n";
    m.nama           = inputNama("Nama Lengkap : ");
    cout << "No. HP       : "; getline(cin, m.noHp);
    m.kodeMember     = generateKode();
    m.jumlahMenginap = 0;
    m.aktif          = true;
    daftarMember[totalMember++] = m;

    cout << "\n[OK] Pendaftaran berhasil!\n";
    cout << "============================================\n";
    cout << left << setw(20) << "Nama"            << ": " << m.nama        << "\n";
    cout << left << setw(20) << "Kode Membership" << ": " << m.kodeMember  << "\n";
    cout << left << setw(20) << "No. HP"          << ": " << m.noHp        << "\n";
    cout << left << setw(20) << "Status Diskon"   << ": Belum (perlu 5x menginap)\n";
    cout << "============================================\n";
}

void lihatDaftarMember() {
    cout << "\n========== DAFTAR MEMBER HOTEL ==========\n";
    if (totalMember == 0) { cout << "Belum ada member terdaftar.\n"; return; }
    cout << left << setw(10) << "Kode" << setw(25) << "Nama"
         << setw(16) << "No. HP" << setw(12) << "Menginap" << "Diskon\n";
    cout << "-----------------------------------------------------------\n";
    for (int i = 0; i < totalMember; i++) {
        if (!daftarMember[i].aktif) continue;
        cout << left << setw(10) << daftarMember[i].kodeMember
             << setw(25) << daftarMember[i].nama
             << setw(16) << daftarMember[i].noHp
             << setw(12) << (to_string(daftarMember[i].jumlahMenginap) + "x")
             << (cekDiskon(i) ? "AKTIF 10%" : "-") << "\n";
    }
    cout << "==========================================================\n";
}

void cekInfoMember() {
    string kode;
    cin.ignore(1000, '\n');
    cout << "\nMasukkan Kode Membership: ";
    getline(cin, kode);
    int idx = cariMember(kode);
    if (idx == -1) { cout << "[!] Kode tidak ditemukan.\n"; return; }
    Member& m      = daftarMember[idx];
    int sisaMenginap = (m.jumlahMenginap < 5) ? (5 - m.jumlahMenginap) : 0;
    cout << "\n========== INFO MEMBER ==========\n";
    cout << left << setw(22) << "Kode Membership" << ": " << m.kodeMember      << "\n";
    cout << left << setw(22) << "Nama"            << ": " << m.nama            << "\n";
    cout << left << setw(22) << "No. HP"          << ": " << m.noHp            << "\n";
    cout << left << setw(22) << "Jumlah Menginap" << ": " << m.jumlahMenginap  << "x\n";
    if (cekDiskon(idx))
        cout << left << setw(22) << "Status Diskon" << ": AKTIF - Dapat potongan 10%\n";
    else {
        cout << left << setw(22) << "Status Diskon" << ": Belum aktif\n";
        cout << left << setw(22) << "Sisa menginap" << ": " << sisaMenginap << "x lagi untuk dapat diskon\n";
    }
    cout << "=================================\n";
}

struct Booking {
    string namaGuest;
    string tanggal;
    string idKamar;
    string tipeKamar;
    int    durasi;
    float  totalHarga;
    bool   aktif;
};

class Kamar {
protected:
    string idKamar;
    string nomor;     
    string tipe;
    float  hpMalam;
    bool   tersedia;
    string fasilitas[15];
    Booking bookingData;

public:
    Kamar() {
        idKamar = ""; nomor = ""; tipe = ""; hpMalam = 0.0f; tersedia = true;
        for (int i = 0; i < 15; i++) fasilitas[i] = "";
        bookingData.aktif = false;
    }

    string getIdKamar()  { return idKamar; }
    string getNomor()    { return nomor;   }
    string getTipe()     { return tipe;    }
    bool   isTersedia()  { return tersedia; }
    float  getHarga()    { return hpMalam;  }

    void setTersedia(bool status)  { tersedia    = status; }
    void setBooking(Booking b)     { bookingData = b;      }

    virtual void tampilInfo()           = 0;
    virtual void hitungTotal(int durasi)= 0;

    void tampilFasilitas() {
        cout << "\n========== DETAIL FASILITAS KAMAR ==========\n";
        cout << "ID Kamar    : " << idKamar << "\n";
        cout << "Nomor Kamar : " << nomor   << "\n";
        cout << "Tipe Kamar  : " << tipe    << "\n";
        cout << "Harga/Malam : Rp. " << fixed << setprecision(0) << hpMalam << "\n";
        cout << "Status      : " << (tersedia ? "Tersedia" : "Tidak Tersedia") << "\n";
        cout << "Fasilitas   :\n";
        for (int i = 0; i < 15; i++)
            if (fasilitas[i] != "") cout << "  - " << fasilitas[i] << "\n";
        cout << "Deskripsi   : ";
        if      (tipe == "Standar")   cout << "Kamar sederhana dengan fasilitas dasar seperti AC, TV, dan WiFi.\n";
        else if (tipe == "Deluxe")    cout << "Kamar nyaman dengan tambahan bathtub dan mini bar.\n";
        else if (tipe == "Executive") cout << "Kamar luas dengan tambahan living room.\n";
        else if (tipe == "VIP")       cout << "Kamar mewah dengan jacuzzi dan butler service.\n";
        else if (tipe == "Premium")   cout << "Kamar paling lengkap dengan private pool dan private chef.\n";
        cout << "============================================\n";
    }

    void cetakStruk() {
        if (!bookingData.aktif) { cout << "Tidak ada booking aktif untuk kamar ini.\n"; return; }
        cout << "\n========================================\n";
        cout << "         STRUK BOOKING HOTEL            \n";
        cout << "========================================\n";
        cout << left << setw(20) << "Nama Tamu"   << ": " << bookingData.namaGuest  << "\n";
        cout << left << setw(20) << "ID Kamar"    << ": " << bookingData.idKamar    << "\n";
        cout << left << setw(20) << "Nomor Kamar" << ": " << nomor                  << "\n";
        cout << left << setw(20) << "Tipe Kamar"  << ": " << bookingData.tipeKamar  << "\n";
        cout << left << setw(20) << "Tanggal"     << ": " << bookingData.tanggal    << "\n";
        cout << left << setw(20) << "Durasi"      << ": " << bookingData.durasi << " Malam\n";
        cout << left << setw(20) << "Harga/Malam" << ": Rp. " << fixed << setprecision(0) << hpMalam << "\n";
        cout << "----------------------------------------\n";
        cout << left << setw(20) << "TOTAL HARGA" << ": Rp. " << fixed << setprecision(0) << bookingData.totalHarga << "\n";
        cout << "========================================\n";
        cout << "     Terima kasih telah menginap!       \n";
        cout << "========================================\n";
    }
};

class Standar : public Kamar {
public:
    Standar(string id, string nom, float hp, string fas[]) {
        idKamar = id; nomor = nom; tipe = "Standar"; hpMalam = hp; tersedia = true;
        for (int i = 0; i < 15; i++) fasilitas[i] = fas[i];
    }
    void tampilInfo() {
        cout << left << setw(6) << idKamar << setw(12) << tipe
             << "Rp. " << setw(14) << fixed << setprecision(0) << hpMalam
             << setw(10) << nomor
             << (tersedia ? "Tersedia" : "Tidak Tersedia") << "\n";
    }
    void hitungTotal(int dur) {
        cout << "Durasi: " << dur << " Malam | Total: Rp. " << fixed << setprecision(0) << hpMalam * dur << "\n";
    }
};

class Deluxe : public Kamar {
public:
    Deluxe(string id, string nom, float hp, string fas[]) {
        idKamar = id; nomor = nom; tipe = "Deluxe"; hpMalam = hp; tersedia = true;
        for (int i = 0; i < 15; i++) fasilitas[i] = fas[i];
    }
    void tampilInfo() {
        cout << left << setw(6) << idKamar << setw(12) << tipe
             << "Rp. " << setw(14) << fixed << setprecision(0) << hpMalam
             << setw(10) << nomor
             << (tersedia ? "Tersedia" : "Tidak Tersedia") << "\n";
    }
    void hitungTotal(int dur) {
        cout << "Durasi: " << dur << " Malam | Total: Rp. " << fixed << setprecision(0) << hpMalam * dur << "\n";
    }
};

class Executive : public Kamar {
public:
    Executive(string id, string nom, float hp, string fas[]) {
        idKamar = id; nomor = nom; tipe = "Executive"; hpMalam = hp; tersedia = true;
        for (int i = 0; i < 15; i++) fasilitas[i] = fas[i];
    }
    void tampilInfo() {
        cout << left << setw(6) << idKamar << setw(12) << tipe
             << "Rp. " << setw(14) << fixed << setprecision(0) << hpMalam
             << setw(10) << nomor
             << (tersedia ? "Tersedia" : "Tidak Tersedia") << "\n";
    }
    void hitungTotal(int dur) {
        cout << "Durasi: " << dur << " Malam | Total: Rp. " << fixed << setprecision(0) << hpMalam * dur << "\n";
    }
};

class Vip : public Kamar {
public:
    Vip(string id, string nom, float hp, string fas[]) {
        idKamar = id; nomor = nom; tipe = "VIP"; hpMalam = hp; tersedia = true;
        for (int i = 0; i < 15; i++) fasilitas[i] = fas[i];
    }
    void tampilInfo() {
        cout << left << setw(6) << idKamar << setw(12) << tipe
             << "Rp. " << setw(14) << fixed << setprecision(0) << hpMalam
             << setw(10) << nomor
             << (tersedia ? "Tersedia" : "Tidak Tersedia") << "\n";
    }
    void hitungTotal(int dur) {
        cout << "Durasi: " << dur << " Malam | Total: Rp. " << fixed << setprecision(0) << hpMalam * dur << "\n";
    }
};

class Premium : public Kamar {
public:
    Premium(string id, string nom, float hp, string fas[]) {
        idKamar = id; nomor = nom; tipe = "Premium"; hpMalam = hp; tersedia = true;
        for (int i = 0; i < 15; i++) fasilitas[i] = fas[i];
    }
    void tampilInfo() {
        cout << left << setw(6) << idKamar << setw(12) << tipe
             << "Rp. " << setw(14) << fixed << setprecision(0) << hpMalam
             << setw(10) << nomor
             << (tersedia ? "Tersedia" : "Tidak Tersedia") << "\n";
    }
    void hitungTotal(int dur) {
        cout << "Durasi: " << dur << " Malam | Total: Rp. " << fixed << setprecision(0) << hpMalam * dur << "\n";
    }
};

const int TOTAL_KAMAR = 10;
Kamar* daftarKamar[TOTAL_KAMAR];

void inisiasiKamar() {
    string fasStandar[15]  = {"AC","TV","WiFi","","","","","","","","","","","",""};
    daftarKamar[0] = new Standar("101","STD-1", 300000, fasStandar);
    daftarKamar[1] = new Standar("102","STD-2", 300000, fasStandar);

    string fasDeluxe[15]   = {"AC","TV","WiFi","Bathtub","Mini Bar","","","","","","","","","",""};
    daftarKamar[2] = new Deluxe("201","DLX-1", 500000, fasDeluxe);
    daftarKamar[3] = new Deluxe("202","DLX-2", 500000, fasDeluxe);

    string fasExec[15]     = {"AC","TV","WiFi","Bathtub","Mini Bar","Living Room","","","","","","","","",""};
    daftarKamar[4] = new Executive("301","EXC-1", 750000, fasExec);
    daftarKamar[5] = new Executive("302","EXC-2", 750000, fasExec);

    string fasVip[15]      = {"AC","TV","WiFi","Jacuzzi","Mini Bar","Living Room","Butler Service","","","","","","","",""};
    daftarKamar[6] = new Vip("401","VIP-1", 1200000, fasVip);
    daftarKamar[7] = new Vip("402","VIP-2", 1200000, fasVip);

    string fasPremium[15]  = {"AC","TV","WiFi","Private Pool","Mini Bar","Living Room","Butler Service","Private Chef","","","","","","",""};
    daftarKamar[8] = new Premium("501","PRM-1", 2000000, fasPremium);
    daftarKamar[9] = new Premium("502","PRM-2", 2000000, fasPremium);
}

void tampilDaftarKamar() {
    cout << "\n========== DAFTAR KAMAR HOTEL ==========\n";
    cout << left << setw(6) << "ID" << setw(12) << "Tipe"
         << setw(18) << "Harga/Malam" << setw(10) << "Nomor" << "Status\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < TOTAL_KAMAR; i++)
        daftarKamar[i]->tampilInfo();
    cout << "========================================\n";
}

bool hariValid(int h, int b, int t) {
    if (h < 1) return false;
    int maxHari = 31;
    if (b == 4 || b == 6 || b == 9 || b == 11) maxHari = 30;
    else if (b == 2) {
        bool kabisat = (t % 4 == 0 && t % 100 != 0) || (t % 400 == 0);
        maxHari = kabisat ? 29 : 28;
    }
    return h <= maxHari;
}

string inputTanggal() {
    string input;
    int hari, bulan, tahun;
    const int tahunMin = 2026, tahunMax = 2026;
    while (true) {
        cout << "Tanggal (dd/mm/yyyy): ";
        getline(cin, input);
        if (input.length() != 10 || input[2] != '/' || input[5] != '/') {
            cout << "[!] Format tidak valid. Gunakan dd/mm/yyyy (contoh: 15/06/2026)\n";
            continue;
        }
        bool valid = true;
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue;
            if (input[i] < '0' || input[i] > '9') { valid = false; break; }
        }
        if (!valid) { cout << "[!] Gunakan angka saja (contoh: 15/06/2026)\n"; continue; }
        hari  = (input[0]-'0')*10 + (input[1]-'0');
        bulan = (input[3]-'0')*10 + (input[4]-'0');
        tahun = (input[6]-'0')*1000 + (input[7]-'0')*100 + (input[8]-'0')*10 + (input[9]-'0');
        if (bulan < 1 || bulan > 12) { cout << "[!] Bulan tidak valid. Masukkan antara 01-12\n"; continue; }
        if (tahun < tahunMin || tahun > tahunMax) {
            cout << "[!] Tahun tidak valid. Range booking hanya " << tahunMin << "-" << tahunMax << "\n";
            continue;
        }
        if (!hariValid(hari, bulan, tahun)) {
            cout << "[!] Tanggal tidak valid untuk bulan " << bulan << "/" << tahun << "\n";
            continue;
        }
        break;
    }
    return input;
}

string normalisasiTipe(const string& raw) {
    if (raw=="standar"||raw=="STANDAR")       return "Standar";
    if (raw=="deluxe"||raw=="DELUXE")         return "Deluxe";
    if (raw=="executive"||raw=="EXECUTIVE")   return "Executive";
    if (raw=="vip"||raw=="VIP")               return "VIP";
    if (raw=="premium"||raw=="PREMIUM")       return "Premium";
    return raw;
}

void prosesBooking() {
    cout << "\n========== FORM BOOKING KAMAR ==========\n";
    cin.ignore(1000, '\n');
    string nama = inputNama("Nama Tamu    : ");
    cout << "Masukkan Tanggal Booking (format: dd/mm/yyyy, contoh: 15/06/2026)\n";
    string tanggal = inputTanggal();

    string tipeRaw;
    cout << "Tipe Kamar (Standar/Deluxe/Executive/VIP/Premium): ";
    getline(cin, tipeRaw);
    string tipe = normalisasiTipe(tipeRaw);

    int durasi = inputInt("Durasi Menginap (malam): ");

    Kamar* kamarDipilih = NULL;
    for (int i = 0; i < TOTAL_KAMAR; i++) {
        if (daftarKamar[i]->getTipe() == tipe && daftarKamar[i]->isTersedia()) {
            kamarDipilih = daftarKamar[i];
            break;
        }
    }
    if (!kamarDipilih) {
        cout << "\n[!] Maaf, semua kamar tipe " << tipe << " sudah penuh / tidak tersedia.\n";
        return;
    }

    Booking b;
    b.namaGuest  = nama;
    b.tanggal    = tanggal;
    b.idKamar    = kamarDipilih->getIdKamar();
    b.tipeKamar  = tipe;
    b.durasi     = durasi;
    b.totalHarga = kamarDipilih->getHarga() * durasi;
    b.aktif      = true;

    kamarDipilih->setBooking(b);
    kamarDipilih->setTersedia(false);

    cout << "\n[OK] Booking berhasil!\n";
    kamarDipilih->cetakStruk();
}

void bookingDenganMembership() {
    string kode;
    cin.ignore(1000, '\n');
    cout << "\n========== BOOKING DENGAN MEMBERSHIP ==========\n";
    cout << "Masukkan Kode Membership (5 angka): ";
    getline(cin, kode);

    if (kode.length() != 5) { cout << "[!] Kode membership harus 5 angka.\n"; return; }
    for (char c : kode) {
        if (c < '0' || c > '9') { cout << "[!] Kode membership hanya boleh berisi angka.\n"; return; }
    }
    int idx = cariMember(kode);
    if (idx == -1) { cout << "[!] Kode membership tidak ditemukan atau tidak aktif.\n"; return; }

    Member& m = daftarMember[idx];
    cout << "\n[OK] Member ditemukan!\n";
    cout << "Nama           : " << m.nama            << "\n";
    cout << "Jumlah Menginap: " << m.jumlahMenginap  << "x\n";
    cout << "Status Diskon  : " << (cekDiskon(idx) ? "AKTIF (10%)" : "Belum aktif (min. 5x menginap)") << "\n";

    string tipeRaw;
    cout << "\nTipe Kamar (Standar/Deluxe/Executive/VIP/Premium): ";
    getline(cin, tipeRaw);
    string tipe = normalisasiTipe(tipeRaw);

    cout << "Masukkan Tanggal Booking (format: dd/mm/yyyy, contoh: 15/06/2026)\n";
    string tanggal = inputTanggal();

    int durasi = inputInt("Durasi Menginap (malam): ");

    Kamar* kamarDipilih = NULL;
    for (int i = 0; i < TOTAL_KAMAR; i++) {
        if (daftarKamar[i]->getTipe() == tipe && daftarKamar[i]->isTersedia()) {
            kamarDipilih = daftarKamar[i];
            break;
        }
    }
    if (!kamarDipilih) {
        cout << "\n[!] Maaf, semua kamar tipe " << tipe << " sudah penuh / tidak tersedia.\n";
        return;
    }

    float hargaPerMalam = kamarDipilih->getHarga();
    float totalNormal   = hargaPerMalam * durasi;
    float totalBayar    = hitungHargaMember(totalNormal, idx);
    float potongan      = totalNormal - totalBayar;

    Booking b;
    b.namaGuest  = m.nama;
    b.tanggal    = tanggal;
    b.idKamar    = kamarDipilih->getIdKamar();
    b.tipeKamar  = tipe;
    b.durasi     = durasi;
    b.totalHarga = totalBayar;
    b.aktif      = true;

    kamarDipilih->setBooking(b);
    kamarDipilih->setTersedia(false);

    cout << "\n========================================\n";
    cout << "      STRUK BOOKING - MEMBERSHIP        \n";
    cout << "========================================\n";
    cout << left << setw(22) << "Nama Tamu"       << ": " << m.nama                              << "\n";
    cout << left << setw(22) << "Kode Membership" << ": " << m.kodeMember                        << "\n";
    cout << left << setw(22) << "ID Kamar"        << ": " << kamarDipilih->getIdKamar()          << "\n";
    cout << left << setw(22) << "Nomor Kamar"     << ": " << kamarDipilih->getNomor()            << "\n";
    cout << left << setw(22) << "Tipe Kamar"      << ": " << tipe                                << "\n";
    cout << left << setw(22) << "Tanggal"         << ": " << tanggal                             << "\n";
    cout << left << setw(22) << "Durasi"          << ": " << durasi << " Malam"                  << "\n";
    cout << left << setw(22) << "Harga/Malam"     << ": Rp. " << fixed << setprecision(0) << hargaPerMalam << "\n";
    cout << left << setw(22) << "Total Normal"    << ": Rp. " << fixed << setprecision(0) << totalNormal   << "\n";
    if (cekDiskon(idx))
        cout << left << setw(22) << "Diskon Member (10%)" << ": - Rp. " << fixed << setprecision(0) << potongan << "\n";
    else {
        int sisaMenginap = 5 - m.jumlahMenginap;
        cout << left << setw(22) << "Diskon Member" << ": Tidak ada (kurang " << sisaMenginap << "x menginap)\n";
    }
    cout << "----------------------------------------\n";
    cout << left << setw(22) << "TOTAL BAYAR" << ": Rp. " << fixed << setprecision(0) << totalBayar << "\n";
    cout << "========================================\n";
    cout << "     Terima kasih telah menginap!       \n";
    cout << "========================================\n";

    tambahMenginap(idx);
}

//*fasilitas kmr*//
void prosesBookingForward(); 

void cekFasilitasKamar() {
    string idTarget;
    char lanjut;
    tampilDaftarKamar();
    cout << "\nMasukkan ID Kamar yang ingin dicek fasilitasnya: ";
    cin >> idTarget;
    bool ketemu = false;
    for (int i = 0; i < TOTAL_KAMAR; i++) {
        if (daftarKamar[i]->getIdKamar() == idTarget) {
            daftarKamar[i]->tampilFasilitas();
            ketemu = true;
            break;
        }
    }
    if (!ketemu) { cout << "[!] ID Kamar tidak ditemukan.\n"; return; }
    cout << "\nMau lanjut isi form booking kamar? (y/n): ";
    cin >> lanjut;
    if (lanjut == 'y' || lanjut == 'Y') {
        prosesBooking();
    } else {
        cout << "Kembali ke menu utama.\n";
    }
}

void menuBookingKamar() {
    int pil = inputInt(
        "\n========== MENU BOOKING KAMAR ==========\n"
        "1. Cek fasilitas kamar dulu\n"
        "2. Lanjut isi form booking kamar\n"
        "3. Kembali ke menu utama\n"
        "Pilihan: ");
    if      (pil == 1) cekFasilitasKamar();
    else if (pil == 2) prosesBooking();
    else if (pil == 3) cout << "Kembali ke menu utama.\n";
    else               cout << "Pilihan tidak valid.\n";
}

//Admin//
void ubahStatusKamar() {
    string password;
    cout << "\n========== PANEL ADMIN ==========\n";
    cout << "Masukkan Password: ";
    cin >> password;
    if (password != "12345") { cout << "[!] Password salah. Akses ditolak.\n"; return; }

    cout << "\n[OK] Akses diterima.\n";
    tampilDaftarKamar();

    string idTarget;
    cout << "Masukkan ID Kamar yang ingin diubah statusnya: ";
    cin >> idTarget;

    bool ketemu = false;
    for (int i = 0; i < TOTAL_KAMAR; i++) {
        if (daftarKamar[i]->getIdKamar() == idTarget) {
            bool statusBaru = !daftarKamar[i]->isTersedia();
            daftarKamar[i]->setTersedia(statusBaru);
            cout << "[OK] Status kamar " << idTarget << " berhasil diubah menjadi: "
                 << (statusBaru ? "Tersedia" : "Tidak Tersedia") << "\n";
            ketemu = true;
            break; // hanya ubah satu kamar
        }
    }
    if (!ketemu) cout << "[!] ID Kamar tidak ditemukan.\n";
}

void menuMembership() {
    int pil;
    do {
        pil = inputInt(
            "\n======== SISTEM MEMBERSHIP HOTEL ========\n"
            "1. Daftar Member Baru\n"
            "2. Booking dengan Membership\n"
            "3. Cek Info Member\n"
            "4. Lihat Semua Member (Admin)\n"
            "5. Kembali ke Menu Utama\n"
            "Pilihan: ");
        switch (pil) {
            case 1: daftarMemberBaru();        break;
            case 2: bookingDenganMembership(); break;
            case 3: cekInfoMember();           break;
            case 4: lihatDaftarMember();       break;
            case 5: cout << "Kembali ke menu utama.\n"; break;
            default: cout << "[!] Pilihan tidak valid.\n";
        }
    } while (pil != 5);
}

int main() {
    inisiasiKamar();

    int pilihan;
    do {
        pilihan = inputInt(
            "\n============ SISTEM HOTEL ============\n"
            "1. Lihat Daftar Kamar\n"
            "2. Booking Kamar\n"
            "3. Ubah Status Kamar (Admin)\n"
            "4. Membership\n"
            "5. Keluar\n"
            "Pilihan: ");

        switch (pilihan) {
            case 1: tampilDaftarKamar(); break;
            case 2: menuBookingKamar();  break;
            case 3: ubahStatusKamar();   break;
            case 4: menuMembership();    break;
            case 5: cout << "Terima kasih!\n"; break;
            default: cout << "[!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    for (int i = 0; i < TOTAL_KAMAR; i++) delete daftarKamar[i];
    return 0;
}