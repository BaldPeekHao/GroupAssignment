#include "Member.h"
#include <iostream>
#include <fstream>
#include <sstream>
Member::Member(std::string username, std::string password, std::string fullName, 
               std::string phoneNumber, std::string email, std::string address) 
    : User(username, password, fullName, phoneNumber, email, address), isListed(false) {}

void Member::addSkill(const std::string& skillName, int pointsPerHour, float minHostRating) {
    skills.push_back({skillName, pointsPerHour, minHostRating});
}
void Member::setListStatus(bool status) {
        isListed = status;
    }

void Member::listYourself() {
    isListed = true;
    std::cout << "You are now listed for booking.\n";
}

void Member::unlistYourself() {
    isListed = false;
    std::cout << "You are no longer listed for booking.\n";
}

void Member::displaySkills() const {
    if (skills.empty()) {
        std::cout << "No skills listed.\n";
        return;
    }
    for (const auto& skill : skills) {
        std::cout << "Skill: " << skill.name 
                  << ", Points/Hour: " << skill.pointsPerHour
                  << ", Min Host Rating: " << skill.minHostRating << std::endl;
    }
}

bool Member::isListedForBooking() const {
    return isListed;
}

void Member::showInfo() const {
    std::cout << "Username: " << getUsername() << "\n";
    std::cout << "Full Name: " << getFullName() << "\n";
    std::cout << "Phone Number: " << getPhoneNumber() << "\n";
    std::cout << "Email: " << getEmail() << "\n";
    std::cout << "Address: " << getAddress() << "\n";
    std::cout << "Listed for Booking: " << (isListed ? "Yes" : "No") << "\n";
    displaySkills();
}
void Member::addRequest(const Request& request) {
    requests.push_back(request);
}
void Member::viewRequests() const {
    if (requests.empty()) {
        std::cout << "No requests for your skills at the moment." << std::endl;
        return;
    }

    std::cout << "Requests for Your Skills:" << std::endl;
    for (const auto& request : requests) {
        std::cout << "Requester: " << request.getRequesterUsername()
                  << ", Skill Requested: " << request.getSkillRequested()
                  << ", Request Time: " << request.getRequestTime() << std::endl;
    }
}
void Member::loadRequests() {
    std::ifstream file("request.dat");
    if (!file) {
        std::cerr << "Error opening request.dat file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string requester, skill, time;
        if (std::getline(iss, requester, ',') &&
            std::getline(iss, skill, ',') &&
            std::getline(iss, time)) {
            std::cout << "Read request: " << requester << ", " << skill << ", " << time << std::endl;  // Debug statement
            if (requester == this->getUsername()) {
                requests.emplace_back(requester, skill, time);
            }
        }
    }
}

