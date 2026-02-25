#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Basic class for anyone using the system
class User {
protected:
    string nickName;      
    string pass;          
    string fName;         
    string lName;         
    string homeAddress;   
    double myMoney;       
    string userRole;      

public:
    User(string u = "", string p = "", string fn = "", string ln = "", string add = "", double m = 0.0, string r = "Customer")
        : nickName(u), pass(p), fName(fn), lName(ln), homeAddress(add), myMoney(m), userRole(r) {}

    virtual ~User() {}

    string getNick() const { return nickName; }
    string getPass() const { return pass; }
    string getFirstName() const { return fName; }
    string getLastName() const { return lName; }
    string getAddress() const { return homeAddress; }
    double getCash() const { return myMoney; }
    string getJob() const { return userRole; }

    void cutMoney(double amount) { myMoney -= amount; }
    void putMoney(double amount) { myMoney += amount; }

    virtual void showProfile() const {
        cout << "Name: " << fName << " " << lName << "\n"
             << "User Name: " << nickName << "\n"
             << "Address: " << homeAddress << "\n"
             << "Balance: $" << myMoney << "\n"
             << "Type: " << userRole << endl;
    }

    virtual string toFileLine() const {
        stringstream ss;
        ss << nickName << "," << pass << "," << fName << "," << lName << "," << homeAddress << "," << myMoney << "," << userRole;
        return ss.str();
    }
};

class Customer : public User {
private:
    int itemsCount; 
    string memberTier;   // "Basic" or "Premium"
    int donationCount;   // How many books donated

public:
    Customer(string u = "", string p = "", string fn = "", string ln = "", string add = "", double m = 100.0, string tier = "Basic", int dons = 0)
        : User(u, p, fn, ln, add, m, "Customer"), itemsCount(0), memberTier(tier), donationCount(dons) {}

    int getItemsCount() const { return itemsCount; }
    void setItemsCount(int c) { itemsCount = c; }
    
    string getTier() const { return memberTier; }
    void setTier(string t) { memberTier = t; }
    
    int getDons() const { return donationCount; }
    void addDonation() { donationCount++; }

    void showProfile() const override {
        User::showProfile();
        cout << "Membership: " << memberTier << "\n"
             << "Donations: " << donationCount << "\n"
             << "Books with you: " << itemsCount << endl;
    }

    string toFileLine() const override {
        stringstream ss;
        ss << User::toFileLine() << "," << itemsCount << "," << memberTier << "," << donationCount;
        return ss.str();
    }
};

class Admin : public User {
public:
    Admin(string u = "", string p = "", string fn = "", string ln = "", string add = "")
        : User(u, p, fn, ln, add, 0.0, "Admin") {}

    string toFileLine() const override {
        stringstream ss;
        ss << User::toFileLine() << ",0,Admin,0"; 
        return ss.str();
    }
};

#endif
