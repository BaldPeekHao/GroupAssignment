#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <string>
#include <vector>

class Member : public User {
private:
    struct Skill {
        std::string name;
        int pointsPerHour;
        float minHostRating;
    };

    std::vector<Skill> skills;
    bool isListed;
// Constructor
public:
    Member(std::string username, std::string password, std::string fullName,
           std::string phoneNumber, std::string email, std::string address);

    void addSkill(const std::string& skillName, int pointsPerHour, float minHostRating);
    void listYourself();
    void unlistYourself();
    void displaySkills() const;
    bool isListedForBooking() const;
    void showInfo() const;
};

#endif // MEMBER_H
