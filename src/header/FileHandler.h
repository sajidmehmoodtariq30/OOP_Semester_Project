#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "ElectionSystem.h"
#include <string>
#include <fstream>


class FileHandler {
private:
    const std::string VOTERS_FILE = "data/voters.txt";
    const std::string ADMINS_FILE = "data/admins.txt";
    const std::string ELECTIONS_FILE = "data/elections.txt";
    const std::string CANDIDATES_FILE = "data/candidates.txt";
    const std::string VOTES_FILE = "data/votes.txt";
    
   
public:
    FileHandler();
    ~FileHandler();
    bool saveAllData(const ElectionSystem& system);
    bool loadAllData(ElectionSystem& system);
};

#endif // FILE_HANDLER_H
