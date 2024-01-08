#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>  // Include for std::istringstream


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
public:
    // Constructor for Member class
    Member(std::string username, std::string password, std::string fullName, 
           std::string phoneNumber, std::string email, std::string address)
           : User(username, password, fullName, phoneNumber, email, address) {}

    // Additional member-specific functionalities can be added here
};

// Supporter class derived from Member
class Supporter : public Member {
public:
    // Constructor for Supporter class
    Supporter(std::string username, std::string password, std::string fullName, 
              std::string phoneNumber, std::string email, std::string address)
              : Member(username, password, fullName, phoneNumber, email, address) {}

    // Additional supporter-specific functionalities can be added here
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
    std::ifstream inFile("memberdata.txt");
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
    std::ofstream outFile("memberdata.txt");
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

    Member newMember(username, password, fullName, phoneNumber, email, address);
    members.push_back(newMember);

    // Saving member data to a file
    std::ofstream outFile("memberdata.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << username << "," << password << "," << fullName << "," 
                << phoneNumber << "," << email << "," << address << "\n";
        outFile.close();
        std::cout << "Registration successful for " << username << std::endl;
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

// Function for member login
bool memberLogin(std::string username, std::string password) {
    std::ifstream inFile("memberdata.txt");
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

// Main function
int main() {
    int choice;

    while (true) {
        std::cout << "TIME BANK APPLICATION\n";
        std::cout << "0. Exit\n";
        std::cout << "1. Register as a new member\n";
        std::cout << "2. Login as Admin\n";
        std::cout << "3. Login as Member\n";
        std::cout << "4. View Supporters (Non-member)\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                return 0; // Exit the program
            case 1:
                registerMember();
                break;
            case 2:
                adminLogin();
                break;
            case 3: {
                std::string username, password;
                std::cout << "Enter member username: ";
                std::cin >> username;
                std::cout << "Enter member password: ";
                std::cin >> password;
                if (memberLogin(username, password)) {
                    std::cout << "Member logged in successfully.\n";
                    // Member-specific functionalities can be implemented here
                } else {
                    std::cout << "Incorrect member credentials.\n";
                }
                break;
            }
            case 4:
                viewSupporters();
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
