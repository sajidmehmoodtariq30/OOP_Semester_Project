#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

class Administrator : public User {
private:
    std::string adminLevel;

public:
    // Default constructor needed for Array template
    Administrator();
    
    // Parameterized constructor
    Administrator(std::string username, std::string password, std::string name, 
                 std::string id, std::string adminLevel);

    // Getter
    std::string getAdminLevel() const;

    // Implementation of pure virtual function
    void displayMenu() override;

    // Comparison operator
    bool operator==(const Administrator &other) const;
};

#endif // ADMIN_H