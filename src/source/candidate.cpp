#include "../header/Candidate.h"


// Default constructor
Candidate::Candidate() : User(), candidateId(""), name(""), partyAffiliation(""), voteCount(0) {}
Candidate::Candidate(std::string username, std::string password, std::string name, std::string id, std::string partyAffiliation)
    : User(username, password, name, id), candidateId(id), name(name), partyAffiliation(partyAffiliation), voteCount(0) {}

// Display menu options for the candidate user
void Candidate::displayMenu() {
    std::cout << "\n===== Candidate Menu =====" << std::endl;
    std::cout << "1. View My Profile" << std::endl;
    std::cout << "2. View Election Results" << std::endl;
    std::cout << "3. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

std::string Candidate::getPartyAffiliation() const { return partyAffiliation; }
std::string Candidate::getCandidateId() const { return candidateId; }
std::string Candidate::getName() const { return name; }
int Candidate::getVoteCount() const { return voteCount; }
void Candidate::incrementVotes() { voteCount++; }
void Candidate::displayInfo() const {
    std::cout << "ID: " << candidateId << ", Name: " << name
              << ", Party: " << partyAffiliation
              << ", Votes: " << voteCount << std::endl;
}