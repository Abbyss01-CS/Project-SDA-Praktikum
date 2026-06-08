const int TOTAL_KAMAR = 25; // 5 tipe x 5 kamar
Kamar* daftarKamar[TOTAL_KAMAR];

void inisiasiKamar() {
    // --- STANDAR (ID: 101-105) ---
    string fasStandar[15] = {"AC", "TV", "WiFi", "", "", "", "", "", "", "", "", "", "", "", ""};
    daftarKamar[0]  = new Standar("101", "STD-1", 300000, fasStandar);
    daftarKamar[1]  = new Standar("102", "STD-2", 300000, fasStandar);
    daftarKamar[2]  = new Standar("103", "STD-3", 300000, fasStandar);
    daftarKamar[3]  = new Standar("104", "STD-4", 300000, fasStandar);
    daftarKamar[4]  = new Standar("105", "STD-5", 300000, fasStandar);

    // --- DELUXE (ID: 201-205) ---
    string fasDeluxe[15] = {"AC", "TV", "WiFi", "Bathtub", "Mini Bar", "", "", "", "", "", "", "", "", "", ""};
    daftarKamar[5]  = new Deluxe("201", "DLX-1", 500000, fasDeluxe);
    daftarKamar[6]  = new Deluxe("202", "DLX-2", 500000, fasDeluxe);
    daftarKamar[7]  = new Deluxe("203", "DLX-3", 500000, fasDeluxe);
    daftarKamar[8]  = new Deluxe("204", "DLX-4", 500000, fasDeluxe);
    daftarKamar[9]  = new Deluxe("205", "DLX-5", 500000, fasDeluxe);

    // --- EXECUTIVE (ID: 301-305) ---
    string fasExec[15] = {"AC", "TV", "WiFi", "Bathtub", "Mini Bar", "Living Room", "", "", "", "", "", "", "", "", ""};
    daftarKamar[10] = new Executive("301", "EXC-1", 750000, fasExec);
    daftarKamar[11] = new Executive("302", "EXC-2", 750000, fasExec);
    daftarKamar[12] = new Executive("303", "EXC-3", 750000, fasExec);
    daftarKamar[13] = new Executive("304", "EXC-4", 750000, fasExec);
    daftarKamar[14] = new Executive("305", "EXC-5", 750000, fasExec);

    // --- VIP (ID: 401-405) ---
    string fasVip[15] = {"AC", "TV", "WiFi", "Jacuzzi", "Mini Bar", "Living Room", "Butler Service", "", "", "", "", "", "", "", ""};
    daftarKamar[15] = new Vip("401", "VIP-1", 1200000, fasVip);
    daftarKamar[16] = new Vip("402", "VIP-2", 1200000, fasVip);
    daftarKamar[17] = new Vip("403", "VIP-3", 1200000, fasVip);
    daftarKamar[18] = new Vip("404", "VIP-4", 1200000, fasVip);
    daftarKamar[19] = new Vip("405", "VIP-5", 1200000, fasVip);

    // --- PREMIUM (ID: 501-505) ---
    string fasPremium[15] = {"AC", "TV", "WiFi", "Private Pool", "Mini Bar", "Living Room", "Butler Service", "Private Chef", "", "", "", "", "", "", ""};
    daftarKamar[20] = new Premium("501", "PRM-1", 2000000, fasPremium);
    daftarKamar[21] = new Premium("502", "PRM-2", 2000000, fasPremium);
    daftarKamar[22] = new Premium("503", "PRM-3", 2000000, fasPremium);
    daftarKamar[23] = new Premium("504", "PRM-4", 2000000, fasPremium);
    daftarKamar[24] = new Premium("505", "PRM-5", 2000000, fasPremium);
}

// ===================== TAMPIL DAFTAR KAMAR =====================
void tampilDaftarKamar() {
    cout << "\n========== DAFTAR KAMAR HOTEL ==========" << endl;
    cout << left << setw(6) << "ID" << setw(12) << "Tipe" << setw(18) << "Harga/Malam" << "Status" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < TOTAL_KAMAR; i++) {
        cout << left << setw(6)  << daftarKamar[i]->getIdKamar()
             << setw(12) << daftarKamar[i]->getTipe()
             << "Rp. " << setw(14) << fixed << setprecision(0) << daftarKamar[i]->getHarga()
             << (daftarKamar[i]->isTersedia() ? "Tersedia" : "Tidak Tersedia") << endl;
    }
    cout << "========================================" << endl;
}

// ===================== VALIDASI TANGGAL =====================
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
    int tahunMin = 2026, tahunMax = 2026;

    while (true) {
        cout << "Tanggal (dd/mm/yyyy): ";
        getline(cin, input);

        // Cek panjang format
        if (input.length() != 10 || input[2] != '/' || input[5] != '/') {
            cout << "[!] Format tidak valid. Gunakan dd/mm/yyyy (contoh: 15/06/2026)\n";
            continue;
        }

        // Cek semua karakter angka kecuali separator
        bool valid = true;
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue;
            if (input[i] < '0' || input[i] > '9') { valid = false; break; }
        }
        if (!valid) {
            cout << "[!] Format tidak valid. Gunakan angka saja (contoh: 15/06/2026)\n";
            continue;
        }

        hari  = (input[0]-'0')*10 + (input[1]-'0');
        bulan = (input[3]-'0')*10 + (input[4]-'0');
        tahun = (input[6]-'0')*1000 + (input[7]-'0')*100 + (input[8]-'0')*10 + (input[9]-'0');

        if (bulan < 1 || bulan > 12) {
            cout << "[!] Bulan tidak valid. Masukkan antara 01-12\n";
            continue;
        }
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