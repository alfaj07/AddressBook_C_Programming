# 📇 Address Book Management System in C

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Compiler](https://img.shields.io/badge/Compiler-GCC%20%7C%20Clang-green.svg)](https://gcc.gnu.org/)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20WSL%20%7C%20Windows-orange.svg)]()
[![License](https://img.shields.io/badge/License-MIT-purple.svg)](LICENSE)

A modular, console-based **Address Book Management System** written in C. This project allows users to efficiently manage personal and business contacts with features like input validation, duplicate detection, multi-field sorting, and persistent CSV storage.

---

## 📑 Table of Contents

- [Features](#-features)
- [Project Architecture](#-project-architecture)
- [Validation Rules](#-validation-rules)
- [Prerequisites](#-prerequisites)
- [Compilation & Execution](#-compilation--execution)
- [Usage & Menu Options](#-usage--menu-options)
- [File Persistence Format](#-file-persistence-format)
- [Contributing](#-contributing)
- [License](#-license)

---

## ✨ Features

- **➕ Create Contact:** Add new contacts with full name, 10-digit phone number, and valid email address.
- **🔍 Search Contact:** Quickly find contacts by searching with Name, Phone Number, or Email.
- **✏️ Edit Contact:** Update contact details with real-time validation and duplicate prevention.
- **🗑️ Delete Contact:** Remove unnecessary contacts with confirmation.
- **📋 List Contacts with Sorting:**
  - View all stored contacts in a formatted ASCII table.
  - Sort dynamically by **Name**, **Phone Number**, or **Email**.
- **🛡️ Robust Input Validation:**
  - Phone numbers must be exactly 10 numeric digits.
  - Emails must conform to standard conventions (`user@domain.com`).
  - Automatic duplicate checks prevent duplicate phone numbers or email addresses.
- **💾 File Persistence:** Automatically saves and loads contacts to/from a CSV file (`contacts.csv`).
- **🧪 Sample Data:** Pre-populated with dummy contacts for quick testing and demonstration.

---

## 📂 Project Architecture

```plaintext
.
├── main.c          # Entry point and interactive menu loop
├── contact.c       # Contact operations (create, search, edit, delete, list, sort)
├── contact.h       # Data structure definitions, constants, and function prototypes
├── validate.c      # Phone & email validation and uniqueness check routines
├── file.c          # File I/O functions for saving and loading CSV records
├── file.h          # Header for file operations
├── populate.c      # Initial dummy data loader for testing
├── contacts.csv    # CSV file storing persistent contact records
└── README.md       # Project documentation
```

### Data Structures

```c
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
```

---

## 🛡️ Validation Rules

| Field | Rules & Constraints |
| :--- | :--- |
| **Phone** | • Must be exactly **10 digits** (`0-9`).<br>• Must not contain letters or special symbols.<br>• Must be unique across all existing contacts. |
| **Email** | • Minimum length: 7 characters (e.g., `a@b.com`).<br>• Must contain exactly one `@` symbol.<br>• Must end with `.com`.<br>• Must have characters before `@` and between `@` and `.com`.<br>• Only lowercase letters, digits, `.`, and `_` allowed.<br>• No whitespace permitted.<br>• Must be unique across all existing contacts. |

---

## ⚙️ Prerequisites

You will need a C compiler installed on your system:

- **Linux / WSL (Ubuntu):** `gcc` and `make` (optional)
  ```bash
  sudo apt update
  sudo apt install build-essential
  ```
- **Windows:** [MinGW-w64](https://www.mingw-w64.org/) or [Git Bash](https://gitforwindows.org/) / WSL.

---

## 🚀 Compilation & Execution

### Option 1: On Linux or WSL (Recommended)

1. Open your terminal in the project directory.
2. Compile all source files:
   ```bash
   gcc main.c contact.c validate.c file.c populate.c -o addressbook
   ```
3. Run the executable:
   ```bash
   ./addressbook
   ```

### Option 2: On Windows (Command Prompt / PowerShell with GCC)

1. Compile the program:
   ```cmd
   gcc main.c contact.c validate.c file.c populate.c -o addressbook.exe
   ```
2. Run the executable:
   ```cmd
   addressbook.exe
   ```

---

## 🖥️ Usage & Menu Options

When you run the application, you are presented with the main menu:

```plaintext
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
Enter your choice: 
```

### Formatted Contacts Table Display

Listing contacts displays a neat ASCII table:

```plaintext
+-------+-----------------+--------------+---------------------------+
| S.No  | Name            | Phone        | Email                     |
+-------+-----------------+--------------+---------------------------+
| 1     | Alice Smith     | 0987654321   | alice@example.com         |
| 2     | Bob Johnson     | 1112223333   | bob@company.com           |
| 3     | John Doe        | 1234567890   | john@example.com          |
+-------+-----------------+--------------+---------------------------+
```

---

## 💾 File Persistence Format

Contacts are stored in `contacts.csv` as comma-separated values:

```csv
John Doe,1234567890,john@example.com
Alice Smith,0987654321,alice@example.com
Bob Johnson,1112223333,bob@company.com
```

Select **Option 6 (Save and Exit)** from the menu to write all pending updates to `contacts.csv`.

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!
1. Fork the Project.
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`).
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the Branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

---

## 📜 License

Distributed under the [MIT](LICENSE) License. See `LICENSE` for more information.
