#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string username;
    std::string password;
    std::string name;
    std::string id;
    bool isLoggedIn;

public:
    // Default constructor
    User();
    
    // Parameterized constructor
    User(std::string username, std::string password, std::string name, std::string id);
    
    // Virtual destructor
    virtual ~User();

    // Authentication methods
    bool login(std::string inputUsername, std::string inputPassword);
    void logout();
    bool isAuthenticated() const;

    // Getters
    std::string getUsername() const;
    std::string getName() const;
    std::string getId() const;

    // Pure virtual function to be implemented by derived classes
    virtual void displayMenu() = 0;
};

#endif // USER_H