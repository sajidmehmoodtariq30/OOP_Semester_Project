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
    // Deprecated: time_t startDate;
    // Deprecated: time_t endDate;
    time_t startTime; // Time when election is started (set by admin)
    time_t endTime;   // Time when election ends (startTime + duration)
    int durationSeconds; // Duration in seconds (set at creation)
    bool isActive;
    Array<Candidate> candidates;
    Array<Vote> votes;

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
    bool isElectionActive() const; // Will now check current time vs endTime
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

    // New methods for time-based elections
    void setDuration(int minutes, int seconds); // Set duration
    void setStartTime(time_t start);            // Set start time
    void calculateEndTime();                    // Calculate end time
    time_t getStartTime() const;
    time_t getEndTime() const;
    int getDurationSeconds() const;
};

#endif // ELECTION_H