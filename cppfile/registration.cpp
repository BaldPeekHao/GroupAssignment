#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>  // Include for std::istringstream
#include <algorithm>
#include <limits>
// Class for storing basic user information
class User {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string address;

public:
    // Constructor for initializing a User object
    User(std::string username, std::string password, std::string fullName, 
         std::string phoneNumber, std::string email, std::string address) 
        : username(username), password(password), fullName(fullName), 
          phoneNumber(phoneNumber), email(email), address(address) {}

    // Getter methods for User attributes
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getFullName() const { return fullName; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
};

// Member class derived from User
class Member : public User {
private:
    struct Skill {
        std::string name;
        int consumingPointsPerHour;
        float minimumHostRating;
    };

    std::vector<Skill> skills;
    bool isListed;
    int creditPoints; // Add credit points attribute
    float hostRating; // Add host rating attribute


public:
    int getCreditPoints() const { return creditPoints; }
    float getHostRating() const { return hostRating; }
    Member(std::string username, std::string password, std::string fullName, 
           std::string phoneNumber, std::string email, std::string address)
        : User(username, password, fullName, phoneNumber, email, address), isListed(false) {}

    void addSkill(const std::string& skillName, int pointsPerHour, float minHostRating) {
        skills.push_back({skillName, pointsPerHour, minHostRating});
    }

    void listYourself() {
        isListed = true;
        std::cout << "You are now listed for booking.\n";
    }

    void unlistYourself() {
        isListed = false;
        std::cout << "You are no longer listed for booking.\n";
    }
    bool isListedForBooking() const {
        return isListed;
    }
    void showInfo() const {
        std::cout << "Username: " << getUsername() << "\n";
        std::cout << "Full Name: " << getFullName() << "\n";
        std::cout << "Phone Number: " << getPhoneNumber() << "\n";
        std::cout << "Email: " << getEmail() << "\n";
        std::cout << "Address: " << getAddress() << "\n";
        std::cout << "Listed for Booking: " << (isListed ? "Yes" : "No") << "\n";
        
        displaySkills(); // Display all the skills
    }

    void displaySkills() const {
        if (skills.empty()) {
            std::cout << "No skills listed.\n";
            return;
        }

        std::cout << "Skills:\n";
        for (const auto& skill : skills) {
            std::cout << " - Skill Name: " << skill.name 
                      << ", Points/Hour: " << skill.consumingPointsPerHour
                      << ", Min Host Rating: " << skill.minimumHostRating << std::endl;
        }
    }
};

// Supporter class derived from Member
class Supporter : public Member {
private:
    int consumingPointsPerHour;
    float minimumHostRating;
    std::string city;

public:
    // Constructor for the Supporter class
    Supporter(std::string username, std::string password, std::string fullName, 
              std::string phoneNumber, std::string email, std::string address,
              int points, float rating, std::string city)
        : Member(username, password, fullName, phoneNumber, email, address),
          consumingPointsPerHour(points), minimumHostRating(rating), city(city) {}

    // Additional supporter-specific functionalities can be added here
    // Getter and Setter
    int getConsumingPointsPerHour() const { return consumingPointsPerHour; }
    float getMinimumHostRating() const { return minimumHostRating; }
    std::string getCity() const { return city; }
    // Method to check if the supporter is suitable
    bool isSuitable(int memberPoints, float memberRating, const std::string& memberCity) const {
        return memberPoints >= consumingPointsPerHour && memberRating >= minimumHostRating && city == memberCity;
    }
};

// Admin class for administrative functionalities
class Admin {
private:
    std::string adminUsername;
    std::string adminPassword;

public:
    // Constructor for Admin class
    Admin(std::string username, std::string password) 
        : adminUsername(username), adminPassword(password) {}

    // Method for admin login
    bool login(std::string username, std::string password) {
        return username == adminUsername && password == adminPassword;
    }

// Method to reset user password
void resetUserPassword(std::vector<Member>& members, const std::string& username, const std::string& newPassword) {
    // Step 1: Read all data from the file
    std::ifstream inFile("memberdata.dat");
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string user, oldPassword, restOfLine;
        getline(iss, user, ',');
        getline(iss, oldPassword, ','); // Read and discard the old password

        if (user == username) {
            // Construct the line with new password, keeping other details intact
            std::getline(iss, restOfLine); // Read the rest of the line
            line = user + "," + newPassword + "," + restOfLine;
            found = true;
        } else {
            // Reconstruct the line with old password as we're not updating it
            line = user + "," + oldPassword + "," + std::string(std::istreambuf_iterator<char>(iss), {});
        }
        lines.push_back(line);
    }
    inFile.close();

    // Check if user was found
    if (!found) {
        std::cout << "Member not found.\n";
        return;
    }

    // Step 2: Write the updated data back to the file
    std::ofstream outFile("memberdata.dat");
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << std::endl;
    }
    outFile.close();

    // Update the password in the members list
    for (auto& member : members) {
        if (member.getUsername() == username) {
            // Here you would normally set the new password
            // member.setPassword(newPassword); // Assuming Member class has a setPassword method
            break;
        }
    }

    std::cout << "Password reset for member: " << username << std::endl;
}
};

// Global variables
std::vector<Member> members; // List of members
std::vector<Supporter> supporters; // List of supporters
Admin admin("admin", "admin123"); // Predefined admin

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
// Function to allow a non-member to view supporter details
void viewSupporters() {
    std::cout << "List of Supporters:" << std::endl;
    for (const auto& supporter : supporters) {
        std::cout << "Username: " << supporter.getUsername() << ", Full Name: " << supporter.getFullName() << std::endl;
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


// Function for member login
bool memberLogin(std::string username, std::string password) {
    std::ifstream inFile("memberdata.dat");
    if (!inFile) {
        std::cerr << "Unable to open memberdata.dat for reading.\n";
        return false;
    }

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


// Note: You'll need to add getCity(), getConsumingPointsPerHour(), and getMinimumHostRating() methods in your Supporter class.

// Admin login function
void adminLogin() {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;
    if (admin.login(username, password)) {
        std::cout << "Admin logged in successfully.\n";
        // Example admin functionality: reset member password
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
        std::cout << "7. Logout\n";
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

                std::cout << "Enter your credit points: ";
                // Ensure that the input is a valid integer.
                while (!(std::cin >> memberCreditPoints)) {
                    std::cin.clear(); // Clear the error state.
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the incorrect input.
                    std::cout << "Invalid input. Please enter a number for credit points: ";
                }

                std::cout << "Enter your host-rating score: ";
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
                // Option 5: Logout
                std::cout << "Logging out...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            
        }
    }
}
// Function to load members from file
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
        std::cout <<"EEET2482/COSC2082 ASSIGNMENT\n";
        std::cout << "TIME BANK APPLICATION\n";
        std::cout <<"Instructor: Mr. Tran Duc Linh\n";
        std::cout <<"Group: 17 \n";
        std::cout <<"s3979259 Truong Tuong Hao \n";
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
