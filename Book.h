#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Base Class: Book
class Book {
protected:
    int bookID;          
    string author;       
    string topic;        
    string bookName;     
    bool isIssue;        
    string edition;      
    string publisher;    
    double price;        
    bool isSold;         // New attribute for bookSold function

public:
    Book(int id = 0, string name = "", string auth = "", string top = "", string ed = "1st", string pub = "Unknown", double pr = 0.0)
        : bookID(id), bookName(name), author(auth), topic(top), edition(ed), publisher(pub), price(pr), isIssue(false), isSold(false) {}

    virtual ~Book() {}

    // EXACT FUNCTIONS REQUESTED
    void setBook(int id, string name, string auth, string top, string ed, string pub, double pr) {
        bookID = id; bookName = name; author = auth; topic = top; edition = ed; publisher = pub; price = pr;
    }

    void issueBook() { isIssue = true; }
    void returnBook() { isIssue = false; }
    
    double getBookPrice() const { return price; } // Alias for book price
    
    void bookPurchase(double cost) {
        price = cost;
        cout << "Book " << bookName << " purchased for inventory at cost: $" << cost << endl;
    }

    int getBookId() const { return bookID; }
    string getBookName() const { return bookName; }
    
    bool checkAvailability() const { return !isIssue && !isSold; }

    virtual void display() const {
        cout << left << setw(5) << bookID 
             << setw(20) << bookName 
             << setw(15) << author 
             << setw(15) << topic 
             << setw(8) << price 
             << (isSold ? "Sold" : (isIssue ? "Issued" : "Available")) << endl;
    }

    void bookSold() {
        isSold = true;
        cout << "Book " << bookName << " (ID: " << bookID << ") has been marked as SOLD.\n";
    }

    // Operator Overloading (Output)
    friend ostream& operator<<(ostream& os, const Book& b) {
        os << "Book ID: " << b.bookID << " | Title: " << b.bookName;
        return os;
    }

    // Operator Overloading (Comparison)
    bool operator==(const Book& other) const {
        return this->bookID == other.bookID;
    }

    virtual string toFileLine() const {
        stringstream ss;
        ss << "BOOK," << bookID << "," << bookName << "," << author << "," << topic << "," 
           << edition << "," << publisher << "," << price << "," << (isIssue ? "1" : "0") << "," << (isSold ? "1" : "0");
        return ss.str();
    }
};

// Derived Class: EBook (Inheritance)
class EBook : public Book {
private:
    string downloadLink;
    bool isPaid;

public:
    EBook(int id = 0, string name = "", string auth = "", string top = "", string link = "http://lib.com/dl", bool paid = false, double pr = 0.0)
        : Book(id, name, auth, top, "Digital", "Online Pub", pr), downloadLink(link), isPaid(paid) {}

    void setEBook(string link, bool paid) {
        downloadLink = link;
        isPaid = paid;
    }

    string getEBook() const { return downloadLink; } // Alias for easy access

    void display() const override {
        cout << "[E-BOOK] ";
        Book::display();
        cout << "         Link: " << downloadLink << " | " << (isPaid ? "Paid" : "Free") << endl;
    }

    void payment() {
        if (isPaid) cout << "Processing digital payment for E-Book: " << getBookName() << "...\n";
        else cout << "E-Book " << getBookName() << " is available for free download.\n";
    }

    string toFileLine() const override {
        stringstream ss;
        ss << "EBOOK," << bookID << "," << bookName << "," << author << "," << topic << "," 
           << edition << "," << publisher << "," << price << "," << (isIssue ? "1" : "0") << ","
           << (isSold ? "1" : "0") << "," << downloadLink << "," << (isPaid ? "1" : "0");
        return ss.str();
    }
};

#endif
