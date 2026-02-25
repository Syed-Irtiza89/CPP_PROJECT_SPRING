#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Base Class: Person
class Person {
protected:
    string name;
    string email;
    string number;
    int id;

public:
    Person(int myId = 0, string n = "", string e = "", string num = "")
        : id(myId), name(n), email(e), number(num) {}

    virtual ~Person() {}

    string getName() const { return name; }
    int getId() const { return id; }
    string getEmail() const { return email; }

    virtual void display() const {
        cout << "ID: " << id << " | Name: " << name << " | Email: " << email << endl;
    }
};

// Derived Class: Student (Inheritance)
class Student : public Person {
private:
    string education;
    string cnic;
    string address;
    int maxLimit;
    int issueCount;
    double fineBalance;
    string password;

public:
    Student(int id = 0, string n = "", string pass = "123", string ed = "", string c = "", string add = "", string e = "", string num = "")
        : Person(id, n, e, num), password(pass), education(ed), cnic(cnic), address(add), maxLimit(2), issueCount(0), fineBalance(0.0) {}

    // EXACT FUNCTIONS REQUESTED
    void setStudent(string ed, string c, string add, int limit) {
        education = ed; cnic = c; address = add; maxLimit = limit;
    }

    void displayStudent() const { display(); } // Alias

    void updateStudent(string n, string ed, string c, string add, string e, string num) {
        name = n; education = ed; cnic = c; address = add; email = e; number = num;
        cout << "Information for Student ID " << id << " has been updated.\n";
    }

    void issueBook() { issueCount++; }
    void returnBook() { issueCount--; }
    
    int getStudentId() const { return id; } 
    int getIssueBookCount() const { return issueCount; }
    
    bool checkLimit() const { return issueCount < maxLimit; }
    
    void addFine(double amount) { fineBalance += amount; }
    void payFine(double amount) { 
        fineBalance -= amount; 
        cout << "Student " << name << " paid $" << amount << " fine. Remaining: $" << fineBalance << endl;
    }

    string getPassword() const { return password; }

    void display() const override {
        Person::display();
        cout << "Edu: " << education << " | CNIC: " << cnic << " | Phone: " << number << "\n"
             << "Books: " << issueCount << "/" << maxLimit << " | Fine: $" << fineBalance << endl;
    }

    // Operator Overloading
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "Student: " << s.name << " (ID: " << s.id << ")";
        return os;
    }

    string toFileLine() const {
        stringstream ss;
        ss << "STUDENT," << id << "," << name << "," << password << "," << education << "," 
           << cnic << "," << address << "," << email << "," << number << "," 
           << maxLimit << "," << issueCount << "," << fineBalance;
        return ss.str();
    }
};

// Derived Class: Librarian (Inheritance)
class Librarian : public Person {
private:
    int age;
    string joinDate;
    double salary;
    string password;

public:
    Librarian(int id = 0, string n = "", string pass = "admin", int a = 35, string jd = "2024-01-01", double sal = 45000.0, string e = "", string num = "")
        : Person(id, n, e, num), password(pass), age(a), joinDate(jd), salary(sal) {}

    // EXACT FUNCTIONS REQUESTED
    void addLibrarian() { cout << "Adding Librarian " << name << " to registry system...\n"; }
    void removeLibrarian() { cout << "Removing Librarian " << name << " from staff records.\n"; }
    
    string getNameLibrarian() const { return name; }
    int getIdLibrarian() const { return id; }
    
    void checkSalary() const {
        cout << "Librarian Salary Confirmation: " << name << " is paid $" << salary << endl;
    }

    void detail() const { display(); } // Alias for display

    void emailLibrarian() {
        cout << "Message sent to " << name << " at electronic address: " << email << endl;
    }

    void collectionFine(double amount) {
        cout << "Librarian " << name << " (ID:" << id << ") collected fine: $" << amount << endl;
    }

    void generateReport() const {
        cout << "Librarian " << name << " is generating the daily library activity report...\n";
    }

    string getPassword() const { return password; }

    void display() const override {
        Person::display();
        cout << "Age: " << age << " | Joined Library: " << joinDate << " | Contact: " << number << endl;
    }

    string toFileLine() const {
        stringstream ss;
        ss << "LIBRARIAN," << id << "," << name << "," << password << "," << age << "," 
           << joinDate << "," << salary << "," << email << "," << number;
        return ss.str();
    }
};

#endif
