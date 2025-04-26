#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

class Candidate {
private:
    std::string id;
    std::string name;
    std::string partyAffiliation;
    int voteCount;

public:
    Candidate();
    Candidate(std::string id, std::string name, std::string partyAffiliation);

    std::string getId() const;
    std::string getName() const;
    std::string getPartyAffiliation() const;
    int getVoteCount() const;
    void incrementVotes();
    void displayInfo() const;

    // For comparison in Array::contains
    bool operator==(const Candidate &other) const;
};

#endif // CANDIDATE_H