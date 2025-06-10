#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;

// Konstanta
const int MAKS_MENU = 100;

// Struktur data
struct MenuItem {
    string nama;
    double harga;
    string kategori;
    int stok;
    bool tersedia;
    string deskripsi;
};

// Fungsi untuk mendapatkan tanggal dan waktu
string getTanggalWaktu() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string tanggal(dt);
    return tanggal;
}

void tampilkanMenuUtama() {
    cout << "==============================\n";
    cout << "        VRAMA BILLIARD        \n";
    cout << "==============================\n";
    cout << "1. Sewa Meja Billiard\n";
    cout << "2. Pesan Makanan / Minuman\n";
    cout << "3. Lihat Estimasi Biaya Usaha\n";
    cout << "4. Laporan Transaksi Harian\n";
    cout << "5. Batal Transaksi\n";
    cout << "6. Keluar\n";
    cout << "==============================\n";
    cout << "Pilih menu (1-6): ";
}

const int MAX_MEJA = 20;
const double DISKON_PERSEN = 0.10;
const double PAJAK_PERSEN = 0.10;

// Jam operasional
const int JAM_BUKA = 10;
const int JAM_TUTUP = 22;

int hargaPerJam;

struct MejaBiliar {
    int nomor;
    string namaPenyewa;
    int durasi;
    bool tersedia;
    double subtotal;
    double diskon;
    double pajak;
    double totalBiaya;
    string metodePembayaran;
    int jamMulai;
};

struct User {
    string username;
    string password;
    string role; // "admin" atau "pengguna"
};

struct MenuMakanan {
    string nama;
    double harga;
};

// Data user hardcoded
User daftarUser[] = {
    {"admin", "admin123", "admin"},
    {"user1", "user123", "pengguna"},
    {"user2", "user234", "pengguna"}
};

// Data menu makanan/minuman
MenuItem menu[MAKS_MENU] = {
    // Data makanan
    {"Chicken Quesadilla",
	 38000,
	 "Makanan",
	  15, true,
	  "Quesadilla ayam dengan keju leleh dan sayuran segar"},
    {"Waffle Original",
	 35000,
	 "Dessert",
	  10, true, 
	 "Waffle hangat dengan sirup maple dan mentega"},
    {"Platter Combo",
	 30000, 
	"Makanan", 
	8, true,
	 "Kombinasi makanan ringan dalam satu piring"},
    {"Cheese Stick", 
	25000, 
	"Makanan", 
	20, true,
	 "Stik keju goreng renyah dengan saus sambal"},
    {"Nachos", 
	24000, "Makanan",
	 12, true,
	  "Tortilla chips dengan saus keju dan salsa"},
    {"Garlic Bread", 
	21000, "Makanan", 
	15, true, "Roti bawang putih panggang dengan butter"},
    {"Singkong Coklat Keju",
	 25000, "Makanan",
	  10, true, "Singkong goreng dengan topping coklat dan keju"},
    {"Singkong Coklat",
	 24000, "Makanan",
	  12, true, "Singkong goreng dengan topping coklat manis"},
    {"Singkong Original",
	 17000, "Makanan",
	  18, true, "Singkong goreng original dengan bumbu tradisional"},
    {"French Fries",
	 21000, "Makanan",
	  15, true, "Kentang goreng renyah dengan berbagai pilihan saus"},
    {"Onion Rings",
	 21000, "Makanan",
	  8, true, "Cincin bawang bombay goreng tepung renyah"},
    {"Mendoan",
	 15000, "Makanan",
	  20, true, "Tempe mendoan khas Purwokerto yang gurih"},
    {"Salad Buah", 
	25000, "Dessert",
	 6, true, "Campuran buah segar dengan yogurt dan madu"},
    {"Club Ice Cream",
	 25000, "Dessert", 
	 12, true, "Es krim dengan berbagai topping menarik"},
    
    // Data minuman
    {"Espresso", 
	15000, "Minuman",
	 10, true, "Kopi espresso dengan rasa kuat dan pekat"},
    {"Americano",
	 17000, "Minuman",
	  10, true, "Espresso dengan tambahan air panas"},
    {"Cappuccino",
	 20000, "Minuman",
	  10, true, "Espresso dengan busa susu yang lembut"},
    {"Caf? Latte",
	 21000, "Minuman",
	  10, true, "Espresso dengan susu hangat"},
    {"Caramel Macchiato",
	 23000, "Minuman",
	  10, true, "Kopi dengan karamel dan susu"},
    {"Hazelnut Latte",
	 23000, "Minuman",
	  10, true, "Kopi latte dengan rasa hazelnut"},
    {"Mochaccino",
	 22000, "Minuman",
	  10, true, "Kopi dengan coklat dan susu"},
    {"Kopi Tubruk", 
	12000, "Minuman",
	 10, true, "Kopi khas Indonesia dengan cita rasa kuat"},
    {"Vietnam Drip", 
	16000, "Minuman",
	 10, true, "Kopi tetes khas Vietnam"},
    {"Cold Brew",
	 20000, "Minuman", 
	 10, true, "Kopi seduh dingin dengan rasa ringan"},
    {"Matcha Latte", 
	22000, "Minuman", 
	10, true, "Teh hijau matcha dengan susu"},
    {"Red Velvet Latte",
	 22000, "Minuman",
	  10, true, "Minuman red velvet dengan susu"},
    {"Taro Latte",
	 22000, "Minuman", 
	 10, true, "Minuman taro dengan susu"},
    {"Chocolate Milk", 
	18000, "Minuman", 
	10, true, "Susu coklat dingin"},
    {"Ice Lemon Tea", 
	15000, "Minuman",
	10, true, "Teh lemon dingin segar"},
    {"Lychee Tea", 
	16000, "Minuman", 
	10, true, "Teh dengan rasa leci yang manis"},
    {"Strawberry Tea", 
	16000, "Minuman",
	 10, true, "Teh rasa stroberi segar"},
    {"Mango Smoothie",
	 23000, "Minuman",
	  10, true, "Smoothie mangga segar"},
    {"Avocado Juice",
	 25000, "Minuman", 
	 10, true, "Jus alpukat dengan susu dan gula"},
    {"Orange Juice", 
	20000, "Minuman", 
	10, true, "Jus jeruk segar"},
    {"Mineral Water", 
	8000, "Minuman",
	 10, true, "Air mineral dingin"},
    {"Soda Gembira",
	 18000, "Minuman", 
	 10, true, "Minuman soda dengan susu kental manis"}
};

const int jumlahUser = sizeof(daftarUser) / sizeof(daftarUser[0]);
const int jumlahMenu = sizeof(menu) / sizeof(menu[0]);

MejaBiliar daftarMeja[MAX_MEJA];
int jumlahPesanan = 0;
double totalPendapatanHarian = 0;

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string getNamaMetode(int kode) {
    switch (kode) {
        case 1: return "Tunai";
        case 2: return "Transfer";
        case 3: return "QRIS";
        default: return "Tidak Valid";
    }
}

int getKodeMetode(const string &metode) {
    string m = toLowerCase(metode);
    if (m == "tunai") return 1;
    if (m == "transfer") return 2;
    if (m == "qris") return 3;
    return 0;
}

void inisialisasiMeja() {
    for (int i = 0; i < MAX_MEJA; i++) {
        daftarMeja[i].nomor = i + 1;
        daftarMeja[i].tersedia = true;
        daftarMeja[i].durasi = 0;
        daftarMeja[i].namaPenyewa = "";
        daftarMeja[i].subtotal = 0;
        daftarMeja[i].diskon = 0;
        daftarMeja[i].pajak = 0;
        daftarMeja[i].totalBiaya = 0;
        daftarMeja[i].metodePembayaran = "-";
        daftarMeja[i].jamMulai = 0;
    }
    jumlahPesanan = 0;
}

void simpanDataKeFile() {
    ofstream file("data_pesanan.txt");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    file << jumlahPesanan << "\n";

    for (int i = 0; i < MAX_MEJA; i++) {
        if (!daftarMeja[i].tersedia) {
            file << daftarMeja[i].nomor << "\n"
                 << daftarMeja[i].namaPenyewa << "\n"
                 << daftarMeja[i].durasi << "\n"
                 << daftarMeja[i].subtotal << "\n"
                 << daftarMeja[i].diskon << "\n"
                 << daftarMeja[i].pajak << "\n"
                 << daftarMeja[i].totalBiaya << "\n"
                 << daftarMeja[i].metodePembayaran << "\n"
                 << daftarMeja[i].jamMulai << "\n";
        }
    }
    file.close();
}

void loadDataDariFile() {
    ifstream file("data_pesanan.txt");
    if (!file) {
        inisialisasiMeja();
        return;
    }

    file >> jumlahPesanan;
    file.ignore();

    for (int i = 0; i < jumlahPesanan; i++) {
        int nomor;
        string nama;
        int durasi;
        double subtotal, diskon, pajak, totalBiaya;
        string metodePembayaran;
        int jamMulai;

        file >> nomor;
        file.ignore();
        getline(file, nama);
        file >> durasi;
        file >> subtotal;
        file >> diskon;
        file >> pajak;
        file >> totalBiaya;
        file.ignore();
        getline(file, metodePembayaran);
        file >> jamMulai;
        file.ignore();

        MejaBiliar &meja = daftarMeja[nomor - 1];
        meja.nomor = nomor;
        meja.namaPenyewa = nama;
        meja.durasi = durasi;
        meja.subtotal = subtotal;
        meja.diskon = diskon;
        meja.pajak = pajak;
        meja.totalBiaya = totalBiaya;
        meja.metodePembayaran = metodePembayaran;
        meja.jamMulai = jamMulai;
        meja.tersedia = false;
        
        totalPendapatanHarian += totalBiaya;
    }

    file.close();
}

void tampilkanSemuaMeja() {
    cout << "\n==================== Daftar Semua Meja Billiard ====================\n";
    cout << string(65, '=') << "\n";
    cout << "| " << left << setw(4) << "Meja" 
         << "| " << setw(15) << "Nama Penyewa"
         << "| " << setw(8) << "Durasi"
         << "| " << setw(10) << "Status"
         << "| " << setw(12) << "Total"
         << "| " << setw(10) << "Metode" << " |\n";
    cout << string(65, '-') << "\n";

    for (int i = 0; i < MAX_MEJA; i++) {
        cout << "| " << setw(4) << i + 1;  // Nomor meja dari 1-20
        
        // Perbaikan logika: cek apakah meja tersedia atau tidak
        if (daftarMeja[i].tersedia == true) {
            // Meja TERSEDIA - belum dipesan
            cout << "| " << setw(15) << "-"
                 << "| " << setw(8) << "-"
                 << "| " << setw(10) << "Tersedia"
                 << "| " << setw(12) << "-"
                 << "| " << setw(10) << "-" << " |";
        } else {
            // Meja TIDAK TERSEDIA - sudah dipesan
            cout << "| " << setw(15) << daftarMeja[i].namaPenyewa
                 << "| " << setw(8) << daftarMeja[i].durasi
                 << "| " << setw(10) << "Dipesan"
                 << "| Rp " << setw(9) << fixed << setprecision(0) << daftarMeja[i].totalBiaya
                 << "| " << setw(10) << daftarMeja[i].metodePembayaran << " |";
        }
        cout << endl;
        
        // Tampilkan garis pemisah setiap 5 meja
        if ((i + 1) % 5 == 0) {
            cout << string(65, '-') << "\n";
        }
    }

    cout << "\nKeterangan:\n";
    cout << "- Status 'Tersedia' : Meja dapat dipesan\n";
    cout << "- Status 'Dipesan'  : Meja sedang digunakan\n";
    cout << string(65, '=') << "\n";
}								

void pesanMeja() {
    int nomor, durasi, metode, jamMulai;
    string nama;

    cout << "\n===== Pesan Meja =====\n";																	
    cout << "Masukkan nomor meja (1-" << MAX_MEJA << "): ";
    cin >> nomor;

    if (nomor < 1 || nomor > MAX_MEJA) {
        cout << "Nomor meja tidak valid.\n";
        return;
    }

    if (!daftarMeja[nomor - 1].tersedia) {
        cout << "Meja tersebut sudah dipesan.\n";
        return;
    }

    cin.ignore();
    cout << "Masukkan nama penyewa: ";
    getline(cin, nama);

    cout << "Masukkan jam mulai sewa (" << JAM_BUKA << " - " << (JAM_TUTUP - 1) << "): ";
    cin >> jamMulai;
    if (jamMulai < JAM_BUKA || jamMulai >= JAM_TUTUP) {
        cout << "Jam mulai sewa tidak sesuai jam operasional.\n";
        return;
    }

    cout << "Masukkan durasi sewa (jam): ";
    cin >> durasi;

    if (jamMulai + durasi > JAM_TUTUP) {
        cout << "Durasi sewa melebihi jam operasional.\n";
        return;
    }

    cout << "Pilih metode pembayaran:\n";
    cout << "1. Tunai\n2. Transfer\n3. QRIS\n";
    cout << "Pilihan: ";
    cin >> metode;

    if (metode < 1 || metode > 3) {
        cout << "Metode pembayaran tidak valid.\n";
        return;
    }

    double subtotal = hargaPerJam * durasi;
    double diskon = (durasi >= 3) ? subtotal * DISKON_PERSEN : 0;
    double pajak = (subtotal - diskon) * PAJAK_PERSEN;
    double total = subtotal - diskon + pajak;

    MejaBiliar &meja = daftarMeja[nomor - 1];
    meja.namaPenyewa = nama;
    meja.durasi = durasi;
    meja.subtotal = subtotal;
    meja.diskon = diskon;
    meja.pajak = pajak;
    meja.totalBiaya = total;
    meja.metodePembayaran = getNamaMetode(metode);
    meja.tersedia = false;
    meja.jamMulai = jamMulai;

    jumlahPesanan++;
    totalPendapatanHarian += total;

    simpanDataKeFile();

    cout << "\n--- Struk Pembayaran ---\n";
    cout << "Nama Penyewa     : " << nama << endl;
    cout << "Nomor Meja       : " << nomor << endl;
    cout << "Durasi           : " << durasi << " jam\n";
    cout << "Harga per Jam    : Rp " << hargaPerJam << endl;
    cout << "Subtotal         : Rp " << subtotal << endl;
    cout << "Diskon (10%)     : Rp " << diskon << endl;
    cout << "Pajak (10%)      : Rp " << pajak << endl;
    cout << "Total Pembayaran : Rp " << total << endl;
    cout << "Metode Pembayaran: " << meja.metodePembayaran << endl;
    cout << "------------------------\n";
}

void tampilkanHeader() {
    cout << "\n============== MENU SNACK - CAFFE V-RAMA ==============\n";
    cout << left << setw(3) << "No" << setw(25) << "Nama Menu" << setw(12) << "Harga (Rp)" 
         << setw(10) << "Stok" << setw(8) << "Status" << setw(15) << "Kategori" << endl;
    cout << "-----------------------------------------------------------\n";
}


// Menampilkan semua menu
void tampilkanMenu(MenuItem menu[], int jumlah) {
    tampilkanHeader();
    cout << "|" << string(65, '-') << "|\n";
    int batas = min(jumlah, 36); // Batasi jumlah data yang ditampilkan hingga 36
    for (int i = 0; i < batas; i++) {
        string status = menu[i].tersedia ? "Tersedia" : "Habis";
        cout << "| " << setw(3) << i + 1
             << "| " << setw(25) << menu[i].nama
             << "| Rp " << fixed << setprecision(0) << setw(8) << menu[i].harga
             << "| " << setw(10) << menu[i].stok
             << "| " << setw(8) << status
             << "| " << setw(15) << menu[i].kategori << " |\n";
        cout << "|" << string(65, '-') << "|\n";
    }
    cout << "-----------------------------------------------------------\n";
}

// Menampilkan menu berdasarkan kategori
void tampilkanMenuKategori(MenuItem menu[], int jumlah) {
    string kategori;
    cin.ignore();
    cout << "Masukkan kategori (Makanan/Minuman/Dessert): ";
    getline(cin, kategori);
    
    cout << "\n========== MENU KATEGORI: " << kategori << " ==========\n";
    tampilkanHeader();
    
    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (menu[i].kategori == kategori) {
            string status = menu[i].tersedia ? "Tersedia" : "Habis";
            cout << setw(3) << i + 1 << setw(25) << menu[i].nama 
                 << "Rp " << fixed << setprecision(0) << setw(8) << menu[i].harga
                 << setw(10) << menu[i].stok << setw(8) << status 
                 << setw(15) << menu[i].kategori << endl;
            ditemukan = true;
        }
    }
    
    if (!ditemukan) {
        cout << "Tidak ada menu dalam kategori tersebut.\n";
    }
    cout << "-----------------------------------------------------------\n";
}

// Menyimpan data ke file dengan format yang lebih detail
void simpanKeFile(MenuItem menu[], int jumlah) {
    ofstream file("menu_caffe_V-RAMA.txt");
    if (file.is_open()) {
        file << "============== MENU SNACK - CAFFE V-RAMA ==============\n";
        file << "Tanggal: " << getTanggalWaktu() << "\n\n";
        file << left << setw(3) << "No" << setw(25) << "Nama Menu" << setw(12) << "Harga (Rp)" 
             << setw(10) << "Stok" << setw(8) << "Status" << setw(15) << "Kategori" << endl;
        file << "-----------------------------------------------------------\n";
        
        for (int i = 0; i < jumlah; i++) {
            string status = menu[i].tersedia ? "Tersedia" : "Habis";
            file << setw(3) << i + 1 << setw(25) << menu[i].nama 
                 << "Rp " << fixed << setprecision(0) << setw(8) << menu[i].harga
                 << setw(10) << menu[i].stok << setw(8) << status 
                 << setw(15) << menu[i].kategori << endl;
        }
        file << "-----------------------------------------------------------\n";
        file.close();
        cout << " Data berhasil disimpan ke 'menu_caffe_V-RAMA.txt'\n";
    } else {
        cout << " Gagal membuka file untuk menyimpan.\n";
    }
}

// Menambahkan menu baru dengan detail lengkap
void tambahMenu(MenuItem menu[], int &jumlah) {
    char lanjut;
    do {
        if (jumlah >= MAKS_MENU) {
            cout << "? Menu penuh. Tidak bisa menambah lagi.\n";
            return;
        }

        cin.ignore();
        cout << "Masukkan nama menu: ";
        getline(cin, menu[jumlah].nama);

        cout << "Masukkan harga menu: ";
        cin >> menu[jumlah].harga;

        cout << "Masukkan stok menu: ";
        cin >> menu[jumlah].stok;

        cin.ignore();
        cout << "Masukkan kategori (Makanan/Minuman/Dessert): ";
        getline(cin, menu[jumlah].kategori);

        cout << "Masukkan deskripsi menu: ";
        getline(cin, menu[jumlah].deskripsi);

        menu[jumlah].tersedia = menu[jumlah].stok > 0;
        jumlah++;

        cout << "Tambah menu lagi? (y/n): ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');
}

// Edit menu yang sudah ada
void editMenu(MenuItem menu[], int jumlah) {
    int nomor;
    tampilkanMenu(menu, jumlah);
    cout << "Pilih nomor menu yang akan diedit (1-" << jumlah << "): ";
    cin >> nomor;

    if (nomor < 1 || nomor > jumlah) {
        cout << "? Nomor menu tidak valid.\n";
        return;
    }

    nomor--; // Konversi ke index array
    cout << "\n=== EDIT MENU: " << menu[nomor].nama << " ===\n";
    cout << "1. Edit Nama\n2. Edit Harga\n3. Edit Stok\n4. Edit Kategori\n5. Edit Deskripsi\n";
    cout << "Pilih yang akan diedit: ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1:
            cout << "Nama baru: ";
            getline(cin, menu[nomor].nama);
            break;
        case 2:
            cout << "Harga baru: ";
            cin >> menu[nomor].harga;
            break;
        case 3:
            cout << "Stok baru: ";
            cin >> menu[nomor].stok;
            menu[nomor].tersedia = menu[nomor].stok > 0;
            break;
        case 4:
            cout << "Kategori baru: ";
            getline(cin, menu[nomor].kategori);
            break;
        case 5:
            cout << "Deskripsi baru: ";
            getline(cin, menu[nomor].deskripsi);
            break;
        default:
            cout << "? Pilihan tidak valid.\n";
            return;
    }
    cout << "? Menu berhasil diupdate.\n";
}

// Hapus menu
void hapusMenu(MenuItem menu[], int &jumlah) {
    int nomor;
    tampilkanMenu(menu, jumlah);
    cout << "Pilih nomor menu yang akan dihapus (1-" << jumlah << "): ";
    cin >> nomor;

    if (nomor < 1 || nomor > jumlah) {
        cout << "? Nomor menu tidak valid.\n";
        return;
    }

    nomor--; // Konversi ke index array
    
    // Geser semua elemen setelah index yang dihapus
    for (int i = nomor; i < jumlah - 1; i++) {
        menu[i] = menu[i + 1];
    }
    
    jumlah--;
    cout << "? Menu berhasil dihapus.\n";
}

// Mencari menu berdasarkan nama atau kategori
void cariMenu(MenuItem menu[], int jumlah) {
    cin.ignore();
    string keyword;
    bool ditemukan = false;

    cout << "Masukkan kata kunci menu yang dicari: ";
    getline(cin, keyword);

    cout << "\nHasil pencarian untuk: \"" << keyword << "\"\n";
    tampilkanHeader();
    
    for (int i = 0; i < jumlah; i++) {
        if (menu[i].nama.find(keyword) != string::npos || 
            menu[i].kategori.find(keyword) != string::npos) {
            string status = menu[i].tersedia ? "Tersedia" : "Habis";
            cout << setw(3) << i + 1 << setw(25) << menu[i].nama 
                 << "Rp " << fixed << setprecision(0) << setw(8) << menu[i].harga
                 << setw(10) << menu[i].stok << setw(8) << status 
                 << setw(15) << menu[i].kategori << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ditemukan menu dengan kata kunci tersebut.\n";
    }
    cout << "-----------------------------------------------------------\n";
}

// Detail menu
void lihatDetailMenu(MenuItem menu[], int jumlah) {
    int nomor;
    tampilkanMenu(menu, jumlah);
    cout << "Pilih nomor menu untuk melihat detail (1-" << jumlah << "): ";
    cin >> nomor;

    if (nomor < 1 || nomor > jumlah) {
        cout << "? Nomor menu tidak valid.\n";
        return;
    }

    nomor--; // Konversi ke index array
    cout << "\n========== DETAIL MENU ==========\n";
    cout << "Nama      : " << menu[nomor].nama << endl;
    cout << "Harga     : Rp " << fixed << setprecision(0) << menu[nomor].harga << endl;
    cout << "Kategori  : " << menu[nomor].kategori << endl;
    cout << "Stok      : " << menu[nomor].stok << endl;
    cout << "Status    : " << (menu[nomor].tersedia ? "Tersedia" : "Habis") << endl;
    cout << "Deskripsi : " << menu[nomor].deskripsi << endl;
    cout << "================================\n";
}

// Menukar dua elemen menu
void tukar(MenuItem &a, MenuItem &b) {
    MenuItem temp = a;
    a = b;
    b = temp;
}

// Mengurutkan menu berdasarkan harga (ascending)
void urutkanHarga(MenuItem menu[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (menu[j].harga > menu[j + 1].harga) {
                tukar(menu[j], menu[j + 1]);
            }
        }
    }
    cout << "? Menu berhasil diurutkan berdasarkan harga.\n";
    tampilkanMenu(menu, jumlah);
}

// Mengurutkan menu berdasarkan nama (A-Z)
void urutkanNama(MenuItem menu[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (menu[j].nama > menu[j + 1].nama) {
                tukar(menu[j], menu[j + 1]);
            }
        }
    }
    cout << "? Menu berhasil diurutkan berdasarkan nama.\n";
    tampilkanMenu(menu, jumlah);
}

// Statistik menu
void tampilkanStatistik(MenuItem menu[], int jumlah) {
    float totalHarga = 0;
    int totalStok = 0;
    int menuTersedia = 0;
    float hargaTertinggi = 0;
    float hargaTerendah = 999999;
    
    for (int i = 0; i < jumlah; i++) {
        totalHarga += menu[i].harga;
        totalStok += menu[i].stok;
        if (menu[i].tersedia) menuTersedia++;
        if (menu[i].harga > hargaTertinggi) hargaTertinggi = menu[i].harga;
        if (menu[i].harga < hargaTerendah) hargaTerendah = menu[i].harga;
    }
    
    cout << "\n========== STATISTIK MENU ==========\n";
    cout << "Total Menu        : " << jumlah << endl;
    cout << "Menu Tersedia     : " << menuTersedia << endl;
    cout << "Menu Habis        : " << (jumlah - menuTersedia) << endl;
    cout << "Total Stok        : " << totalStok << endl;
    cout << "Rata-rata Harga   : Rp " << fixed << setprecision(0) << (totalHarga / jumlah) << endl;
    cout << "Harga Tertinggi   : Rp " << fixed << setprecision(0) << hargaTertinggi << endl;
    cout << "Harga Terendah    : Rp " << fixed << setprecision(0) << hargaTerendah << endl;
    cout << "===================================\n";
}

// Menampilkan menu utama interaktif
void menuUtama(MenuItem menu[], int &jumlah) {
    int pilihan;
    do {
        cout << "\n========== SISTEM MANAJEMEN MENU CAFFE V-RAMA ==========\n";
        cout << "1.  Tampilkan Semua Menu\n";
        cout << "2.  Tampilkan Menu Berdasarkan Kategori\n";
        cout << "3.  Tambah Menu Baru\n";
        cout << "4.  Edit Menu\n";
        cout << "5.  Hapus Menu\n";
        cout << "6.  Cari Menu\n";
        cout << "7.  Lihat Detail Menu\n";
        cout << "8.  Urutkan Menu Berdasarkan Harga\n";
        cout << "9.  Urutkan Menu Berdasarkan Nama\n";
        cout << "10. Statistik Menu\n";
        cout << "11. Simpan ke File\n";
        cout << "12. Keluar\n";
        cout << "Pilih menu (1-12): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanMenu(menu, jumlah);
                break;
            case 2:
                tampilkanMenuKategori(menu, jumlah);
                break;
            case 3:
                tambahMenu(menu, jumlah);
                break;
            case 4:
                editMenu(menu, jumlah);
                break;
            case 5:
                hapusMenu(menu, jumlah);
                break;
            case 6:
                cariMenu(menu, jumlah);
                break;
            case 7:
                lihatDetailMenu(menu, jumlah);
                break;
            case 8:
                urutkanHarga(menu, jumlah);
                break;
            case 9:
                urutkanNama(menu, jumlah);
                break;
            case 10:
                tampilkanStatistik(menu, jumlah);
                break;
            case 11:
                simpanKeFile(menu, jumlah);
                break;
            case 12:
                cout << "Program selesai. Terima kasih telah menggunakan sistem kami!\n";
                break;
            default:
                cout << "? Pilihan tidak valid. Silakan coba lagi.\n";
        }

    } while (pilihan != 12);
}




void laporanTransaksiHarian() {
    cout << "\n===== Laporan Transaksi Harian =====\n";
    cout << "Total Meja Tersewa   : " << jumlahPesanan << "/" << MAX_MEJA << endl;
    cout << "Total Pendapatan     : Rp " << totalPendapatanHarian << endl;
    
    int tunai = 0, transfer = 0, qris = 0;
    for (int i = 0; i < MAX_MEJA; i++) {
        if (!daftarMeja[i].tersedia) {
            if (daftarMeja[i].metodePembayaran == "Tunai") tunai++;
            else if (daftarMeja[i].metodePembayaran == "Transfer") transfer++;
            else if (daftarMeja[i].metodePembayaran == "QRIS") qris++;
        }
    }
    
    cout << "Pembayaran Tunai     : " << tunai << " transaksi\n";
    cout << "Pembayaran Transfer  : " << transfer << " transaksi\n";
    cout << "Pembayaran QRIS      : " << qris << " transaksi\n";
    cout << "====================================\n";
}

void batalTransaksi() {
    int nomor;
    cout << "\n===== Batal Transaksi =====\n";
    cout << "Masukkan nomor meja yang ingin dibatalkan: ";
    cin >> nomor;

    if (nomor < 1 || nomor > MAX_MEJA) {
        cout << "Nomor meja tidak valid.\n";
        return;
    }

    if (daftarMeja[nomor - 1].tersedia) {
        cout << "Meja tersebut belum dipesan.\n";
        return;
    }

    totalPendapatanHarian -= daftarMeja[nomor - 1].totalBiaya;
    
    daftarMeja[nomor - 1].tersedia = true;
    daftarMeja[nomor - 1].namaPenyewa = "";
    daftarMeja[nomor - 1].durasi = 0;
    daftarMeja[nomor - 1].subtotal = 0;
    daftarMeja[nomor - 1].diskon = 0;
    daftarMeja[nomor - 1].pajak = 0;
    daftarMeja[nomor - 1].totalBiaya = 0;
    daftarMeja[nomor - 1].metodePembayaran = "-";
    daftarMeja[nomor - 1].jamMulai = 0;

    jumlahPesanan--;

    simpanDataKeFile();

    cout << "Transaksi meja nomor " << nomor << " telah dibatalkan.\n";
}

void tampilkanMenuAdmin() {
    cout << "\n======= MENU ADMIN =======\n";
    cout << "Harga sewa per jam: Rp " << hargaPerJam << endl;
    cout << "1. Tampilkan Semua Meja\n";
    cout << "2. Pesan Meja\n";
    cout << "3. Hapus Pesanan\n";
    cout << "4. Cari Meja Berdasarkan Nama Penyewa\n";
    cout << "5. Reset Semua Pesanan\n";
    cout << "6. Logout\n";
    cout << "=========================\n";
    cout << "Pilih menu (1-6): ";
}

void tampilkanMenuPengguna() {
    cout << "\n======= MENU PENGGUNA =======\n";
    cout << "Harga sewa per jam: Rp " << hargaPerJam << endl;
    cout << "1. Tampilkan Semua Meja\n";
    cout << "2. Pesan Meja\n";
    cout << "3. Logout\n";
    cout << "=============================\n";
    cout << "Pilih menu (1-3): ";
}

void hapusPesanan() {
    int nomor;
    cout << "\n===== Hapus Pesanan =====\n";
    cout << "Masukkan nomor meja yang ingin dibatalkan: ";
    cin >> nomor;

    if (nomor < 1 || nomor > MAX_MEJA) {
        cout << "Nomor meja tidak valid.\n";
        return;
    }

    if (daftarMeja[nomor - 1].tersedia) {
        cout << "Meja tersebut belum dipesan.\n";
        return;
    }

    totalPendapatanHarian -= daftarMeja[nomor - 1].totalBiaya;

    daftarMeja[nomor - 1].tersedia = true;
    daftarMeja[nomor - 1].namaPenyewa = "";
    daftarMeja[nomor - 1].durasi = 0;
    daftarMeja[nomor - 1].subtotal = 0;
    daftarMeja[nomor - 1].diskon = 0;
    daftarMeja[nomor - 1].pajak = 0;
    daftarMeja[nomor - 1].totalBiaya = 0;
    daftarMeja[nomor - 1].metodePembayaran = "-";
    daftarMeja[nomor - 1].jamMulai = 0;

    jumlahPesanan--;

    simpanDataKeFile();

    cout << "Pesanan meja nomor " << nomor << " telah dibatalkan.\n";
}

void cariMeja() {
    string nama;
    bool ditemukan = false;

    cout << "\n===== Cari Meja Berdasarkan Nama =====\n";
    cin.ignore();
    cout << "Masukkan nama penyewa: ";
    getline(cin, nama);
    string namaLower = toLowerCase(nama);

    for (int i = 0; i < MAX_MEJA; i++) {
        if (!daftarMeja[i].tersedia &&
            toLowerCase(daftarMeja[i].namaPenyewa) == namaLower) {
            cout << "Meja nomor " << daftarMeja[i].nomor
                 << " disewa oleh " << daftarMeja[i].namaPenyewa
                 << " selama " << daftarMeja[i].durasi
                 << " jam, total: Rp " << daftarMeja[i].totalBiaya
                 << ", metode: " << daftarMeja[i].metodePembayaran << ".\n";
            ditemukan = true;
        }
    }
    
    if (!ditemukan) {
        cout << "Tidak ada pesanan atas nama \"" << nama << "\".\n";
    }
}

void resetSemuaPesanan() {
    char konfirmasi;
    cout << "\n===== RESET SEMUA PESANAN =====\n";
    cout << "Apakah Anda yakin ingin menghapus semua data pesanan? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        inisialisasiMeja();
        totalPendapatanHarian = 0;
        simpanDataKeFile();
        cout << "Semua data pesanan berhasil direset.\n";
    } else {
        cout << "Reset dibatalkan.\n";
    }
}

bool login(string &role) {
    string username, password;
    cout << "===== LOGIN =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].username == username && daftarUser[i].password == password) {
            role = daftarUser[i].role;
            cout << "Login berhasil sebagai " << role << "!\n";
            return true;
        }
    }
    cout << "Login gagal, username atau password salah.\n";
    return false;
}

void pesanMakananMinuman() {
    MenuItem pesanan[100];
    int jumlahPesanan = 0;
    char lanjut;
    double totalBiaya = 0;
    
    do {
        tampilkanMenu(menu, MAKS_MENU);
        int nomor;
        int jumlah;
        
        cout << "Pilih nomor menu (1-" << MAKS_MENU << "): ";
        cin >> nomor;
        
        if (nomor < 1 || nomor > MAKS_MENU) {
            cout << "Nomor menu tidak valid.\n";
            continue;
        }
        
        nomor--; // Konversi ke index array
        
        if (!menu[nomor].tersedia) {
            cout << "Maaf, menu ini sedang tidak tersedia.\n";
            continue;
        }
        
        cout << "Jumlah pesanan: ";
        cin >> jumlah;
        
        if (jumlah > menu[nomor].stok) {
            cout << "Maaf, stok tidak mencukupi.\n";
            continue;
        }
        
        pesanan[jumlahPesanan] = menu[nomor];
        pesanan[jumlahPesanan].stok = jumlah;
        totalBiaya += menu[nomor].harga * jumlah;
        
        menu[nomor].stok -= jumlah;
        menu[nomor].tersedia = menu[nomor].stok > 0;
        
        jumlahPesanan++;
        
        cout << "Pesan menu lain? (y/n): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');
    
    // Tampilkan struk
    cout << "\n====== STRUK PEMESANAN ======\n";
    for (int i = 0; i < jumlahPesanan; i++) {
        cout << pesanan[i].nama << " x" << pesanan[i].stok 
             << " = Rp " << pesanan[i].harga * pesanan[i].stok << endl;
    }
    cout << "Total: Rp " << totalBiaya << endl;
    cout << "===========================\n";
}

void lihatEstimasiBiayaUsaha() {
    double biayaSewa = 5000000;  // Biaya sewa tempat per bulan
    double biayaListrik = 2000000;  // Estimasi biaya listrik per bulan
    double biayaAir = 500000;  // Estimasi biaya air per bulan
    double biayaKaryawan = 3000000;  // Gaji per karyawan
    int jumlahKaryawan = 5;  // Jumlah karyawan
    
    cout << "\n===== ESTIMASI BIAYA USAHA BULANAN =====\n";
    cout << "Biaya Sewa Tempat     : Rp " << biayaSewa << endl;
    cout << "Biaya Listrik         : Rp " << biayaListrik << endl;
    cout << "Biaya Air             : Rp " << biayaAir << endl;
    cout << "Biaya Gaji Karyawan   : Rp " << biayaKaryawan * jumlahKaryawan << endl;
    cout << "--------------------------------\n";
    double totalBiaya = biayaSewa + biayaListrik + biayaAir + (biayaKaryawan * jumlahKaryawan);
    cout << "Total Biaya Bulanan   : Rp " << totalBiaya << endl;
    cout << "Estimasi Biaya Harian : Rp " << totalBiaya / 30 << endl;
    cout << "=====================================\n";
}

int main() {
    string role;
    cout << "Masukkan harga sewa per jam: Rp ";
    cin >> hargaPerJam;

    loadDataDariFile();

    bool berhasilLogin = false;
    do {
        berhasilLogin = login(role);
    } while (!berhasilLogin);

    int pilihan;
    do {
        tampilkanMenuUtama();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: // Sewa Meja Billiard
                if (role == "admin") {
                    int pilihanAdmin;
                    do {
                        tampilkanMenuAdmin();
                        cin >> pilihanAdmin;
                        switch (pilihanAdmin) {
                            case 1:
                                tampilkanSemuaMeja();
                                break;
                            case 2:
                                pesanMeja();
                                break;
                            case 3:
                                hapusPesanan();
                                break;
                            case 4:
                                cariMeja();
                                break;
                            case 5:
                                resetSemuaPesanan();
                                break;
                            case 6:
                                cout << "Kembali ke menu utama...\n";
                                break;
                            default:
                                cout << "Pilihan tidak valid.\n";
                                break;
                        }
                    } while (pilihanAdmin != 6);
                } else {
                    int pilihanUser;
                    do {
                        tampilkanMenuPengguna();
                        cin >> pilihanUser;
                        switch (pilihanUser) {
                            case 1:
                                tampilkanSemuaMeja();
                                break;
                            case 2:
                                pesanMeja();
                                break;
                            case 3:
                                cout << "Kembali ke menu utama...\n";
                                break;
                            default:
                                cout << "Pilihan tidak valid.\n";
                                break;
                        }
                    } while (pilihanUser != 3);
                }
                break;
                
            case 2: // Pesan Makanan/Minuman
                pesanMakananMinuman();
                break;
                
            case 3: // Lihat Estimasi Biaya Usaha
                lihatEstimasiBiayaUsaha();
                break;
                
            case 4: // Laporan Transaksi Harian
                laporanTransaksiHarian();
                break;
                
            case 5: // Batal Transaksi
                batalTransaksi();
                break;
                
            case 6: // Keluar
                cout << "Terima kasih telah menggunakan sistem VRAMA BILLIARD!\n";
                break;
                
            default:
                cout << "Pilihan tidak valid. Silakan pilih 1-6.\n";
                break;
        }
        
        if (pilihan != 6) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (pilihan != 6);

    return 0;
}





