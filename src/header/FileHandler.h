#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "ElectionSystem.h"
#include "Election.h"
#include "Voter.h"
#include "Admin.h"
#include "Candidate.h"
#include "Vote.h"
#include "LocalElection.h"
#include "RegionalElection.h"
#include "NationalElection.h"
#include <string>
#include <fstream>

class ElectionSystem; // Forward declaration
class TXTParser; // Forward declaration

class FileHandler {
private:
    const std::string VOTERS_FILE = "data/voters.txt";
    const std::string ADMINS_FILE = "data/admins.txt";
    const std::string ELECTIONS_FILE = "data/elections.txt";
    const std::string CANDIDATES_FILE = "data/candidates.txt";
    const std::string VOTES_FILE = "data/votes.txt";
    
    // Helper methods for ensuring the data directory exists
    bool ensureDataDirectoryExists();
    
    // Helper methods for serialization
    std::string serializeVoter(const Voter& voter);
    std::string serializeAdmin(const Administrator& admin);
    std::string serializeElection(const Election* election);
    std::string serializeCandidate(const Candidate& candidate, const std::string& electionId);
    std::string serializeVote(const Vote& vote, const std::string& electionId);
    
    // Helper methods for deserialization
    Voter deserializeVoter(const std::string& data);
    Administrator deserializeAdmin(const std::string& data);
    Election* deserializeElection(const std::string& data);
    Candidate deserializeCandidate(const std::string& data);
    Vote deserializeVote(const std::string& data);

    // TXT parsing helpers
    TXTParser splitTXT(const std::string& line);
    std::string escapeTXT(const std::string& field);
    
public:
    FileHandler();
    ~FileHandler();
    
    // Password encryption/decryption helpers - made public so they can be used by other classes
    std::string encryptPassword(const std::string& password);
    std::string decryptPassword(const std::string& encryptedPassword);
    
    // Save methods
    bool saveVoters(const Array<Voter>& voters);
    bool saveAdmins(const Array<Administrator>& admins);
    bool saveCandidates(const Array<Candidate>& candidates);
    bool saveElections(const Array<Election*>& elections);
    
    // Load methods
    bool loadVoters(Array<Voter>& voters);
    bool loadAdmins(Array<Administrator>& admins);
    bool loadCandidates(Array<Candidate>& candidates);
    bool loadElections(Array<Election*>& elections);
    
    // Save all data from ElectionSystem
    bool saveAllData(const ElectionSystem& system);
    
    // Load all data into ElectionSystem
    bool loadAllData(ElectionSystem& system);
};

#endif // FILE_HANDLER_H
