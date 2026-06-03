#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

long long operasi = 0;

// Menampilkan array
void tampilkan(const vector<long long>& arr)
{
    for(long long x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
}

// Counting Sort untuk LSD Radix Sort
void countingSort(vector<long long>& arr, long long exp)
{
    int n = arr.size();

    vector<long long> output(n);
    int count[10] = {0};

    // Hitung frekuensi digit
    for(int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
        operasi++;
    }

    // Prefix Sum
    for(int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
        operasi++;
    }

    // Susun output
    for(int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        operasi++;
    }

    // Salin kembali
    for(int i = 0; i < n; i++)
    {
        arr[i] = output[i];
        operasi++;
    }
}

// LSD Radix Sort
void radixSortLSD(vector<long long>& arr)
{
    long long maxVal = *max_element(arr.begin(), arr.end());

    int pass = 1;

    for(long long exp = 1; maxVal / exp > 0; exp *= 10)
    {
        countingSort(arr, exp);

        // Visualisasi hanya jika data <= 20
        if(arr.size() <= 20)
        {
            cout << "\nPass " << pass
                 << " (Digit " << exp << ")\n";

            tampilkan(arr);
        }

        pass++;
    }
}

int main()
{
    int n;

    cout << "=====================================\n";
    cout << "SISTEM PENGURUTAN NIM MAHASISWA\n";
    cout << "LSD RADIX SORT\n";
    cout << "=====================================\n\n";

    cout << "Masukkan jumlah NIM: ";
    cin >> n;

    vector<long long> nim(n);

    cout << "\nMasukkan data NIM:\n";

    for(int i = 0; i < n; i++)
    {
        cout << "NIM ke-" << i + 1 << ": ";
        cin >> nim[i];
    }

    cout << "\nData Sebelum Sorting:\n";
    tampilkan(nim);

    auto start = chrono::high_resolution_clock::now();

    radixSortLSD(nim);

    auto stop = chrono::high_resolution_clock::now();

    auto duration =
    chrono::duration_cast<chrono::microseconds>
    (stop - start);

    cout << "\n=====================================\n";
    cout << "HASIL SORTING\n";
    cout << "=====================================\n";

    tampilkan(nim);

    cout << "\nJumlah Operasi : "
         << operasi << endl;

    cout << "Waktu Eksekusi : "
         << duration.count()
         << " microseconds\n";

    return 0;
}

