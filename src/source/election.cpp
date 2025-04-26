#include "../header/Election.h"
#include <iostream>
#include <iomanip>
#include <ctime>

Election::Election(std::string id, std::string name, std::string description, 
               time_t startDate, time_t endDate)
    : id(id), name(name), description(description),
      startDate(startDate), endDate(endDate), isActive(false) {
}

Election::~Election() {
    // Virtual destructor to ensure proper cleanup of derived classes
}

std::string Election::getId() const {
    return id;
}

std::string Election::getName() const {
    return name;
}

bool Election::isElectionActive() const {
    return isActive;
}

void Election::startElection() {
    isActive = true;
}

void Election::endElection() {
    isActive = false;
}

void Election::addCandidate(const Candidate &candidate) {
    candidates.add(candidate);
}

bool Election::hasVoted(const std::string &voterId) const {
    // Check if this voter has already cast a vote in this election
    for (int i = 0; i < votes.getSize(); i++) {
        if (votes.get(i).getVoterId() == voterId) {
            return true;
        }
    }
    return false;
}

bool Election::castVote(const std::string &voterId, const std::string &candidateId) {
    // Check if the voter has already voted
    if (hasVoted(voterId)) {
        return false;
    }

    // Create a new vote
    Vote vote(voterId, candidateId, id);
    votes.add(vote);

    // Increment the vote count for the candidate
    for (int i = 0; i < candidates.getSize(); i++) {
        if (candidates.get(i).getId() == candidateId) {
            candidates.get(i).incrementVotes();
            break;
        }
    }

    return true;
}

void Election::displayCandidates() const {
    std::cout << "\nCandidates for " << name << ":" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    if (candidates.getSize() == 0) {
        std::cout << "No candidates registered yet." << std::endl;
        return;
    }

    for (int i = 0; i < candidates.getSize(); i++) {
        std::cout << (i + 1) << ". ";
        candidates.get(i).displayInfo();
    }
}

void Election::displayInfo() const {
    std::cout << "Election ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    
    // Convert time_t to readable format
    char startDateStr[26];
    char endDateStr[26];
    ctime_s(startDateStr, sizeof(startDateStr), &startDate);
    ctime_s(endDateStr, sizeof(endDateStr), &endDate);
    
    std::cout << "Start Date: " << startDateStr;
    std::cout << "End Date: " << endDateStr;
    std::cout << "Status: " << (isActive ? "Active" : "Inactive") << std::endl;
}

void Election::displayResults() const {
    std::cout << "\nResults for " << name << ":" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    if (candidates.getSize() == 0) {
        std::cout << "No candidates registered." << std::endl;
        return;
    }

    if (votes.getSize() == 0) {
        std::cout << "No votes cast yet." << std::endl;
        return;
    }

    // Display each candidate and their vote count
    for (int i = 0; i < candidates.getSize(); i++) {
        const Candidate& candidate = candidates.get(i);
        int voteCount = candidate.getVoteCount();
        double percentage = (votes.getSize() > 0) ? 
            (static_cast<double>(voteCount) / votes.getSize() * 100.0) : 0.0;
        
        std::cout << candidate.getName() << " (" << candidate.getPartyAffiliation() << "): "
                  << voteCount << " votes " 
                  << "(" << std::fixed << std::setprecision(2) << percentage << "%)" << std::endl;
    }
    
    std::cout << "\nTotal votes: " << votes.getSize() << std::endl;
}

int Election::getCandidateCount() const {
    return candidates.getSize();
}

Candidate& Election::getCandidate(int index) {
    return candidates.get(index);
}

const Candidate& Election::getCandidate(int index) const {
    return candidates.get(index);
}

bool Election::operator==(const Election &other) const {
    return id == other.id;
}