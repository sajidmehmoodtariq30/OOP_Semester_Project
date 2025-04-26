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

void ElectionSystem::registerVoter(std::string username, std::string password, std::string name, 
    std::string id, std::string address, std::string voterIdNumber) {
// Check if the current user is an admin
if (!isLoggedIn() || !isAdmin()) {
std::cout << "Only administrators can register voters." << std::endl;
return;
}

// Check if username already exists
for (int i = 0; i < voters.getSize(); i++) {
if (voters.get(i).getUsername() == username) {
std::cout << "Username already exists. Please choose another username." << std::endl;
return;
}
}

// Check if voter ID already exists
for (int i = 0; i < voters.getSize(); i++) {
if (voters.get(i).getVoterIdNumber() == voterIdNumber) {
std::cout << "Voter ID already exists. Please check your ID number." << std::endl;
return;
}
}

// Store the original password so it can be used for login
// This way, the voter object has the plaintext password for authentication
// but we'll save the encrypted version to the file
std::cout << "Creating voter with encrypted password..." << std::endl;

// Add the new voter with original password (for login authentication)
voters.add(Voter(username, password, name, id, address, voterIdNumber));
std::cout << "Voter registered successfully." << std::endl;

// Save all data immediately to ensure the encrypted password is stored
saveData();
}

void ElectionSystem::registerCandidate(std::string username, std::string password, std::string name, std::string id, std::string partyAffiliation) {
    if (!isLoggedIn() || !isAdmin()) {
        std::cout << "Only administrators can register candidates." << std::endl;
        return;
    }
    // Check if username already exists
    for (int i = 0; i < candidates.getSize(); i++) {
        if (candidates.get(i).getUsername() == username) {
            std::cout << "Username already exists. Please choose another username." << std::endl;
            return;
        }
    }
    // Check if candidate ID already exists
    for (int i = 0; i < candidates.getSize(); i++) {
        if (candidates.get(i).getCandidateId() == id) {
            std::cout << "Candidate ID already exists. Please check your ID number." << std::endl;
            return;
        }
    }
    // Add the new candidate
    candidates.add(Candidate(username, password, name, id, partyAffiliation));
    std::cout << "Candidate registered successfully." << std::endl;
    saveData();
}

void ElectionSystem::addCandidate() {
    if (!isLoggedIn() || !isAdmin()) {
        std::cout << "Only administrators can add candidates." << std::endl;
        return;
    }

    // Display available elections
    displayElections();

    if (elections.getSize() == 0) {
        std::cout << "No elections available." << std::endl;
        return;
    }

    int electionChoice;
    std::cout << "Select an election to add a candidate to: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > elections.getSize()) {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    Election* selectedElection = elections.get(electionChoice - 1);

    std::string id, name, partyAffiliation;
    std::cin.ignore(); // Clear the newline character

    std::cout << "Enter Candidate ID: ";
    std::getline(std::cin, id);

    std::cout << "Enter Candidate Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Party Affiliation: ";
    std::getline(std::cin, partyAffiliation);

    // For election candidates, use empty username/password
    Candidate newCandidate("", "", name, id, partyAffiliation);
    selectedElection->addCandidate(newCandidate);
    std::cout << "Candidate added successfully." << std::endl;
}