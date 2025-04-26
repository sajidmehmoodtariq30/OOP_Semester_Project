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

bool ElectionSystem::login(std::string username, std::string password) {
    // Try to login as voter
    for (int i = 0; i < voters.getSize(); i++) {
        if (voters.get(i).getUsername() == username) {
            if (voters.get(i).login(username, password)) {
                currentUser = &voters.get(i);
                std::cout << "Logged in as Voter: " << currentUser->getName() << std::endl;
                return true;
            }
        }
    }
    // Try to login as admin
    for (int i = 0; i < admins.getSize(); i++) {
        if (admins.get(i).getUsername() == username) {
            if (admins.get(i).login(username, password)) {
                currentUser = &admins.get(i);
                std::cout << "Logged in as Administrator: " << currentUser->getName() << std::endl;
                return true;
            }
        }
    }
    // Try to login as candidate
    for (int i = 0; i < candidates.getSize(); i++) {
        if (candidates.get(i).getUsername() == username) {
            if (candidates.get(i).login(username, password)) {
                currentUser = &candidates.get(i);
                std::cout << "Logged in as Candidate: " << currentUser->getName() << std::endl;
                return true;
            }
        }
    }
    std::cout << "Invalid username or password." << std::endl;
    return false;
}

void ElectionSystem::logout() {
    if (currentUser) {
        currentUser->logout();
        currentUser = nullptr;
        std::cout << "Logged out successfully." << std::endl;
    }
}

bool ElectionSystem::isLoggedIn() const {
    return currentUser != nullptr && currentUser->isAuthenticated();
}

bool ElectionSystem::isAdmin() const {
    return dynamic_cast<Administrator*>(currentUser) != nullptr;
}

bool ElectionSystem::isCandidate() const {
    return dynamic_cast<Candidate*>(currentUser) != nullptr;
}