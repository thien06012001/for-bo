#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_ADMIN_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_ADMIN_H
#include <iostream>
#include <string>
#include "User.h"

using std::string;

// Forward declaration to avoid circular dependency
class RegularMember;
class Admin : public User
{
private:
    float revenue; // revenue of the company

public:
    // Constructor
    explicit Admin(float revenue = 0); // avoid implicit type conversion
    float getRevenue() const { return revenue; };
    void setRevenue(float revenue) { this->revenue = revenue; };
    void showInfo();

    bool resetPasswordForMember(RegularMember &member, string newPassword);

    friend class TimeBankSystem;
    friend class RegularMember;
    friend class FileHandler;
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_ADMIN_H