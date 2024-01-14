#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_SKILL_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_SKILL_H

#include <iostream>
#include <string>
using std::string;

class Skill
{

private:
    string skillID; // Sxxxxxxxx
    string skillName;
    string description;
    std::string skillEfficiency;
    std::string ownerName; // username of the member who created the skill

public:
    Skill(string skillID = "",string skillName = "", string description = "", std::string skillEfficiency = "",std::string ownerName = "");

    void showInfo();

    // Getters and Setters
    string getSkillID() const { return skillID; };
    string getSkillName() const { return skillName; };
    string getDescription() const { return description; };
    std::string getSkillEfficiency() const { return skillEfficiency; };
    std::string getOwnerName() const { return ownerName; };
    void setSkillID(string skillID) { this->skillID = skillID; };
    void setSkillName(string skillName) { this->skillName = skillName; };
    void setDescription(string description) { this->description = description; };
    void setSkillEfficiency(std::string skillEfficiency) { this->skillEfficiency = skillEfficiency; };
    void setOwnerName(std::string ownerName) { this->ownerName = ownerName; };
    

    friend class SkillListing;
    friend class FileHandler;
    friend class TimeBankSystem;
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_SKILL_H