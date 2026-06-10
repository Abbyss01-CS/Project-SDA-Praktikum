void tampilFasilitas() {
    cout << "\n========== DETAIL FASILITAS KAMAR ==========" << endl;
    cout << "ID Kamar    : " << idKamar << endl;
    cout << "Nomor Kamar : " << nomor << endl;
    cout << "Tipe Kamar  : " << tipe << endl;
    cout << "Harga/Malam : Rp. " << fixed << setprecision(0) << hpMalam << endl;
    cout << "Status      : " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
    cout << "Fasilitas   : " << endl;

    for (int i = 0; i < 15; i++) {
        if (fasilitas[i] != "") {
            cout << "- " << fasilitas[i] << endl;
        }
    }

    cout << "Deskripsi   : ";

    if (tipe == "Standar") {
        cout << "Kamar sederhana dengan fasilitas dasar seperti AC, TV, dan WiFi." << endl;
    } else if (tipe == "Deluxe") {
        cout << "Kamar nyaman dengan tambahan bathtub dan mini bar." << endl;
    } else if (tipe == "Executive") {
        cout << "Kamar luas dengan tambahan living room." << endl;
    } else if (tipe == "VIP") {
        cout << "Kamar mewah dengan jacuzzi dan butler service." << endl;
    } else if (tipe == "Premium") {
        cout << "Kamar paling lengkap dengan private pool dan private chef." << endl;
    }

    cout << "============================================" << endl;
}

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

    if (!ketemu) {
        cout << "[!] ID Kamar tidak ditemukan." << endl;
        return;
    }

    cout << "\nMau lanjut isi form booking kamar? (y/n): ";
    cin >> lanjut;

    if (lanjut == 'y' || lanjut == 'Y') {
        prosesBooking();
    } else {
        cout << "Kembali ke menu utama." << endl;
    }
}

void menuBookingKamar() {
    int pilihan;

    cout << "\n========== MENU BOOKING KAMAR ==========" << endl;
    cout << "1. Cek fasilitas kamar dulu" << endl;
    cout << "2. Lanjut isi form booking kamar" << endl;
    cout << "3. Kembali ke menu utama" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        cekFasilitasKamar();
    } else if (pilihan == 2) {
        prosesBooking();
    } else if (pilihan == 3) {
        cout << "Kembali ke menu utama." << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}