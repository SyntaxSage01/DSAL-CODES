#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Employee {
    int empID;
    char name[50], designation[50];
    float salary;
    bool isDeleted = false;
};
struct Index {
    int empID;
    long pos;
};
void addEmployee() {
    Employee e;
    Index idx;
    cout << "Enter Employee ID: ";
    cin >> e.empID;
    cin.ignore();
    cout << "Enter Name: "; cin.getline(e.name, 50);
    cout << "Enter Designation: "; cin.getline(e.designation, 50);
    cout << "Enter Salary: "; cin >> e.salary;
    ofstream empFile("employee.dat", ios::binary | ios::app);
    ofstream idxFile("index.dat", ios::binary | ios::app);
    idx.empID = e.empID;
    idx.pos = empFile.tellp();
    empFile.write((char*)&e, sizeof(e));
    idxFile.write((char*)&idx, sizeof(idx));
    cout << "Employee record added successfully.\n";
}
void displayEmployee() {
    int id; bool found = false;
    cout << "Enter Employee ID to search: "; cin >> id;
    ifstream empFile("employee.dat", ios::binary);
    ifstream idxFile("index.dat", ios::binary);
    Index idx; Employee e;
    while (idxFile.read((char*)&idx, sizeof(idx))) {
        if (idx.empID == id) {
            empFile.seekg(idx.pos);
            empFile.read((char*)&e, sizeof(e));
            if (!e.isDeleted) {
                cout << "\n--- Employee Details ---\n";
                cout << "Employee ID: " << e.empID << "\nName: " << e.name
                     << "\nDesignation: " << e.designation << "\nSalary: " << e.salary << "\n";
            } else cout << "Employee record is deleted.\n";
            found = true; break;
        }
    }
    if (!found) cout << "Employee not found.\n";
}
void deleteEmployee() {
    int id; bool found = false;
    cout << "Enter Employee ID to delete: "; cin >> id;
    fstream empFile("employee.dat", ios::binary | ios::in | ios::out);
    ifstream idxFile("index.dat", ios::binary);
    Index idx; Employee e;
    while (idxFile.read((char*)&idx, sizeof(idx))) {
        if (idx.empID == id) {
            empFile.seekg(idx.pos); empFile.read((char*)&e, sizeof(e));
            if (!e.isDeleted) {
                e.isDeleted = true;
                empFile.seekp(idx.pos); empFile.write((char*)&e, sizeof(e));
                cout << "Employee record deleted successfully.\n";
            } else cout << "Employee already deleted.\n";
            found = true; break;
        }
    }
    if (!found) cout << "Employee not found.\n";
}
int main() {
    int ch;
    do {
        cout << "\n--- Company Employee System ---\n";
        cout << "1. Add Employee\n2. Delete Employee\n3. Display Employee by ID\n4. Exit\nEnter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1: addEmployee(); break;
            case 2: deleteEmployee(); break;
            case 3: displayEmployee(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (ch != 4);
    return 0;
}