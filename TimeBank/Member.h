#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <string>
#include <vector>
#include "Request.h"
class Member : public User {
private:
    struct Skill {
        std::string name;
        int pointsPerHour;
        float minHostRating;
    };

    std::vector<Skill> skills;
    std::vector<Request> requests;
    bool isListed;
    int creditPoints; // Add credit points attribute
    float hostRating; // Add host rating attribute
// Constructor
public:
    Member(std::string username, std::string password, std::string fullName,
           std::string phoneNumber, std::string email, std::string address);
    int getCreditPoints() const { return creditPoints; }
    float getHostRating() const { return hostRating; }
    void setListStatus(bool status);
    void addRequest(const Request& request);
    void viewRequests() const;
    void loadRequests();
    void addSkill(const std::string& skillName, int pointsPerHour, float minHostRating);
    void listYourself();
    void unlistYourself();
    void displaySkills() const;
    bool isListedForBooking() const;
    void showInfo() const;
};

#endif // MEMBER_H
