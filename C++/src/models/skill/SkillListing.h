#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_SKILLLISTING_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_SKILLLISTING_H
#include <iostream>
#include <string>
#include "../user/RegularMember.h"
#include "Skill.h"
#include "../../utils/myUtils.h"
#include "../../utils/time/Period.h"
using std::cin;
using std::cout;
using std::string;
class RegularMember; // Forward declaration to avoid circular dependency
class SkillListing
{
private:
    // Skill *skillPerformed;
    string skillID;   // Sxxxxxxxx
    string listingID; // Lxxxxxxxx
    int consumedCredsPerHour = 0;
    float minHostRatingScore = -1; // -1 = no minimum rating score, optional
    int listingState = 0;          // 0 = available, 1 = hidden, 2 = booked, 3 = ongoing (in progress), 4 = completed
    string supporterName;          // username of the member who created the listing
    string hostName;               // username of the member who booked the listing
    Period workingTimeSlot;

public:
    SkillListing(string listingID = "", string skillID = "", int consumedCreds = 0, float minHostRatingScore = -1, int listingSate = 0, std::string supporterName = "", string hostName = "", Period workingTimeSlot = Period());

    // Getters
    string getSkillID() const { return skillID; };
    string getListingID() const { return listingID; };
    int getConsumedCredsPerHour() const { return consumedCredsPerHour; };
    float getMinHostRatingScore() const { return minHostRatingScore; };
    int getListingState() const { return listingState; };
    string getSupporterName() const { return supporterName; };
    string getHostName() const { return hostName; };
    Period getWorkingTimeSlot() const { return workingTimeSlot; };

    // Setters
    void setConsumedCredsPerHour(int consumedCreds) { this->consumedCredsPerHour = consumedCreds; };
    void setMinHostRatingScore(int minHostRatingScore) { this->minHostRatingScore = minHostRatingScore; };
    void setListingState(int listingState) { this->listingState = listingState; };
    void setSupporterName(string supporterName) { this->supporterName = supporterName; };
    void setHostName(string hostName) { this->hostName = hostName; };

    // Methods
    void displaySkillListing();
    bool hideListing();
    bool unhideListing();
    float calculateTotalCreds();                     // Calculate total creds for a listing
    bool isListingAvailable();                       // Check if a listing is available
    bool isListingBooked();                          // Check if a listing is booked
    bool isEligibleToBook(RegularMember &requester); // Check if a member is eligible to book a listing
    bool isEligibleToView(RegularMember &searcher); // Check if a member is eligible to view a listing in search

    friend class TimeBankSystem;
    friend class FileHandler;
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_SKILLLISTING_H