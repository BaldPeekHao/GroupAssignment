#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill {
private:
    std::string name;
    int pointsPerHour;
    float minHostRating;

public:
    // Constructor
    Skill(const std::string& name, int pointsPerHour, float minHostRating);

    // Getters
    std::string getName() const;
    int getPointsPerHour() const;
    float getMinHostRating() const;

    // Setters (if needed)
    void setName(const std::string& name);
    void setPointsPerHour(int points);
    void setMinHostRating(float rating);
};

#endif // SKILL_H
