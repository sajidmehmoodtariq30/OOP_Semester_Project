# 🎯 Castify - Voting Management System

img src="./assets/logo.png" />

**Castify** is an Object-Oriented Voting Management System developed in C++ with file-based data persistence. It offers role-based access for administrators, voters, and candidates, ensuring a secure and efficient platform for managing elections.

> _This project avoids STL containers like vectors or maps, adhering to core C++ OOP principles and file I/O operations._

---

## 📌 Features Overview

### 🧑‍💼 User Management

- Role-based registration: Admin, Voter, Candidate
- Secure login and user profile management

### 🗳️ Election Management

- Create and configure elections with start/end dates
- Support for multiple election types and eligibility settings

### 🧾 Candidate Management

- Candidate registration and approval workflows
- Display candidate profiles and information

### ✅ Voting System

- Secure, unique vote casting
- Support for multiple voting methods (e.g., First-Past-The-Post, Ranked Choice)
- Prevention of duplicate voting

### 📊 Results Processing

- Real-time vote counting
- Election result generation and reporting
- Statistical analysis of voting data

### 💾 Data Persistence

- File-based storage using `fstream`
- Backup and recovery mechanisms
- Efficient data loading and saving

### 🔐 Security Features

- Basic encryption for sensitive data
- Audit logging for user and system activity
- Mitigation of common vulnerabilities

### 💻 User Interface

- Command-line interface (CLI)
- Intuitive navigation with clear prompts and error messages

---

## 🛠️ Technical Details

### Object-Oriented Design

- Core principles: Encapsulation, Inheritance, Polymorphism
- Modular class design (e.g., User, Admin, Election, Vote)
- Use of abstract base classes and interfaces

### File Handling

- Manual parsing and storage using text files
- Persistent data across program runs
- No reliance on STL containers (`vector`, `map`, etc.)

---

## 📂 Planned File Structure

```plaintext
Castify/
├── src/
│   ├── main.cpp
│   ├── user.cpp / .h
│   ├── admin.cpp / .h
│   ├── voter.cpp / .h
│   ├── candidate.cpp / .h
│   ├── election.cpp / .h
│   ├── vote.cpp / .h
│   ├── filehandler.cpp / .h
├── data/
│   ├── users.txt
│   ├── elections.txt
│   ├── candidates.txt
│   ├── votes.txt
│   ├── logs.txt
├── README.md
└── Makefile
```

---

## 🚀 Run the Project

```bash
# Clone the repository
git clone https://github.com/sajidmehmoodtariq30/Castify
cd Castify
# Build the project
make
# Run the project
make run
# To clean up the build files
make clean
```

---

## 🤝 Contributing

Contributions are welcome! If you'd like to contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## 👥 Developers

Developer | GitHub Profile
--- | ---
Sajid Mehmood Tariq | [sajidmehmoodtariq30](https://github.com/sajidmehmoodtariq30)
Areej | [areejchdry](https://github.com/areejchdry)
Fiza Shahid Khan | [F20060](https://github.com/F20060)

## 📧 Contact

For any inquiries or feedback, please reach out to [sajidmehmoodtariq30](https://github.com/sajidmehmoodtariq30) via GitHub.
