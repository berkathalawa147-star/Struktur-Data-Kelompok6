#include <iostream>
#include <vector>
#include <string>

using namespace std;

int ternarySearch(vector<string>& arr, string target)
{
    int left = 0;
    int right = arr.size() - 1;

    while(left <= right)
    {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        cout << "\n================================";
        cout << "\nLeft  = " << left;
        cout << "\nMid1  = " << mid1 << " (" << arr[mid1] << ")";
        cout << "\nMid2  = " << mid2 << " (" << arr[mid2] << ")";
        cout << "\nRight = " << right << endl;

        if(arr[mid1] == target)
            return mid1;

        if(arr[mid2] == target)
            return mid2;

        if(target < arr[mid1])
        {
            right = mid1 - 1;
        }
        else if(target > arr[mid2])
        {
            left = mid2 + 1;
        }
        else
        {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }

    return -1;
}

int main()
{
    vector<string> nim =
    {
        "231401001",
        "231401002",
        "231401003",
        "231401007",
        "231401010",
        "231401015",
        "231401020"
    };

    string cari;

    cout << "Masukkan NIM yang dicari : ";
    cin >> cari;

    int hasil = ternarySearch(nim,cari);

    if(hasil != -1)
    {
        cout << "\nNIM ditemukan pada indeks "
             << hasil << endl;
    }
    else
    {
        cout << "\nNIM tidak ditemukan" << endl;
    }
}
