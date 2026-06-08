#include <iostream>
using namespace std;

class Kamar {
protected :
    string nomor;
    string tipe;
    float hpMalam;
    bool tersedia;
    string fasilitas[15];

public:
    Kamar(){
        nomor = "";
        tipe = "";
        hpMalam = 0.0;
        tersedia = true;
        for (int i = 0; i < 15; i++) {
            fasilitas[i] = "";
        }
    }

    virtual void tampilInfo() = 0;
    
    virtual void hitungTotal(int durasi) = 0;
};

class Standar : public Kamar {
public :
    Standar(string nomor, float hpMalam, string fasilitas[]) {
        this->nomor = nomor;
        this->tipe = "Standar";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) {
            this->fasilitas[i] = fasilitas[i];
         }
    }

    void tampilInfo() override {
        cout << "Nomor Kamar: " << nomor << endl;
        cout << "Tipe Kamar: " << tipe << endl;
        cout << "Harga per Malam: " << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas: ";
        for (int i = 0; i < 15; i++) {
            if (fasilitas[i] != "") {
                cout << fasilitas[i] << ", ";
            }
        }
        cout << endl; 
    }

    void hitungTotal(int durasi) override{
        float total= hpMalam * durasi;
        cout << "Durasi Menginap : " << durasi << " Malam" << endl;
        cout << "Total Harga : Rp. " <<total << endl;
    }

};

class Deluxe : public Kamar {
public :
    Deluxe (string nomor, float hpMalam, string fasilitas[]) {
        this->nomor = nomor;
        this->tipe = "Deluxe";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) {
            this->fasilitas[i] = fasilitas[i];
        }
    }

    void tampilInfo() override {
        cout << "Nomor Kamar: " << nomor << endl;
        cout << "Tipe Kamar: " << tipe << endl;
        cout << "Harga per Malam: " << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas: ";
        for (int i = 0; i < 15; i++) {
            if (fasilitas[i] != "") {
                cout << fasilitas[i] << ", ";
            }
        }
        cout << endl; 
    }

    void hitungTotal(int durasi)  override {
        float total= hpMalam * durasi;
        cout << "Durasi Menginap : " << durasi << " Malam" << endl;
        cout << "Total Harga : Rp. " <<total << endl;
    }
};  

class Executive : public Kamar {
public : 
    Executive (string nomor, float hpMalam, string fasilitas[]) {
        this->nomor = nomor;
        this->tipe = "Executive";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) {
            this->fasilitas[i] = fasilitas[i];
        }
    }

    void tampilInfo() override {
        cout << "Nomor Kamar: " << nomor << endl;
        cout << "Tipe Kamar: " << tipe << endl;
        cout << "Harga per Malam: " << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas: ";
        for (int i = 0; i < 15; i++) {
            if (fasilitas[i] != "") {
                cout << fasilitas[i] << ", ";
            }
        }
        cout << endl; 
    }
    
    void hitungTotal(int durasi) override {
        float total= hpMalam * durasi;
        cout << "Durasi Menginap : " << durasi << " Malam" << endl;
        cout << "Total Harga : Rp. " <<total << endl;
    }
};

class Vip : public Kamar {
public :
    Vip (string nomor, float hpMalam, string fasilitas[]){
        this->nomor = nomor;
        this->tipe = "VIP";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++) {
            this->fasilitas[i] = fasilitas[i];
        }
    }

    void tampilInfo() override {
        cout << "Nomor Kamar: " << nomor << endl;
        cout << "Tipe Kamar: " << tipe << endl;
        cout << "Harga per Malam: " << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas: ";
        for (int i = 0; i < 15; i++) {
            if (fasilitas[i] != "") {
                cout << fasilitas[i] << ", ";
            }
        }
        cout << endl; 
    }

     void hitungTotal(int durasi) override {
        float total= hpMalam * durasi;
        cout << "Durasi Menginap : " << durasi << " Malam" << endl;
        cout << "Total Harga : Rp. " <<total << endl;
    }
};

class Premium : public Kamar {
public :
    Premium (string nomor, float hpMalam, string fasilitas[]) {
        this->nomor = nomor;
        this->tipe = "Premium";
        this->hpMalam = hpMalam;
        this->tersedia = true;
        for (int i = 0; i < 15; i++){
            if (fasilitas[i] != "") {
                this->fasilitas[i] = fasilitas[i];
            }
        }
    }

    void tampilInfo() override {
        cout << "Nomor Kamar: " << nomor << endl;
        cout << "Tipe: " << tipe << endl;
        cout << "Harga per Malam: " << hpMalam << endl;
        cout << "Ketersediaan: " << (tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
        cout << "Fasilitas: ";
        for(int i = 0; i < 15; i++) {
            if (fasilitas[i] != "") {
                cout << fasilitas[i] << ", ";
            }
        }
        cout << endl;
    }

    void hitungTotal(int durasi) override {
        float total= hpMalam * durasi;
        cout << "Durasi Menginap : " << durasi << " Malam" << endl;
        cout << "Total Harga : Rp. " <<total << endl;
    }
};

