#ifndef RATING_H
#define RATING_H

#include <string>

struct Rating {
    float score;
    std::string comments;
    std::string supporterUsername; // Username of the supporter being rated

    Rating(float score, const std::string& comments, const std::string& username)
        : score(score), comments(comments), supporterUsername(username) {}
};

#endif // RATING_H
