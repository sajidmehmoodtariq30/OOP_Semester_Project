#include "../header/FileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <direct.h> // For _mkdir on Windows

// Constructor
FileHandler::FileHandler() {
    // Ensure data directory exists when FileHandler is created
    ensureDataDirectoryExists();
}

// Destructor
FileHandler::~FileHandler() {
    // Nothing to clean up
}

// Helper method to ensure data directory exists
bool FileHandler::ensureDataDirectoryExists() {
    int result = _mkdir("data");
    if (result == 0 || errno == EEXIST) {
        return true;
    } else {
        std::cerr << "Error creating data directory" << std::endl;
        return false;
    }
}

// TXT Helper Methods
class TXTParser {
private:
    std::string* fields;
    int size;
    int capacity;
    
public:
    TXTParser() : fields(nullptr), size(0), capacity(0) {}
    
    ~TXTParser() {
        if (fields) {
            delete[] fields;
        }
    }
    
    void parse(const std::string& line) {
        // Clear any existing data
        if (fields) {
            delete[] fields;
            fields = nullptr;
        }
        
        // Pre-calculate number of fields by counting commas (rough estimate)
        // This helps reduce reallocations by setting a better initial capacity
        int commaCount = 0;
        bool inQuotes = false;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '"') {
                inQuotes = !inQuotes;
            } else if (line[i] == ',' && !inQuotes) {
                commaCount++;
            }
        }
        
        // Initial allocation with better size estimate
        capacity = commaCount + 2; // +1 for last field, +1 for buffer
        size = 0;
        fields = new std::string[capacity];
        
        // Parse the line
        inQuotes = false;
        std::string field;
        
        for (int i = 0; i < line.size(); i++) {
            char ch = line[i];
            
            if (ch == '"') {
                inQuotes = !inQuotes;
            } else if (ch == ',' && !inQuotes) {
                // Add field to array
                addField(field);
                field.clear();
            } else {
                field += ch;
            }
        }
        
        // Add the last field
        addField(field);
    }
    
    void addField(const std::string& field) {
        // Resize if needed
        if (size >= capacity) {
            int newCapacity = capacity * 2;
            std::string* newFields = new std::string[newCapacity];
            
            // Use copy with size check as a safety measure
            for (int i = 0; i < size && i < capacity; i++) {
                newFields[i] = fields[i];
            }
            
            delete[] fields;
            fields = newFields;
            capacity = newCapacity;
        }
        
        // Add the field to the array
        fields[size++] = field;
    }
    
    std::string get(int index) const {
        if (index >= 0 && index < size) {
            return fields[index];
        }
        return "";
    }
    
    int getSize() const {
        return size;
    }
};

TXTParser FileHandler::splitTXT(const std::string& line) {
    TXTParser parser;
    parser.parse(line);
    return parser;
}

std::string FileHandler::escapeTXT(const std::string& field) {
    if (field.find(',') != std::string::npos || field.find('"') != std::string::npos) {
        std::string escaped = field;
        // Replace all double quotes with two double quotes
        size_t pos = 0;
        while ((pos = escaped.find('"', pos)) != std::string::npos) {
            escaped.replace(pos, 1, "\"\"");
            pos += 2;
        }
        // Wrap in quotes
        return "\"" + escaped + "\"";
    }
    return field;
}

// Simple shift cipher (Caesar cipher) with shift of 3 for password encryption
std::string FileHandler::encryptPassword(const std::string& password) {
    std::string encrypted = password;
    for (int i = 0; i < encrypted.size(); i++) {  // Changed size_t to int
        if (isalnum(encrypted[i])) {  // Only encrypt alphanumeric characters
            encrypted[i] = encrypted[i] + 3;  // Shift by 3
        }
    }
    return encrypted;
}

// Simple shift cipher (Caesar cipher) with shift of -3 for password decryption
std::string FileHandler::decryptPassword(const std::string& encryptedPassword) {
    std::string decrypted = encryptedPassword;
    for (int i = 0; i < decrypted.size(); i++) {  // Changed size_t to int
        if (isalnum(decrypted[i])) {  // Only decrypt alphanumeric characters
            decrypted[i] = decrypted[i] - 3;  // Shift by -3
        }
    }
    return decrypted;
}

// Serialization Methods
std::string FileHandler::serializeVoter(const Voter& voter) {
    // Get password from default users for demonstration
    std::string encryptedPassword = "";
    std::string username = voter.getUsername();
    
    // For default users, we know the passwords
    if (username == "voter1") {
        encryptedPassword = encryptPassword("pass123");
    } else if (username == "voter2") {
        encryptedPassword = encryptPassword("pass456");
    } else if (username == "voter3") {
        encryptedPassword = encryptPassword("pass789");
    } else {
        // For non-default users, the password should have been encrypted when they were added
        // Just use placeholder for now (this is a limitation we would fix in a real system)
        encryptedPassword = encryptPassword("defaultpass");
    }
    
    std::ostringstream oss;
    oss << escapeTXT(voter.getUsername()) << ","
        << escapeTXT(encryptedPassword) << ","
        << escapeTXT(voter.getName()) << ","
        << escapeTXT(voter.getId()) << ","
        << escapeTXT(voter.getAddress()) << ","
        << escapeTXT(voter.getVoterIdNumber());
    return oss.str();
}

std::string FileHandler::serializeAdmin(const Administrator& admin) {
    // Get password from default users for demonstration
    std::string encryptedPassword = "";
    std::string username = admin.getUsername();
    
    // For default admins, we know the passwords
    if (username == "admin") {
        encryptedPassword = encryptPassword("admin123");
    } else if (username == "manager") {
        encryptedPassword = encryptPassword("manager123");
    } else {
        // For non-default admins, the password should have been encrypted when they were added
        // Just use placeholder for now (this is a limitation we would fix in a real system)
        encryptedPassword = encryptPassword("defaultpass");
    }
    
    std::ostringstream oss;
    oss << escapeTXT(admin.getUsername()) << ","
        << escapeTXT(encryptedPassword) << ","
        << escapeTXT(admin.getName()) << ","
        << escapeTXT(admin.getId()) << ","
        << escapeTXT("Admin"); // Role isn't accessible via a getter
    return oss.str();
}

std::string FileHandler::serializeElection(const Election* election) {
    std::ostringstream oss;
    oss << escapeTXT(election->getId()) << ","
        << escapeTXT(election->getName()) << ","
        << escapeTXT(election->getType()) << ","  // Type helps identify the correct class during deserialization
        << escapeTXT(election->isElectionActive() ? "1" : "0");

    // Serialize additional type-specific fields
    if (election->getType() == "Local") {
        const LocalElection* local = dynamic_cast<const LocalElection*>(election);
        if (local) {
            oss << "," << escapeTXT(local->getLocality());
        }
    } else if (election->getType() == "National") {
        const NationalElection* national = dynamic_cast<const NationalElection*>(election);
        if (national) {
            oss << "," << escapeTXT(national->getCountry());
        }
    } else if (election->getType() == "Regional") {
        const RegionalElection* regional = dynamic_cast<const RegionalElection*>(election);
        if (regional) {
            oss << "," << escapeTXT(regional->getRegion()) 
                << "," << escapeTXT(regional->getCountry());
        }
    }

    return oss.str();
}

std::string FileHandler::serializeCandidate(const Candidate& candidate, const std::string& electionId) {
    std::ostringstream oss;
    oss << escapeTXT(candidate.getCandidateId()) << ","
        << escapeTXT(candidate.getName()) << ","
        << escapeTXT(candidate.getPartyAffiliation()) << ","
        << candidate.getVoteCount() << ","
        << escapeTXT(electionId);  // Store which election this candidate belongs to
    return oss.str();
}

std::string FileHandler::serializeVote(const Vote& vote, const std::string& electionId) {
    std::ostringstream oss;
    oss << escapeTXT(vote.getVoterId()) << ","
        << escapeTXT(vote.getCandidateId()) << ","
        << escapeTXT(electionId);  // Store which election this vote belongs to
    return oss.str();
}

// Deserialization Methods
Voter FileHandler::deserializeVoter(const std::string& data) {
    TXTParser fields = splitTXT(data);
    
    if (fields.getSize() >= 6) {
        std::string username = fields.get(0);
        std::string encryptedPassword = fields.get(1);
        
        // Decrypt the password
        std::string password = decryptPassword(encryptedPassword);
        
        return Voter(
            username,
            password,
            fields.get(2), // name
            fields.get(3), // id
            fields.get(4), // address
            fields.get(5)  // voterIdNumber
        );
    }
    
    // Return a default voter if data is invalid
    return Voter("", "", "", "", "", "");
}

Administrator FileHandler::deserializeAdmin(const std::string& data) {
    TXTParser fields = splitTXT(data);
    
    if (fields.getSize() >= 5) {
        std::string username = fields.get(0);
        std::string encryptedPassword = fields.get(1);
        
        // Decrypt the password
        std::string password = decryptPassword(encryptedPassword);
        
        return Administrator(
            username,
            password,
            fields.get(2), // name
            fields.get(3), // id
            fields.get(4)  // role
        );
    }
    
    // Return a default admin if data is invalid
    return Administrator("", "", "", "", "");
}

Election* FileHandler::deserializeElection(const std::string& data) {
    TXTParser fields = splitTXT(data);
    
    if (fields.getSize() >= 4) {
        std::string id = fields.get(0);
        std::string name = fields.get(1);
        std::string type = fields.get(2);
        bool isActive = (fields.get(3) == "1");
        
        // Use string dates for constructors
        std::string startDateStr = "2025-04-17";
        std::string endDateStr = "2025-05-17";
        std::string description = "Loaded from file";
        
        // Create appropriate election type based on the stored type
        if (type == "Local" && fields.getSize() >= 5) {
            return new LocalElection(id, name, description, startDateStr, endDateStr, fields.get(4));
        } else if (type == "National" && fields.getSize() >= 5) {
            return new NationalElection(id, name, description, startDateStr, endDateStr, fields.get(4));
        } else if (type == "Regional" && fields.getSize() >= 6) {
            return new RegionalElection(id, name, description, startDateStr, endDateStr, fields.get(4), fields.get(5));
        }
    }
    
    // Return nullptr if data is invalid or unrecognized type
    return nullptr;
}

Candidate FileHandler::deserializeCandidate(const std::string& data) {
    TXTParser fields = splitTXT(data);
    if (fields.getSize() >= 5) {
        std::string id = fields.get(0);
        std::string name = fields.get(1);
        std::string party = fields.get(2);
        int voteCount = 0;
        try {
            voteCount = std::stoi(fields.get(3));
        } catch (...) {}
        // For election candidates, username/password are empty
        Candidate candidate("", "", name, id, party);
        // Set voteCount via a workaround (direct access or add a setter if needed)
        for (int i = 0; i < voteCount; ++i) candidate.incrementVotes();
        return candidate;
    }
    // Return a default candidate if data is invalid
    return Candidate();
}

Vote FileHandler::deserializeVote(const std::string& data) {
    TXTParser fields = splitTXT(data);
    
    if (fields.getSize() >= 3) {
        // Vote constructor requires voterId, candidateId, and electionId
        return Vote(fields.get(0), fields.get(1), fields.get(2));
    }
    
    // Return a default vote if data is invalid, using default constructor
    return Vote();
}

// Save Methods
bool FileHandler::saveVoters(const Array<Voter>& voters) {
    std::ofstream file(VOTERS_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening file for voters: " << VOTERS_FILE << std::endl;
        return false;
    }
    
    for (int i = 0; i < voters.getSize(); i++) {
        file << serializeVoter(voters.get(i)) << std::endl;
    }
    
    return true;
}

bool FileHandler::saveAdmins(const Array<Administrator>& admins) {
    std::ofstream file(ADMINS_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening file for admins: " << ADMINS_FILE << std::endl;
        return false;
    }
    
    for (int i = 0; i < admins.getSize(); i++) {
        file << serializeAdmin(admins.get(i)) << std::endl;
    }
    
    return true;
}

bool FileHandler::saveCandidates(const Array<Candidate>& candidates) {
    std::ofstream file("data/candidates.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file for candidates: data/candidates.txt" << std::endl;
        return false;
    }
    for (int i = 0; i < candidates.getSize(); i++) {
        // Save username, encrypted password, name, id, partyAffiliation
        std::string encryptedPassword = encryptPassword(candidates.get(i).getUsername()); // Placeholder, should use actual password
        file << escapeTXT(candidates.get(i).getUsername()) << ","
             << escapeTXT(encryptedPassword) << ","
             << escapeTXT(candidates.get(i).getName()) << ","
             << escapeTXT(candidates.get(i).getCandidateId()) << ","
             << escapeTXT(candidates.get(i).getPartyAffiliation()) << std::endl;
    }
    return true;
}

bool FileHandler::loadCandidates(Array<Candidate>& candidates) {
    std::ifstream file("data/candidates.txt");
    if (!file.is_open()) {
        // Not an error if file doesn't exist yet
        return true;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            TXTParser fields = splitTXT(line);
            if (fields.getSize() >= 5) {
                std::string username = fields.get(0);
                std::string password = decryptPassword(fields.get(1));
                std::string name = fields.get(2);
                std::string id = fields.get(3);
                std::string party = fields.get(4);
                candidates.add(Candidate(username, password, name, id, party));
            }
        }
    }
    return true;
}

bool FileHandler::saveElections(const Array<Election*>& elections) {
    // Save elections
    std::ofstream electionFile(ELECTIONS_FILE);
    if (!electionFile.is_open()) {
        std::cerr << "Error opening file for elections: " << ELECTIONS_FILE << std::endl;
        return false;
    }
    
    // Save candidates
    std::ofstream candidateFile(CANDIDATES_FILE);
    if (!candidateFile.is_open()) {
        std::cerr << "Error opening file for candidates: " << CANDIDATES_FILE << std::endl;
        return false;
    }
    
    // Save votes
    std::ofstream voteFile(VOTES_FILE);
    if (!voteFile.is_open()) {
        std::cerr << "Error opening file for votes: " << VOTES_FILE << std::endl;
        return false;
    }
    
    for (int i = 0; i < elections.getSize(); i++) {
        Election* election = elections.get(i);
        electionFile << serializeElection(election) << std::endl;
        
        // Save candidates for this election
        for (int j = 0; j < election->getCandidateCount(); j++) {
            const Candidate& candidate = election->getCandidate(j);
            candidateFile << serializeCandidate(candidate, election->getId()) << std::endl;
        }
        
        // Note: We would need a way to access votes from the Election class
        // This is a placeholder for that functionality
        // for (int j = 0; j < election->getVoteCount(); j++) {
        //    const Vote& vote = election->getVote(j);
        //    voteFile << serializeVote(vote, election->getId()) << std::endl;
        // }
    }
    
    return true;
}

// Load Methods
bool FileHandler::loadVoters(Array<Voter>& voters) {
    std::ifstream file(VOTERS_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening file for voters: " << VOTERS_FILE << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Voter voter = deserializeVoter(line);
            voters.add(voter);
        }
    }
    
    return true;
}

bool FileHandler::loadAdmins(Array<Administrator>& admins) {
    std::ifstream file(ADMINS_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening file for admins: " << ADMINS_FILE << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Administrator admin = deserializeAdmin(line);
            admins.add(admin);
        }
    }
    
    return true;
}

bool FileHandler::loadElections(Array<Election*>& elections) {
    // First clear any existing elections to avoid memory leaks
    for (int i = 0; i < elections.getSize(); i++) {
        delete elections.get(i);
    }
    
    // Load elections
    std::ifstream electionFile(ELECTIONS_FILE);
    if (!electionFile.is_open()) {
        std::cerr << "Error opening file for elections: " << ELECTIONS_FILE << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(electionFile, line)) {
        if (!line.empty()) {
            Election* election = deserializeElection(line);
            if (election) {
                elections.add(election);
            }
        }
    }
    
    // Load candidates
    std::ifstream candidateFile(CANDIDATES_FILE);
    if (candidateFile.is_open()) {
        std::string line;
        while (std::getline(candidateFile, line)) {
            if (!line.empty()) {
                TXTParser fields = splitTXT(line);
                if (fields.getSize() >= 5) {
                    Candidate candidate = deserializeCandidate(line);
                    std::string electionId = fields.get(4);
                    
                    // Find the election and add the candidate
                    for (int i = 0; i < elections.getSize(); i++) {
                        if (elections.get(i)->getId() == electionId) {
                            elections.get(i)->addCandidate(candidate);
                            break;
                        }
                    }
                }
            }
        }
    }
    
    // Load votes
    std::ifstream voteFile(VOTES_FILE);
    if (voteFile.is_open()) {
        std::string line;
        while (std::getline(voteFile, line)) {
            if (!line.empty()) {
                TXTParser fields = splitTXT(line);
                if (fields.getSize() >= 3) {
                    Vote vote = deserializeVote(line);
                    std::string electionId = fields.get(2);
                    
                    // Find the election and add the vote
                    for (int i = 0; i < elections.getSize(); i++) {
                        if (elections.get(i)->getId() == electionId) {
                            elections.get(i)->castVote(vote.getVoterId(), vote.getCandidateId());
                            break;
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

// Save all data from ElectionSystem
bool FileHandler::saveAllData(const ElectionSystem& system) {
    const Array<Voter>& voters = system.getVoters();
    const Array<Administrator>& admins = system.getAdmins();
    const Array<Candidate>& candidates = system.getCandidates();
    const Array<Election*>& elections = system.getElections();
    bool votersSaved = saveVoters(voters);
    bool adminsSaved = saveAdmins(admins);
    bool candidatesSaved = saveCandidates(candidates);
    bool electionsSaved = saveElections(elections);
    return votersSaved && adminsSaved && candidatesSaved && electionsSaved;
}

// Load all data into ElectionSystem
bool FileHandler::loadAllData(ElectionSystem& system) {
    Array<Voter>& voters = system.getVoters();
    Array<Administrator>& admins = system.getAdmins();
    Array<Candidate>& candidates = system.getCandidates();
    Array<Election*>& elections = system.getElections();
    bool votersLoaded = loadVoters(voters);
    bool adminsLoaded = loadAdmins(admins);
    bool candidatesLoaded = loadCandidates(candidates);
    bool electionsLoaded = loadElections(elections);
    return votersLoaded && adminsLoaded && candidatesLoaded && electionsLoaded;
}
