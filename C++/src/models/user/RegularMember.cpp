#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "./User.h"
#include "../skill/Review.h"
#include "../skill/Skill.h"
#include "RegularMember.h"

// Define ANSI escape codes for text formatting
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

using std::cin;
using std::cout;
using std::string;

// Constructor
RegularMember::RegularMember(string username, string password, string fullName, string phoneNumber, string email, string homeAddress, allowedCities city, double latitude, double longitude, string creditCardNumber, float balance, float creditPoints, float skillRatingScore, float supporterRatingScore, float hostRatingScore) : User(username, password, "RegularMember")
{

    this->fullName = fullName;
    this->creditPoints = creditPoints;
    this->phoneNumber = phoneNumber;
    this->email = email;
    this->homeAddress = homeAddress;
    this->city = city;
    this->latitude = latitude;
    this->longitude = longitude;
    this->creditCardNumber = creditCardNumber;
    this->balance = balance;
    this->skillRatingScore = skillRatingScore;
    this->supporterRatingScore = supporterRatingScore;
    this->hostRatingScore = hostRatingScore;
}

vector<Review *> RegularMember::getReceivedHostReviews()
{
    // Clear the vector before populating it
    this->receivedHostReviews.clear();
    for (Review *review : this->sentreceivedReviews)
    {
        if (review->getReviewee() == this->getUsername() && review->getReviewID()[1] == 'H')
        {
            this->receivedHostReviews.push_back(review);
        }
    }
    return this->receivedHostReviews;
}

vector<Review *> RegularMember::getReceivedSupporterReviews()
{
    // Clear the vector before populating it
    this->receivedSupporterReviews.clear();
    for (Review *review : this->sentreceivedReviews)
    {
        if (review->getReviewee() == this->getUsername() && review->getReviewID()[1] == 'S')
        {
            this->receivedSupporterReviews.push_back(review);
        }
    }
    return this->receivedSupporterReviews;
}

void RegularMember::printReviews()
{
    if (this->sentreceivedReviews.size() == 0)
    {
        cout << "You have not received or given any reviews yet!\n";
    }
    else
    {
        for (int i = 0; i < this->sentreceivedReviews.size(); i++)
        {
            (this->sentreceivedReviews[i])->printReview();
        }
    }
}

void RegularMember::printSkills()
{
    if (this->skills.size() == 0)
    {
        cout << "You have not added any skills yet!\n";
        return;
    }
    else
    {
        for (int i = 0; i < this->skills.size(); i++)
        {
            // cout << this->skills[i] << ", "; // Print the address of the skill
            if (i == this->skills.size() - 1)
            {
                (this->skills[i])->showInfo();
            }
        }
    }
}

void RegularMember::printTimeTable()
{
    if (this->timeTable.size() == 0)
    {
        cout << "You have not added any time slots yet!\n";
        return;
    }
    else
    {
        cout << "Occupied time slots:\n";
        for (int i = 0; i < this->timeTable.size(); i++)
        {
            cout << (this->timeTable[i])->getFormattedPeriod();
            // Print the skill listing ID of the owner if the time slot is occupied
            for (SkillListing *listing : this->skillListings)
            {
                if (listing->getWorkingTimeSlot().isSameAs(*(this->timeTable[i])))
                {
                    cout << " --> ";
                    cout << listing->getListingID();
                }
            }

            cout << "\n";
        }
    }
}

float RegularMember::getSkillRatingScore()
{

    if (this->getReceivedSupporterReviews().empty())
    {
        return this->skillRatingScore;
    }
    else
    {
        this->skillRatingScore = 0.0f;
        int count = 0; // Initialize count to 1 to avoid division by zero: nan problem
        // Calculate the average skill rating score
        for (const auto &review : this->receivedSupporterReviews)
        {
            if (review->getReviewee() == getUsername() && review->getSkillRating() != 0)
            {
                this->skillRatingScore += static_cast<float>(review->getSkillRating());
                count++;
            }
        }
        this->skillRatingScore = this->skillRatingScore / static_cast<float>(count);
        return this->skillRatingScore;
    }
}

float RegularMember::getSupporterRatingScore()
{
    if (this->getReceivedSupporterReviews().empty())
    {
        return this->supporterRatingScore;
    }
    else
    {
        this->supporterRatingScore = 0.0f;
        int count = 0; // Initialize count to 1 to avoid division by zero
        // Calculate the average supporter rating score
        for (const auto &review : this->receivedSupporterReviews)
        {
            if (review->getReviewee() == getUsername() && review->getSupporterRating() != 0)
            {
                this->supporterRatingScore += static_cast<float>(review->getSupporterRating());
                count++;
            }
        }
        this->supporterRatingScore = this->supporterRatingScore / static_cast<float>(count);
        return this->supporterRatingScore;
    }
}

float RegularMember::getHostRatingScore()
{
    if (this->getReceivedHostReviews().empty())
    {
        return this->hostRatingScore;
    }
    else
    {
        this->hostRatingScore = 0.0f;
        int count = 0; // Initialize count to 1 to avoid division by zero
        // Calculate the average host rating score
        for (const auto &review : this->receivedHostReviews)
        {
            if (review->getReviewee() == getUsername() && review->getHostRating() != 0)
            {
                this->hostRatingScore += static_cast<float>(review->getHostRating());
                count++;
            }
        }
        // cout << "count: " << count << "\n";
        this->hostRatingScore = this->hostRatingScore / static_cast<float>(count);
        return this->hostRatingScore;
    }
}

// Pay to the system for the registration fee
bool RegularMember::payRegistrationFee()
{
    if (this->balance < 20)
    {
        cout << "You don't have enough money to pay for the registration fee!\n";
        return false;
    }
    else
    {
        this->balance -= 20;
        return true;
    }
}

// Calculate the distance between a host and a supporter
double RegularMember::calculateDistance(RegularMember &otherMember)
{
    long double lat1, lon1, lat2, lon2;
    lat1 = this->latitude;
    lon1 = this->longitude;
    lat2 = otherMember.latitude;
    lon2 = otherMember.longitude;

    const int R = 6371; // Radius of the Earth in kilometers
    double latDistance = (lat2 - lat1) * M_PI / 180.0;
    double lonDistance = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(latDistance / 2) * sin(latDistance / 2) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * sin(lonDistance / 2) * sin(lonDistance / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c; // in kilometers
}

void RegularMember::showInfo()
{
    // Define ANSI escape codes for bold and blue text
    const std::string BOLD_BLUE = "\033[1;34m"; // Bold Blue

    std::cout << BOLD_BLUE << "Username:" << RESET << " " << getUsername() << "\n";
    std::cout << BOLD_BLUE << "Password:" << RESET << " " << getPassword() << "\n";
    std::cout << BOLD_BLUE << "Active status:" << RESET << " " << getIsAuthenticated() << "\n";
    std::cout << BOLD_BLUE << "Full Name:" << RESET << " " << fullName << "\n";
    std::cout << BOLD_BLUE << "Credit card Number:" << RESET << " " << creditCardNumber << "\n";
    std::cout << BOLD_BLUE << "Balance:" << RESET << " " << balance << "\n";
    std::cout << BOLD_BLUE << "Credit Points:" << RESET << " " << creditPoints << "\n";
    std::cout << BOLD_BLUE << "Phone Number:" << RESET << " " << phoneNumber << "\n";
    std::cout << BOLD_BLUE << "Email:" << RESET << " " << email << "\n";
    std::cout << BOLD_BLUE << "Home Address:" << RESET << " " << homeAddress << "\n";
    std::cout << BOLD_BLUE << "City:" << RESET << " ";
    if (city == Hanoi)
    {
        std::cout << "Hanoi\n";
    }
    else
    {
        std::cout << "Saigon\n";
    }

    // Print skills added by the member
    std::cout << BOLD_BLUE << "Skills:" << RESET << " ";
    if (skills.empty())
    {
        std::cout << "N/A";
    }
    else
    {
        for (size_t i = 0; i < skills.size(); ++i)
        {

            std::cout << skills[i]->getSkillID();
            if (i != skills.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << "\n";

    // Print listings created by the member
    std::cout << BOLD_BLUE << "Listings:" << RESET << " ";
    if (skillListings.empty())
    {
        std::cout << "N/A";
    }
    else
    {
        for (size_t i = 0; i < skillListings.size(); ++i)
        {

            std::cout << skillListings[i]->getListingID();
            if (i != skillListings.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << "\n";

    // Print blocked members' usernames
    std::cout << BOLD_BLUE << "Blocked Members:" << RESET << " ";
    if (blockedMembers.empty())
    {
        std::cout << "N/A";
    }
    else
    {
        for (size_t i = 0; i < blockedMembers.size(); ++i)
        {

            std::cout << blockedMembers[i]->getUsername();
            if (i != blockedMembers.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << "\n";
    // Pending requests counts
    int countRequest = 0;

    for (int i = 0; i < sentreceivedRequests.size(); i++)
    {
        if (sentreceivedRequests[i]->getReceiverName() == this->getUsername() && sentreceivedRequests[i]->getRequestStatus() == "Pending")
        {
            countRequest++;
        }
    }
    std::cout << BOLD_BLUE << "Pending Requests:" << RESET << " " << countRequest << "\n";

    // Rating scores
    std::cout << BOLD_BLUE << "Skill Rating Score:" << RESET << " " << getSkillRatingScore() << "\n";
    std::cout << BOLD_BLUE << "Supporter Rating Score:" << RESET << " " << getSupporterRatingScore() << "\n";
    std::cout << BOLD_BLUE << "Host Rating Score:" << RESET << " " << getHostRatingScore() << "\n";

    // End with an empty line
    std::cout << "\n";
}

void RegularMember::showRestrictedMemberInfo()
{
    // Define ANSI escape codes for bold and blue text
    const std::string BOLD_BLUE = "\033[1;34m"; // Bold Blue

    std::cout << BOLD_BLUE << "Username:" << RESET << " " << getUsername() << "\n";
    std::cout << BOLD_BLUE << "Full Name:" << RESET << " " << fullName << "\n";
    std::cout << BOLD_BLUE << "Phone Number:" << RESET << " " << phoneNumber << "\n";
    std::cout << BOLD_BLUE << "Email:" << RESET << " " << email << "\n";
    std::cout << BOLD_BLUE << "Home Address:" << RESET << " " << homeAddress << "\n";
    std::cout << BOLD_BLUE << "City:" << RESET << " ";
    if (city == Hanoi)
    {
        std::cout << "Hanoi\n";
    }
    else
    {
        std::cout << "Saigon\n";
    }
    // Rating scores
    std::cout << BOLD_BLUE << "Skill Rating Score:" << RESET << " " << getSkillRatingScore() << "\n";
    std::cout << BOLD_BLUE << "Supporter Rating Score:" << RESET << " " << getSupporterRatingScore() << "\n";
    std::cout << BOLD_BLUE << "Host Rating Score:" << RESET << " " << getHostRatingScore() << "\n";

    // End with an empty line
    std::cout << "\n";
}

bool RegularMember::topUp(int credPoints)
{
    if (credPoints < 0)
    {
        cout << "Invalid amount!\n";
        return false;
    }
    if (credPoints > 1000)
    {
        cout << "You can only top up up to $1000!\n";
        return false;
    }
    if (credPoints > this->balance)
    {
        cout << "You don't have enough money in your bank account!\n";
        return false;
    }

    this->balance -= credPoints;
    this->creditPoints += credPoints;
    return true;
}

bool RegularMember::sellCredits(int credPoints)
{
    if (credPoints < 0)
    {
        cout << "Invalid amount!\n";
        return false;
    }

    if (credPoints > this->creditPoints)
    {
        cout << "You don't have enough credit points!\n";
        return false;
    }
    // Exchange rate, the admin will profit 10% for commission fee: 1 credit point = $0.9
    this->balance += credPoints * 0.9;
    this->creditPoints -= credPoints;
    return true;
}

bool RegularMember::blockMember(RegularMember &memberToBlock)
{
    for (int i = 0; i < this->blockedMembers.size(); i++)
    {
        if (this->blockedMembers[i]->getUsername() == memberToBlock.getUsername())
        {
            cout << "You have already blocked this member :D\n";
            return false;
        }
    }
    this->blockedMembers.push_back(&memberToBlock);
    return true;
}

bool RegularMember::unblockMember(RegularMember &memberToUnblock)
{
    for (int i = 0; i < this->blockedMembers.size(); i++)
    {
        if (this->blockedMembers[i]->getUsername() == memberToUnblock.getUsername())
        {
            this->blockedMembers.erase(this->blockedMembers.begin() + i);
            return true;
        }
    }
    cout << "You have not blocked this member yet!\n";
    return false;
}

bool RegularMember::isBlockerOf(string blockedUsn)
{
    // Traverse throught the list
    for (int i = 0; i < this->blockedMembers.size(); i++)
    {
        if (this->blockedMembers[i]->getUsername() == blockedUsn)
        {
            return true;
        }
    }
    return false;
}

bool RegularMember::isBlockedBy(string blockerUsn)
{
    // Loop through the blacklist.csv file in read mode
    std::fstream blockFile("./databases/blocklist.csv", std::ios::in);

    if (!blockFile.is_open())
    {
        std::cout << "Error opening blocklist.csv file\n";
        return false;
    }
    // Read the file line by line
    std::string line;
    // Skip the header
    std::getline(blockFile, line);
    while (std::getline(blockFile, line))
    {
        // get the blocker and blocked username
        std::string blocker = line.substr(0, line.find(","));
        std::string blocked = line.substr(line.find(",") + 1, line.length());

        // Check if the other is the blocker
        if (blocker == blockerUsn)
        {
            // Check if current is in the blockedUsername column
            if (blocked == this->getUsername())
            {
                blockFile.close();
                return true;
            }
        }
    }
    blockFile.close();
    return false;
}

// Get the number of skills added by the member
int RegularMember::getNumberOfSkills()
{
    return this->skills.size();
}

// Get the number of skill listings created by the member
int RegularMember::getNumberOfSkillListings()
{
    return this->skillListings.size();
}

// Get the number of incoming requests
int RegularMember::getNumberOfIncomingRequests()
{
    int count = 0;
    for (int i = 0; i < sentreceivedRequests.size(); i++)
    {
        if (sentreceivedRequests[i]->getReceiverName() == this->getUsername())
        {
            count++;
        }
    }
    return count;
}