#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "User.h"
#include "Member.h"
#include "Supporter.h"
#include "Admin.h"
#include "Request.h"
#include <algorithm>
#include <limits>

// Global variables
std::vector<Member> members; 
std::vector<Supporter> supporters; 
Admin admin("admin", "rmit1234"); 

// Function to register a new member
void registerMember() {
    std::string username, password, fullName, phoneNumber, email, address;
    std::string skillName;
    int pointsPerHour;
    float minHostRating;
    int creditPoints = 20; // Initialize credit points to 20 for new members

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter full name: ";
    std::cin.ignore(); // To ignore the newline left in the buffer
    std::getline(std::cin, fullName);
    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter address: ";
    std::cin.ignore(); // To ignore the newline left in the buffer
    std::getline(std::cin, address);

    // Collect skill information
    std::cout << "Enter your skill (e.g., English tutoring): ";
    std::getline(std::cin, skillName);

    float tempPointsPerHour;
    std::cout << "Enter points per hour for this skill: ";
    while (!(std::cin >> tempPointsPerHour)) {
        std::cout << "Invalid input. Please enter a number for points per hour: ";
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input
    }
    pointsPerHour = static_cast<int>(tempPointsPerHour); // Cast to int if necessary

    std::cout << "Enter minimum host rating for this skill: ";
    std::cin >> minHostRating;
    std::cin.ignore(); // Ignore the rest of the line to prevent issues with future input

    Member newMember(username, password, fullName, phoneNumber, email, address);
    newMember.addSkill(skillName, pointsPerHour, minHostRating);
    members.push_back(newMember);

    // Saving member data to a file, including skill and credit point information
    std::ofstream outFile("memberdata.dat", std::ios::app);
    if (outFile.is_open()) {
        outFile << username << "," << password << "," << fullName << "," 
                << phoneNumber << "," << email << "," << address << ","
                << skillName << "," << pointsPerHour << "," << minHostRating << ","
                << creditPoints << "\n"; // Add skill and credit points
        outFile.close();
        std::cout << "Registration successful for " << username << ". You have been credited with 20 points.\n";
    } else {
        std::cout << "Error opening file for saving data.\n";
    }
}

// Function for member login
bool memberLogin(const std::string& username, const std::string& password) {
    std::ifstream inFile("memberdata.dat");
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string user, pass;
        getline(iss, user, ',');
        getline(iss, pass, ',');
        if (username == user && password == pass) {
            return true;
        }
    }
    return false;
}


// Admin login function
void adminLogin() {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;
    if (admin.login(username, password)) {
        std::cout << "Admin logged in successfully.\n";
        std::string memberToReset, newPassword;
        std::cout << "Enter username to reset password: ";
        std::cin >> memberToReset;
        std::cout << "Enter new password: ";
        std::cin >> newPassword;
        admin.resetUserPassword(members, memberToReset, newPassword);
    } else {
        std::cout << "Incorrect admin credentials.\n";
    }
}
void bookSupporter(const std::vector<Supporter>& suitableSupporters) {
    if (suitableSupporters.empty()) {
        std::cout << "No suitable supporters available to book.\n";
        return;
    }

    std::cout << "Select a supporter to book:\n";
    for (size_t i = 0; i < suitableSupporters.size(); ++i) {
        std::cout << i + 1 << ". " << suitableSupporters[i].getFullName() << "\n";
    }

    size_t choice;
    std::cin >> choice;
    if (choice < 1 || choice > suitableSupporters.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // Handle the booking logic here
    const auto& selectedSupporter = suitableSupporters[choice - 1];
    std::cout << "You have successfully booked " << selectedSupporter.getFullName() << ".\n";

    // Additional logic for booking (e.g., updating files or notifying the supporter) can be added here
}
std::vector<Supporter> searchForSupporters(const std::vector<Supporter>& supporters, const std::string& searchCity, int memberCreditPoints, float memberHostRating) {
    std::vector<Supporter> suitableSupporters;
    for (const auto& supporter : supporters) {
        std::cout << "Checking supporter: " << supporter.getFullName() << " in city: " << supporter.getCity() 
                  << " with points per hour: " << supporter.getConsumingPointsPerHour() 
                  << " and min host rating: " << supporter.getMinimumHostRating() << std::endl;

        if (supporter.getCity() == searchCity && 
            memberCreditPoints >= supporter.getConsumingPointsPerHour() &&
            memberHostRating >= supporter.getMinimumHostRating()) {
            suitableSupporters.push_back(supporter);
            std::cout << "Supporter suitable: " << supporter.getFullName() << std::endl;
        }
    }
    return suitableSupporters;
}
void memberMenu(Member& member) {
    int choice;
    while (true) {
        // Display the member-specific menu
        std::cout << "Member Menu\n";
        std::cout << "1. View My Information\n";
        std::cout << "2. Add Skill\n";
        std::cout << "3. List Myself for Booking\n";
        std::cout << "4. Unlist Myself\n";
        std::cout << "5. Supporter Searching\n";
        std::cout << "6. Booking a Supporter\n";
        std::cout << "7. View Requests to My Skills\n";
        std::cout << "8. Manage Requests\n";
        std::cout << "9. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Option 1: Show member's personal information
                member.showInfo();
                break;
            case 2:
                {
                    // Option 2: Add a new skill
                    std::string skillName;
                    int pointsPerHour;
                    float minHostRating;

                    std::cout << "Enter Skill Name: ";
                    std::cin.ignore();  // Ignore newline left in the input buffer
                    std::getline(std::cin, skillName);

                    std::cout << "Enter Points per Hour for this skill: ";
                    std::cin >> pointsPerHour;

                    std::cout << "Enter Minimum Host Rating required: ";
                    std::cin >> minHostRating;

                    // Add the new skill to the member's skill list
                    member.addSkill(skillName, pointsPerHour, minHostRating);

                    std::cout << "Skill added successfully.\n";
                }
                break;
            case 3:
                // Option 3: List the member for booking
                member.listYourself();
                break;
            case 4:
                // Option 4: Unlist the member from booking
                member.unlistYourself();
                break;
            case 5: {
                int memberCreditPoints;
                float memberHostRating;
                std::string searchCity;

                std::cout << "Enter your credit points (open the memberdata.dat to check): ";
                // Ensure that the input is a valid integer.
                while (!(std::cin >> memberCreditPoints)) {
                    std::cin.clear(); // Clear the error state.
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the incorrect input.
                    std::cout << "Invalid input. Please enter a number for credit points: ";
                }

                std::cout << "Enter your host-rating score (open the memberdata.dat to check): ";
                // Ensure that the input is a valid float.
                while (!(std::cin >> memberHostRating)) {
                    std::cin.clear(); // Clear the error state.
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the incorrect input.
                    std::cout << "Invalid input. Please enter a number for host-rating score: ";
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any leftover newline character.
                std::cout << "Enter city to search for supporters: ";
                std::getline(std::cin, searchCity);

                // Search for suitable supporters
                std::cout << "Suitable Supporters in " << searchCity << ":\n";
                bool foundSupporter = false;
                for (const auto& supporter : supporters) {
                    if (supporter.getCity() == searchCity && 
                        supporter.getConsumingPointsPerHour() <= memberCreditPoints &&
                        supporter.getMinimumHostRating() <= memberHostRating) {
                        std::cout << "Username: " << supporter.getUsername()
                                << ", Full Name: " << supporter.getFullName()
                                << ", Consuming Points/Hour: " << supporter.getConsumingPointsPerHour()
                                << ", Minimum Host Rating: " << supporter.getMinimumHostRating() << std::endl;
                        foundSupporter = true;
                    }
                }

                if (!foundSupporter) {
                    std::cout << "No suitable supporters found in " << searchCity << std::endl;
                }
                break;
            }
            case 6: { // New case for booking a supporter
            std::cout << "Searching for suitable supporters...\n";
            // Assuming getCreditPoints() and getHostRating() are methods of Member class
            int memberCreditPoints = member.getCreditPoints();
            float memberHostRating = member.getHostRating();
            std::string memberCity = member.getAddress(); // Assuming the city is stored in address

            auto suitableSupporters = searchForSupporters(supporters, memberCity, memberCreditPoints, memberHostRating);
            bookSupporter(suitableSupporters);
            break;
        }
            case 7:
            member.viewRequests();
            break;

            case 8:
            member.manageRequests();
            break;

            case 9:
                // Option 9: Logout
                std::cout << "Logging out...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            
        }
    }
}
// Function to allow a non-member to view supporter details
void viewSupporters() {
    std::cout << "List of Supporters:" << std::endl;
    for (const auto& supporter : supporters) {
        std::cout << "Username: " << supporter.getUsername() << ", Full Name: " << supporter.getFullName() << std::endl;
    }
}
void loadMembersFromFile() {
    std::ifstream inFile("memberdata.dat");
    if (!inFile) {
        std::cerr << "Unable to open memberdata.dat for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string username, password, fullName, phoneNumber, email, address;
        std::string skillName;
        int consumingPointsPerHour;
        float minimumHostRating;
        int initialCreditPoints;

        getline(iss, username, ',');
        getline(iss, password, ',');
        getline(iss, fullName, ',');
        getline(iss, phoneNumber, ',');
        getline(iss, email, ',');
        getline(iss, address, ',');
        getline(iss, skillName, ',');
        iss >> consumingPointsPerHour;
        iss.ignore(1); // Skip the comma
        iss >> minimumHostRating;
        iss.ignore(1); // Skip the comma
        iss >> initialCreditPoints; // Assuming this is the last element in the line

        Member member(username, password, fullName, phoneNumber, email, address);
        member.addSkill(skillName, consumingPointsPerHour, minimumHostRating);
        // Add initial credit points logic here if needed
        members.push_back(member);
    }
}
void loadSupportersFromFile(std::vector<Supporter>& supporters) {
    std::ifstream inFile("supporter.dat");
    if (!inFile) {
        std::cerr << "Unable to open supporter.dat for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string username, password, fullName, phoneNumber, email, address, city;
        int consumingPoints;
        float minHostRating;

        getline(iss, username, ',');
        getline(iss, password, ',');
        getline(iss, fullName, ',');
        getline(iss, phoneNumber, ',');
        getline(iss, email, ',');
        getline(iss, address, ',');

        if (!(iss >> consumingPoints)) {
            std::cerr << "Error reading consuming points for " << username << ".\n";
            continue;
        }
        iss.ignore(1); // Skip the comma

        if (!(iss >> minHostRating)) {
            std::cerr << "Error reading minimum host rating for " << username << ".\n";
            continue;
        }
        iss.ignore(1); // Skip the comma

        getline(iss, city);

        supporters.emplace_back(username, password, fullName, phoneNumber, email, address, consumingPoints, minHostRating, city);
    }
}
// Main function
int main() {
    loadMembersFromFile(); // Load members from file
    loadSupportersFromFile(supporters); // Load supporters from a file
    int choice;
    while (true) {
        std::cout << "EEET2482/COSC2082 ASSIGNMENT\n";
        std::cout << "''TIME BANK'' APPLICATION\n";
        std::cout << "Instructor: Tran Duc Linh\n";
        std::cout << "Group: 17\n";
        std::cout << "s3979259, Truong Tuong Hao\n";
        std::cout << "s3927197, Vo Duy Dinh\n";
        std::cout << "s3978742, Huynh Nguyen Thien Minh\n";
        std::cout << "s3924695, Truong Loc Thien\n";
        std::cout << "0. Exit\n";
        std::cout << "1. Register as a new member\n";
        std::cout << "2. Login as Admin\n";
        std::cout << "3. Login as Member\n";
        std::cout << "4. View Supporters (Non-member)\n";
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
        std::cout << "Invalid input. Please enter a valid choice.\n";
        continue;
        }

        switch (choice) {
            case 0:
                return 0; // Exit the program
            case 1:
                registerMember(); // Handle new member registration
                break;
            case 2:
                adminLogin(); // Admin login process
                break;
            case 3: {  // Member login case
    std::string username, password;
    std::cout << "Enter member username: ";
    std::cin >> username;
    std::cout << "Enter member password: ";
    std::cin >> password;

    if (memberLogin(username, password)) {
        std::cout << "Member logged in successfully.\n";
        // Find the logged-in member in the list
        auto it = std::find_if(members.begin(), members.end(), 
                               [&](const Member& m) { return m.getUsername() == username; });
        if (it != members.end()) {
            it->loadRequests(); // Load requests for the logged-in member
            memberMenu(*it); // Show member menu
        } else {
            std::cout << "Member not found in records.\n";
        }
    } else {
        std::cout << "Incorrect member credentials.\n";
    }
    break;
}
            case 4:
                viewSupporters(); // Display supporters to non-members
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}
