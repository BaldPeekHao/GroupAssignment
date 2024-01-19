#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include "Rating.h"
#include <string>
#include <vector>
#include <unordered_set>
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
    std::unordered_set<std::string> blockedMembers; // Set of usernames of blocked members
    std::vector<Rating> ratingsGiven;
    std::vector<Rating> ratingsGivenAsSupporter; // Ratings given by this member as a supporter
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
    void manageRequests();
    void updateRequestFile();
    void addSkill(const std::string& skillName, int pointsPerHour, float minHostRating);
    void listYourself();
    void unlistYourself();
    void displaySkills() const;
    void blockMember(const std::string& username);
    void unblockMember(const std::string& username);
    bool isBlocked(const std::string& username) const;
    void rateSupporter(const std::string& supporterUsername, float score, const std::string& comments);
    bool isListedForBooking() const;
    void rateHost(const std::string& hostUsername, float score, const std::string& comments);
    void showInfo() const;
};

#endif // MEMBER_H
