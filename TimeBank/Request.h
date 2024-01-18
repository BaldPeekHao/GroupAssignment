#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
private:
    std::string requesterUsername;
    std::string skillRequested;
    std::string requestTime;

public:
    Request(std::string requester, std::string skill, std::string time);

    std::string getRequesterUsername() const;
    std::string getSkillRequested() const;
    std::string getRequestTime() const;
};

#endif // REQUEST_H
