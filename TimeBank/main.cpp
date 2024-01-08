#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "User.h"
#include "Member.h"
#include "Supporter.h"
#include "Admin.h"

// Global variables
std::vector<Member> members; 
std::vector<Supporter> supporters; 
Admin admin("admin", "admin123"); 

// Function to register a new member
void registerMember() {
    std::string username, password, fullName, phoneNumber, email, address;

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter full name: ";
    std::cin.ignore();
    std::getline(std::cin, fullName);
    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter address: ";
    std::cin.ignore();
    std::getline(std::cin, address);

    Member newMember(username, password, fullName, phoneNumber, email, address);
    members.push_back(newMember);

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

// Function for member login
bool memberLogin(const std::string& username, const std::string& password) {
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

// Function to allow a non-member to view supporter details
void viewSupporters() {
    std::cout << "List of Supporters:" << std::endl;
    for (const auto& supporter : supporters) {
        std::cout << "Username: " << supporter.getUsername() << ", Full Name: " << supporter.getFullName() << std::endl;
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
                    // Here you can add additional functionalities for logged-in members
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
