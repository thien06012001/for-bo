#include <iostream>
#include <string>
#include "Admin.h"
#include "RegularMember.h"
using std::cin;
using std::cout;
using std::string;

// Constructor
Admin::Admin(float revenue) : User("@dmin2023", "aptfinalproject", "Admin")
{
    this->revenue = revenue;
};

void Admin::showInfo()
{
    User::showInfo();
    cout << "Role: " << this->getRole() << "\n";
    cout << "Revenue of Time Bank company: " << this->revenue << "\n";
}

bool Admin::resetPasswordForMember(RegularMember &member, string newPassword)
{
    member.setPassword(newPassword);
    if (member.getPassword() == newPassword)
    {
        cout << "Password has been reset successfully!\n";
        return true;
    }
    else
    {
        cout << "Error performing reseting action!\n";
        return false;
    }
}
