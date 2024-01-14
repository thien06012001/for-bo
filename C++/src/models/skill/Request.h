#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_REQUEST_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_REQUEST_H

#include <iostream>
#include <string>
#include "SkillListing.h"
#include "../user/RegularMember.h"
#include "../../utils/time/DateTime.h"

using std::string;

class SkillListing; // forward declaration
class Request
{

private:
    string requestID; // Rxxxxxxxx
    // SkillListing *pSkillListing;
    string listingID;                      // Lxxxxxxxx
    std::string requestStatus = "Pending"; // Pending, Accepted, Rejected
    DateTime requestTimeStamp;             // DD/MM/YYYY HH:MM:SS format
    std::string requesterName;
    std::string receiverName;

public:
    Request(std::string requestID = "", std::string listingID = "", std::string requesterName = "", std::string receiverName = "", DateTime requestTimeStamp = DateTime(), std::string requestStatus = "Pending");

    // Getters
    string getRequestID() const { return requestID; };
    string getListingID() const { return listingID; };
    std::string getRequestStatus() const { return requestStatus; };
    DateTime getRequestTimeStamp() const { return requestTimeStamp; };
    std::string getRequesterName() const { return requesterName; };
    std::string getReceiverName() const { return receiverName; };

    // Setters
    void setRequestID(string requestID) { this->requestID = requestID; };
    void setListingID(string listingID) { this->listingID = listingID; };
    void setRequestStatus(std::string requestStatus) { this->requestStatus = requestStatus; };
    void setRequestTimeStamp(DateTime requestTimeStamp) { this->requestTimeStamp = requestTimeStamp; };
    void setRequesterName(std::string requesterName) { this->requesterName = requesterName; };
    void setReceiverName(std::string receiverName) { this->receiverName = receiverName; };

    friend class TimeBankSystem;
    friend class FileHandler;
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_MODELS_SKILL_REQUEST_H