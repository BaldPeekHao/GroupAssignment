#include "Request.h"

Request::Request(std::string requester, std::string skill, std::string time)
    : requesterUsername(requester), skillRequested(skill), requestTime(time) {}

std::string Request::getRequesterUsername() const {
    return requesterUsername;
}

std::string Request::getSkillRequested() const {
    return skillRequested;
}

std::string Request::getRequestTime() const {
    return requestTime;
}
