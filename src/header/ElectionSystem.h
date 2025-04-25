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
}