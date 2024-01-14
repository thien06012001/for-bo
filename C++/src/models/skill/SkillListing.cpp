#include <iostream>
#include <string>
#include <cmath>
#include "SkillListing.h"
#include "Skill.h"
#include "../../utils/myUtils.h"

using std::cin;
using std::cout;
using std::string;

// Constructor implementation without default arguments
SkillListing::SkillListing(string listingID, string skillID, int consumedCreds, float minHostRatingScore, int listingState, string supporterName, string hostName, Period workingTimeSlot)
{
    // this->skillPerformed = skillPerformed;
    this->supporterName = supporterName;
    this->hostName = hostName;
    this->workingTimeSlot = workingTimeSlot;
    this->consumedCredsPerHour = consumedCreds;
    this->minHostRatingScore = minHostRatingScore;
    this->listingState = listingState;
    if (!listingID.empty())
    {
        this->listingID = listingID;
    }
    else
    {
        this->listingID = "L" + generateRandomID();
    }
    this->skillID = skillID;
}

// Methods
void SkillListing::displaySkillListing()
{
    cout << "Listing ID: " << this->listingID << "\n";
    // cout << "Skill Perform: " << this->skillID << "\n";
    cout << "Cost: " << this->consumedCredsPerHour << "\n";
    // cout << "Minimum Host Rating Score: " << this->minHostRatingScore << "\n";
    // cout << "Listing State: " << this->listingState << "\n";
    cout << "Owner: " << this->supporterName << "\n";
    cout << "Host: " << this->hostName << "\n";
    cout << "Working Time Slot: " << this->workingTimeSlot.getFormattedPeriod() << "\n";
};

bool SkillListing::hideListing()
{
    if (isListingAvailable())
    {
        this->listingState = 1; // 1 = hidden
        return true;
    }
    else
    {
        cout << "This listing is not available to hide or already hidden.\n";
        return false;
    }
}

bool SkillListing::unhideListing()
{
    // Can only unhide listing if the listing is hidden and the listing's start date is in the future
    if ((this->listingState == 1) && (DateTime().isBeforeStartDate(this->workingTimeSlot.getStartDate())))
    {
        this->listingState = 0; // 0 = available
        return true;
    }
    else
    {
        cout << "This listing is not available to unhide or already unhidden.\n";
        return false;
    }
}

float SkillListing::calculateTotalCreds()
{
    int duration = this->workingTimeSlot.durationInSeconds();
    float credsPerSec = static_cast<float>(this->consumedCredsPerHour) / 3600.0f;

    float totalCredits = credsPerSec * static_cast<float>(duration);

    // Round to two decimal places
    totalCredits = std::round(totalCredits * 100.0) / 100.0;

    return totalCredits;
}

bool SkillListing::isListingAvailable()
{
    if (this->listingState == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SkillListing::isListingBooked()
{
    if (this->listingState == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SkillListing::isEligibleToBook(RegularMember &requester)
{
    //    Case 1: If the listing is available
    if (this->listingState == 0)
    {
        // Case 1.1: If the requester is not the owner of the listing, and not get blocked or blocked the owner of the listing
        if ((requester.getUsername() != this->supporterName) && (!requester.isBlockerOf(this->supporterName)) && (!requester.isBlockedBy(this->supporterName)))
        {
            // Case 1.2: If the requester has enough credits to book the listing
            if (requester.getCreditPoints() >= this->calculateTotalCreds())
            {
                // Case 1.3: If the requester's host rating score is higher than the minimum rating score of the listing
                if (requester.getHostRatingScore() >= this->minHostRatingScore)
                {
                    // Case 1.4 If the requester's bookings working time slot is not overlapped with the listing's working time slot
                    for (int i = 0; i < requester.getSkillListings().size(); i++)
                    {
                        if (requester.getSkillListings()[i]->isListingBooked())
                        {
                            if (requester.getSkillListings()[i]->getWorkingTimeSlot().isOverlappedWith(this->workingTimeSlot))
                            {
                                cout << "You can't book this listing because your booking's working time slot is overlapped with this listing's working time slot.\n";
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else
                {
                    cout << "You don't have enough hostRatingScore to book this listing.\n";
                    return false;
                }
            }
            else
            {
                cout << "You don't have enough credits.\n";
                return false;
            }
        }
        else
        {
            cout << "You cannot book your own listing or you two block one another :D\n";
            return false;
        }
    }
    else
    {
        cout << "This listing is not available.\n";
        return false;
    }
}

bool SkillListing::isEligibleToView(RegularMember &searcher)
{
    //    Case 1: If the listing is available
    if (this->listingState == 0)
    {
        // Case 1.1: If the requester is not the owner of the listing, and not get blocked or blocked the owner of the listing
        if ((searcher.getUsername() != this->supporterName) && (!searcher.isBlockerOf(this->supporterName)) && (!searcher.isBlockedBy(this->supporterName)))
        {
            // Case 1.2: If the requester has enough credits to book the listing
            if (searcher.getCreditPoints() >= this->calculateTotalCreds())
            {
                // Case 1.3: If the requester's host rating score is higher than the minimum rating score of the listing
                if (searcher.getHostRatingScore() >= this->minHostRatingScore)
                {
                    // Case 1.4 If the requester's bookings working time slot is not overlapped with the listing's working time slot
                    for (int i = 0; i < searcher.getSkillListings().size(); i++)
                    {
                        if (searcher.getSkillListings()[i]->isListingBooked())
                        {
                            if (searcher.getSkillListings()[i]->getWorkingTimeSlot().isOverlappedWith(this->workingTimeSlot))
                            {
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}