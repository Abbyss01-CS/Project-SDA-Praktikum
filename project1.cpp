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

    //admin//
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
