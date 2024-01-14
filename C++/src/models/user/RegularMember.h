#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_REGULARMEMBER_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_REGULARMEMBER_H
#include <iostream>
#include <string>
#include <vector>
#include "../skill/Request.h"
#include "../skill/Review.h"
#include "../skill/Skill.h"
#include "User.h"

using std::string;
using std::vector;

class Skill;        // Forward declaration to avoid circular dependency
class SkillListing; // Forward declaration to avoid circular dependency
class Request;      // Forward declaration to avoid circular dependency
class Review;       // Forward declaration to avoid circular dependency
class Period;       // Forward declaration to avoid circular dependency

enum allowedCities
{
    Hanoi = 24,
    Saigon = 28
}; // Hanoi or Saigon only
class RegularMember : public User
{

private:
    string fullName;
    float creditPoints;
    string phoneNumber;
    string email;
    string homeAddress;
    allowedCities city; // Hanoi or Saigon only
    double latitude;
    double longitude;
    string creditCardNumber;
    float balance; // Assume that the balance is in USD, and each card has 1000 USD
    float skillRatingScore;
    float supporterRatingScore;
    float hostRatingScore;
    vector<Skill *> skills = {};
    vector<SkillListing *> skillListings = {};
    vector<Review *> sentreceivedReviews = {};
    vector<Review *> receivedHostReviews = {};
    vector<Review *> receivedSupporterReviews = {};
    vector<Request *> sentreceivedRequests = {};
    vector<RegularMember *> blockedMembers = {};
    vector<Period *> timeTable = {};

public:
    // Constructor
    RegularMember(string username = "", string password = "", string fullName = "", string phoneNumber = "", string email = "", string homeAddress = "", allowedCities city = Hanoi, double latitude = 0, double longitude = 0, string creditCardNumber = "", float balance = 0, float creditPoints = 20, float skillRatingScore = 0, float supporterRatingScore = 0, float hostRatingScore = 0);

    // Getters and Setters
    float getCreditPoints() { return creditPoints; };
    float getBalance() { return balance; };
    string getPhoneNumber() { return phoneNumber; };
    string getEmail() { return email; };
    string getCreditCardNumber() { return creditCardNumber; };
    vector<Skill *> getSkills() { return skills; };
    vector<SkillListing *> getSkillListings() { return skillListings; };
    vector<RegularMember *> getBlockedMembers() { return blockedMembers; };
    vector<Period *> getTimeTable() { return timeTable; };

    void setCreditPoints(float creditPoints) { this->creditPoints = creditPoints; };
    void setPhoneNumber(string phoneNumber) { this->phoneNumber = phoneNumber; };
    void setEmail(string email) { this->email = email; };
    void setCreditCardNumber(string creditCardNumber) { this->creditCardNumber = creditCardNumber; };
    void setBalance(float balance) { this->balance = balance; };
    void setSkillRating(float skillRatingScore) { this->skillRatingScore = skillRatingScore; };
    void setSupporterRating(float supporterRatingScore) { this->supporterRatingScore = supporterRatingScore; };
    void setHostRating(float hostRatingScore) { this->hostRatingScore = hostRatingScore; };
    void setBlockedMembers(vector<RegularMember *> blockedMembers) { this->blockedMembers = blockedMembers; };

    // Push back from the original sentreceivedReviews vector
    vector<Review *> getReceivedHostReviews();      // get RH type reviews, reviewee - usn
    vector<Review *> getReceivedSupporterReviews(); // get RS type reviews, reviewee - usn

    // Member functions
    int getNumberOfSkills();
    int getNumberOfSkillListings();
    int getNumberOfIncomingRequests();
    void printReviews();
    void printSkills();
    void printTimeTable();
    float getSkillRatingScore();
    float getSupporterRatingScore();
    float getHostRatingScore();
    bool payRegistrationFee();
    double calculateDistance(RegularMember &otherMember);
    void showInfo();
    void showRestrictedMemberInfo();

    bool topUp(int credPoints);
    bool sellCredits(int credPoints);

    bool blockMember(RegularMember &memberToBlock);
    bool unblockMember(RegularMember &memberToUnblock);

    bool isBlockerOf(string blockedUsn); // The current user is the blocker
    bool isBlockedBy(string blockerUsn); // In the database, the current user is in the blockedUsername column, not the blocker column
    friend class Skill;
    friend class SkillListing;
    friend class Request;
    friend class Review;
    friend class FileHandler;
    friend class TimeBankSystem;
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_USER_REGULARMEMBER_H