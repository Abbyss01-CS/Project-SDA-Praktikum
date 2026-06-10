#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_MEMBER    = 100;
const float DISKON_PERSEN = 0.10; 

struct Member {
    string kodeMember;
    string nama;
    string noHp;
    int jumlahMenginap;
    bool aktif;
};

Member daftarMember[MAX_MEMBER];
int totalMember = 0;
int kodeCounter = 10001;

string generateKode() {
    return to_string(kodeCounter++);
}

void daftarMemberBaru() {
    if (totalMember >= MAX_MEMBER) {
        cout << "[!] Database member penuh." << endl;
        return;
    }

    Member m;
    cin.ignore(1000, '\n');

    cout << "\n========== PENDAFTARAN MEMBERSHIP ==========" << endl;
    cout << "Nama Lengkap : "; getline(cin, m.nama);
    cout << "No. HP       : "; getline(cin, m.noHp);

    m.kodeMember     = generateKode();
    m.jumlahMenginap = 0;
    m.aktif          = true;

    daftarMember[totalMember++] = m;

    cout << "\n[OK] Pendaftaran berhasil!" << endl;
    cout << "============================================" << endl;
    cout << left << setw(20) << "Nama"          << ": " << m.nama << endl;
    cout << left << setw(20) << "Kode Membership" << ": " << m.kodeMember << endl;
    cout << left << setw(20) << "No. HP"        << ": " << m.noHp << endl;
    cout << left << setw(20) << "Status Diskon" << ": Belum (perlu 5x menginap)" << endl;
    cout << "============================================" << endl;
}

int cariMember(const string& kode) {
    for (int i = 0; i < totalMember; i++) {
        if (daftarMember[i].kodeMember == kode && daftarMember[i].aktif) {
            return i;
        }
    }
    return -1;
}

bool cekDiskon(int indexMember) {
    return daftarMember[indexMember].jumlahMenginap >= 5;
}

float hitungHargaMember(float hargaNormal, int indexMember) {
    if (cekDiskon(indexMember)) {
        return hargaNormal * (1.0f - DISKON_PERSEN);
    }
    return hargaNormal;
}

void tambahMenginap(int indexMember) {
    daftarMember[indexMember].jumlahMenginap++;

    int jml = daftarMember[indexMember].jumlahMenginap;
    cout << "\n[INFO] Riwayat menginap member '" << daftarMember[indexMember].nama
         << "' sekarang: " << jml << "x" << endl;

    if (jml == 5) {
        cout << "[SELAMAT] Member ini sekarang berhak mendapat DISKON 10% untuk booking berikutnya!" << endl;
    }
}

void bookingDenganMembership() {
    string kode;
    cin.ignore(1000, '\n');

    cout << "\n========== BOOKING DENGAN MEMBERSHIP ==========" << endl;
    cout << "Masukkan Kode Membership (5 angka): ";
    getline(cin, kode);

    if (kode.length() != 5) {
        cout << "[!] Kode membership harus 5 angka." << endl;
        return;
    }
    for (char c : kode) {
        if (c < '0' || c > '9') {
            cout << "[!] Kode membership hanya boleh berisi angka." << endl;
            return;
        }
    }

    int idx = cariMember(kode);
    if (idx == -1) {
        cout << "[!] Kode membership tidak ditemukan atau tidak aktif." << endl;
        return;
    }

    Member& m = daftarMember[idx];
    cout << "\n[OK] Member ditemukan!" << endl;
    cout << "Nama           : " << m.nama << endl;
    cout << "Jumlah Menginap: " << m.jumlahMenginap << "x" << endl;
    cout << "Status Diskon  : " << (cekDiskon(idx) ? "AKTIF (10%)" : "Belum aktif (min. 5x menginap)") << endl;

    string tipe;
    int durasi;
    float hargaPerMalam;

    cout << "\nTipe Kamar (Standar/Deluxe/Executive/VIP/Premium): ";
    getline(cin, tipe);
    cout << "Harga/Malam (Rp): ";
    cin >> hargaPerMalam;
    cout << "Durasi Menginap (malam): ";
    cin >> durasi;

    float totalNormal = hargaPerMalam * durasi;
    float totalBayar  = hitungHargaMember(totalNormal, idx);
    float potongan    = totalNormal - totalBayar;

    cout << "\n";
    cout << "========================================" << endl;
    cout << "      STRUK BOOKING - MEMBERSHIP        " << endl;
    cout << "========================================" << endl;
    cout << left << setw(22) << "Nama Tamu"       << ": " << m.nama << endl;
    cout << left << setw(22) << "Kode Membership" << ": " << m.kodeMember << endl;
    cout << left << setw(22) << "Tipe Kamar"      << ": " << tipe << endl;
    cout << left << setw(22) << "Durasi"          << ": " << durasi << " Malam" << endl;
    cout << left << setw(22) << "Harga/Malam"     << ": Rp. " << fixed << setprecision(0) << hargaPerMalam << endl;
    cout << left << setw(22) << "Total Normal"    << ": Rp. " << fixed << setprecision(0) << totalNormal << endl;

    if (cekDiskon(idx)) {
        cout << left << setw(22) << "Diskon Member (10%)" << ": - Rp. " << fixed << setprecision(0) << potongan << endl;
    } else {
        int sisaMenginap = 5 - m.jumlahMenginap;
        cout << left << setw(22) << "Diskon Member" << ": Tidak ada (kurang " << sisaMenginap << "x menginap)" << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << left << setw(22) << "TOTAL BAYAR" << ": Rp. " << fixed << setprecision(0) << totalBayar << endl;
    cout << "========================================" << endl;
    cout << "     Terima kasih telah menginap!       " << endl;
    cout << "========================================" << endl;

    tambahMenginap(idx);
}

void lihatDaftarMember() {
    cout << "\n========== DAFTAR MEMBER HOTEL ==========" << endl;
    if (totalMember == 0) {
        cout << "Belum ada member terdaftar." << endl;
        return;
    }

    cout << left
         << setw(10) << "Kode"
         << setw(25) << "Nama"
         << setw(16) << "No. HP"
         << setw(12) << "Menginap"
         << "Diskon" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (int i = 0; i < totalMember; i++) {
        if (!daftarMember[i].aktif) continue;
        cout << left
             << setw(10) << daftarMember[i].kodeMember
             << setw(25) << daftarMember[i].nama
             << setw(16) << daftarMember[i].noHp
             << setw(12) << (to_string(daftarMember[i].jumlahMenginap) + "x")
             << (cekDiskon(i) ? "AKTIF 10%" : "-") << endl;
    }
    cout << "==========================================================" << endl;
}

void cekInfoMember() {
    string kode;
    cin.ignore(1000, '\n');
    cout << "\nMasukkan Kode Membership: ";
    getline(cin, kode);

    int idx = cariMember(kode);
    if (idx == -1) {
        cout << "[!] Kode tidak ditemukan." << endl;
        return;
    }

    Member& m = daftarMember[idx];
    int sisaMenginap = (m.jumlahMenginap < 5) ? (5 - m.jumlahMenginap) : 0;

    cout << "\n========== INFO MEMBER ==========" << endl;
    cout << left << setw(22) << "Kode Membership" << ": " << m.kodeMember << endl;
    cout << left << setw(22) << "Nama"            << ": " << m.nama << endl;
    cout << left << setw(22) << "No. HP"          << ": " << m.noHp << endl;
    cout << left << setw(22) << "Jumlah Menginap" << ": " << m.jumlahMenginap << "x" << endl;
    if (cekDiskon(idx)) {
        cout << left << setw(22) << "Status Diskon"   << ": AKTIF - Dapat potongan 10%" << endl;
    } else {
        cout << left << setw(22) << "Status Diskon"   << ": Belum aktif" << endl;
        cout << left << setw(22) << "Sisa menginap"   << ": " << sisaMenginap << "x lagi untuk dapat diskon" << endl;
    }
    cout << "=================================" << endl;
}

int main() {
    int pilihan;
    do {
        cout << "\n======== SISTEM MEMBERSHIP HOTEL ========" << endl;
        cout << "1. Daftar Member Baru" << endl;
        cout << "2. Booking dengan Membership" << endl;
        cout << "3. Cek Info Member" << endl;
        cout << "4. Lihat Semua Member (Admin)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: daftarMemberBaru();          break;
            case 2: bookingDenganMembership();   break;
            case 3: cekInfoMember();             break;
            case 4: lihatDaftarMember();         break;
            case 5: cout << "Sampai jumpa!" << endl; break;
            default: cout << "[!] Pilihan tidak valid." << endl;
        }
    } while (pilihan != 5);

    return 0;
}