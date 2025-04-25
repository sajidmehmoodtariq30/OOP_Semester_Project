#ifndef ELECTION_H
#define ELECTION_H

#include "Array.h"
#include "Candidate.h"
#include "Vote.h"
#include <string>
#include <ctime>

class Election {
protected:
    std::string id;
    std::string name;
    std::string description;
    time_t startDate;
    time_t endDate;
    bool isActive;
    candidates* candidates;
    vote* votes;

public:
    // Accessor methods for protected members
    int getCandidateCount() const;
    Candidate& getCandidate(int index);
    const Candidate& getCandidate(int index) const;

    Election(std::string id, std::string name, std::string description, 
             time_t startDate, time_t endDate);
    virtual ~Election();

    std::string getId() const;
    std::string getName() const;
    bool isElectionActive() const;
    void startElection();
    void endElection();
    
    void addCandidate(const Candidate &candidate);
    bool hasVoted(const std::string &voterId) const;
    bool castVote(const std::string &voterId, const std::string &candidateId);
    void displayCandidates() const;
    virtual void displayResults() const;
    
    // Base implementation of displayInfo that derived classes can extend
    virtual void displayInfo() const;

    // Pure virtual method to be overridden by derived classes
    virtual std::string getType() const = 0;

    // For comparison
    bool operator==(const Election &other) const;
};

#endif // ELECTION_H