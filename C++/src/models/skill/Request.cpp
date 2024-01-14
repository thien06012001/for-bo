#include <iostream>
#include "Request.h"
#include "../../utils/myUtils.h"
#include <string>
using std::cin;
using std::cout;
using std::string;

Request::Request(string requestID, string listingID, std::string requesterName, std::string receiverName, DateTime requestTimeStamp, std::string requestStatus)
{
    if (requestID.empty())
    {
        this->requestID = "R" + generateRandomID();
    }
    else
    {
        this->requestID = requestID;
    }
    if (requestStatus.empty())
    {
        this->requestStatus = "Pending";
    }
    else
    {
        this->requestStatus = requestStatus;
    }
    this->requesterName = requesterName;
    this->receiverName = receiverName;
    this->requestTimeStamp = requestTimeStamp;
    this->listingID = listingID;
}
