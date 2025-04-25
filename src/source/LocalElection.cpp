#include "../header/LocalElection.h"
#include <iostream>
#include <ctime>

LocalElection::LocalElection(std::string id, std::string name, std::string description, 
                          std::string startDate, std::string endDate, std::string locality)
    : Election(id, name, description, time(nullptr), time(nullptr)), locality(locality) {
    // This is a simplified implementation - in a real application, you would parse the date strings
    // and convert them to time_t values properly
}

void LocalElection::displayInfo() const {
    Election::displayInfo();
    std::cout << "Locality: " << locality << std::endl;
}

std::string LocalElection::getLocality() const {
    return locality;
}

std::string LocalElection::getType() const {
    return "Local";
}
