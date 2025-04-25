#include "../header/NationalElection.h"
#include <iostream>
#include <ctime>

NationalElection::NationalElection(std::string id, std::string name, std::string description, 
                                 std::string startDate, std::string endDate, std::string country)
    : Election(id, name, description, time(nullptr), time(nullptr)), country(country) {
    // This is a simplified implementation - in a real application, you would parse the date strings
    // and convert them to time_t values properly
}

void NationalElection::displayInfo() const {
    Election::displayInfo();
    std::cout << "Country: " << country << std::endl;
}

std::string NationalElection::getCountry() const {
    return country;
}

std::string NationalElection::getType() const {
    return "National";
}
