#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string address;

public:
    User(std::string username, std::string password, std::string fullName, 
         std::string phoneNumber, std::string email, std::string address);

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getAddress() const;
};

#endif // USER_H
