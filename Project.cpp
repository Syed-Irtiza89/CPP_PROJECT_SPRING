#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include "LibrarySystem.h"

using namespace std;

// Function for colorful text output (Visual Excellence)
void printHeader(string text) {
    cout << "\n========================================\n";
    cout << "   " << text << "\n";
    cout << "========================================\n";
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int readInt() {
    int v;
    while (!(cin >> v)) {
        cout << "Err: Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return v;
}

void wait() {
    cout << "\nPress Enter to continue...";
    cin.ignore(100, '\n');
    string dummy;
    getline(cin, dummy);
}

// LIBRARIAN Portal
void librarianMenu(LibrarySystem& sys) {
    Librarian* lib = dynamic_cast<Librarian*>(sys.getUser());
    int opt;
    while (true) {
        clear();
        printHeader("LIBRARIAN PORTAL : " + lib->getName());
        cout << "1. Add New Book Record\n";
        cout << "2. Add New E-Book\n";
        cout << "3. View All Records\n";
        cout << "4. Collect Fines\n";
        cout << "5. Check My Salary Info\n";
        cout << "6. Generate Library Report\n";
        cout << "7. Logout\n";
        cout << "Choice: ";
        opt = readInt();

        if (opt == 7) break;

        if (opt == 1 || opt == 2) {
            int id; string n, a, t; double p;
            cout << "ID: "; id = readInt();
            cout << "Title: "; cin.ignore(); getline(cin, n);
            cout << "Author: "; getline(cin, a);
            cout << "Topic: "; getline(cin, t);
            cout << "Price: "; cin >> p;

            if (opt == 1) {
                sys.addBook(new Book(id, n, a, t, "1st", "Gen Pub", p));
            } else {
                string link;
                cout << "Download Link: "; cin >> link;
                sys.addBook(new EBook(id, n, a, t, link, (p > 0), p));
            }
            cout << "Success! Item recorded.\n";
            wait();
        } else if (opt == 3) {
            sys.displayAllBooks();
            wait();
        } else if (opt == 4) {
            double amt;
            cout << "Amount to collect: "; cin >> amt;
            lib->collectionFine(amt);
            wait();
        } else if (opt == 5) {
            lib->checkSalary();
            wait();
        } else if (opt == 6) {
            sys.report();
            lib->generateReport();
            wait();
        }
    }
}

// STUDENT Portal
void studentMenu(LibrarySystem& sys) {
    Student* stu = dynamic_cast<Student*>(sys.getUser());
    int opt;
    while (true) {
        clear();
        printHeader("STUDENT DASHBOARD : " + stu->getName());
        cout << "1. View Catalog\n";
        cout << "2. Issue a Book\n";
        cout << "3. Return a Book\n";
        cout << "4. My Profile & Fines\n";
        cout << "5. E-Book Payment & Access\n";
        cout << "6. Logout\n";
        cout << "Choice: ";
        opt = readInt();

        if (opt == 6) break;

        if (opt == 1) {
            sys.displayAllBooks();
            wait();
        } else if (opt == 2) {
            int bid;
            cout << "Enter Book ID to issue: "; bid = readInt();
            if (sys.issue(bid, stu->getId())) cout << "Success! Book issued.\n";
            else cout << "Err: Not available or limit reached.\n";
            wait();
        } else if (opt == 3) {
            int bid;
            cout << "Enter Book ID to return: "; bid = readInt();
            if (sys.returnItem(bid, stu->getId())) cout << "Success! Item back in library.\n";
            else cout << "Err: Transaction not found.\n";
            wait();
        } else if (opt == 4) {
            stu->display();
            wait();
        } else if (opt == 5) {
            cout << "Processing digital collection access...\n";
            wait();
        }
    }
}

int main() {
    LibrarySystem sys;
    int choice;

    while (true) {
        clear();
        printHeader("VIRTUAL LIBRARY MANAGEMENT SYSTEM");
        cout << "1. Login Portal\n";
        cout << "2. Create Student Account\n";
        cout << "3. Exit System\n";
        cout << "Choice: ";
        choice = readInt();

        if (choice == 3) break;

        if (choice == 1) {
            int id, roleOpt;
            string p, role;
            cout << "Select Portal: (1. Student, 2. Librarian): ";
            roleOpt = readInt();
            role = (roleOpt == 1) ? "Student" : "Librarian";

            cout << "Enter ID: "; id = readInt();
            cout << "Enter Password: "; cin >> p;

            if (sys.login(id, p, role)) {
                if (role == "Student") studentMenu(sys);
                else librarianMenu(sys);
                sys.logout();
            } else {
                cout << "Invalid Credentials!\n";
                wait();
            }
        } else if (choice == 2) {
            int id; string n, p, ed, c, add, e, num;
            cout << "Pick ID Number: "; id = readInt();
            cout << "Full Name: "; cin.ignore(); getline(cin, n);
            cout << "Password: "; getline(cin, p);
            cout << "Education: "; getline(cin, ed);
            cout << "CNIC: "; getline(cin, c);
            cout << "Address: "; getline(cin, add);
            cout << "Email: "; getline(cin, e);
            cout << "Phone No: "; getline(cin, num);

            if (sys.registerStudent(id, n, p, ed, c, add, e, num)) {
                cout << "Account Created! Please login.\n";
            } else {
                cout << "Error: ID already taken.\n";
            }
            wait();
        }
    }

    cout << "Shutting down... Data saved successfully.\n";
    return 0;
}
