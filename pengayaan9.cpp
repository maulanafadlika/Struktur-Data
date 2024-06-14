#include <iostream>
#include <stack>
#include <string>
#include <limits> // Tambahkan header ini

using namespace std;

void clearScreen() 
{
    // Membersihkan layar tergantung pada sistem operasi
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tambahBuku(stack<string>& tumpukanBuku) 
{
    string buku;
    cout << "Masukkan nama buku yang akan ditambahkan (boleh mengandung huruf dan angka): ";
    getline(cin, buku);
    tumpukanBuku.push(buku);
    cout << buku << " telah ditambahkan ke tumpukan." << endl;
}

void ambilBuku(stack<string>& tumpukanBuku) 
{
    if (!tumpukanBuku.empty()) 
    {
        cout << tumpukanBuku.top() << " telah diambil dari tumpukan." << endl;
        tumpukanBuku.pop();
    } 
    else 
    {
        cout << "Tumpukan kosong" << endl;
    }
}

void lihatBukuPalingAtas(const stack<string>& tumpukanBuku) 
{
    if (!tumpukanBuku.empty()) 
    {
        cout << "Buku paling atas: " << tumpukanBuku.top() << endl;
    } 
    else 
    {
        cout << "Tumpukan kosong" << endl;
    }
}

void cekApakahTumpukanKosong(const stack<string>& tumpukanBuku) 
{
    if (tumpukanBuku.empty()) 
    {
        cout << "Tumpukan kosong" << endl;
    } 
    else 
    {
        cout << "Tumpukan tidak kosong" << endl;
    }
}

void lihatJumlahBuku(const stack<string>& tumpukanBuku) 
{
    cout << "Jumlah buku dalam tumpukan: " << tumpukanBuku.size() << endl;
}

int main() 
{
    stack<string> tumpukanBuku;
    int pilihan;
    bool keluar = false;

    while (!keluar) 
    {
        clearScreen(); // Bersihkan layar sebelum menampilkan menu
        cout << "Menu Operasi Tumpukan Buku:" << endl;
        cout << "1. Tambah Buku (push)" << endl;
        cout << "2. Ambil Buku (pop)" << endl;
        cout << "3. Lihat Buku Paling Atas (peek)" << endl;
        cout << "4. Cek Apakah Tumpukan Kosong (isEmpty)" << endl;
        cout << "5. Lihat Jumlah Buku dalam Tumpukan (size)" << endl;
        cout << "6. Keluar (exit)" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        if(cin.fail()) 
        {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            cout << "Pilihan tidak valid. Silakan masukkan angka antara 1 dan 6." << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            continue; // Kembali ke menu
        }

        cin.ignore(); // Mengabaikan karakter newline setelah input pilihan

        switch (pilihan) 
        {
            case 1:
                tambahBuku(tumpukanBuku);
                break;
            case 2:
                ambilBuku(tumpukanBuku);
                break;
            case 3:
                lihatBukuPalingAtas(tumpukanBuku);
                break;
            case 4:
                cekApakahTumpukanKosong(tumpukanBuku);
                break;
            case 5:
                lihatJumlahBuku(tumpukanBuku);
                break;
            case 6:
                keluar = true;
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan masukkan angka antara 1 dan 6." << endl;
        }

        if (!keluar) 
        {
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
        }
    }

    return 0;
}
