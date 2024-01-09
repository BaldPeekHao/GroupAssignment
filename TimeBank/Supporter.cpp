#include "Supporter.h"
#include <iostream>

Supporter::Supporter(std::string username, std::string password, std::string fullName,
                     std::string phoneNumber, std::string email, std::string address,
                     int points, float rating, std::string city)
    : Member(username, password, fullName, phoneNumber, email, address),
      consumingPointsPerHour(points), minimumHostRating(rating), city(city) {}

int Supporter::getConsumingPointsPerHour() const {
    return consumingPointsPerHour;
}

float Supporter::getMinimumHostRating() const {
    return minimumHostRating;
}

std::string Supporter::getCity() const {
    return city;
}

bool Supporter::isSuitable(int memberPoints, float memberRating, const std::string& memberCity) const {
    return memberPoints >= consumingPointsPerHour && memberRating >= minimumHostRating && city == memberCity;
}
