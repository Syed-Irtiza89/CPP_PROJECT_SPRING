#  Library Management System (FYP) 📚🎓

A robust, full-featured Library Management System implemented in C++ as a Final Year Project. This system demonstrates advanced Object-Oriented Programming (OOP) concepts, robust error handling, and persistent data management.

## 🚀 Key Features

### 🔐 Multi-Role Login Portal
- **Librarian Portal**: Full administrative access to manage books, e-books, users, and generate system-wide reports.
- **Student Portal**: User-friendly dashboard to search catalogs, borrow/return items, and track fine balances.

### 📖 Resource Management
- **Physical Books**: Standard automated issuing and return logic.
- **E-Books**: Digital access management with download links and payment tracking.
- **Book Sales**: Ability to mark items as sold and remove them from active circulation.

### 💰 Automated Transactions
- **System Fines**: Automatic calculation of late fees based on due dates.
- **Donation Tracking**: Reward system for members who contribute to the library.

---

## 🛠 Technical Achievements (OOP Concepts)

This project was specifically designed to showcase core and advanced C++ OOP principles:

- **Inheritance**: Hierarchical structure with `Person -> Student/Librarian` and `Book -> EBook`.
- **Polymorphism**: Extensive use of `virtual` functions and method overriding (e.g., `display()`).
- **Templates**: Generic `ListManager<T>` class for uniform aggregation and management of pointers.
- **Operator Overloading**: Overloaded `<<` for intuitive console output and `==` for object comparisons.
- **Function Overloading**: Multiple `searchBy` implementations (by ID or by Name).
- **Aggregation**: Complex relationship management where the `LibrarySystem` aggregates books and users.
- **Exception Handling**: Professional `try-catch` blocks for file I/O and runtime safety.
- **File Handling**: Persistent data storage using formatted `.dat` files.

---

## 📁 Project Structure

| File | Description |
| :--- | :--- |
| `Project.cpp` | Main application entry point and Menu UI logic. |
| `LibrarySystem.h` | Core business logic and system orchestrator. |
| `ListManager.h` | Template class for generic list management. |
| `Book.h` | Definitions for `Book` and `EBook` classes. |
| `Person.h` | Definitions for `Student` and `Librarian` classes. |
| `Transaction.h` | Logic for tracking loan history and fine calculations. |

---

## ⚙️ Installation & Usage

### Prerequisites
- A C++ compiler (e.g., GCC/MinGW)

### Compilation
Open your terminal in the project directory and run:
```bash
g++ -o LibrarySystem Project.cpp
```

### Execution
```bash
./LibrarySystem
```

### Default Credentials
- **Role**: Librarian
- **ID**: `1001`
- **Password**: `admin123`

---

## ✨ Developed by
**[Your Name/Irtiza Abbas]**
* Project for C++ Spring 2026*
