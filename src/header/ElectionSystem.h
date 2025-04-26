#ifndef ELECTION_SYSTEM_H
#define ELECTION_SYSTEM_H

#include "FileHandler.h"

class FileHandler;

class ElectionSystem {
    User* currentUser;
    FileHandler* fileHandler;
public:
    ElectionSystem();
    ~ElectionSystem();

    void seedData();
    bool saveData();
    bool loadData();

    bool login(std::string username, std::string password);
    void logout();
    bool isLoggedIn() const;
    bool isAdmin() const;

    void run();
}