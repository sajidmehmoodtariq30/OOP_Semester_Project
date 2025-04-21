cmake_minimum_required(VERSION 3.10)
project(OnlineVotingSystem)

set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(src/header)

# Source files
file(GLOB SOURCES 
    "src/source/*.cpp"
    "*.cpp"
)

# Create executable
add_executable(voting_system ${SOURCES})
