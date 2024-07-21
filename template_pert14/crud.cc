#include <iostream>
#include <mysql/mysql.h>
#include <sstream>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "cpp_crud_library";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db();
void tambah_buku(const string& judul, const string& penulis, int tahun, int jumlah);
void tampilkan_buku();
void ubah_buku(int id_buku, const string& judul, const string& penulis, int tahun, int jumlah);
void hapus_buku(int id_buku);
void pinjam_buku(int id_buku);
void kembalikan_buku(int id_buku);
void tambah_user(const string& username, const string& password, bool is_admin = false);
bool login_user(const string& username, const string& password);
bool login_admin(const string& username, const string& password);

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            cout << "Terhubung ke database dengan sukses." << endl;
        } else {
            cerr << "Koneksi gagal: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init gagal" << endl;
    }
    return conn;
}

void tambah_buku(const string& judul, const string& penulis, int tahun, int jumlah) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "INSERT INTO perpustakaan (title, author, year, copies) VALUES ('" << judul << "', '" << penulis << "', " << tahun << ", " << jumlah << ")";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "INSERT gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil ditambahkan." << endl;
        }
        mysql_close(conn);
    }
}

void tampilkan_buku() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM perpustakaan")) {
            cerr << "SELECT gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << ", Judul: " << row[1] << ", Penulis: " << row[2] << ", Tahun: " << row[3] << ", Jumlah: " << row[4] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void ubah_buku(int id_buku, const string& judul, const string& penulis, int tahun, int jumlah) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE perpustakaan SET title = '" << judul << "', author = '" << penulis << "', year = " << tahun << ", copies = " << jumlah << " WHERE id = " << id_buku;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil diubah." << endl;
        }
        mysql_close(conn);
    }
}

void hapus_buku(int id_buku) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM perpustakaan WHERE id = " << id_buku;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

void pinjam_buku(int id_buku) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE perpustakaan SET copies = copies - 1 WHERE id = " << id_buku << " AND copies > 0";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Pinjam gagal: " << mysql_error(conn) << endl;
        } else {
            if (mysql_affected_rows(conn) > 0) {
                cout << "Buku berhasil dipinjam." << endl;
            } else {
                cout << "Buku tidak tersedia untuk dipinjam." << endl;
            }
        }
        mysql_close(conn);
    }
}

void kembalikan_buku(int id_buku) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE perpustakaan SET copies = copies + 1 WHERE id = " << id_buku;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Kembalikan gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil dikembalikan." << endl;
        }
        mysql_close(conn);
    }
}

void tambah_user(const string& username, const string& password, bool is_admin) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        if (is_admin) {
            query << "INSERT INTO admins (username, password) VALUES ('" << username << "', '" << password << "')";
        } else {
            query << "INSERT INTO users (username, password) VALUES ('" << username << "', '" << password << "')";
        }
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Register user gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "User berhasil diregistrasi." << endl;
        }
        mysql_close(conn);
    }
}

bool login_user(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    bool login_success = false;
    if (conn) {
        stringstream query;
        query << "SELECT * FROM users WHERE username = '" << username << "' AND password = '" << password << "'";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Login gagal: " << mysql_error(conn) << endl;
        } else {
            MYSQL_RES* res = mysql_store_result(conn);
            if (res != nullptr && mysql_num_rows(res) > 0) {
                login_success = true;
                cout << "Login berhasil." << endl;
            } else {
                cout << "Username atau password salah." << endl;
            }
            mysql_free_result(res);
        }
        mysql_close(conn);
    }
    return login_success;
}

bool login_admin(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    bool login_success = false;
    if (conn) {
        stringstream query;
        query << "SELECT * FROM admins WHERE username = '" << username << "' AND password = '" << password << "'";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Login gagal: " << mysql_error(conn) << endl;
        } else {
            MYSQL_RES* res = mysql_store_result(conn);
            if (res != nullptr && mysql_num_rows(res) > 0) {
                login_success = true;
                cout << "Login berhasil." << endl;
            } else {
                cout << "Username atau password salah." << endl;
            }
            mysql_free_result(res);
        }
        mysql_close(conn);
    }
    return login_success;
}

int main() {
    while (true) {
        int role_choice;
        cout << "Masukan Pilihan : \n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> role_choice;

        if (role_choice == 3) {
            break;
        }

        if (role_choice == 1) {
            int reg_choice;
            cout << "Register sebagai:\n";
            cout << "1. Admin\n";
            cout << "2. User\n";
            cout << "Masukkan pilihan: ";
            cin >> reg_choice;

            string username, password;
            cout << "Masukkan username: ";
            cin >> username;
            cout << "Masukkan password: ";
            cin >> password;

            if (reg_choice == 1) {
                tambah_user(username, password, true);
            } else if (reg_choice == 2) {
                tambah_user(username, password, false);
            } else {
                cout << "Pilihan tidak valid." << endl;
            }

        } else if (role_choice == 2) {
            int login_choice;
            cout << "Login sebagai:\n";
            cout << "1. Admin\n";
            cout << "2. User\n";
            cout << "Masukkan pilihan: ";
            cin >> login_choice;

            string username, password;
            cout << "Masukkan username: ";
            cin >> username;
            cout << "Masukkan password: ";
            cin >> password;

            if (login_choice == 1) {
                if (login_admin(username, password)) {
                    // Admin Menu
                    while (true) {
                        int choice;
                        cout << "Menu Admin:\n";
                        cout << "1. Tambah Buku\n";
                        cout << "2. Tampilkan Buku\n";
                        cout << "3. Ubah Buku\n";
                        cout << "4. Hapus Buku\n";
                        cout << "5. Logout\n";
                        cout << "Masukkan pilihan: ";
                        cin >> choice;

                        if (choice == 1) {
                            string judul, penulis;
                            int tahun, jumlah;
                            cout << "Masukkan judul buku: ";
                            cin.ignore();
                            getline(cin, judul);
                            cout << "Masukkan penulis: ";
                            getline(cin, penulis);
                            cout << "Masukkan tahun terbit: ";
                            cin >> tahun;
                            cout << "Masukkan jumlah buku: ";
                            cin >> jumlah;
                            tambah_buku(judul, penulis, tahun, jumlah);
                        } else if (choice == 2) {
                            tampilkan_buku();
                        } else if (choice == 3) {
                            int id_buku;
                            string judul, penulis;
                            int tahun, jumlah;
                            cout << "Masukkan ID buku yang akan diubah: ";
                            cin >> id_buku;
                            cout << "Masukkan judul baru: ";
                            cin.ignore();
                            getline(cin, judul);
                            cout << "Masukkan penulis baru: ";
                            getline(cin, penulis);
                            cout << "Masukkan tahun terbit baru: ";
                            cin >> tahun;
                            cout << "Masukkan jumlah buku baru: ";
                            cin >> jumlah;
                            ubah_buku(id_buku, judul, penulis, tahun, jumlah);
                        } else if (choice == 4) {
                            int id_buku;
                            cout << "Masukkan ID buku yang akan dihapus: ";
                            cin >> id_buku;
                            hapus_buku(id_buku);
                        } else if (choice == 5) {
                            cout << "Logout berhasil." << endl;
                            break;
                        } else {
                            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                        }
                    }
                }

            } else if (login_choice == 2) {
                if (login_user(username, password)) {
                    // User Menu
                    while (true) {
                        int choice;
                        cout << "Menu User:\n";
                        cout << "1. Tampilkan Buku\n";
                        cout << "2. Pinjam Buku\n";
                        cout << "3. Kembalikan Buku\n";
                        cout << "4. Logout\n";
                        cout << "Masukkan pilihan: ";
                        cin >> choice;

                        if (choice == 1) {
                            tampilkan_buku();
                        } else if (choice == 2) {
                            int id_buku;
                            cout << "Masukkan ID buku yang akan dipinjam: ";
                            cin >> id_buku;
                            pinjam_buku(id_buku);
                        } else if (choice == 3) {
                            int id_buku;
                            cout << "Masukkan ID buku yang akan dikembalikan: ";
                            cin >> id_buku;
                            kembalikan_buku(id_buku);
                        } else if (choice == 4) {
                            cout << "Logout berhasil." << endl;
                            break;
                        } else {
                            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                        }
                    }
                }

            } else {
                cout << "Pilihan tidak valid." << endl;
            }

        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}
