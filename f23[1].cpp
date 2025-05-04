#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Student {
    int roll;
    string name;
    char division;
    string address;
};
void addStudent() {
    Student s;
    ofstream fout("students.txt", ios::app);
    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Division: ";
    cin >> s.division;
    cin.ignore();
    cout << "Enter Address: ";
    getline(cin, s.address);
    fout << s.roll << '|' << s.name << '|' << s.division << '|' << s.address << '\n';
    fout.close();
    cout << "Student record added successfully.\n";
}
void displayStudent(int roll) {
    ifstream fin("students.txt");
    Student s;
    bool found = false;
    string line;
    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        s.roll = stoi(line.substr(0, pos1));
        if (s.roll == roll) {
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);
            s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            s.division = line[pos2 + 1];
            s.address = line.substr(pos3 + 1);
            cout << "\n--- Student Found ---\n";
            cout << "Roll Number: " << s.roll << "\n";
            cout << "Name: " << s.name << "\n";
            cout << "Division: " << s.division << "\n";
            cout << "Address: " << s.address << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with roll number " << roll << " not found.\n";
    }
    fin.close();
}
void deleteStudent(int roll) {
    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    Student s;
    bool deleted = false;
    string line;
    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        s.roll = stoi(line.substr(0, pos1));
        if (s.roll == roll) {
            deleted = true;
            continue; // skip this line
        }
        temp << line << '\n';
    }
    fin.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (deleted)
        cout << "Student with roll number " << roll << " deleted successfully.\n";
    else
        cout << "Student with roll number " << roll << " not found.\n";
}
int main() {
    int choice, roll;
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n2. Delete Student\n3. Display Student by Roll No\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            cout << "Enter Roll Number to delete: ";
            cin >> roll;
            deleteStudent(roll);
            break;
        case 3:
            cout << "Enter Roll Number to search: ";
            cin >> roll;
            displayStudent(roll);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
    return 0;
}