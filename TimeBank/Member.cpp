#include "Member.h"
#include <iostream>

Member::Member(std::string username, std::string password, std::string fullName, 
               std::string phoneNumber, std::string email, std::string address) 
    : User(username, password, fullName, phoneNumber, email, address), isListed(false) {}

void Member::addSkill(const std::string& skillName, int pointsPerHour, float minHostRating) {
    skills.push_back({skillName, pointsPerHour, minHostRating});
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
