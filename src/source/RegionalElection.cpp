#include "../header/RegionalElection.h"
#include <iostream>
#include <ctime>

RegionalElection::RegionalElection(std::string id, std::string name, std::string description, 
                                 std::string startDate, std::string endDate, 
                                 std::string region, std::string country)
    : Election(id, name, description, time(nullptr), time(nullptr)), 
      region(region), country(country) {
    // This is a simplified implementation - in a real application, you would parse the date strings
    // and convert them to time_t values properly
}

void RegionalElection::displayInfo() const {
    Election::displayInfo();
    std::cout << "Region: " << region << std::endl;
    std::cout << "Country: " << country << std::endl;
}

std::string RegionalElection::getRegion() const {
    return region;
}

std::string RegionalElection::getCountry() const {
    return country;
}

std::string RegionalElection::getType() const {
    return "Regional";
}
