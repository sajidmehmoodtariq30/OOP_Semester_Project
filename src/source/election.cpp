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