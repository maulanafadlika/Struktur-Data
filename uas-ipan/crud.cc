#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <limits>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "warkop";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            cout << "Connected to the database successfully." << endl;
        } else {
            cerr << "Connection failed: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init failed" << endl;
    }
    return conn;
}

void create_user(const string& nama, int harga, const string& kategori, const string& merek, int stok) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "INSERT INTO warkop_nalgat (nama, kategori, merek, harga, stok) VALUES ('" << nama << "', '" << kategori << "', '" << merek << "', " << harga << ", " << stok << ")";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "INSERT failed: " << mysql_error(conn) << endl;
        } else {
            cout << "User successfully added." << endl;
        }
        mysql_close(conn);
    }
}

void get_users() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM warkop_nalgat")) {
            cerr << "SELECT failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << ", Nama: " << row[1] << ", Kategori: " << row[2] << ", Merek: " << row[3] << ", Harga: " << row[4] << ", Stok: " << row[5] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void update_user(int user_id, const string& nama, const string& kategori, const string& merek, int harga, int stok) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE warkop_nalgat SET nama = '" << nama << "', kategori = '" << kategori << "', merek = '" << merek << "', harga = " << harga << ", stok = " << stok << " WHERE id = " << user_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE failed: " << mysql_error(conn) << endl;
        } else {
            cout << "User successfully updated." << endl;
        }
        mysql_close(conn);
    }
}

void delete_user(int user_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM warkop_nalgat WHERE id = " << user_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE failed: " << mysql_error(conn) << endl;
        } else {
            cout << "User successfully deleted." << endl;
        }
        mysql_close(conn);
    }
}

bool admin_login() {
    const int MAX_ATTEMPTS = 3;
    string password;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        cout << "Enter admin password: ";
        cin >> password;
        if (password == "12345") {
            return true; // Password correct
        } else {
            cout << "Incorrect password. Try again." << endl;
            attempts++;
        }
    }
    
    cout << "Too many failed attempts. Exiting program." << endl;
    return false; // Too many failed attempts
}

void tampilan() {
    int choice;
    bool is_admin = false;

    // Login sebagai admin jika password cocok
    if (admin_login()) {
        is_admin = true;
    } else {
        // Jika tidak berhasil login sebagai admin, keluar dari program
        return;// Exit code 1 untuk menunjukkan kesalahan
    }

    while (true) {
        cout << "====================================\n";
        cout << RED << "Warkop Nalagati Uhuuuuyyyyy\n" << RESET;
        cout << "====================================\n";
        cout << "\nMenu:\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Semua Produk\n";
        cout << "3. Update Produk\n";
        cout << "4. Delete Produk\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (is_admin) {
                string nama, kategori, merek;
                int harga,stok;
                cout << "Enter Nama Produk: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Enter Kategori: ";
                getline(cin, kategori);
                cout << "Enter Merek: ";
                getline(cin, merek);
                cout << "Enter Harga: ";
                cin >> harga;
                cout << "Enter Stok: ";
                cin >> stok;
                
                create_user(nama, harga, kategori, merek,stok);
            } else {
                cout << "Permission denied. You can only view data." << endl;
            }
        } else if (choice == 2) {
            get_users();
        } else if (choice == 3) {
            if (is_admin) {
                int user_id, harga,stok;
                string nama, kategori, merek;
                cout << "Enter user ID to update: ";
                cin >> user_id;
                cin.ignore();
                cout << "Enter new Nama Produk: ";
                getline(cin, nama);
                cout << "Enter new Kategori: ";
                getline(cin, kategori);
                cout << "Enter new Merek: ";
                getline(cin, merek);
                cout << "Enter new Harga: ";
                cin >> harga;
                cout << "Enter Stok: ";
                cin >> stok;

                update_user(user_id, nama, kategori, merek, harga,stok);
            } else {
                cout << "Permission denied. You can only view data." << endl;
            }
        } else if (choice == 4) {
            if (is_admin) {
                int user_id;
                cout << "Enter user ID to delete: ";
                cin >> user_id;
                delete_user(user_id);
            } else {
                cout << "Permission denied. You can only view data." << endl;
            }
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return ;
}

void show_user(){
    while (true)
    {  
    int choice;
    cout <<"1. Lihat Produk " << endl;
    cout <<"2. exit";
    cin >> choice;

    if (choice == 1){
        get_users();
    }
    else if (choice == 2){
        break;
    }
    else{
        cout << "masukan sesuai menu";
    }    
   }
    
}

int main(){
    while (true){   
    int pilihan;
    cout << "1. Admin" << endl;
    cout << "2. User" << endl;
    cout << "silahkan pilih : ";
    cin >> pilihan;

    if (pilihan == 1){
        tampilan();
        break;
    }
    else if (pilihan == 2){
        show_user();
        break;
    }
    
    }
   
}