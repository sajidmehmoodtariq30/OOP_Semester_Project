#include "../header/ElectionSystem.h"
#include "../header/User.h"
#include "../header/Voter.h"
#include "../header/Admin.h"
#include "../header/Election.h"
#include "../header/LocalElection.h"
#include "../header/NationalElection.h"
#include "../header/RegionalElection.h"
#include "../header/Candidate.h"
#include "../header/Vote.h"
#include "../header/FileHandler.h"
#include <iostream>
#include <string>
#include <ctime>
#include <filesystem>

// Implementation of ElectionSystem class methods
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
    
    // Clean up elections
    for (int i = 0; i < elections.getSize(); i++) {
        delete elections.get(i);
    }
    
    // Clean up file handler
    delete fileHandler;
}

// File handling methods
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
    voters.add(Voter("voter1", "pass123", "John Doe", "V001", "123 Main St", "VID12345"));
    voters.add(Voter("voter2", "pass456", "Jane Smith", "V002", "456 Elm St", "VID67890"));
    voters.add(Voter("voter3", "pass789", "Bob Johnson", "V003", "789 Oak St", "VID54321"));
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

void ElectionSystem::displayElections() const {
    std::cout << "\nAvailable Elections:" << std::endl;
    for (int i = 0; i < elections.getSize(); i++) {
        Election* election = elections.get(i);
        std::cout << i + 1 << ". " << election->getName() << " - Type: " << election->getType()
             << " - Status: " << (election->isElectionActive() ? "Active" : "Inactive") << std::endl;
    }
}

void ElectionSystem::manageElection() {
    if (!isLoggedIn() || !isAdmin()) {
        std::cout << "Only administrators can manage elections." << std::endl;
        return;
    }

    int action;
    std::cout << "\nElection Management:" << std::endl;
    std::cout << "1. Start Election" << std::endl;
    std::cout << "2. End Election" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> action;

    displayElections();

    if (elections.getSize() == 0) {
        std::cout << "No elections available." << std::endl;
        return;
    }

    int electionChoice;
    std::cout << "Select an election: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > elections.getSize()) {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    Election* selectedElection = elections.get(electionChoice - 1);

    if (action == 1) {
        selectedElection->startElection();
    } else if (action == 2) {
        selectedElection->endElection();
    } else {
        std::cout << "Invalid choice." << std::endl;
    }
}

void ElectionSystem::castVote() {
    if (!isLoggedIn() || isAdmin()) {
        std::cout << "Only voters can cast votes." << std::endl;
        return;
    }

    // Display active elections
    std::cout << "\nActive Elections:" << std::endl;
    int activeCount = 0;
    for (int i = 0; i < elections.getSize(); i++) {
        Election* election = elections.get(i);
        if (election->isElectionActive()) {
            std::cout << ++activeCount << ". " << election->getName() << " - Type: " << election->getType() << std::endl;
        }
    }

    if (activeCount == 0) {
        std::cout << "No active elections available." << std::endl;
        return;
    }

    int electionChoice;
    std::cout << "Select an election to vote in: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > activeCount) {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    // Find the selected active election
    Election* selectedElection = nullptr;
    int currentActive = 0;
    for (int i = 0; i < elections.getSize(); i++) {
        if (elections.get(i)->isElectionActive()) {
            currentActive++;
            if (currentActive == electionChoice) {
                selectedElection = elections.get(i);
                break;
            }
        }
    }

    if (!selectedElection) {
        std::cout << "Error selecting election." << std::endl;
        return;
    }

    // Check if already voted
    if (selectedElection->hasVoted(currentUser->getId())) {
        std::cout << "You have already voted in this election." << std::endl;
        return;
    }

    // Display candidates
    selectedElection->displayCandidates();

    int candidateChoice;
    std::cout << "Select a candidate to vote for: ";
    std::cin >> candidateChoice;

    if (candidateChoice < 1 || candidateChoice > selectedElection->getCandidateCount()) {
        std::cout << "Invalid candidate selection." << std::endl;
        return;
    }

    std::string candidateId = selectedElection->getCandidate(candidateChoice - 1).getId();
    selectedElection->castVote(currentUser->getId(), candidateId);
}

void ElectionSystem::viewResults() const {
    displayElections();

    if (elections.getSize() == 0) {
        return;
    }

    int electionChoice;
    std::cout << "Select an election to view results: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > elections.getSize()) {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    Election* selectedElection = elections.get(electionChoice - 1);
    selectedElection->displayResults();
}

void ElectionSystem::displayMainMenu() const {
    std::cout << "\n=== Online Voting System ===" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void ElectionSystem::run() {
    int choice;
    while (true) {
        if (!isLoggedIn()) {
            displayMainMenu();
            std::cin >> choice;
            switch (choice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter Username: ";
                std::cin >> username;
                std::cout << "Enter Password: ";
                std::cin >> password;
                login(username, password);
                break;
            }
            case 2:
                std::cout << "Thank you for using the Online Voting System!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } else {
            // User is logged in, show appropriate menu
            currentUser->displayMenu();
            std::cin >> choice;
            if (isAdmin()) {
                switch (choice) {
                case 1: {
                    int electionType;
                    std::cout << "\nSelect Election Type:" << std::endl;
                    std::cout << "1. Local Election" << std::endl;
                    std::cout << "2. National Election" << std::endl;
                    std::cout << "3. Regional Election" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> electionType;
                    createElection(electionType);
                    break;
                }
                case 2:
                    addCandidate();
                    break;
                case 3:
                    manageElection();
                    break;
                case 4:
                    viewResults();
                    break;
                case 5:
                    logout();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } else if (isCandidate()) {
                switch (choice) {
                case 1:
                    std::cout << "\nCandidate Profile: " << currentUser->getName() << std::endl;
                    break;
                case 2:
                    viewResults();
                    break;
                case 3:
                    logout();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } else { // Voter
                switch (choice) {
                case 1:
                    castVote();
                    break;
                case 2:
                    viewResults();
                    break;
                case 3:
                    logout();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        }
    }
}
