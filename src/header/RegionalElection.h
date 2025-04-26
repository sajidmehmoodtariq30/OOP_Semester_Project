#ifndef REGIONAL_ELECTION_H
#define REGIONAL_ELECTION_H

#include "Election.h"
#include <string>

class RegionalElection : public Election {
private:
    std::string region;
    std::string country;

public:
    // Constructor with string dates for easier user input
    RegionalElection(std::string id, std::string name, std::string description, 
                    std::string startDateStr, std::string endDateStr, 
                    std::string region, std::string country);

    virtual void displayInfo() const override;
    std::string getRegion() const;
    std::string getCountry() const;
    virtual std::string getType() const override;
};

#endif // REGIONAL_ELECTION_H
