#ifndef SUPPORTER_H
#define SUPPORTER_H

#include "Member.h"

class Supporter : public Member {
public:
    Supporter(std::string username, std::string password, std::string fullName, 
              std::string phoneNumber, std::string email, std::string address);
};

#endif // SUPPORTER_H
