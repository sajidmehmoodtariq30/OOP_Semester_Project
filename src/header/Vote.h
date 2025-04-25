#ifndef VOTE_H
#define VOTE_H

#include <string>
#include <ctime>

class Vote {
private:
    std::string voterId;
    std::string candidateId;
    std::string electionId;
    time_t timestamp;

public:
    Vote();
    Vote(std::string voterId, std::string candidateId, std::string electionId);

    std::string getVoterId() const;
    std::string getCandidateId() const;
    std::string getElectionId() const;
    time_t getTimestamp() const;

    // For comparison in Array::contains
    bool operator==(const Vote &other) const;
};

#endif // VOTE_H