#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

// This class tracks book borrows
class Transaction {
private:
    int transID;         
    int bookID;           
    int studentID;      
    time_t issueDate;      
    time_t returnDate;  
    bool isReturned;          

public:
    Transaction(int tId = 0, int bId = 0, int sId = 0, time_t iss = 0)
        : transID(tId), bookID(bId), studentID(sId), issueDate(iss), returnDate(0), isReturned(false) {}

    // EXACT FUNCTIONS REQUESTED
    static void create() { cout << "Initializing new transaction record structure...\n"; }
    
    void display() const {
        cout << "[TX Record] ID:" << transID << " | BookID:" << bookID << " | StudentID:" << studentID 
             << " | Issued:" << formatTime(issueDate) 
             << " | Status: " << (isReturned ? "Returned" : "Active") << endl;
    }

    void returnTransaction(time_t now) {
        returnDate = now;
        isReturned = true;
    }

    double calculate() const {
        if (!isReturned) return 0.0;
        // Calculation: $2 fine per day after 7 days
        double diff = difftime(returnDate, issueDate);
        double days = diff / (24 * 3600);
        if (days > 7) {
            return (days - 7) * 2.0; 
        }
        return 0.0;
    }

    int getTransactionId() const { return transID; }
    bool checkDone() const { return isReturned; }

    // Helper to format time
    string formatTime(time_t t) const {
        if (t == 0) return "N/A";
        char buffer[20];
        struct tm* info = localtime(&t);
        if (info) {
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", info);
            return string(buffer);
        }
        return "Err";
    }

    int getBookId() const { return bookID; }
    int getStudentId() const { return studentID; }

    string toFileLine() const {
        stringstream ss;
        ss << transID << "," << bookID << "," << studentID << "," 
           << (long long)issueDate << "," << (long long)returnDate << "," << (isReturned ? "1" : "0");
        return ss.str();
    }
};

#endif
