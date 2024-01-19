#include "Skill.h"

// Constructor
Skill::Skill(const std::string& name, int pointsPerHour, float minHostRating)
    : name(name), pointsPerHour(pointsPerHour), minHostRating(minHostRating) {}

// Getters
std::string Skill::getName() const {
    return name;
}

int Skill::getPointsPerHour() const {
    return pointsPerHour;
}

float Skill::getMinHostRating() const {
    return minHostRating;
}

// Setters
void Skill::setName(const std::string& newName) {
    name = newName;
}

void Skill::setPointsPerHour(int points) {
    pointsPerHour = points;
}

void Skill::setMinHostRating(float rating) {
   
