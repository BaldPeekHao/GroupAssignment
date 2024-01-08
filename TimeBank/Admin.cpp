#include "TimeBank/Admin.h"
#include <fstream>
#include <sstream>
#include <iostream>

Admin::Admin(std::string username, std::string password) 
    : adminUsername(username), adminPassword(password) {}

bool Admin::login(std::string username, std::string password) {
    return username == adminUsername && password == adminPassword;
}

void Admin::resetUserPassword(std::vector<Member>& members, const std::string& username, const std::string& newPassword) {
    std::ifstream inFile("memberdata.txt");
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string user, oldPassword, restOfLine;
        getline(iss, user, ',');
        getline(iss, oldPassword, ',');
        if (user == username) {
            std::getline(iss, restOfLine);
            line = user + "," + newPassword + "," + restOfLine;
            found = true;
        } else {
            line = user + "," + oldPassword + "," + std::string(std::istreambuf_iterator<char>(iss), {});
        }
        lines.push_back(line);
    }
    inFile.close();

    if (!found) {
        std::cout << "Member not found.\n";
        return;
    }

    std::ofstream outFile("memberdata.txt");
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << std::endl;
    }
    outFile.close();

    std::cout << "Password reset for member: " << username << std::endl;
}
