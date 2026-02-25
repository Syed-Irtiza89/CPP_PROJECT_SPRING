#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Base class for everything in the library
class Resource {
protected:
    int id;               
    string bookName;      
    string writer;        
    string bookType;      // This will be "Book" or "Magazine"
    bool available;       

public:
    Resource(int myId = 0, string myName = "", string myWriter = "", string myType = "Generic", bool isOk = true)
        : id(myId), bookName(myName), writer(myWriter), bookType(myType), available(isOk) {}

    int getBookId() const { return id; }
    string getBookName() const { return bookName; }
    string getWriter() const { return writer; }
    string getBookType() const { return bookType; }
    bool isStillAvailable() const { return available; }

    void setStatus(bool status) { available = status; }

    virtual void showDetails() const {
        cout << left << setw(5) << id 
             << setw(25) << bookName 
             << setw(20) << writer 
             << setw(15) << bookType 
             << (available ? "Available" : "Borrowed") << endl;
    }

    virtual string toFileLine() const {
        stringstream ss;
        ss << id << "," << bookName << "," << writer << "," << bookType << "," << (available ? "1" : "0");
        return ss.str();
    }

    virtual ~Resource() {}
};

// Specialized class for Books
class Book : public Resource {
public:
    Book(int id = 0, string n = "", string w = "", bool ok = true)
        : Resource(id, n, w, "Book", ok) {}

    void showDetails() const override {
        cout << "[BOOK] ";
        Resource::showDetails();
    }
};

// Specialized class for Magazines
class Magazine : public Resource {
public:
    Magazine(int id = 0, string n = "", string w = "Publisher", bool ok = true)
        : Resource(id, n, w, "Magazine", ok) {}

    void showDetails() const override {
        cout << "[MAG]  ";
        Resource::showDetails();
    }
};

#endif
