#include <iostream>
#include "Skill.h"
#include "../../utils/myUtils.h"

using std::cin;
using std::cout;
using std::string;

Skill::Skill(string skillID, string skillName, string description, std::string skillEfficiency, std::string ownerName)
{
    if (skillID.empty())
    {
        this->skillID = "S" + generateRandomID();
    }
    else
    {
        this->skillID = skillID;
    }
    this->skillName = skillName;
    this->description = description;
    this->skillEfficiency = skillEfficiency;
    this->ownerName = ownerName;
}

void Skill::showInfo()
{
    cout << "Skill ID: " << this->skillID << "\n";
    cout << "Skill Name: " << this->skillName << "\n";
    cout << "Description: " << this->description << "\n";
    cout << "Skill Efficiency: " << this->skillEfficiency << "\n";
}