#include "TimeBank/Member.h"

Member::Member(std::string username, std::string password, std::string fullName, 
               std::string phoneNumber, std::string email, std::string address)
    : User(username, password, fullName, phoneNumber, email, address) {}
