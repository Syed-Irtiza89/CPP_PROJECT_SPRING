#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

#include "Book.h"
#include "Person.h"
#include "Transaction.h"
#include "ListManager.h"

using namespace std;

// Main System Class - Demonstrates Aggregation and Exception Handling
class LibrarySystem {
private:
    ListManager<Book> bookList;     
    ListManager<Person> userList;   
    vector<Transaction> history;    
    Person* currentUser;            

    vector<string> split(const string& str, char d) {
        vector<string> res;
        string t;
        istringstream s(str);
        while (getline(s, t, d)) res.push_back(t);
        return res;
    }

public:
    LibrarySystem() : currentUser(nullptr) {
        try {
            loadAllData();
        } catch (...) {
            cout << "Notice: Library records initialized.\n";
        }
    }

    ~LibrarySystem() {
        saveAllData();
    }

    // Login Portal Logic
    bool login(int id, string pass, string role) {
        Person* p = userList.getById(id);
        if (p) {
            if (role == "Librarian") {
                Librarian* lib = dynamic_cast<Librarian*>(p);
                if (lib && lib->getPassword() == pass) {
                    currentUser = p;
                    return true;
                }
            } else {
                Student* stu = dynamic_cast<Student*>(p);
                if (stu && stu->getPassword() == pass) {
                    currentUser = p;
                    return true;
                }
            }
        }
        return false;
    }

    void logout() { currentUser = nullptr; }
    Person* getUser() { return currentUser; }

    // Student Functions
    bool registerStudent(int id, string n, string p, string ed, string c, string add, string e, string num) {
        if (userList.getById(id)) return false;
        userList.add(new Student(id, n, p, ed, c, add, e, num));
        return true;
    }

    // Function Overloading 
    Book* searchBy(int id) {
        for (int i = 0; i < bookList.size(); i++) {
            if (bookList.getAll()[i]->getBookId() == id) return bookList.getAll()[i];
        }
        return nullptr;
    }

    Book* searchBy(string name) {
        for (int i = 0; i < bookList.size(); i++) {
            if (bookList.getAll()[i]->getBookName() == name) return bookList.getAll()[i];
        }
        return nullptr;
    }

    // Book Management
    bool addBook(Book* b) {
        if (searchBy(b->getBookId())) return false;
        bookList.add(b);
        return true;
    }

    void sellBook(int id) {
        Book* b = searchBy(id);
        if (b) b->bookSold();
        else cout << "Error: Book ID invalid.\n";
    }

    void displayAllBooks() {
        cout << "\n--- Library Catalog ---\n";
        cout << left << setw(15) << "Type" << setw(5) << "ID" << setw(20) << "Title" << setw(15) << "Author" << setw(8) << "Price" << "Status" << endl;
        cout << string(80, '-') << endl;
        for (int i = 0; i < bookList.size(); i++) {
            bookList.getAll()[i]->display();
        }
    }

    // Transaction Logic
    bool issue(int bId, int sId) {
        Book* b = searchBy(bId);
        Person* p = userList.getById(sId);
        Student* s = dynamic_cast<Student*>(p);

        if (b && s && b->checkAvailability() && s->checkLimit()) {
            b->issueBook();
            s->issueBook();
            int tId = history.size() + 500;
            history.push_back(Transaction(tId, bId, sId, time(0)));
            return true;
        }
        return false;
    }

    bool returnItem(int bId, int sId) {
        for (int i = 0; i < history.size(); i++) {
            if (history[i].getBookId() == bId && history[i].getStudentId() == sId && !history[i].checkDone()) {
                time_t now = time(0);
                history[i].returnTransaction(now);
                
                Book* b = searchBy(bId);
                if (b) b->returnBook();
                
                Student* s = dynamic_cast<Student*>(userList.getById(sId));
                if (s) {
                    s->returnBook();
                    double fine = history[i].calculate();
                    if (fine > 0) {
                        s->addFine(fine);
                        cout << "Fine calculated: $" << fine << " added to Profile.\n";
                    }
                }
                return true;
            }
        }
        return false;
    }

    // Librarian Functions
    void report() {
        cout << "\n--- Full Library Record Report ---\n";
        cout << "Physical Books: " << bookList.size() << endl;
        cout << "System Members: " << userList.size() << endl;
        cout << "Active History: " << history.size() << endl;
    }

    void saveAllData() {
        ofstream f1("books.dat");
        if (f1.is_open()) {
            for (int i = 0; i < bookList.size(); i++) f1 << bookList.getAll()[i]->toFileLine() << "\n";
        }
        f1.close();

        ofstream f2("users.dat");
        if (f2.is_open()) {
            for (int i = 0; i < userList.size(); i++) {
                Librarian* l = dynamic_cast<Librarian*>(userList.getAll()[i]);
                Student* s = dynamic_cast<Student*>(userList.getAll()[i]);
                if (l) f2 << l->toFileLine() << "\n";
                else if (s) f2 << s->toFileLine() << "\n";
            }
        }
        f2.close();

        ofstream f3("trans.dat");
        if (f3.is_open()) {
            for (int i = 0; i < history.size(); i++) f3 << history[i].toFileLine() << "\n";
        }
        f3.close();
    }

    void loadAllData() {
        ifstream f1("books.dat");
        string l;
        while (getline(f1, l)) {
            if (l == "") continue;
            vector<string> d = split(l, ',');
            if (d[0] == "BOOK") {
                Book* b = new Book(atoi(d[1].c_str()), d[2], d[3], d[4], d[5], d[6], atof(d[7].c_str()));
                if (d[8] == "1") b->issueBook();
                // Check if sold (d[9])
                bookList.add(b);
            } else if (d[0] == "EBOOK") {
                EBook* e = new EBook(atoi(d[1].c_str()), d[2], d[3], d[4], d[10], d[11] == "1", atof(d[7].c_str()));
                if (d[8] == "1") e->issueBook();
                bookList.add(e);
            }
        }
        f1.close();

        ifstream f2("users.dat");
        while (getline(f2, l)) {
            if (l == "") continue;
            vector<string> d = split(l, ',');
            if (d[0] == "STUDENT") {
                Student* s = new Student(atoi(d[1].c_str()), d[2], d[3], d[4], d[5], d[6], d[7], d[8]);
                s->setStudent(d[4], d[5], d[6], atoi(d[9].c_str()));
                if (d.size() >= 12) s->addFine(atof(d[11].c_str()));
                userList.add(s);
            } else if (d[0] == "LIBRARIAN") {
                userList.add(new Librarian(atoi(d[1].c_str()), d[2], d[3], atoi(d[4].c_str()), d[5], atof(d[6].c_str()), d[7], d[8]));
            }
        }
        f2.close();

        if (userList.size() == 0) {
            userList.add(new Librarian(1001, "Main Librarian", "admin123"));
        }

        ifstream f3("trans.dat");
        while (getline(f3, l)) {
            if (l == "") continue;
            vector<string> d = split(l, ',');
            if (d.size() >= 6) {
                Transaction t(atoi(d[0].c_str()), atoi(d[1].c_str()), atoi(d[2].c_str()), (time_t)atoll(d[3].c_str()));
                if (d[5] == "1") t.returnTransaction((time_t)atoll(d[4].c_str()));
                history.push_back(t);
            }
        }
        f3.close();
    }
};

#endif
