#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Employee 
{
    int empID;
    char name[50];
    char designation[50];
    float salary;
};

void addEmployee();
void deleteEmployee();
void displayEmployee();

int main() 
{
    int choice;
    do {
        cout << "\n**Menu**\n1. Add Employee\n2. Delete Employee\n3. Display Employee\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); 
                    break;
            case 2: deleteEmployee(); 
                    break;
            case 3: displayEmployee(); 
                    break;
            case 4: cout << "Exiting..."; 
                    break;
            default: cout << "Invalid choice!";
        }
    } while (choice != 4);

    return 0;
}

void addEmployee() 
{
    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.empID;
    cin.ignore();  
    cout << "Enter Name: ";
    cin.getline(emp.name, 50);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 50);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    ofstream outFile("employees.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
}

void deleteEmployee() 
{
    int empID;
    cout << "Enter Employee ID to delete: ";
    cin >> empID;

    ifstream inFile("employees.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);
    Employee emp;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        if (emp.empID != empID) 
        {
            tempFile.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
        } 
        else 
        {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) 
    {
        remove("employees.dat");
        rename("temp.dat", "employees.dat");
        cout << "Employee deleted successfully.\n";
    } 
    else 
    {
        cout << "Employee not found!\n";
    }
}

void displayEmployee() 
{
    int empID;
    cout << "Enter Employee ID to display: ";
    cin >> empID;

    ifstream inFile("employees.dat", ios::binary);
    Employee emp;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) 
    {
        if (emp.empID == empID) 
        {
            cout << "\nEmployee ID: " << emp.empID
                 << "\nName: " << emp.name
                 << "\nDesignation: " << emp.designation
                 << "\nSalary: " << emp.salary << endl;
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) 
    {
        cout << "Employee not found!\n";
    }
}