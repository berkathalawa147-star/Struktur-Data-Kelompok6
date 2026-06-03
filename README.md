**Implementasi dan Analisis Perbandingan LSD Radix Sort, MSD Radix Sort, dan Ternary Search pada Sistem Pengurutan dan Pencarian NIM Mahasiswa**

## Deskripsi Proyek
Proyek ini bertujuan untuk mengimplementasikan serta menganalisis performa algoritma LSD Radix Sort, MSD Radix Sort, dan Ternary Search dalam pengurutan dan pencarian data NIM mahasiswa.

## Teknologi/Compiler yang Digunakan

* Bahasa Pemrograman: C++
* IDE: Dev-C++
* Compiler: MinGW GCC (g++)
* Standar C++: C++11

## Struktur Folder

Struktur-Data-Kelompok6
│
├── Source_code/
├ │── main.cpp
├     │── LSDRadix.cpp
├     │── MSDRadix.cpp
├     │── TernarySearch.cpp
├ │─ README.compile.txt
│
├── Laporan/
│  └── Laporan_Kelompok 6.pdf
├── Slide/
│  └── Presentasi_Kelompok6.pptx
└── Readme.md


**Cara Compile**
g++ main.cpp LSDRadix.cpp MSDRadix.cpp TernarySearch.cpp -o program

## Fitur Program

* Pengurutan NIM menggunakan LSD Radix Sort
* Pengurutan NIM menggunakan MSD Radix Sort
* Pencarian NIM menggunakan Ternary Search
* Perhitungan jumlah operasi
* Pengukuran waktu eksekusi
* Analisis performa algoritma

## Pembagian Tugas

| Anggota   | Tugas                            |
| --------- | -------------------------------- |
| Anggota 1 | Lead Programmer & LSD Radix Sort |
| Anggota 2 | MSD Radix Sort                   |
| Anggota 3 | Ternary Search & Dataset         |
| Anggota 4 | Pengujian dan Analisis Hasil     |

## Dataset

Dataset yang digunakan berupa data NIM mahasiswa dalam format CSV yang digunakan untuk pengujian berbagai ukuran data seperti 100, 500, dan 1000 data.
