#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_USER_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_USER_H

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

class User
{
private:
    string username;
    string password;
    string role; // Admin, RegularMember
    bool isAuthenticated = false;

public:
    // Constructor
    User(string username, string password, string role);

    string getUsername() const { return username; };
    string getPassword() const { return password; };
    string getRole() const { return role; };
    bool getIsAuthenticated() const { return isAuthenticated; };
    void setUsername(string username) { this->username = username; };
    void setPassword(string password) { this->password = password; };
    void setRole(string role) { this->role = role; };
    void setIsAuthenticated(bool isAuthenticated) { this->isAuthenticated = isAuthenticated; };

    virtual void showInfo();

    friend class TimeBankSystem;
    friend class FileHandler;
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_USER_H