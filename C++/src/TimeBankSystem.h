#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_TIMEBANKSYSTEM_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_TIMEBANKSYSTEM_H

#include <iostream>
#include <vector>
#include "./models/user/RegularMember.h"
#include "./models/user/Admin.h"
#include "./models/skill/Request.h"
#include "./models/skill/SkillListing.h"
#include "./models/skill/Skill.h"
#include "./utils/myUtils.h"
using std::cin;
using std::cout;

class TimeBankSystem
{
private:
    Admin admin;
    RegularMember *currentMember; // The member who is currently logged in
    std::vector<RegularMember> memberList{};
    std::vector<Request> requestList{};
    std::vector<SkillListing> skillListingList{};
    std::vector<Skill> skillList{};
    std::vector<Review> reviewList{};

public:
    TimeBankSystem();

    void welcomeScreen();
    void systemMenu();
    void guestMenu();
    void regularMemberMenu();
    void adminMenu();
    void searchMenu();

    void skillMenu();
    void requestMenu();
    void reviewMenu();
    void listingMenu();
    void profileMenu();

    void loginMenu();
    void registerMenu();
    void promptLogin();
    void logout();
    void promptRegister();

    bool isSkillIDExistAndOwned(string skillID);
    bool isListingIDExistAndOwned(string listingID);
    bool isListingIDExistAndNotOwned(string listingID);
    bool isRequestIDExistAndOwned(string requestID);
    bool isHostReviewGiven(string listingID);
    bool isSupporterReviewGiven(string listingID);

    bool login(const std::string &username, const std::string &password);
    bool isUniqueUsername(string username);

    // Functions for admin
    // Comparison function for sorting in descending order
    int findNumberOfListings(RegularMember &member);
    // Function to find the top 5 members with the most skill listings
    std::vector<RegularMember> findTop5Members(const std::vector<RegularMember> &members);
    void promptAdminChangePassword();
    void viewBarGraph();

    // Functions for regular member
    void promptAddSkill();
    void promptAddListing();
    void promptHideListing();
    void promptUnhideListing();
    bool promptAddRequest();
    void addRequestFromPrompt();
    void promptHostReview();
    void promptSupporterReview();

    bool promptRespondRequest();
    void respondRequestFromPrompt(char choice);

    void promptSearchMember();
    void promptSearchListing();

    void promptTopUp();
    void promptSellCredits();
    void promptBlockMember();
    void promptUnblockMember();

    // Functions for adding new objects to the system's vectors
    void addMember(RegularMember &member);
    void addSkill(Skill &skill);
    void addListing(SkillListing &listing);
    void addRequest(Request &request);
    void addReview(Review &review);

    // Use function template to add new objects to the system's vectors
    template <typename T>
    void addElement(std::vector<T> &vector, T &object)
    {
        vector.push_back(object);
    }

    // Functions for dipslay objects in the system's vectors in pretty tabular format, used by admin or guests based on mode
    void printMemberTable(int mode);  // mode = 1 for admin, mode = 2 for guest
    void printListingTable(int mode); // mode = 1 for admin, mode = 2 for guest
    void printSkillListingTable(SkillListing &listing);
    void printListingNoReviews(SkillListing &listing);

    // Function for display information tailored to a specific user
    void printRequestTableMember();
    void printOutgoingRequestTableMember();
    void printListingTableMember(); // print other supporters listing
    void printOwnedListing();
    void printOwnedSkill();
    void viewProfile();
    void viewReviews();
    void viewTimeTable();

    // Functions for searching objects in the system's vectors
    RegularMember &findMemberByUsername(string username);
    Skill &findSkillByID(string skillID);
    SkillListing &findListingByID(string listingID);
    Request &findRequestByID(string requestID);

    // This two functions use method from FileHandler.cpp to load data from CSV files to vectors and vice versa
    void loadData(); // Load data from CSV files to vectors
    void saveData(); // Save data from vectors to CSV files

    void automaticallyUpdate(); // Automatically update listing state based on current time, and automatically update member's credit based on listing state, and reject expired requests on start
    void updateRatings();       // When the program ends, traverse the review vector and extract each user's rating once more.
    // Function to clear all vectors
    void clearData();

    // When a member is logged in, this function will be called to extract the member's data from the system's vectors
    void extractMemberData();

    void bye();
    int promptAndGetChoice(unsigned min, unsigned max);
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_TIMEBANKSYSTEM_H