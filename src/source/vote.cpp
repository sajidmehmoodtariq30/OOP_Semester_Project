#include "../header/Vote.h"
#include <ctime>

// Default constructor
Vote::Vote() : voterId(""), candidateId(""), electionId(""), timestamp(0) {
}

// Parameterized constructor
Vote::Vote(std::string voterId, std::string candidateId, std::string electionId)
    : voterId(voterId), candidateId(candidateId), electionId(electionId) {
    // Set timestamp to current time
    timestamp = time(nullptr);
}

// Getters
std::string Vote::getVoterId() const {
    return voterId;
}

std::string Vote::getCandidateId() const {
    return candidateId;
}

std::string Vote::getElectionId() const {
    return electionId;
}

time_t Vote::getTimestamp() const {
    return timestamp;
}

// Comparison operator for finding duplicates in voting
bool Vote::operator==(const Vote &other) const {
    // Consider a vote equal if it's from the same voter for the same election
    return (voterId == other.voterId && electionId == other.electionId);
}