#ifndef NATIONAL_ELECTION_H
#define NATIONAL_ELECTION_H

#include "Election.h"
#include <string>

class NationalElection : public Election {
private:
    std::string country;

public:
    // Constructor with string dates for easier user input
    NationalElection(std::string id, std::string name, std::string description, 
                    std::string startDateStr, std::string endDateStr, std::string country);

    virtual void displayInfo() const override;
    std::string getCountry() const;
    virtual std::string getType() const override;
};

#endif // NATIONAL_ELECTION_H
