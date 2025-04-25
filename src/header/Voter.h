#ifndef VOTER_H
#define VOTER_H

#include "User.h"
#include <string>

class Voter : public User {
private:
    std::string address;
    std::string voterIdNumber;

public:
    Voter();
    
    // Parameterized constructor
    Voter(std::string username, std::string password, std::string name, std::string id, 
          std::string address, std::string voterIdNumber);

    // Getters
    std::string getAddress() const;
    std::string getVoterIdNumber() const;

    // Implementation of pure virtual function
    void displayMenu() override;

    // Comparison operator
    bool operator==(const Voter &other) const;
};

#endif // VOTER_H