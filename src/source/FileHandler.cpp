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

bool FileHandler::saveAllData(const ElectionSystem& system) {
    // We need accessors in ElectionSystem to get voters, admins, and elections
    
    bool votersSaved = true;
    bool adminsSaved = true;
    bool electionsSaved = true;
    
    return votersSaved && adminsSaved && electionsSaved;
}

bool FileHandler::loadAllData(ElectionSystem& system) {
    // We need methods in ElectionSystem to set voters, admins, and elections
    
    bool votersLoaded = true;
    bool adminsLoaded = true;
    bool electionsLoaded = true;
    
    return votersLoaded && adminsLoaded && electionsLoaded;
}