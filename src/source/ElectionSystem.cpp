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
#include <conio.h> // For getch() on Windows

// Forward declaration for getMaskedPassword
std::string getMaskedPassword();

// Implementation of ElectionSystem class methods
ElectionSystem::ElectionSystem() : currentUser(nullptr)
{
    // Initialize the file handler
    fileHandler = new FileHandler();

    // Try to load data from files
    if (!loadData())
    {
        // If loading fails, initialize with default data
        std::cout << "No existing data found. Creating seed data..."
                  << std::endl;
        seedData();

        // Save the seed data to files
        saveData();
    }
    else
    {
        std::cout << "Existing data loaded successfully."
                  << std::endl;
    }
}

ElectionSystem::~ElectionSystem()
{
    // Save data before shutting down
    saveData();

    // Clean up elections
    for (int i = 0; i < elections.getSize(); i++)
    {
        delete elections.get(i);
    }

    // Clean up file handler
    delete fileHandler;
}

// File handling methods
bool ElectionSystem::saveData()
{
    if (!fileHandler)
    {
        return false;
    }

    std::cout << "Saving data to files..." << std::endl;

    // Use FileHandler to save all data
    bool success = fileHandler->saveAllData(*this);

    if (success)
    {
        std::cout << "Data saved successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error saving data." << std::endl;
    }

    return success;
}

bool ElectionSystem::loadData()
{
    if (!fileHandler)
    {
        return false;
    }

    std::cout << "Loading data from files..." << std::endl;

    // Use FileHandler to load all data
    bool success = fileHandler->loadAllData(*this);

    if (success)
    {
        std::cout << "Data loaded successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error loading data or no data found." << std::endl;
    }

    return success;
}

void ElectionSystem::seedData()
{
    // Add some default administrators
    admins.add(Administrator("admin", "admin123", "System Admin", "A001", "Super Admin"));
    admins.add(Administrator("manager", "manager123", "Election Manager", "A002", "Manager"));

    // Add some default voters
    voters.add(Voter("voter1", "pass123", "John Doe", "V001", "123 Main St", "VID12345"));
    voters.add(Voter("voter2", "pass456", "Jane Smith", "V002", "456 Elm St", "VID67890"));
    voters.add(Voter("voter3", "pass789", "Bob Johnson", "V003", "789 Oak St", "VID54321"));
}

bool ElectionSystem::login(std::string username, std::string password)
{
    // Try to login as voter
    for (int i = 0; i < voters.getSize(); i++)
    {
        if (voters.get(i).getUsername() == username)
        {
            if (voters.get(i).login(username, password))
            {
                currentUser = &voters.get(i);
                std::cout << "Logged in as Voter: " << currentUser->getName() << std::endl;
                return true;
            }
        }
    }
    // Try to login as admin
    for (int i = 0; i < admins.getSize(); i++)
    {
        if (admins.get(i).getUsername() == username)
        {
            if (admins.get(i).login(username, password))
            {
                currentUser = &admins.get(i);
                std::cout << "Logged in as Administrator: " << currentUser->getName() << std::endl;
                return true;
            }
        }
    }
    // Try to login as candidate
    for (int i = 0; i < candidates.getSize(); i++)
    {
        if (candidates.get(i).getUsername() == username)
        {
            if (candidates.get(i).login(username, password))
            {
                currentUser = &candidates.get(i);
                std::cout << "Logged in as Candidate: " << currentUser->getName() << std::endl;
                return true;
            }
        }
    }
    std::cout << "Invalid username or password." << std::endl;
    return false;
}

void ElectionSystem::logout()
{
    if (currentUser)
    {
        currentUser->logout();
        currentUser = nullptr;
        std::cout << "Logged out successfully." << std::endl;
    }
}

bool ElectionSystem::isLoggedIn() const
{
    return currentUser != nullptr && currentUser->isAuthenticated();
}

bool ElectionSystem::isAdmin() const
{
    return dynamic_cast<Administrator *>(currentUser) != nullptr;
}

bool ElectionSystem::isCandidate() const
{
    return dynamic_cast<Candidate *>(currentUser) != nullptr;
}

void ElectionSystem::registerVoter(std::string username, std::string password, std::string name,
                                   std::string id, std::string address, std::string voterIdNumber)
{
    // Check if the current user is an admin
    if (!isLoggedIn() || !isAdmin())
    {
        std::cout << "Only administrators can register voters." << std::endl;
        return;
    }

    // Check if username already exists
    for (int i = 0; i < voters.getSize(); i++)
    {
        if (voters.get(i).getUsername() == username)
        {
            std::cout << "Username already exists. Please choose another username." << std::endl;
            return;
        }
    }

    // Check if voter ID already exists
    for (int i = 0; i < voters.getSize(); i++)
    {
        if (voters.get(i).getVoterIdNumber() == voterIdNumber)
        {
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

void ElectionSystem::registerVoter()
{
    if (!isLoggedIn() || !isAdmin())
    {
        std::cout << "Only administrators can register voters." << std::endl;
        return;
    }
    std::string username, password, name, id, address, voterIdNumber;
    std::cin.ignore();
    std::cout << "Enter Voter Username: ";
    std::getline(std::cin, username);
    std::cout << "Enter Voter Password: ";
    password = getMaskedPassword();
    std::cout << "Enter Voter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Voter ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter Voter Address: ";
    std::getline(std::cin, address);
    std::cout << "Enter Voter ID Number: ";
    std::getline(std::cin, voterIdNumber);
    registerVoter(username, password, name, id, address, voterIdNumber);
}

void ElectionSystem::registerCandidate(std::string username, std::string password, std::string name, std::string id, std::string partyAffiliation)
{
    if (!isLoggedIn() || !isAdmin())
    {
        std::cout << "Only administrators can register candidates." << std::endl;
        return;
    }
    // Check if username already exists
    for (int i = 0; i < candidates.getSize(); i++)
    {
        if (candidates.get(i).getUsername() == username)
        {
            std::cout << "Username already exists. Please choose another username." << std::endl;
            return;
        }
    }
    // Check if candidate ID already exists
    for (int i = 0; i < candidates.getSize(); i++)
    {
        if (candidates.get(i).getCandidateId() == id)
        {
            std::cout << "Candidate ID already exists. Please check your ID number." << std::endl;
            return;
        }
    }
    // Add the new candidate
    candidates.add(Candidate(username, password, name, id, partyAffiliation));
    std::cout << "Candidate registered successfully." << std::endl;
    saveData();
}

void ElectionSystem::createElection(int electionType)
{
    if (!isLoggedIn() || !isAdmin())
    {
        std::cout << "Only administrators can create elections." << std::endl;
        return;
    }

    std::string id, name, description;
    int durationMinutes, durationSeconds;
    std::cout << "Enter Election ID: ";
    std::cin.ignore();
    std::getline(std::cin, id);
    std::cout << "Enter Election Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Description: ";
    std::getline(std::cin, description);
    std::cout << "Enter Election Duration (minutes): ";
    std::cin >> durationMinutes;
    std::cout << "Enter Election Duration (seconds): ";
    std::cin >> durationSeconds;
    std::cin.ignore();

    Election *newElection = nullptr;

    switch (electionType)
    {
    case 1:
    { // Local Election
        std::string locality;
        std::cout << "Enter Locality: ";
        std::getline(std::cin, locality);
        newElection = new LocalElection(id, name, description, "", "", locality);
        break;
    }
    case 2:
    { // National Election
        std::string country;
        std::cout << "Enter Country: ";
        std::getline(std::cin, country);
        newElection = new NationalElection(id, name, description, "", "", country);
        break;
    }
    case 3:
    { // Regional Election
        std::string region, country;
        std::cout << "Enter Region: ";
        std::getline(std::cin, region);
        std::cout << "Enter Country: ";
        std::getline(std::cin, country);
        newElection = new RegionalElection(id, name, description, "", "", region, country);
        break;
    }
    default:
        std::cout << "Invalid election type." << std::endl;
        return;
    }

    if (newElection)
    {
        newElection->setDuration(durationMinutes, durationSeconds);
        elections.add(newElection);
        std::cout << "Election created successfully." << std::endl;
    }
}

void ElectionSystem::addCandidate()
{
    if (!isLoggedIn() || !isAdmin())
    {
        std::cout << "Only administrators can add candidates." << std::endl;
        return;
    }

    // Display available elections
    displayElections();

    if (elections.getSize() == 0)
    {
        std::cout << "No elections available." << std::endl;
        return;
    }

    int electionChoice;
    std::cout << "Select an election to add a candidate to: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > elections.getSize())
    {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    Election *selectedElection = elections.get(electionChoice - 1);

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

    // Check for National Election: only one candidate per party
    if (selectedElection->getType() == "National") {
        for (int i = 0; i < selectedElection->getCandidateCount(); i++) {
            if (selectedElection->getCandidate(i).getPartyAffiliation() == partyAffiliation) {
                std::cout << "A candidate from this party already exists in this national election.\n";
                return;
            }
        }
    }
    selectedElection->addCandidate(newCandidate);
    std::cout << "Candidate added successfully." << std::endl;
}

void ElectionSystem::displayElections() const
{
    std::cout << "\nAvailable Elections:" << std::endl;
    for (int i = 0; i < elections.getSize(); i++)
    {
        Election *election = elections.get(i);
        std::cout << i + 1 << ". " << election->getName() << " - Type: " << election->getType()
                  << " - Status: " << (election->isElectionActive() ? "Active" : "Inactive") << std::endl;
    }
}

void ElectionSystem::manageElection()
{
    if (!isLoggedIn() || !isAdmin())
    {
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

    if (elections.getSize() == 0)
    {
        std::cout << "No elections available." << std::endl;
        return;
    }

    int electionChoice;
    std::cout << "Select an election: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > elections.getSize())
    {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    Election *selectedElection = elections.get(electionChoice - 1);

    if (action == 1)
    {
        selectedElection->startElection();
        std::cout << "Election started. It will end automatically after the set duration." << std::endl;
    }
    else if (action == 2)
    {
        selectedElection->endElection();
        std::cout << "Election ended manually." << std::endl;
    }
    else
    {
        std::cout << "Invalid choice." << std::endl;
    }
}

void ElectionSystem::castVote()
{
    if (!isLoggedIn() || isAdmin())
    {
        std::cout << "Only voters can cast votes." << std::endl;
        return;
    }

    // Display active elections
    std::cout << "\nActive Elections:" << std::endl;
    int activeCount = 0;
    for (int i = 0; i < elections.getSize(); i++)
    {
        Election *election = elections.get(i);
        if (election->isElectionActive())
        {
            std::cout << ++activeCount << ". " << election->getName() << " - Type: " << election->getType() << std::endl;
        }
        else if (!election->isElectionActive())
        {
            // If election was active but time expired, end it
            election->endElection();
        }
    }

    if (activeCount == 0)
    {
        std::cout << "No active elections available." << std::endl;
        return;
    }

    int electionChoice;
    std::cout << "Select an election to vote in: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > activeCount)
    {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    // Find the selected active election
    Election *selectedElection = nullptr;
    int currentActive = 0;
    for (int i = 0; i < elections.getSize(); i++)
    {
        if (elections.get(i)->isElectionActive())
        {
            currentActive++;
            if (currentActive == electionChoice)
            {
                selectedElection = elections.get(i);
                break;
            }
        }
    }

    if (!selectedElection)
    {
        std::cout << "Error selecting election." << std::endl;
        return;
    }

    // Check if already voted
    if (selectedElection->hasVoted(currentUser->getId()))
    {
        std::cout << "You have already voted in this election." << std::endl;
        return;
    }

    // Display candidates
    selectedElection->displayCandidates();

    int candidateChoice;
    std::cout << "Select a candidate to vote for: ";
    std::cin >> candidateChoice;

    if (candidateChoice < 1 || candidateChoice > selectedElection->getCandidateCount())
    {
        std::cout << "Invalid candidate selection." << std::endl;
        return;
    }

    std::string candidateId = selectedElection->getCandidate(candidateChoice - 1).getId();
    selectedElection->castVote(currentUser->getId(), candidateId);
    std::cout << "Vote cast successfully!" << std::endl;
}

void ElectionSystem::viewResults() const
{
    displayElections();

    if (elections.getSize() == 0)
    {
        return;
    }

    int electionChoice;
    std::cout << "Select an election to view results: ";
    std::cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > elections.getSize())
    {
        std::cout << "Invalid election selection." << std::endl;
        return;
    }

    Election *selectedElection = elections.get(electionChoice - 1);
    selectedElection->displayResults();
}

void ElectionSystem::displayMainMenu() const
{
    std::cout << "\n=== Online Voting System ===" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

std::string getMaskedPassword()
{
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r')
    { // Enter key
        if (ch == '\b')
        { // Backspace
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (ch == 3)
        { // Ctrl+C
            exit(0);
        }
        else if (isprint(ch))
        {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

void ElectionSystem::run()
{
    int choice;
    while (true)
    {
        if (!isLoggedIn())
        {
            displayMainMenu();
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
                std::string username, password;
                std::cout << "Enter Username: ";
                std::cin >> username;
                std::cout << "Enter Password: ";
                password = getMaskedPassword();
                login(username, password);
                break;
            }
            case 2:
                std::cout << "Thank you for using the Online Voting System!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        else
        {
            // User is logged in, show appropriate menu
            currentUser->displayMenu();
            std::cin >> choice;
            if (isAdmin())
            {
                switch (choice)
                {
                case 1:
                {
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
                    // Register Voter
                    registerVoter();
                    break;
                case 4:
                    manageElection();
                    break;
                case 5:
                    viewResults();
                    break;
                case 6:
                    logout();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
            else if (isCandidate())
            {
                switch (choice)
                {
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
            }
            else
            { // Voter
                switch (choice)
                {
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

void ElectionSystem::runDemo()
{
    std::cout << "\n=== DEMO MODE: Online Voting System ===\n";
    std::cout << "Step 1: Logging in as admin (admin/admin123)...\n";
    if (!login("admin", "admin123"))
    {
        std::cout << "Demo failed: Could not login as admin.\n";
        return;
    }
    std::cout << "Step 2: Creating a Local Election...\n";
    // Create a local election with hardcoded values
    elections.add(new LocalElection("E001", "Local Election 2025", "Demo local election.", "", "", "DemoTown"));
    std::cout << "Step 3: Adding candidates to the election...\n";
    elections.get(0)->addCandidate(Candidate("", "", "Alice Demo", "C001", "Party A"));
    elections.get(0)->addCandidate(Candidate("", "", "Bob Demo", "C002", "Party B"));
    std::cout << "Step 4: Starting the election...\n";
    elections.get(0)->startElection();
    logout();
    std::cout << "Step 5: Logging in as voter (voter1/pass123)...\n";
    if (!login("voter1", "pass123"))
    {
        std::cout << "Demo failed: Could not login as voter.\n";
        return;
    }
    std::cout << "Step 6: Casting a vote for Alice Demo...\n";
    elections.get(0)->castVote(currentUser->getId(), "C001");
    logout();
    std::cout << "Step 7: Logging in as admin to end election and view results...\n";
    login("admin", "admin123");
    elections.get(0)->endElection();
    std::cout << "\nDEMO: Final Results for 'Local Election 2025':\n";
    elections.get(0)->displayResults();
    logout();
    std::cout << "\n=== DEMO COMPLETE ===\n";
}
