@echo off
echo Building Online Voting System...

REM Create a build directory if it doesn't exist
if not exist build mkdir build
cd build

REM Compile all source files
g++ -std=c++14 -I../src/header -o voting_system.exe ../main.cpp ../src/source/*.cpp

if %ERRORLEVEL% EQU 0 (
    echo Build successful!
    echo.
    echo Run the program with: voting_system.exe
) else (
    echo Build failed with error code %ERRORLEVEL%
)

cd ..
