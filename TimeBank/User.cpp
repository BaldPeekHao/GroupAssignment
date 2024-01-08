#include "User.h"

User::User(std::string username, std::string password, std::string fullName, 
           std::string phoneNumber, std::string email, std::string address) 
    : username(username), password(password), fullName(fullName), 
      phoneNumber(phoneNumber), email(email), address(address) {}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFullName() const { return fullName; }
std::string User::getPhoneNumber() const { return phoneNumber; }
std::string User::getEmail() const { return email; }
std::string User::getAddress() const { return address; }
