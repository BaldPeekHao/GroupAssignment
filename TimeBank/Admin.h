#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include <string>
#include "Member.h"

class Admin {
private:
    std::string adminUsername;
    std::string adminPassword;
// Overload
public:
    Admin(std::string username, std::string password);

    bool login(std::string username, std::string password);
    void resetUserPassword(std::vector<Member>& members, const std::string& username, const std::string& newPassword);
};

#endif // ADMIN_H
