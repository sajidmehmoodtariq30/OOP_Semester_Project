#include "../header/Admin.h"
#include <iostream>

// Default constructor
Administrator::Administrator() : User(), adminLevel("") {
}

// Parameterized constructor
Administrator::Administrator(std::string username, std::string password, std::string name, 
                           std::string id, std::string adminLevel)
    : User(username, password, name, id), adminLevel(adminLevel) {
}

// Getter
std::string Administrator::getAdminLevel() const {
    return adminLevel;
}

// Implementation of pure virtual function
void Administrator::displayMenu() {
    std::cout << "\n===== Administrator Menu =====" << std::endl;
    std::cout << "1. Create Election" << std::endl;
    std::cout << "2. Add Candidate" << std::endl;
    std::cout << "3. Register Voter" << std::endl;
    std::cout << "4. Manage Election" << std::endl;
    std::cout << "5. View Result" << std::endl;
    std::cout << "6. Logout" << std::endl;
    std::cout << "Enter you choice: ";
}

// Comparison operator
bool Administrator::operator==(const Administrator &other) const {
    return getId() == other.getId();
}