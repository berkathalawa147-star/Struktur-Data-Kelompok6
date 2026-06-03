#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// ============================================================================
// VARIABLE GLOBAL UNTUK ANALISIS PERFORMA 
// ============================================================================
long long operasi = 0; // Untuk mencatat operasi sorting & searching

// ============================================================================
// MODUL UTILITAS & TAMPILAN DATA 
// ============================================================================
void tampilkanArray(const vector<string>& arr) {
    for (const string& x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

// ============================================================================
// MODUL SORTING LSD - LEAST SIGNIFICANT DIGIT 
// ============================================================================
char getCharAtPositionLSD(const string& str, int pos) {
    int index = str.length() - 1 - pos;
    if (index >= 0) return str[index];
    return '0'; 
}

void countingSortLSD(vector<string>& arr, int position, bool verbose) {
    int n = arr.size();
    vector<string> output(n);
    int count[256] = {0}; 

    for (int i = 0; i < n; i++) {
        char ch = getCharAtPositionLSD(arr[i], position);
        count[(unsigned char)ch]++;
        operasi++;
    }

    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
        operasi++;
    }

    for (int i = n - 1; i >= 0; i--) {
        char ch = getCharAtPositionLSD(arr[i], position);
        output[count[(unsigned char)ch] - 1] = arr[i];
        count[(unsigned char)ch]--;
        operasi++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        operasi++;
    }
}

void radixSortLSD(vector<string>& arr, bool verbose) {
    if (arr.empty()) return;

    size_t maxLen = 0;
    for (const string& str : arr) {
        maxLen = max(maxLen, str.length());
        operasi++;
    }

    int pass = 1;
    for (int pos = 0; pos < (int)maxLen; pos++) {
        countingSortLSD(arr, pos, verbose);

        if (verbose && arr.size() <= 20) {
            cout << "\n[Trace LSD] Pass " << pass << " (Digit ke-" << pos + 1 << " dari kanan):\n";
            tampilkanArray(arr);
        }
        pass++;
    }
}

// ============================================================================
// MODUL SORTING MSD - MOST SIGNIFICANT DIGIT
// ============================================================================
int getCharIndexMSD(const string& str, int digit) {
    if (digit < (int)str.length()) {
        return (unsigned char)str[digit];
    }
    return 0; 
}

void msdRadixSortStep(vector<string>& arr, int left, int right, int digit, int maxLen, bool verbose) {
    if (left >= right || digit >= maxLen) {
        return;
    }

    vector<vector<string>> bucket(256);

    for (int i = left; i <= right; i++) {
        int chIdx = getCharIndexMSD(arr[i], digit);
        bucket[chIdx].push_back(arr[i]);
        operasi++;
    }

    int index = left;
    vector<pair<int, int>> nextRanges;

    for (int i = 0; i < 256; i++) {
        if (!bucket[i].empty()) {
            int start = index;
            for (const string& item : bucket[i]) {
                arr[index++] = item;
                operasi++;
            }
            int end = index - 1;
            
            if (start < end) {
                nextRanges.push_back({start, end});
            }
        }
    }

    if (verbose && arr.size() <= 20) {
        cout << "\n[Trace MSD] Digit ke-" << digit + 1 << " (Range indeks [" << left << ".." << right << "]):\n";
        tampilkanArray(arr);
    }

    for (auto r : nextRanges) {
        msdRadixSortStep(arr, r.first, r.second, digit + 1, maxLen, verbose);
    }
}

void radixSortMSD(vector<string>& arr, bool verbose) {
    if (arr.empty()) return;

    size_t maxLen = 0;
    for (const string& str : arr) {
        maxLen = max(maxLen, str.length());
        operasi++;
    }

    msdRadixSortStep(arr, 0, arr.size() - 1, 0, (int)maxLen, verbose);
}

// ============================================================================
// MODUL SEARCHING - TERNARY SEARCH (ANGGOTA 2)
// ============================================================================
int ternarySearch(const vector<string>& arr, const string& target) {
    int left = 0;
    int right = arr.size() - 1;
    int langkah = 0;

    while (left <= right) {
        langkah++;
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        cout << "\n[Search Langkah " << langkah << "]";
        cout << "\n   Left  = " << left;
        cout << "\n   Mid1  = " << mid1 << " (" << arr[mid1] << ")";
        cout << "\n   Mid2  = " << mid2 << " (" << arr[mid2] << ")";
        cout << "\n   Right = " << right << endl;

        operasi++;
        if (arr[mid1] == target) return mid1;

        operasi++;
        if (arr[mid2] == target) return mid2;

        if (target < arr[mid1]) {
            right = mid1 - 1;
        } else if (target > arr[mid2]) {
            left = mid2 + 1;
        } else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return -1;
}

// ============================================================================
// MODUL DATA, BENCHMARK & FILE HANDLING 
// ============================================================================
vector<string> datasetUtama;

void inputString() {
    int jumlahStr;
    cout << "Jumlah data string: ";
    cin >> jumlahStr;

    datasetUtama.clear();
    for (int i = 0; i < jumlahStr; i++) {
        string temp;
        cout << "Data ke-" << i + 1 << ": ";
        cin >> temp;
        datasetUtama.push_back(temp);
    }
    cout << "Data manual berhasil disimpan.\n";
}

void generateRandomInteger() {
    int jumlahInt;
    cout << "Jumlah data yang ingin dibuat acak: ";
    cin >> jumlahInt;

    datasetUtama.clear();
    srand(time(0));

    for (int i = 0; i < jumlahInt; i++) {
        // Generate angka acak 8 digit (simulasi NIM) dalam bentuk string
        string nimAcak = to_string(10000000 + rand() % 90000000);
        datasetUtama.push_back(nimAcak);
    }
    cout << "Data acak sebanyak " << jumlahInt << " berhasil dibuat.\n";
}

void bacaFileString() {
    string namaFile;
    cout << "Nama file teks input (misal: data.txt): ";
    cin >> namaFile;

    ifstream file(namaFile);
    if (!file) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    datasetUtama.clear();
    string temp;
    while (file >> temp) {
        datasetUtama.push_back(temp);
    }
    file.close();
    cout << datasetUtama.size() << " data berhasil dibaca dari file.\n";
} 

void bubbleSortString(vector<string> arr) {
    operasi = 0;
    
    // PROSES NORMALISASI: Otomatis merapikan spasi dan merubah NIM 7 digit jadi 8 digit berawalan '0'
    vector<string> clean_arr;
    for (string s : arr) {
        while(!s.empty() && isspace(s.back())) s.pop_back();
        while(!s.empty() && isspace(s.front())) s.erase(s.begin());

        if (!s.empty() && isdigit(s[0])) {
            while (s.length() < 8) {
                s = "0" + s;
            }
            clean_arr.push_back(s);
        }
    }
    
    int n = clean_arr.size();
    if (n == 0) {
        cout << "Error: Tidak ada data NIM yang valid untuk diurutkan!" << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            operasi++;
            if (clean_arr[j] > clean_arr[j + 1]) {
                swap(clean_arr[j], clean_arr[j + 1]);
                operasi++;
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\n==================================================" << endl;
    cout << "   HASIL SORTING (10 ELEMEN PERTAMA & TERAKHIR)" << endl;
    cout << "==================================================" << endl;
    
    cout << ">>> 10 Elemen Pertama (Indeks 0 - 9):" << endl;
    for (int k = 0; k < 10 && k < n; k++) {
        cout << "[" << k << "] " << clean_arr[k] << endl;
    }

    cout << "\n . . . [ DATA SISA " << (n > 20 ? n - 20 : 0) << " NIM DISEMBUNYIKAN ] . . .\n" << endl;

    cout << ">>> 10 Elemen Terakhir (Indeks " << (n - 10 < 0 ? 0 : n - 10) << " - " << n - 1 << "):" << endl;
    int indeksMulai = (n - 10 < 0) ? 0 : n - 10;
    for (int k = indeksMulai; k < n; k++) {
        cout << "[" << k << "] " << clean_arr[k] << endl;
    }
    cout << "==================================================" << endl;

    cout << "       STATISTIK EKSPERIMEN BUBBLE SORT" << endl;
    cout << "==================================================" << endl;
    cout << "Waktu Eksekusi : " << duration.count() << " microseconds" << endl;
    cout << "Jumlah Operasi : " << operasi << " kali operasi aktual" << endl;
    cout << "==================================================" << endl;
}

void exportCSVString(const string& namaFile, const vector<string>& arr) {
    ofstream file(namaFile);
    file << "No,Data\n";
    for (size_t i = 0; i < arr.size(); i++) {
        file << i + 1 << "," << arr[i] << "\n";
    }
    file.close();
    cout << namaFile << " berhasil dibuat.\n";
}

// ============================================================================
// MENU UTAMA PROGRAM INTERAKTIF
// ============================================================================
int main() {
    int pilih;

    do {
        cout << "\n=============================================\n";
        cout << "   SISTEM GABUNGAN SORTING & SEARCHING KELOMPOK\n";
        cout << "=============================================\n";
        cout << "1. Input Data Manual (String/NIM)\n";
        cout << "2. Generate Data Angka/NIM Acak\n";
        cout << "3. Baca Data dari File (.txt)\n";
        cout << "4. Tampilkan Data Saat Ini\n";
        cout << "5. Uji Eksperimen Radix Sort LSD\n";
        cout << "6. Uji Eksperimen Radix Sort MSD\n";
        cout << "7. Jalankan Bubble Sort (Pembanding)\n";
        cout << "8. Cari Data (Ternary Search)\n";
        cout << "9. Export Hasil Data ke CSV\n";
        cout << "0. Keluar\n";
        cout << "---------------------------------------------\n";
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {
        case 1:
            inputString();
            break;
        case 2:
            generateRandomInteger();
            break;
        case 3:
            bacaFileString();
            break;
        case 4:
            if (datasetUtama.empty()) {
                cout << "Memori kosong! Silakan isi data dulu.\n";
            } else {
                cout << "\n--- Isi Data Teratas (Maksimal 20 data) ---\n";
                for (size_t i = 0; i < min(datasetUtama.size(), (size_t)20); i++) {
                    cout << datasetUtama[i] << " ";
                }
                cout << "\nTotal data dalam sistem: " << datasetUtama.size() << "\n";
            }
            break;
        case 5: {
            if (datasetUtama.empty()) {
                cout << "Tidak ada data untuk disort!\n";
                break;
            }
            vector<string> dataLSD = datasetUtama;
            operasi = 0;
            bool verbose = (dataLSD.size() <= 20);

            cout << "\n--- Menjalankan LSD Radix Sort ---";
            auto start = high_resolution_clock::now();
            radixSortLSD(dataLSD, verbose);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            cout << "\n\n[Hasil Akhir Terurut LSD]:\n";
            tampilkanArray(dataLSD);
            cout << "\nJumlah Operasi : " << operasi << " kali\n";
            cout << "Waktu Eksekusi : " << duration.count() << " microseconds\n";
            
            datasetUtama = dataLSD; // Simpan hasil agar bisa dipakai mencari data
            break;
        }
        case 6: {
            if (datasetUtama.empty()) {
                cout << "Tidak ada data untuk disort!\n";
                break;
            }
            vector<string> dataMSD = datasetUtama;
            operasi = 0;
            bool verbose = (dataMSD.size() <= 20);

            cout << "\n--- Menjalankan MSD Radix Sort ---";
            auto start = high_resolution_clock::now();
            radixSortMSD(dataMSD, verbose);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            cout << "\n\n[Hasil Akhir Terurut MSD]:\n";
            tampilkanArray(dataMSD);
            cout << "\nJumlah Operasi : " << operasi << " kali\n";
            cout << "Waktu Eksekusi : " << duration.count() << " microseconds\n";

            datasetUtama = dataMSD; // Simpan hasil agar bisa dipakai mencari data
            break;
        }
        case 7:
            if (datasetUtama.empty()) {
                cout << "Tidak ada data untuk disort!\n";
            } else {
                bubbleSortString(datasetUtama);
            }
            break;
        case 8: {
            if (datasetUtama.empty()) {
                cout << "Isi data dan urutkan terlebih dahulu menggunakan Radix Sort!\n";
                break;
            }
            string cari;
            cout << "Masukkan NIM/Data yang dicari: ";
            cin >> cari;

            operasi = 0;
            int hasil = ternarySearch(datasetUtama, cari);

            if (hasil != -1) {
                cout << "\n[Sukses] Data ditemukan pada indeks ke- " << hasil << endl;
            } else {
                cout << "\n[Gagal] Data tidak ditemukan dalam sistem.\n";
            }
            cout << "Total Operasi Komparasi: " << operasi << " kali\n";
            break;
        }
        case 9:
            if (datasetUtama.empty()) {
                cout << "Tidak ada data yang bisa diekspor!\n";
            } else {
                exportCSVString("hasil_output_kelompok.csv", datasetUtama);
            }
            break;
        }
    } while (pilih != 0);

    return 0;
}
