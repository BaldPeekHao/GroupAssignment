#ifndef SUPPORTER_H
#define SUPPORTER_H

#include "Member.h"
#include <string>

class Supporter : public Member {
private:
    int consumingPointsPerHour;
    float minimumHostRating;
    std::string city;

public:
    Supporter(std::string username, std::string password, std::string fullName,
              std::string phoneNumber, std::string email, std::string address,
              int points, float rating, std::string city);

    int getConsumingPointsPerHour() const;
    float getMinimumHostRating() const;
    std::string getCity() const;
    bool isSuitable(int memberPoints, float memberRating, const std::string& memberCity) const;
};

#endif // SUPPORTER_H
