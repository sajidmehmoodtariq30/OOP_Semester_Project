#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "User.h"
#include <iostream>
#include <string>

class Candidate : public User {
private:
    std::string candidateId;
    std::string name;
    std::string partyAffiliation;
    int voteCount;
public:
    Candidate();
    Candidate(std::string username, std::string password, std::string name, std::string id, std::string partyAffiliation);
    void displayMenu() override;
    std::string getPartyAffiliation() const;
    std::string getCandidateId() const;
    std::string getName() const;
    int getVoteCount() const;
    void incrementVotes();
    void displayInfo() const;
};

#endif // CANDIDATE_USER_H
