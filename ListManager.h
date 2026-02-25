#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// TEMPLATE Class for managing lists of objects (Aggregation)
template <class T>
class ListManager {
private:
    vector<T*> items;

public:
    ~ListManager() {
        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }
    }

    void add(T* item) {
        items.push_back(item);
    }

    T* getById(int id) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getId() == id) return items[i];
        }
        return nullptr;
    }

    // Overloaded search for books (they use getBookId)
    // This is handled by specialization or distinct naming
    // But for simplicity in this student project, we use getID interface
    
    vector<T*>& getAll() {
        return items;
    }

    int size() const {
        return items.size();
    }

    void remove(int id) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getId() == id) {
                delete items[i];
                items.erase(items.begin() + i);
                return;
            }
        }
    }
};

#endif
