#include "../header/User.h"
#include <iostream>

// Default constructor
User::User() : username(""), password(""), name(""), id(""), isLoggedIn(false) {}

// Parameterized constructor
User::User(std::string username, std::string password, std::string name, std::string id)
    : username(username), password(password), name(name), id(id), isLoggedIn(false) {}

// Virtual destructor
User::~User() {}

// Authentication methods
bool User::login(std::string inputUsername, std::string inputPassword) {
    if (username == inputUsername && password == inputPassword) {
        isLoggedIn = true;
        return true;
    }
    return false;
}

void User::logout() {
    isLoggedIn = false;
}

bool User::isAuthenticated() const {
    return isLoggedIn;
}

// Getters
std::string User::getUsername() const {
    return username;
}

std::string User::getName() const {
    return name;
}

std::string User::getId() const {
    return id;
}