#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include "Review.h"
#include "../../utils/myUtils.h"

using std::cin;
using std::cout;
using std::string;

// Constructor for review by host
Review::Review(string reviewID, string listingID, int skillRating, int supporterRating, std::string comments, string reviewer, string reviewee, DateTime timestamp)
{
    this->timestamp = timestamp;
    if (reviewID == "")
    {
        this->reviewID = "RS" + generateRandomID();
    }
    else
    {
        this->reviewID = reviewID;
    }
    this->listingID = listingID;
    this->skillRating = skillRating;
    this->supporterRating = supporterRating;
    this->comments = comments;
    this->reviewer = reviewer;
    this->reviewee = reviewee;
}

// Constructor for review by supporter
Review::Review(string reviewID, string listingID, std::string comments, string reviewer, string reviewee, DateTime timestamp, int hostRating)
{
    this->timestamp = timestamp;
    if (reviewID == "")
    {
        this->reviewID = "RH" + generateRandomID();
    }
    else
    {
        this->reviewID = reviewID;
    }
    this->listingID = listingID;
    this->hostRating = hostRating;
    this->comments = comments;
    this->reviewer = reviewer;
    this->reviewee = reviewee;
}

void Review::printReview()
{
    cout << "Review ID: " << this->reviewID << " on ListingID: " << this->listingID << "\n";
    cout << reviewer << " --> " << reviewee << " ~ posted on " << this->timestamp.getFormattedTimestamp() << "\n";
    if (this->skillRating != 0)
    {
        cout << "Skill Rating: " << this->skillRating << "\n";
        cout << "Supporter Rating: " << this->supporterRating << "\n";
    }
    else
    {
        cout << "Host Rating: " << this->hostRating << "\n";
    }
    cout << "Description: " << this->comments << "\n";
    cout << std::endl;
}