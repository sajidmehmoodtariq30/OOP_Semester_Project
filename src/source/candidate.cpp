#include "../header/Candidate.h"
#include <iostream>

// Default constructor
Candidate::Candidate() : id(""), name(""), partyAffiliation(""), voteCount(0) {
}

// Parameterized constructor
Candidate::Candidate(std::string id, std::string name, std::string partyAffiliation)
    : id(id), name(name), partyAffiliation(partyAffiliation), voteCount(0) {
}

// Getters
std::string Candidate::getId() const {
    return id;
}

std::string Candidate::getName() const {
    return name;
}

std::string Candidate::getPartyAffiliation() const {
    return partyAffiliation;
}

int Candidate::getVoteCount() const {
    return voteCount;
}

// Increment vote count
void Candidate::incrementVotes() {
    voteCount++;
}

// Display candidate information
void Candidate::displayInfo() const {
    std::cout << "ID: " << id << ", Name: " << name
              << ", Party: " << partyAffiliation
              << ", Votes: " << voteCount << std::endl;
}

// Comparison operator for Array::contains
bool Candidate::operator==(const Candidate &other) const {
    return id == other.id;
}