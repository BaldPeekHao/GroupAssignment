#include "Supporter.h"

Supporter::Supporter(std::string username, std::string password, std::string fullName, 
                     std::string phoneNumber, std::string email, std::string address)
    : Member(username, password, fullName, phoneNumber, email, address) {}
