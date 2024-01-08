#ifndef MEMBER_H
#define MEMBER_H

#include "TimeBank/User.h"

class Member : public User {
public:
    Member(std::string username, std::string password, std::string fullName, 
           std::string phoneNumber, std::string email, std::string address);
};

#endif // MEMBER_H
