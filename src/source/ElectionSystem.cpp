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