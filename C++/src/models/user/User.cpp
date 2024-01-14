#include <iostream>
#include "User.h"
using std::cin;
using std::cout;

// Constructor
User::User(string usn = "", string pwd = "", string role = "NA")
{
    this->username = usn;
    this->password = pwd;
    this->role = role;
    this->isAuthenticated = isAuthenticated;
};

void User::showInfo()
{
    cout << "Username: " << username << std::endl;
    cout << "Password: " << password << std::endl;
}