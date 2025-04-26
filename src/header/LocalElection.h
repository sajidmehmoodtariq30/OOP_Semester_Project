#ifndef LOCAL_ELECTION_H
#define LOCAL_ELECTION_H

#include "Election.h"
#include <string>

class LocalElection : public Election {
private:
    std::string locality;

public:
    // Constructor with string dates for easier user input
    LocalElection(std::string id, std::string name, std::string description, 
                 std::string startDateStr, std::string endDateStr, std::string locality);

    virtual void displayInfo() const override;
    std::string getLocality() const;
    virtual std::string getType() const override;
};

#endif // LOCAL_ELECTION_H
