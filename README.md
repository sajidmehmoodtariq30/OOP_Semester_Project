# 🎯 Castify - Voting Management System

![Castify logo](./assets/logo.png)

**Castify** is an Object-Oriented Voting Management System developed in C++ (no STL containers) with file-based data persistence. It provides role-based access for administrators, voters, and candidates, supporting secure, real-world election workflows.

> _This project avoids STL containers like vectors or maps, adhering to core C++ OOP principles and manual file I/O operations._

---

## 📌 Key Features

- **Role-based Access:** Admin, Voter, and Candidate roles, each with custom menus and permissions.
- **Election Management:**
  - Create Local, National, and Regional elections with custom durations.
  - Start/end elections manually or automatically (time-based).
- **Candidate Management:**
  - Register and assign candidates to elections.
  - Prevent duplicate party candidates in national elections.
- **Voter Management:**
  - Register voters with unique IDs and addresses.
  - Prevent duplicate voter registration.
- **Voting System:**
  - Secure, unique vote casting (one vote per election per voter).
  - Real-time vote counting and result display.
- **Data Persistence:**
  - All data (users, elections, candidates, votes) stored in plain text files in `/data`.
  - Simple password encryption (Caesar cipher).
- **Command-Line Interface:**
  - Intuitive CLI with clear prompts and error handling.
  - Demo mode for quick demonstration of system features.

---

## 🗂️ Project Structure

``` text
OOP_Semester_Project/
├── main.cpp
├── build.bat
├── CMakeLists.txt
├── assets/
│   ├── logo.png
│   └── oop uml.drawio.png
├── data/
│   ├── admins.txt
│   ├── candidates.txt
│   ├── elections.txt
│   ├── voters.txt
│   └── votes.txt
├── src/
│   ├── header/
│   │   ├── Admin.h, Array.h, Candidate.h, Election.h, ...
│   └── source/
│       ├── admin.cpp, candidate.cpp, election.cpp, ...
├── build/ (output .exe)
├── docs/
│   └── OOP project 2025.docx, ...
└── README.md
```

---

## ⚙️ Build & Run (Windows)

1. **Build using batch script:**

   ```powershell
   .\build.bat
   ```

   This compiles all sources and creates `voting_system.exe` in the `build/` directory.

2. **Run the program:**

   ```powershell
   .\build\voting_system.exe
   ```

3. **Modes:**
   - **Normal Mode:** Interactive CLI for real use.
   - **Demo Mode:** Automated demonstration of login, election creation, voting, and result display.

---

## 📝 Usage Overview

- **Admins:**
  - Login, create/manage elections, add candidates, register voters, view results.
- **Voters:**
  - Login, cast votes in active elections, view results.
- **Candidates:**
  - Login, view profile, view election results.

All data is persisted in `/data` as plain text. Passwords are stored with basic encryption.

---

## 👥 Developers

| Developer              | GitHub Profile                                 |
|-----------------------|------------------------------------------------|
| Sajid Mehmood Tariq   | [sajidmehmoodtariq30](https://github.com/sajidmehmoodtariq30) |
| Areej                 | [areejchdry](https://github.com/areejchdry)    |
| Fiza Shahid Khan      | [F20060](https://github.com/F20060)            |

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---
