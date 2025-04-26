#include "../header/ElectionSystem.h"

ElectionSystem::ElectionSystem() : currentUser(nullptr) {
    // Initialize the file handler
    fileHandler = new FileHandler();
    
    // Try to load data from files
    if (!loadData()) {
        // If loading fails, initialize with default data
        std::cout << "No existing data found. Creating seed data..."
                  << std::endl;
        seedData();
        
        // Save the seed data to files
        saveData();
    } else {
        std::cout << "Existing data loaded successfully."
                  << std::endl;
    }
}

ElectionSystem::~ElectionSystem() {
    // Save data before shutting down
    saveData();
    
    // Clean up file handler
    delete fileHandler;
}

bool ElectionSystem::saveData() {
    if (!fileHandler) {
        return false;
    }

    std::cout << "Saving data to files..." << std::endl;

    // Use FileHandler to save all data
    bool success = fileHandler->saveAllData(*this);

    if (success) {
        std::cout << "Data saved successfully." << std::endl;
    } else {
        std::cerr << "Error saving data." << std::endl;
    }

    return success;
}

bool ElectionSystem::loadData() {
    if (!fileHandler) {
        return false;
    }

    std::cout << "Loading data from files..." << std::endl;

    // Use FileHandler to load all data
    bool success = fileHandler->loadAllData(*this);

    if (success) {
        std::cout << "Data loaded successfully." << std::endl;
    } else {
        std::cerr << "Error loading data or no data found." << std::endl;
    }

    return success;
}

void ElectionSystem::seedData() {
    // Add some default administrators
    admins.add(Administrator("admin", "admin123", "System Admin", "A001", "Super Admin"));
    admins.add(Administrator("manager", "manager123", "Election Manager", "A002", "Manager"));

    // Add some default voters
    voters.add(Voter("voter1", "pass123", "Mooez Sultan", "V001", "Lahore Pakistan", "VID12345"));
    voters.add(Voter("voter2", "pass456", "Rehan Ali", "V002", "Lahore Pakistan", "VID67890"));
    voters.add(Voter("voter3", "pass789", "Haseeb Iqbal", "V003", "Lahore Pakistan", "VID54321"));
}

void ElectionSystem::createElection(int electionType) {
    if (!isLoggedIn() || !isAdmin()) {
        std::cout << "Only administrators can create elections." << std::endl;
        return;
    }

    std::string id, name, description, startDateStr, endDateStr;
    time_t startDate, endDate;

    std::cout << "Enter Election ID: ";
    std::cin.ignore();
    std::getline(std::cin, id);
    std::cout << "Enter Election Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Description: ";
    std::getline(std::cin, description);
    std::cout << "Enter Start Date (YYYY-MM-DD): ";
    std::getline(std::cin, startDateStr);
    std::cout << "Enter End Date (YYYY-MM-DD): ";
    std::getline(std::cin, endDateStr);

    // In a real system, you would parse these date strings and convert to time_t
    // For simplicity, we'll just use the current time
    startDate = time(nullptr);
    endDate = time(nullptr) + 30*24*60*60; // Add 30 days

    Election* newElection = nullptr;

    switch (electionType) {
    case 1: { // Local Election
        std::string locality;
        std::cout << "Enter Locality: ";
        std::getline(std::cin, locality);
        // Using the converted time_t values for dates
        newElection = new LocalElection(id, name, description, startDateStr, endDateStr, locality);
        break;
    }
    case 2: { // National Election
        std::string country;
        std::cout << "Enter Country: ";
        std::getline(std::cin, country);
        newElection = new NationalElection(id, name, description, startDateStr, endDateStr, country);
        break;
    }
    case 3: { // Regional Election
        std::string region, country;
        std::cout << "Enter Region: ";
        std::getline(std::cin, region);
        std::cout << "Enter Country: ";
        std::getline(std::cin, country);
        newElection = new RegionalElection(id, name, description, startDateStr, endDateStr, region, country);
        break;
    }
    default:
        std::cout << "Invalid election type." << std::endl;
        return;
    }

    if (newElection) {
        elections.add(newElection);
        std::cout << "Election created successfully." << std::endl;
    }
}