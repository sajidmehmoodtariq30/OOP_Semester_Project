#include "../header/Voter.h"
#include <iostream>

// Default constructor
Voter::Voter() : User(), address(""), voterIdNumber("") {
}

// Parameterized constructor
Voter::Voter(std::string username, std::string password, std::string name, std::string id, 
           std::string address, std::string voterIdNumber)
    : User(username, password, name, id), address(address), voterIdNumber(voterIdNumber) {
}

// Getters
std::string Voter::getAddress() const {
    return address;
}

std::string Voter::getVoterIdNumber() const {
    return voterIdNumber;
}

// Implementation of pure virtual function
void Voter::displayMenu() {
    std::cout << "\n===== Voter Menu =====" << std::endl;
    std::cout << "1. Cast Vote" << std::endl;
    std::cout << "2. View Results" << std::endl;
    std::cout << "3. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

// Comparison operator
bool Voter::operator==(const Voter &other) const {
    return getId() == other.getId();
}