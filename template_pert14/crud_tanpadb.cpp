#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct User {
    int id;
    string name;
    string nim;
    string asal_kampus;
    string jurusan;
    string fakultas;
};

vector<User> users;
int current_id = 1;

void create_user(const string& name, const string& nim, const string& asal_kampus, const string& jurusan, const string& fakultas) {
    User user = {current_id++, name, nim, asal_kampus, jurusan, fakultas};
    users.push_back(user);
    cout << "User successfully added." << endl;
}

void get_users() {
    if (users.empty()) {
        cout << "No users found." << endl;
        return;
    }

    for (const auto& user : users) {
        cout << "ID: " << user.id << ", Name: " << user.name << ", NIM: " << user.nim 
             << ", Asal Kampus: " << user.asal_kampus << ", Jurusan: " << user.jurusan 
             << ", Fakultas: " << user.fakultas << endl;
    }
}

void update_user(int user_id, const string& name, const string& nim, const string& asal_kampus, const string& jurusan, const string& fakultas) {
    for (auto& user : users) {
        if (user.id == user_id) {
            user.name = name;
            user.nim = nim;
            user.asal_kampus = asal_kampus;
            user.jurusan = jurusan;
            user.fakultas = fakultas;
            cout << "User successfully updated." << endl;
            return;
        }
    }
    cout << "User not found." << endl;
}

void delete_user(int user_id) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->id == user_id) {
            users.erase(it);
            cout << "User successfully deleted." << endl;
            return;
        }
    }
    cout << "User not found." << endl;
}

int main() {
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add User\n";
        cout << "2. Show All Users\n";
        cout << "3. Update User\n";
        cout << "4. Delete User\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, nim, asal_kampus, jurusan, fakultas;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter NIM: ";
            getline(cin, nim);
            cout << "Enter Asal Kampus: ";
            getline(cin, asal_kampus);
            cout << "Enter Jurusan: ";
            getline(cin, jurusan);
            cout << "Enter Fakultas: ";
            getline(cin, fakultas);
            create_user(name, nim, asal_kampus, jurusan, fakultas);
        } else if (choice == 2) {
            get_users();
        } else if (choice == 3) {
            int user_id;
            string name, nim, asal_kampus, jurusan, fakultas;
            cout << "Enter user ID to update: ";
            cin >> user_id;
            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, name);
            cout << "Enter new NIM: ";
            getline(cin, nim);
            cout << "Enter new Asal Kampus: ";
            getline(cin, asal_kampus);
            cout << "Enter new Jurusan: ";
            getline(cin, jurusan);
            cout << "Enter new Fakultas: ";
            getline(cin, fakultas);
            update_user(user_id, name, nim, asal_kampus, jurusan, fakultas);
        } else if (choice == 4) {
            int user_id;
            cout << "Enter user ID to delete: ";
            cin >> user_id;
            delete_user(user_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
