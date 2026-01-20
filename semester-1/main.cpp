#include <iostream>
#include <fstream>
using namespace std;

class User {
protected:
    string name;
    int id;
public:
    void setUser(string n, int i) {
        name = n;
        id = i;
    }

    virtual void viewDashboard() {
        cout << "Generic user dashboard.\n";
    }

    virtual void saveToFile() {
        ofstream fout("users.txt", ios::app);
        fout << "User," << name << "," << id << endl;
        fout.close();
    }
};

class Student : public User {

public:
    void viewDashboard() override {
        cout << "\n📚 Student Dashboard\n";
        cout << "Name: " << name << ", ID: " << id << "\n";
        cout << "You can view and register for courses.\n";
    }

    void saveToFile() override {
        ofstream fout("users.txt", ios::app);
        fout << "Student," << name << "," << id << endl;
        fout.close();
    }
};

class Teacher : public User {
public:
    void viewDashboard() override {
        cout << "\n🧑‍🏫 Teacher Dashboard\n";
        cout << "Name: " << name << ", ID: " << id << "\n";
        cout << "You can manage courses and upload marks.\n";
    }

    void saveToFile() override {
        ofstream fout("users.txt", ios::app);
        fout << "Teacher," << name << "," << id << endl;
        fout.close();
    }
};

class Admin : public User {
public:
    void viewDashboard() override {
        cout << "\n🛠️ Admin Dashboard\n";
        cout << "Name: " << name << ", ID: " << id << "\n";
        cout << "You can add/edit/remove courses and faculty.\n";
    }

    void saveToFile() override {
        ofstream fout("users.txt", ios::app);
        fout << "Admin," << name << "," << id << endl;
        fout.close();
    }
};

void showAllUsers() {
    ifstream fin("users.txt");
    string line;
    cout << "\n=== All Users ===\n";
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

int main() {
    int choice;
    User* user = nullptr;

    cout << "=== University Course Management System ===\n";
    cout << "1. Student\n2. Teacher\n3. Admin\n4. View All Users\nEnter choice: ";
    cin >> choice;

    if (choice >= 1 && choice <= 3) {
        string uname;
        int uid;
        cout << "Enter Name: ";
        getline(cin, uname);
        cout << "Enter ID: ";
        cin >> uid;

        if (choice == 1) user = new Student();
        else if (choice == 2) user = new Teacher();
        else user = new Admin();

        user->setUser(uname, uid);
        user->viewDashboard();
        user->saveToFile();
        delete user;
    } else if (choice == 4) {
        showAllUsers();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
};