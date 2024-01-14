/*
  RMIT University Vietnam
  Course: EEET2482/COSC2082 Advanced Programming Techniques
  Semester: 2023-3
  Assignment: Final Group Project
  Author: Trinh Nguyen Ha (s3981134)
  Compiler used: g++ (MinGW.org GCC-6.3.0-1) 6.3.0
  Created date: 22/12/2023
  Acknowledgement:
  https://patorjk.com/software/taag/#p=display&f=Big%20Money-nw&t=TIME%20BANK
  https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124
  https://aarsoftx.com/blogs/make-bar-chart-on-consoleterminal-using-this-c-library
*/

// write documentation

#include <iostream>
#include <string>
#include <unordered_set>

#include "TimeBankSystem.h"
#include "./models/user/Admin.h"
#include "./models/user/RegularMember.h"
#include "./models/user/User.h"
#include "./utils/myUtils.h"
#include "./utils/file/FileHandler.h"
#include "./utils/time/Period.h"
#include "./utils/time/DateTime.h"
#include "./utils/graphs/ConsoleBarChart.h"

using std::cin;
using std::cout;
using std::string;
using namespace aarsoftx; // For the ConsoleBarChart library

// Constructor
TimeBankSystem::TimeBankSystem()
{
}

// Used ANSI escape codes to print colored text
void TimeBankSystem::welcomeScreen()
{
    std::cout << "\033[\e[38;5;16m----------------------------------------------------------------------------------------\033[0m\n"; // Orange color

    std::cout << "                          \033[1m EEET2482/COSC2082 ASSIGNMENT\033[0m                  \n\n";
    std::cout << "\033[\e[38;5;196m $$$$$$$$\\ $$$$$$\\ $$\\      $$\\ $$$$$$$$\\       $$$$$$$\\   $$$$$$\\  $$\\   $$\\ $$\\   $$\\\033[0m\n";
    std::cout << "\033[\e[38;5;202m \\__$$  __|\\_$$  _|$$$\\    $$$ |$$  _____|      $$  __$$\\ $$  __$$\\ $$$\\  $$ |$$ | $$  |\033[0m\n";
    std::cout << "\033[\e[38;5;214m    $$ |     $$ |  $$$$\\  $$$$ |$$ |            $$ |  $$ |$$ /  $$ |$$$$\\ $$ |$$ |$$  /\033[0m\n";
    std::cout << "\033[\e[38;5;227m    $$ |     $$ |  $$\\$$\\$$ $$ |$$$$$\\          $$$$$$$\\ |$$$$$$$$ |$$ $$\\$$ |$$$$$  /\033[0m\n";
    std::cout << "\033[\e[38;5;42m    $$ |     $$ |  $$ \\$$$  $$ |$$  __|         $$  __$$\\ $$  __$$ |$$ \\$$$$ |$$  $$<\033[0m\n";
    std::cout << "\033[\e[38;5;37m    $$ |     $$ |  $$ |\\$  /$$ |$$ |            $$ |  $$ |$$ |  $$ |$$ |\\$$$ |$$ |\\$$\\\033[0m\n";
    std::cout << "\033[\e[38;5;20m    $$ |   $$$$$$\\ $$ | \\_/ $$ |$$$$$$$$\\       $$$$$$$  |$$ |  $$ |$$ | \\$$ |$$ | \\$$\\\033[0m\n";
    std::cout << "\033[\e[38;5;54m    \\__|   \\______|\\__|     \\__|\\________|      \\_______/ \\__|  \\__|\\__|  \\__|\\__|  \\__|\033[0m\n";
    std::cout << "\nInstructor: \033[1;32mMr. Tran Duc Linh\033[0m                  \n";
    std::cout << "Group: \033[1;38;5;131mGroup 14 - HD Destroyers\033[0m             \n"; // Bold text, Orange color
    std::cout << " Trinh Nguyen Ha (s3981134)                      \n";
    std::cout << " Chau Chan Thien (s3975010)                      \n";
    std::cout << " Chau Chan Bang (s3975015)                       \n";
    std::cout << " Tran Manon Ophelie (s3968993)                   \n";
    std::cout << "\033[\e[38;5;16m----------------------------------------------------------------------------------------\033[0m\n";
    std::cout << "Note: Currently supporting hosts and supporters residing in \033[1;31mHanoi\033[0m and \033[1;31mSaigon\033[0m only.                    \n";
    std::cout << "\033[\e[38;5;16m----------------------------------------------------------------------------------------\033[0m\n";
}

void TimeBankSystem::bye()
{
    std::cout << "\033[\e[38;5;16m----------------------------------------------------------------------------------------\033[0m\n";
    std::cout << "Thank you for using our application! See you next time <3\n";
    std::cout << "\033[\e[38;5;16m----------------------------------------------------------------------------------------\033[0m\n";
}

void TimeBankSystem::systemMenu()
{
    printMenuLabel("APPLICATION MENU");
    cout << "0. Quit\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Continue as Guest\n";

    switch (promptAndGetChoice(0, 3))
    {
    case 0:
        bye();
        return;
        break;
    case 1:
        loginMenu();
        break;
    case 2:
        registerMenu();
        break;
    case 3:
        guestMenu();
        break;
    }
}

void TimeBankSystem::loginMenu()
{
    printMenuLabel("LOGIN MENU");
    cout << "1. Login as Admin\n";
    cout << "2. Login as Regular Member\n";
    cout << "3. Back\n";

    switch (promptAndGetChoice(1, 3))
    {
    case 1:
        promptLogin();
        break;
    case 2:
        promptLogin();
        break;
    case 3:
        systemMenu();
        break;
    }
}

void TimeBankSystem::registerMenu()
{
    printMenuLabel("REGISTER MENU");
    cout << "1. Register as Regular Member\n";
    cout << "2. Back\n";

    switch (promptAndGetChoice(1, 2))
    {
    case 1:
        promptRegister();
        break;
    case 2:
        systemMenu();
        break;
    }
}

void TimeBankSystem::guestMenu()
{
    printMenuLabel("GUEST MENU");
    cout << "1. View all of our members\n";
    cout << "2. View all listings available, but be aware that you won't be able to view their reviews!\n";
    cout << "3. Register as Regular Member\n";
    cout << "4. Back\n";

    switch (promptAndGetChoice(1, 4))
    {
    case 1:
        printMemberTable(2); // view all members
        break;
    case 2:
        printListingTable(2); // method to list all skill listings
        break;
    case 3:
        promptRegister();
        break;
    case 4:
        systemMenu();
        break;
    }
}

void TimeBankSystem::adminMenu()
{
    printMenuLabel("ADMIN MENU");
    cout << "1. View All Members\n";
    cout << "2. View All Listings\n";
    cout << "3. Reset Password for a particular Member\n";
    cout << "4. View Sales Figures and Statistics\n"; // Revenue, number of members, number of skills, number of skill listings, who is most active,...
    cout << "5. Sign Out\n";

    switch (promptAndGetChoice(1, 5))
    {
    case 1:
        printMemberTable(1); // method to view all members
        break;
    case 2:
        printListingTable(1); // method to view all listings
        break;
    case 3:
        promptAdminChangePassword();
        break;
    case 4:
        // method to view sales figures and statistics
        // TODO
        viewBarGraph();
        cout << "SALES FIGURES AND STATISTICS\n";
        cout << "Revenue: $" << admin.revenue << "\n";
        cout << "Number of members: " << memberList.size() << "\n";
        cout << "Number of skills: " << skillList.size() << "\n";
        cout << "Number of skill listings: " << skillListingList.size() << "\n";
        adminMenu();
        break;
    case 5:
        logout();
        systemMenu();
        break;
    }
}

void TimeBankSystem::regularMemberMenu()
{
    printMenuLabel("MEMBER MENU");
    cout << "1. Manage Personal Account\n";
    cout << "2. Manage Skills\n";
    cout << "3. Manage Listings\n";
    cout << "4. Manage Requests\n";
    cout << "5. Manage Reviews\n";
    cout << "6. Search\n";
    cout << "7. Sign Out\n";

    switch (promptAndGetChoice(1, 7))
    {
    case 1:
        profileMenu();
        break;
    case 2:
        skillMenu();
        break;
    case 3:
        listingMenu();
        break;
    case 4:
        requestMenu();
        break;
    case 5:
        reviewMenu();
        break;
    case 6:
        searchMenu();
        break;
    case 7:
        logout();
        systemMenu();
        break;
    }
}

int TimeBankSystem::promptAndGetChoice(unsigned min, unsigned max)
{
    // Inclusive
    int choice = -1;
    std::string buffer;
    fflush(stdin); // Clear the input buffer, esp when previously user has entered their info, \n is still in the buffer

    do
    {
        std::cout << "Choose an operation: ";
        std::getline(std::cin, buffer);

        try
        {
            size_t pos;
            choice = std::stoi(buffer, &pos);

            if (pos != buffer.size())
            {
                throw std::invalid_argument("Invalid input");
            }

            if (choice < min || choice > max)
            {
                std::cout << "Invalid choice. Please enter a number between " << min << " and " << max << ".\n";
                choice = -1; // Reset choice if out of range
            }
        }
        catch (std::exception &e)
        {
            std::cout << "Invalid input. Please enter a valid number.\n";
            choice = -1; // Reset choice on exception
        }

    } while (choice == -1);

    return choice;
}

bool TimeBankSystem::isUniqueUsername(string username)
{
    // For admin login
    if (username == "@dmin2023")
    {
        return false;
    }
    // For member login
    for (int i = 0; i < this->memberList.size(); i++)
    {
        if (this->memberList[i].getUsername() == username)
        {
            return false;
        }
    }
    return true;
}

bool TimeBankSystem::login(const std::string &username, const std::string &password)
{
    if (username == "@dmin2023" && password == "aptfinalproject")
    {
        admin.isAuthenticated = true;
        return true;
    }
    else if (username == "@dmin2023" && password != "aptfinalproject")
    {
        return false;
    }
    else if (username != "@dmin2023" && password == "aptfinalproject")
    {
        return false;
    }

    for (auto &user : this->memberList)
    {
        if (user.username == username && user.password == password)
        {
            user.isAuthenticated = true;
            this->currentMember = &user; // Set current member to the user who just logged in
            extractMemberData();         // Extract data from the system's vectors to the current member's vectors
            return true;
        }
    }
    return false;
}

void TimeBankSystem::logout()
{
    if (this->admin.isAuthenticated)
    {
        admin.isAuthenticated = false;
    }
    else if (this->currentMember != nullptr)
    {
        this->currentMember->isAuthenticated = false; // Hot fix for logout bug: segmentation fault
    }
}

RegularMember &TimeBankSystem::findMemberByUsername(string usn)
{
    for (RegularMember &member : this->memberList)
    {
        if (member.getUsername() == usn)
        {
            return member;
        }
    }
    throw std::runtime_error("Member not found!");
}

Skill &TimeBankSystem::findSkillByID(string skillID)
{
    for (Skill &skill : this->skillList)
    {
        if (skill.skillID == skillID)
        {
            return skill;
        }
    }
    throw std::runtime_error("Skill not found!");
}

SkillListing &TimeBankSystem::findListingByID(string listingID)
{
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.listingID == listingID)
        {
            return listing;
        }
    }
    throw std::runtime_error("Listing not found!");
}

Request &TimeBankSystem::findRequestByID(string requestID)
{
    for (Request &request : this->requestList)
    {
        if (request.requestID == requestID)
        {
            return request;
        }
    }
    throw std::runtime_error("Request not found!");
}

void TimeBankSystem::addMember(RegularMember &member)
{
    memberList.push_back(member);
}

void TimeBankSystem::addSkill(Skill &skill)
{
    skillList.push_back(skill);
}

void TimeBankSystem::addListing(SkillListing &listing)
{
    skillListingList.push_back(listing);
}

void TimeBankSystem::addRequest(Request &request)
{
    requestList.push_back(request);
}

void TimeBankSystem::addReview(Review &review)
{
    reviewList.push_back(review);
}

void TimeBankSystem::promptLogin()
{
    std::string username, password;
    do
    {
        cout << "Enter your username: ";
        cin >> username;

        if (isUniqueUsername(username))
        {
            cout << "User not found! Please try again.\n";
        }
    } while (isUniqueUsername(username));

    do
    {
        cout << "Enter your password: ";
        cin >> password;

        if (!login(username, password))
        {
            cout << "Wrong password! Please try again.\n";
        }
    } while (!login(username, password));

    if (username == "@dmin2023")
    {
        adminMenu();
    }
    else
    {
        regularMemberMenu();
    }
}

// For RegularMember registration only
void TimeBankSystem::promptRegister()
{
    std::string username, password, fullName, phoneNumber, email, homeAddress, creditCardNumber, city;
    double latitude, longitude;
    float balance = 1000; // Assume member has 1000$ in their bank account when they type their credit card number
    float skillRatingScore = 0;
    float supporterRatingScore = 0;
    float hostRatingScore = 0;
    float creditPoints = 20; // Default value, pay to system 20$ to get 20 credit points
    do
    {
        username = getValidUsername();

        if (!isUniqueUsername(username))
        {
            cout << "Username already exists! Please try again.\n";
        }
    } while (!isUniqueUsername(username));

    password = getValidPassword();
    fullName = getValidFullName();
    phoneNumber = getValidPhoneNumber();
    email = getValidEmail();
    homeAddress = getValidAddress();
    city = getValidCity();
    std::cout << "Before entering the coordinates, go to the link below and find out your geographic location :)\n";
    cout << "https://support.google.com/maps/answer/18539?hl=en&co=GENIE.Platform\%3DDesktop\n";
    latitude = getValidLatitude();
    longitude = getValidLongitude();
    cin.ignore();
    fflush(stdin); // Clear input buffer
    creditCardNumber = getValidCardNumber();

    if (city == "Hanoi")
    {
        RegularMember newMember(username, password, fullName, phoneNumber, email, homeAddress, Hanoi, latitude, longitude, creditCardNumber, balance, creditPoints, skillRatingScore, supporterRatingScore, hostRatingScore);
        if (newMember.payRegistrationFee())
        {
            addMember(newMember); // Add new member to the member list
            admin.revenue += 20;  // Add 20$ to the system revenue
        }
    }
    else if (city == "Saigon")
    {
        RegularMember newMember(username, password, fullName, phoneNumber, email, homeAddress, Saigon, latitude, longitude, creditCardNumber, balance, creditPoints, skillRatingScore, supporterRatingScore, hostRatingScore);
        if (newMember.payRegistrationFee())
        {
            addMember(newMember); // Add new member to the member list
            admin.revenue += 20;  // Add 20$ to the system revenue
        }
    }

    cout << "Registration successful!\n";
    systemMenu();
}

void TimeBankSystem::profileMenu()
{
    printMenuLabel("PROFILE MENU");
    cout << "1. View Profile\n";
    cout << "2. Top Up Credits\n";
    cout << "3. Sell Credits\n";
    cout << "4. Block a Member\n";
    cout << "5. Unblock a Member\n";
    cout << "6. View Timetable\n";
    cout << "7. Back\n";

    switch (promptAndGetChoice(1, 7))
    {
    case 1:
        viewProfile(); // can view blocked members' usernames
        break;
    case 2:
        promptTopUp();
        break;
    case 3:
        promptSellCredits();
        break;
    case 4:
        promptBlockMember();
        break;

    case 5:
        promptUnblockMember();
        break;
    case 6:
        viewTimeTable();
        break;
    case 7:
        regularMemberMenu();
        break;
    }
}

void TimeBankSystem::skillMenu()
{
    printMenuLabel("SKILLS MENU");
    cout << "1. View Skills\n";
    cout << "2. Add Skill\n";
    cout << "3. Back\n";

    switch (promptAndGetChoice(1, 3))
    {
    case 1:
        // method to view skills of the current members
        printOwnedSkill();
        skillMenu();
        break;
    case 2:
        promptAddSkill();
        break;
    case 3:
        regularMemberMenu();
        break;
    }
}

void TimeBankSystem::listingMenu()
{
    printMenuLabel("LISTINGS MENU");
    cout << "1. View Your Listed Services\n";
    cout << "2. View Listings On Market\n";
    cout << "3. Add Listing\n";
    cout << "4. Hide Listing\n";
    cout << "5. Unhide Listing\n";
    cout << "6. Back\n";

    switch (promptAndGetChoice(1, 6))
    {
    case 1:
        // method to view owned listings of the current members
        printOwnedListing();
        listingMenu();
        break;
    case 2:
        // method to view others listings
        printListingTableMember();
        break;
    case 3:
        // method to add listing, but first display a list of user's skills, and then prompt them to get the ID of the skill they want to list
        promptAddListing();
        break;
    case 4:
        // method to hide listing
        printOwnedListing();
        promptHideListing();
        break;

    case 5:
        // method to unhide listing
        printOwnedListing();
        promptUnhideListing();
        break;

    case 6:
        regularMemberMenu();
        break;
    }
}

void TimeBankSystem::requestMenu()
{
    printMenuLabel("REQUESTS MENU");
    cout << "1. View Incoming Requests\n";
    cout << "2. View Outgoing Requests\n";
    cout << "3. Add Request for a Listing\n";
    cout << "4. Back\n";

    switch (promptAndGetChoice(1, 4))
    {
    case 1:
        // method to view requests, and prompt them to get the ID of the request they want to respond.
        // Check if the user does not have incomming requests, then print out a message and go back to the menu
        if (this->currentMember->getNumberOfIncomingRequests() == 0)
        {
            cout << "You have no incoming requests!\n";
            regularMemberMenu();
            break;
        }
        else
        {
            printRequestTableMember();
            char choice;
            do
            {
                cout << "Do you want to respond to a request? (Y/N): ";
                cin >> choice;

            } while (choice != 'Y' & choice != 'y' & choice != 'N' & choice != 'n');
            if (choice == 'Y' || choice == 'y')
            {
                cout << "1. Accept Request\n";
                cout << "2. Reject Request\n";
                switch (promptAndGetChoice(1, 2))
                {
                case 1:
                    if (promptRespondRequest())
                    {
                        respondRequestFromPrompt('A');
                    }
                    else
                    {
                        cout << "Cannot accept this request. Please try again.\n";
                        regularMemberMenu();
                    }
                    break;
                case 2:
                    // method to reject request
                    respondRequestFromPrompt('R');
                    break;
                }
            }
            else if (choice == 'N' || choice == 'n')
            {
                regularMemberMenu();
                break;
            }
        }
        break;

    case 2:
        printOutgoingRequestTableMember();
        break;
    case 3:
        // method to add request: prompt them to get the ID of the listing they want to request
        if (promptAddRequest())
        {
            addRequestFromPrompt();
        }
        else
        {
            regularMemberMenu();
        }
        break;
    case 4:
        regularMemberMenu();
        break;
    }
}

void TimeBankSystem::reviewMenu()
{
    printMenuLabel("REVIEWS MENU");
    cout << "1. View Review History\n";
    cout << "2. Add Review For a Host\n";
    cout << "3. Add Review For a Supporter\n";
    cout << "4. Back\n";

    switch (promptAndGetChoice(1, 4))
    {
    case 1:
        viewReviews(); // method to view reviews
        break;
    case 2:
        promptHostReview(); // method for a supporter to add review: #RH type
        break;
    case 3:
        promptSupporterReview(); // method for a host to add review: #RS type
        break;

    case 4:
        regularMemberMenu();
        break;
    }
}

void TimeBankSystem::searchMenu()
{
    printMenuLabel("SEARCH MENU");
    cout << "1. Search for a Member\n";
    cout << "2. Search for a listing\n";
    cout << "3. Back\n";

    switch (promptAndGetChoice(1, 3))
    {
    case 1:
        promptSearchMember(); // method to search by username
        break;
    case 2:
        promptSearchListing(); // method to search by location, and min host rate, and by current credits: isEligibleToView()
        break;
    case 3:
        regularMemberMenu();
        break;
    }
}

void TimeBankSystem::viewProfile()
{
    /* Less efficient way because we have to loop through the member list to find the current member
    for (RegularMember &member : this->memberList)
    {
        if (member.isAuthenticated)
        {
            cout << "=============YOUR INFORMATION=============\n";
            member.showInfo();
            break;
        }
    }*/

    cout << "YOUR INFORMATION\n";
    (this->currentMember)->showInfo();
    profileMenu();
}

void TimeBankSystem::viewReviews()
{
    cout << "YOUR REVIEWS\n";
    this->currentMember->printReviews();
    reviewMenu();
}

void TimeBankSystem::viewTimeTable()
{
    this->currentMember->printTimeTable();
    cout << "--------------------------------------------------------------------------------------\n";
    if (!this->currentMember->timeTable.empty())
    {
        cout << "Your busy periods are shown in red.\n";
        Period::printYearCalendar(this->currentMember->timeTable);
    }

    profileMenu();
}

void TimeBankSystem::promptAdminChangePassword()
{
    string username, newPassword;
    int attempts = 0; // Initialize the attempts counter

    do
    {
        cout << "Enter the username of the member you want to reset the password: ";
        cin >> username;

        if (isUniqueUsername(username))
        {
            cout << "User not found! Please try again.\n";
            attempts++;
        }
        else if (username == "@dmin2023")
        {
            cout << "You cannot reset your own password! Please try again.\n";
            attempts++;
        }

        if (attempts >= 3) // Check if the maximum number of attempts (3) has been reached
        {
            cout << "Maximum number of attempts reached. Exiting...\n";
            adminMenu();
            return; // Exit the function
        }

    } while (isUniqueUsername(username) || username == "@dmin2023");
    fflush(stdin); // Clear input buffer
    newPassword = getValidPassword();
    if (!admin.resetPasswordForMember(findMemberByUsername(username), newPassword))
    {
        cout << "Please try again\n";
    }
    adminMenu();
}
int TimeBankSystem::findNumberOfListings(RegularMember &member)
{
    int count = 0;
    for (SkillListing &listing : TimeBankSystem::skillListingList)
    {
        if (listing.getSupporterName() == member.getUsername())
        {
            count++;
        }
    }
    return count;
}

// Function to find the top 5 members with the most skill listings
std::vector<RegularMember> TimeBankSystem::findTop5Members(const std::vector<RegularMember> &members)
{
    std::vector<RegularMember> sortedMembers = members;
    // Capture the TimeBankSystem instance in a lambda
    auto compareMembers = [this](RegularMember &a, RegularMember &b)
    {
        return this->findNumberOfListings(a) > this->findNumberOfListings(b);
    };
    std::sort(sortedMembers.begin(), sortedMembers.end(), compareMembers);

    // Ensure that there are at least 5 members
    if (sortedMembers.size() < 5)
    {
        return sortedMembers;
    }

    // Return the top 5 members
    return std::vector<RegularMember>(sortedMembers.begin(), sortedMembers.begin() + 5);
}

void TimeBankSystem::viewBarGraph()
{
    vector<ConsoleChartData> result;
    vector<RegularMember> top5Members = findTop5Members(this->memberList);
    for (RegularMember &member : top5Members)
    {
        result.push_back({member.getUsername(), findNumberOfListings(member)});
    }
    ConsoleBarChart *cbc = new ConsoleBarChart("Most Active Users (by listings made)", 3, 1, result);
    cbc->show();
}

bool TimeBankSystem::isSkillIDExistAndOwned(string skillID)
{
    for (Skill &skill : this->skillList)
    {
        if (skill.skillID == skillID && skill.getOwnerName() == (this->currentMember)->getUsername())
        {
            return true;
        }
    }
    return false;
}

bool TimeBankSystem::isListingIDExistAndOwned(string listingID)
{
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.listingID == listingID && listing.getSupporterName() == (this->currentMember)->getUsername())
        {
            return true;
        }
    }
    return false;
}

bool TimeBankSystem::isListingIDExistAndNotOwned(string listingID)
{
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.listingID == listingID && listing.getSupporterName() != (this->currentMember)->getUsername())
        {
            return true;
        }
    }
    return false;
}

bool TimeBankSystem::isRequestIDExistAndOwned(string requestID)
{
    for (Request &request : this->requestList)
    {
        if (request.requestID == requestID && request.getReceiverName() == (this->currentMember)->getUsername())
        {
            return true;
        }
    }
    return false;
}

bool TimeBankSystem::isHostReviewGiven(string listingID)
{
    for (Review &review : this->reviewList)
    {
        if (review.reviewID[1] == 'H' && review.listingID == listingID && review.getReviewer() == (this->currentMember)->getUsername())
        {
            return true;
        }
    }
    return false;
}

bool TimeBankSystem::isSupporterReviewGiven(string listingID)
{
    for (Review &review : this->reviewList)
    {
        if (review.reviewID[1] == 'S' && review.listingID == listingID && review.getReviewer() == (this->currentMember)->getUsername())
        {
            return true;
        }
    }
    return false;
}

// Functions to ask user input for adding new objects to the system's vectors

void TimeBankSystem::promptAddSkill()
{
    std::string skillID, skillName, skillDescription, skillEfficiency, ownerName = "";
    skillName = getValidStringInput("Enter skill name: ");
    skillDescription = getValidStringInput("Enter skill description (no commas): ");
    skillEfficiency = getValidStringInput("Enter skill efficiency (Skillful/Adequate/Medium/...): ");
    ownerName = (this->currentMember)->getUsername();
    Skill newSkill(skillID, skillName, skillDescription, skillEfficiency, ownerName);
    addSkill(newSkill);
    (currentMember)->skills.push_back(&newSkill);
    cout << "Skill added successfully!\n";
    regularMemberMenu();
}

void TimeBankSystem::promptAddListing()
{
    printOwnedSkill();
    cout << std::endl;
    std::string listingID, startDate, endDate, buffer = "";
    std::string skillID;
    int consumedCredsPerHour = 0;
    float minHostRatingScore = -1;
    int listingState = 0; // 0 = available, 1 = hidden, 2 = booked, 3 = completed; default = available when listing is created
    Period workingTimeSlot;
    // Exit the loop after 3 wrong attempts
    int attempts = 0;
    do
    {
        skillID = getValidStringInput("Enter skillID to begin making a Job Listing on the market: ");
        if (!isSkillIDExistAndOwned(skillID))
        {
            cout << "SkillID not found or not one of your added skills! Please try again.\n";
            attempts++;
        }
        if (attempts >= 3)
        {
            cout << "You've reached the maximum number of wrong attempts. Exiting...\n";
            listingMenu();
            return;
        }
    } while (!isSkillIDExistAndOwned(skillID));

    consumedCredsPerHour = getValidInt("Enter consumed credits per hour: ");
    do
    {
        cout << "Do you want to set a minimum host rating score? (Y/N): ";
        cin >> buffer;
        if (buffer == "Y" || buffer == "y")
        {
            minHostRatingScore = getValidFloat("Enter minimum host rating score: ");
            break;
        }
        else if (buffer == "N" || buffer == "n")
        {
            minHostRatingScore = -1;
            break;
        }
        else
        {
            cout << "Invalid input! Please try again.\n";
        }
    } while (buffer != "Y" || buffer != "y" || buffer != "N" || buffer != "n");
    fflush(stdin); // Clear input buffer
    std::string supporterName = (this->currentMember)->getUsername();
    std::string hostName = ""; // Host name is empty when listing is created, will be updated when the listing is booked by that host
    startDate = getValidTimestamp("Enter start date in DD/MM/YYYY HH:MM:SS format: ");

    // Improve algorithm to make sure that the start date is after today's date
    DateTime checkStartDate(startDate);
    while (!DateTime().isBeforeStartDate(checkStartDate))
    {
        cout << "Start date cannot be before today's date! Please try again.\n";
        startDate = getValidTimestamp("Enter start date in DD/MM/YYYY HH:MM:SS format: ");
        checkStartDate = DateTime(startDate);
    }

    // Improve algorithm to make sure that the end date is after start date
    endDate = getValidTimestamp("Enter end date in DD/MM/YYYY HH:MM:SS format: ");
    DateTime checkEndDate(endDate);
    while (!checkStartDate.isBeforeStartDate(checkEndDate))
    {
        cout << "End date cannot be before start date! Please try again.\n";
        endDate = getValidTimestamp("Enter end date in DD/MM/YYYY HH:MM:SS format: ");
        checkEndDate = DateTime(endDate);
    }
    workingTimeSlot = Period(DateTime(startDate), DateTime(endDate));
    SkillListing newListing = SkillListing(listingID, skillID, consumedCredsPerHour, minHostRatingScore, listingState, supporterName, hostName, workingTimeSlot);
    addListing(newListing);
    // (currentMember->skillListings).push_back(&newListing); // Bug: dangling pointer because of a shallow copy and the object is destroyed after the function ends
    (currentMember->skillListings).push_back(&findListingByID(newListing.listingID)); // Hot fix: push back the pointer to the listing in the system's vector
    cout << "Listing added successfully!\n";
    listingMenu();
}

void TimeBankSystem::promptHideListing()
{
    std::string listingID;
    // Prompt user to enter listingID until they enter a valid listingID that is owned by them
    int attempts = 0;
    do
    {
        listingID = getValidStringInput("Enter listingID to hide: ");
        if (!isListingIDExistAndOwned(listingID))
        {
            cout << "ListingID not found or not one of your added listings! Please try again.\n";
            attempts++;
        }
        if (attempts >= 3)
        {
            cout << "You've reached the maximum number of wrong attempts. Exiting...\n";
            listingMenu();
            return;
        }

    } while ((!isListingIDExistAndOwned(listingID)));

    if (findListingByID(listingID).hideListing())
    {
        cout << "Listing hidden successfully!\n";
    }
    else
    {
        cout << "Listing hide failed! Please try again.\n";
    }
    listingMenu();
}

void TimeBankSystem::promptUnhideListing()
{
    std::string listingID;
    // Prompt user to enter listingID until they enter a valid listingID that is owned by them
    // Exit the loop after 3 wrong attempts
    int attempts = 0;
    do
    {
        listingID = getValidStringInput("Enter listingID to unhide: ");
        if (!isListingIDExistAndOwned(listingID))
        {
            cout << "ListingID not found or not one of your added listings! Please try again.\n";
            attempts++;
        }

        else if (findListingByID(listingID).getListingState() != 1)
        {
            cout << "Listing is not hidden! Please try again.\n";
            attempts++;
        }
        if (attempts >= 3)
        {
            cout << "You've reached the maximum number of wrong attempts. Exiting...\n";
            listingMenu();
            return;
        }

    } while ((!isListingIDExistAndOwned(listingID)) || findListingByID(listingID).getListingState() != 1);

    if (findListingByID(listingID).unhideListing())
    {
        cout << "Listing unhidden successfully!\n";
    }
    else
    {
        cout << "Listing unhide failed! Please try again.\n";
    }
    listingMenu();
}

bool TimeBankSystem::promptAddRequest()
{

    std::string requestID, listingID, requesterName, receiverName, requestStatus = "";

    std::string buffer = "";
    int attempts = 0;
    // Exit the loop when wrong attempts is bigger than 3
    do
    {
        listingID = getValidStringInput("Enter listingID to begin making a request: ");
        if (!isListingIDExistAndNotOwned(listingID))
        {
            cout << "ListingID not found or is one of your added listings! Please try again.\n";
            attempts++;
        }
        if (attempts == 3)
        {
            return false;
        }
    } while (!isListingIDExistAndNotOwned(listingID));

    // cout << "Checking today's date and listing's start date...\n"; // For debugging purpose
    if (!DateTime().isBeforeStartDate(findListingByID(listingID).getWorkingTimeSlot().getStartDate()))
    {
        cout << "You cannot make a request for this listing because today's date is after the listing's start date!\n";
        return false;
    }

    requesterName = (this->currentMember)->getUsername();         // host
    receiverName = findListingByID(listingID).getSupporterName(); // supporter
    /*Deep check*/
    // If the supporter is blocked by the host, the host cannot make a request for that supporter
    if (currentMember->isBlockerOf(receiverName))
    {
        cout << "You cannot make a request for this supporter because you have blocked them!\n";
        return false;
    }
    // If the host is blocked by the supporter, the host cannot make a request for that supporter
    else if (currentMember->isBlockedBy(receiverName))
    {
        cout << "You cannot make a request for this supporter because they have blocked you :(\n";
        return false;
    }

    // If the supporter is not available at the time the host wants to book, the host cannot make a request for that supporter
    for (Request *request : currentMember->sentreceivedRequests)
    {
        if (request->getRequestStatus() == "Accepted")
        {
            if (findListingByID(request->getListingID()).getSupporterName() == findListingByID(listingID).getSupporterName())
            {
                if (findListingByID(request->getListingID()).getWorkingTimeSlot().isOverlappedWith(findListingByID(listingID).getWorkingTimeSlot()))
                {
                    cout << "You cannot make a request for this supporter because they are not available at that time!\n";
                    return false;
                }
            }
        }
    }

    // If the host has already made a request for that listing, the host cannot make another one when the previous one is still pending
    for (Request *request : currentMember->sentreceivedRequests)
    {
        if (request->getRequestStatus() == "Pending")
        {
            if (request->getListingID() == listingID)
            {
                cout << "You cannot make a request because you have already done one for this listing!\n";
                return false;
            }
        }
    }

    // isEligibleToBook method
    SkillListing listing = findListingByID(listingID);
    if (!listing.isEligibleToBook(*currentMember))
    {
        cout << "You cannot make a request for this listing because some of the requirements are not met!\n";
        return false;
    }
    // Proceed to create a new request when all the above conditions are met
    return true;
}

void TimeBankSystem::addRequestFromPrompt()
{
    std::string requestID, listingID, requesterName, receiverName, requestStatus = "";
    listingID = getValidStringInput("Reenter the listingID to confirm: ");
    requesterName = (this->currentMember)->getUsername();         // host
    receiverName = findListingByID(listingID).getSupporterName(); // supporter

    Request newRequest(requestID, listingID, requesterName, receiverName, DateTime(), requestStatus);
    addRequest(newRequest);                                                                  // Add new request to the system's request list
    (currentMember->sentreceivedRequests).push_back(&findRequestByID(newRequest.requestID)); // Add new request to the current member's request list

    cout << "Request added successfully!\n";
    regularMemberMenu();
}

void TimeBankSystem::respondRequestFromPrompt(char choice)
{
    std::string requestID;
    bool isValidRequest;
    do
    {
        requestID = getValidStringInput("Enter requestID to respond: ");
        isValidRequest = isRequestIDExistAndOwned(requestID);

        if (!isValidRequest)
        {
            cout << "RequestID not found or not one of your incoming requests! Please try again.\n";
        }
    } while (!isValidRequest);

    if (choice == 'A')
    {
        findRequestByID(requestID).setRequestStatus("Accepted");
        findListingByID(findRequestByID(requestID).getListingID()).setListingState(2); // Set to book
        findListingByID(findRequestByID(requestID).getListingID()).setHostName(findRequestByID(requestID).getRequesterName());
        // Add timeslot to occupied timetable
        DateTime date1(findListingByID(findRequestByID(requestID).getListingID()).workingTimeSlot.getStartDate());
        DateTime date2(findListingByID(findRequestByID(requestID).getListingID()).workingTimeSlot.getEndDate());
        Period period(date1, date2);
        this->currentMember->timeTable.push_back(&period);
        cout << "Request accepted successfully!\n";
    }
    else if (choice == 'R')
    {
        findRequestByID(requestID).setRequestStatus("Rejected");
        cout << "Request rejected successfully!\n";
    }
    regularMemberMenu();
}

bool TimeBankSystem::promptRespondRequest()
{
    std::string requestID;
    bool isValidRequest;
    int wrongAttempts = 0; // Counter for wrong attempts

    do
    {
        requestID = getValidStringInput("Enter requestID to check: ");
        isValidRequest = isRequestIDExistAndOwned(requestID);

        if (!isValidRequest)
        {
            wrongAttempts++; // Increment the wrong attempts
            cout << "RequestID not found or not one of your incoming requests! Please try again.\n";

            if (wrongAttempts >= 3)
            {
                cout << "You've reached the maximum number of wrong attempts. Exiting...\n";
                return false;
            }
        }
    } while (!isValidRequest);

    if (!DateTime().isBeforeStartDate(findListingByID(findRequestByID(requestID).getListingID()).getWorkingTimeSlot().getStartDate()))
    {
        cout << "You cannot respond to this request because today's date is after the listing's start date!\n";
        return false;
    }

    else if (findRequestByID(requestID).getRequestStatus() == "Accepted")
    {
        cout << "You cannot respond to this request because it is already accepted!\n";
        return false;
    }

    else if (findRequestByID(requestID).getRequestStatus() == "Rejected")
    {
        cout << "You cannot respond to this request because it is already rejected!\n";
        return false;
    }

    // Check if the listingID has already been booked
    if (findListingByID(findRequestByID(requestID).listingID).isListingBooked())
    {
        cout << "You cannot respond to this request because the listingID is not available anymore.\n";
        return false;
    }

    // Check with ongoing bookings of the supporter if they are available to accept the request (e,g: not overlapped with other bookings timeslot)
    for (Request *request : currentMember->sentreceivedRequests)
    {
        if (request->getRequestStatus() == "Accepted")
        {
            if (findListingByID(request->getListingID()).getSupporterName() == findListingByID(findRequestByID(requestID).getListingID()).getSupporterName())
            {
                if (findListingByID(request->getListingID()).getWorkingTimeSlot().isOverlappedWith(findListingByID(findRequestByID(requestID).getListingID()).getWorkingTimeSlot()))
                {
                    cout << "You cannot respond to this request because you are not available at that time!\n";
                    return false;
                }
            }
        }
    }
    return true;
}

void TimeBankSystem::promptHostReview()
{
    // Print a table of completed listings that wasn't given a host review yet
    cout << "UNREVIEWED LISTINGS\n";
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.listingState == 4 && listing.getSupporterName() == (this->currentMember)->getUsername())
        {
            if (!isHostReviewGiven(listing.listingID))
            {
                findSkillByID(listing.skillID).showInfo();
                listing.displaySkillListing();
                cout << std::endl;
            }
        }
    }

    std::string listingID, reviewID, reviewContent, reviewerName, revieweeName = "";
    int wrongAttempts = 0; // Counter for wrong attempts
    // Exit the loop after 3 wrong attempts
    do
    {
        listingID = getValidStringInput("Enter listingID to begin making a review: ");
        if (!isListingIDExistAndOwned(listingID))
        {
            cout << "ListingID not found or not one of your added listings! Please try again.\n";
            wrongAttempts++;
        }
        else if (isHostReviewGiven(listingID))
        {
            cout << "You have already given a host review for this listing! Please try again.\n";
            wrongAttempts++;
        }

        if (wrongAttempts == 3) // Check if wrong attempts have reached 3
        {
            cout << "Maximum attempts reached. Returning to the menu.\n";
            regularMemberMenu();
            return; // Exit the method
        }

    } while (!isListingIDExistAndOwned(listingID) || isHostReviewGiven(listingID));

    // Check if the listing is completed
    if (findListingByID(listingID).listingState == 4)
    {
        reviewerName = (this->currentMember)->getUsername();
        revieweeName = findListingByID(listingID).getHostName();
        if (revieweeName == (this->currentMember)->getUsername())
        {
            cout << "You cannot review yourself! Please try again.\n";
            regularMemberMenu();
        }
        else if (revieweeName == "@dmin2023")
        {
            cout << "You cannot review the admin! Please try again.\n";
            regularMemberMenu();
        }
        else if (currentMember->isBlockedBy(revieweeName))
        {
            cout << "You cannot review this host because they have blocked you :(\n";
            regularMemberMenu();
        }
        else if (currentMember->isBlockerOf(revieweeName))
        {
            cout << "You cannot review this host because you have blocked them!\n";
            regularMemberMenu();
        }
        else
        {
            reviewContent = getValidStringInput("Enter review content: ");
            int hostRatingScore = getValidInt("Enter host rating score (1-5): ");
            reviewerName = (this->currentMember)->getUsername();
            Review newReview(reviewID, listingID, reviewContent, reviewerName, revieweeName, DateTime(), hostRatingScore);
            addReview(newReview);
            (currentMember->sentreceivedReviews).push_back(&newReview);
            // Also add to the reviewee's review list
            // findMemberByUsername(revieweeName).sentreceivedReviews.push_back(&newReview);
            cout << "Review added successfully!\n";
            regularMemberMenu();
        }
    }
    else
    {
        cout << "You cannot review this listing because it is not completed yet!\n";
        regularMemberMenu();
    }
}

void TimeBankSystem::promptSupporterReview()
{
    // Cannot give supporter review if you are the supporter of the listing
    // Print a table of completed listings that wasn't given a host review yet
    cout << "UNREVIEWED LISTINGS: \n";
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.listingState == 4 && listing.getHostName() == (this->currentMember)->getUsername())
        {
            if (!isSupporterReviewGiven(listing.listingID))
            {
                printSkillListingTable(listing);
            }
        }
    }
    std::string listingID, reviewID, reviewContent, reviewerName, revieweeName = "";
    int wrongAttempts = 0; // Counter for wrong attempts
    // Exit the loop after 3 wrong attempts
    do
    {
        listingID = getValidStringInput("Enter listingID to begin making a review: ");
        if (!isListingIDExistAndNotOwned(listingID))
        {
            cout << "ListingID not found or is one of your added listings! Please try again.\n";
            wrongAttempts++;
        }
        else if (isSupporterReviewGiven(listingID))
        {
            cout << "You have already given a review for this listing! Please try again.\n";
            wrongAttempts++;
        }

        if (wrongAttempts == 3) // Check if wrong attempts have reached 3
        {
            cout << "Maximum attempts reached. Returning to the menu.\n";
            regularMemberMenu();
            return; // Exit the method
        }

    } while (!isListingIDExistAndNotOwned(listingID) || isSupporterReviewGiven(listingID));

    // Check if the listing is completed
    if (findListingByID(listingID).listingState == 4)
    {
        reviewerName = (this->currentMember)->getUsername();
        revieweeName = findListingByID(listingID).getSupporterName();
        if (revieweeName == (this->currentMember)->getUsername())
        {
            cout << "You cannot review yourself! Please try again.\n";
            regularMemberMenu();
        }
        else if (revieweeName == "@dmin2023")
        {
            cout << "You cannot review the admin! Please try again.\n";
            regularMemberMenu();
        }
        else if (currentMember->isBlockedBy(revieweeName))
        {
            cout << "You cannot review this supporter because they have blocked you :(\n";
            regularMemberMenu();
        }
        else if (currentMember->isBlockerOf(revieweeName))
        {
            cout << "You cannot review this supporter because you have blocked them!\n";
            regularMemberMenu();
        }
        else
        {
            reviewContent = getValidStringInput("Enter review content: ");
            int skillRatingScore = getValidInt("Enter skill rating score (1-5): ");
            int supporterRatingScore = getValidInt("Enter supporter rating score (1-5): ");
            reviewerName = (this->currentMember)->getUsername();
            Review newReview(reviewID, listingID, skillRatingScore, supporterRatingScore, reviewContent, reviewerName, revieweeName, DateTime());
            addReview(newReview);
            (currentMember->sentreceivedReviews).push_back(&newReview);
            // Also add to the reviewee's review list
            // findMemberByUsername(revieweeName).sentreceivedReviews.push_back(&newReview);
            cout << "Review added successfully!\n";
            regularMemberMenu();
        }
    }
    else
    {
        cout << "You cannot review this listing because it is not completed yet!\n";
        regularMemberMenu();
    }
}

void TimeBankSystem::promptSearchMember()
{
    std::string username;
    int attempts = 0; // Initialize the attempts counter

    do
    {
        username = getValidStringInput("Enter username to search: ");

        if (isUniqueUsername(username))
        {
            cout << "User not found! Please try again.\n";
            attempts++;
        }
        else if (username == this->currentMember->getUsername())
        {
            cout << "You cannot search yourself! Please try again.\n";
            attempts++;
        }
        else if (username == "@dmin2023")
        {
            cout << "You cannot search the admin! Please try again.\n";
            attempts++;
        }

        if (attempts >= 3) // Check if the maximum number of attempts (3) has been reached
        {
            cout << "Maximum number of attempts reached. Exiting...\n";
            regularMemberMenu();
            return; // Exit the function
        }
    } while (isUniqueUsername(username) || username == currentMember->getUsername() || username == "@dmin2023");
    RegularMember searchedMember = findMemberByUsername(username);
    if (currentMember->isBlockedBy(searchedMember.getUsername()))
    {
        cout << "Seems like they have blocked you :(\n";
        regularMemberMenu();
    }
    else if (currentMember->isBlockerOf(searchedMember.getUsername()))
    {
        cout << "You cannot search this member because you have blocked them!\n";
        regularMemberMenu();
    }
    else
    {
        cout << "SEARCHED MEMBER INFORMATION\n";
        searchedMember.showRestrictedMemberInfo();
        regularMemberMenu();
    }
}

void TimeBankSystem::promptSearchListing()
{
    std::string startDay, endDay, city;
    // This method will filter the listings based on the city, start date, end date
    // The displayed listings will be based on if the current member is eligible to view them

    // Prompt user to enter the city
    city = getValidCity();
    fflush(stdin); // Clear input buffer
    vector<SkillListing> saigonListings;
    vector<SkillListing> hanoiListings;

    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.getSupporterName() != this->currentMember->getUsername() && listing.listingState == 0)
        {
            if (listing.isEligibleToView(*currentMember))
            {
                if (findMemberByUsername(listing.getSupporterName()).city == 24)
                {
                    hanoiListings.push_back(listing);
                }
                else if (findMemberByUsername(listing.getSupporterName()).city == 28)
                {
                    saigonListings.push_back(listing);
                }
            }
        }
    }

    // Ask for start date and end date
    startDay = getValidTimestamp("Enter start date in DD/MM/YYYY HH:MM:SS format: ");
    cout << "Choose intervals: 1. Within 6 hours  2. Within 1 day  3. Within 1 week  4. Not specified\n";

    Period timeSlot1, timeSlot2, timeSlot3;
    switch (promptAndGetChoice(1, 4))
    {
    case 1:
        endDay = DateTime(startDay).addTimePeriod(0, 6, 0, 0).getFormattedTimestamp();
        cout << "Estimated end date: " << endDay << std::endl;
        timeSlot1 = Period(DateTime(startDay), DateTime(endDay));
        if (city == "Hanoi")
        {
            for (SkillListing &listing : hanoiListings)
            {
                if (listing.getWorkingTimeSlot().isOverlappedWith(timeSlot1))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        else if (city == "Saigon")
        {
            for (SkillListing &listing : saigonListings)
            {
                if (listing.getWorkingTimeSlot().isOverlappedWith(timeSlot1))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        break;
    case 2:
        endDay = DateTime(startDay).addTimePeriod(1, 0, 0, 0).getFormattedTimestamp();
        cout << "Estimated end date: " << endDay << std::endl;
        timeSlot2 = Period(DateTime(startDay), DateTime(endDay));
        if (city == "Hanoi")
        {
            for (SkillListing &listing : hanoiListings)
            {
                if (listing.getWorkingTimeSlot().isOverlappedWith(timeSlot2))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        else if (city == "Saigon")
        {
            for (SkillListing &listing : saigonListings)
            {
                if (listing.getWorkingTimeSlot().isOverlappedWith(timeSlot2))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        break;
    case 3:
        endDay = DateTime(startDay).addTimePeriod(7, 0, 0, 0).getFormattedTimestamp();
        cout << "Estimated end date: " << endDay << std::endl;
        timeSlot3 = Period(DateTime(startDay), DateTime(endDay));

        if (city == "Hanoi")
        {
            for (SkillListing &listing : hanoiListings)
            {
                if (listing.getWorkingTimeSlot().isOverlappedWith(timeSlot3))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        else if (city == "Saigon")
        {
            for (SkillListing &listing : saigonListings)
            {
                if (listing.getWorkingTimeSlot().isOverlappedWith(timeSlot3))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        break;
    case 4:
        cout << "Estimated end date: ~" << std::endl;
        if (city == "Hanoi")
        {
            for (SkillListing &listing : hanoiListings)
            {
                if (!listing.getWorkingTimeSlot().getStartDate().isBeforeStartDate(DateTime(startDay)))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        else if (city == "Saigon")
        {

            for (SkillListing &listing : saigonListings)
            {
                if (!listing.getWorkingTimeSlot().getStartDate().isBeforeStartDate(DateTime(startDay)))
                {
                    printSkillListingTable(listing);
                }
            }
        }
        break;
    }

    regularMemberMenu();
}

void TimeBankSystem::promptTopUp()
{
    float amount = getValidFloat("Enter amount of credit to top up: ");
    // Authorize the payment by get the user to enter their password to confirm
    string password;
    do
    {
        cout << "Enter your password to confirm transaction: ";
        cin >> password;
        if (password != (this->currentMember)->getPassword())
        {
            cout << "Wrong password! Please try again.\n";
        }
    } while (password != (this->currentMember)->getPassword());
    cout << "Processing payment...\n";

    if (currentMember->topUp(amount))
    {
        cout << "Top up successful! Added " << amount << " credits to your account.\n";
        this->admin.revenue += amount; // Add the amount of credits to the system's revenue
    }
    else
    {
        cout << "Top up failed! Please try again.\n";
    }
    profileMenu();
}

void TimeBankSystem::promptSellCredits()
{
    // This will transfer 90% value of the amount of credits to the member's bank account from the system's revenue
    float amount = getValidFloat("Enter amount of credit to sell: ");
    if (currentMember->sellCredits(amount))
    {
        cout << "Sell credits successful! Added $" << amount * 0.9 << " to your account.\n";
        this->admin.revenue -= amount * 0.9;
    }
    else
    {
        cout << "Sell credits failed! Please try again.\n";
    }
    profileMenu();
}

void TimeBankSystem::promptBlockMember()
{
    string username;
    std::fstream blockFile("./databases/blocklist.csv", std::ios::app);

    do
    {
        cout << "Enter the username of the member you want to block: ";
        cin >> username;
        if (isUniqueUsername(username))
        {
            cout << "User not found! Please try again.\n";
        }
        else if (username == this->currentMember->getUsername())
        {
            cout << "You cannot block yourself! Please try again.\n";
        }
        else if (username == "@dmin2023")
        {
            cout << "You cannot block the admin! Please try again.\n";
        }

    } while (isUniqueUsername(username) || username == currentMember->getUsername() || username == "@dmin2023");
    RegularMember blockedMember = findMemberByUsername(username);
    if (currentMember->blockMember(blockedMember))
    {
        cout << "Block successful!\n";
        // Write the blocked member directly to the file
        blockFile << currentMember->getUsername() << "," << username << "\n";
        blockFile.close(); // Close the file
    }
    else
    {
        cout << "Block failed! Please try again.\n";
    }
    profileMenu();
}

void TimeBankSystem::promptUnblockMember()
{

    if (currentMember->blockedMembers.size() == 0)
    {
        cout << "You have not blocked anyone yet!\n";
    }
    else
    {
        cout << "=============YOUR BLOCKED MEMBERS=============\n";
        for (RegularMember *member : currentMember->blockedMembers)
        {
            cout << member->getUsername() << std::endl;
        }
        cout << "==============================================\n";
    }
    string username;
    std::fstream blockFile("./databases/blocklist.csv", std::ios::app);

    do
    {
        cout << "Enter the username of the member you want to unblock: ";
        cin >> username;
        if (isUniqueUsername(username))
        {
            cout << "User not found! Please try again.\n";
        }
        else if (username == this->currentMember->getUsername())
        {
            cout << "You cannot unblock yourself! Please try again.\n";
        }
        else if (username == "@dmin2023")
        {
            cout << "You cannot unblock the admin! Please try again.\n";
        }

    } while (isUniqueUsername(username) || username == currentMember->getUsername() || username == "@dmin2023");
    RegularMember unblockedMember = findMemberByUsername(username);
    if (currentMember->unblockMember(unblockedMember))
    {
        // cout << "Unblock successful!\n";
        // Delete the unblocked member directly from the file by finding the info line, then delete that line
        std::string line;
        std::ifstream blockFile("./databases/blocklist.csv");
        int lineCount = 0;
        while (getline(blockFile, line))
        {
            lineCount++;
            if (line.find(currentMember->getUsername() + "," + username) != std::string::npos)
            {
                break;
            }
        }
        cout << "Line count: " << lineCount << std::endl;

        blockFile.close();
        if (deleteLine("./databases/blocklist.csv", lineCount))
        {
            cout << "Unblock successful!\n";
        }
        else
        {
            cout << "Unblock failed! Please try again.\n";
        }
    }
    else
    {
        cout << "Unblock failed! Please try again.\n";
    }
    profileMenu();
}

void TimeBankSystem::printRequestTableMember()
{
    vector<string> headers = {"RequestID", "ListingID", "Requester", "Receiver", "Timestamp", "Status"};
    vector<int> widths = {12, 15, 15, 15, 25, 15};

    // Print the header
    printHeader(headers, widths);
    for (const auto &request : this->currentMember->sentreceivedRequests)
    {
        if (request->getReceiverName() == (this->currentMember)->getUsername())
        {
            string requestID = request->getRequestID();
            string listingID = request->getListingID();
            string requesterName = request->getRequesterName();
            string receiverName = request->getReceiverName();
            string requestTimeStamp = request->getRequestTimeStamp().getFormattedTimestamp();
            string requestStatus = request->getRequestStatus();
            printRow({requestID, listingID, requesterName, receiverName, requestTimeStamp, requestStatus}, widths);
        }
    }
    printFooter(widths);
    cout << "\nPotential Hosts' Information: \n";

    // Create a set to store processed usernames
    std::unordered_set<std::string> processedUsernames;

    for (const auto &request : this->currentMember->sentreceivedRequests)
    {
        if (request->getReceiverName() == (this->currentMember)->getUsername() && request->requestStatus == "Pending")
        {
            // Check if the username has been processed
            const std::string requesterName = request->getRequesterName();
            if (processedUsernames.find(requesterName) == processedUsernames.end())
            {
                // Print information and mark as processed
                findMemberByUsername(requesterName).showRestrictedMemberInfo();
                processedUsernames.insert(requesterName);
            }
        }
    }
}

void TimeBankSystem::printOutgoingRequestTableMember()
{
    vector<string> headers = {"RequestID", "ListingID", "Requester", "Receiver", "Timestamp", "Status"};
    vector<int> widths = {10, 15, 15, 15, 20, 15};
    printHeader(headers, widths);
    for (const auto &request : this->currentMember->sentreceivedRequests)
    {
        if (request->getRequesterName() == (this->currentMember)->getUsername())
        {
            string requestID = request->getRequestID();
            string listingID = request->getListingID();
            string requesterName = request->getRequesterName();
            string receiverName = request->getReceiverName();
            string requestTimeStamp = request->getRequestTimeStamp().getFormattedTimestamp();
            string requestStatus = request->getRequestStatus();
            printRow({requestID, listingID, requesterName, receiverName, requestTimeStamp, requestStatus}, widths);
        }
    }
    printFooter(widths);
    cout << "\nRequested Listings Information: \n";

    for (const auto &request : this->currentMember->sentreceivedRequests)
    {
        if (request->getRequesterName() == (this->currentMember)->getUsername())
        {
            printSkillListingTable(findListingByID(request->getListingID()));
        }
    }
    requestMenu();
}

void TimeBankSystem::printOwnedListing()
{
    if (this->currentMember->skillListings.size() == 0)
    {
        cout << "You have not added any listings yet" << std::endl;
    }
    else
    {
        cout << "Here are your added listings:\n";
        vector<string> headers = {"ListingID", "SkillID", "Cost", "MinHostRating", "State", "Supporter", "Host", "WorkingTimeSlot"};
        vector<int> widths = {11, 11, 7, 15, 6, 15, 15, 45};
        // Print the header
        printHeader(headers, widths);

        for (SkillListing *&listing : this->currentMember->skillListings)
        {
            string rating;
            std::string workingTime = listing->getWorkingTimeSlot().getFormattedPeriod();
            string listingID = listing->getListingID();
            string skillID = listing->getSkillID();
            string cost = roundUpToNDecimalPlaces(listing->calculateTotalCreds(), 1);
            if (listing->getMinHostRatingScore() == -1)
            {
                rating = "Any";
            }
            else
            {
                rating = roundUpToNDecimalPlaces(listing->getMinHostRatingScore(), 2);
            }

            string state = std::to_string(listing->getListingState());
            string supporter = listing->getSupporterName();
            string host = listing->getHostName();
            printRow({listingID, skillID, cost, rating, state, supporter, host, workingTime}, widths);
        }

        // Print the footer
        printFooter(widths);
    }
    // listingMenu();
}

void TimeBankSystem::printOwnedSkill()
{
    if (this->currentMember->skills.size() == 0)
    {
        cout << "You have not added any skills yet" << std::endl;
    }
    else
    {
        cout << "Here are your added skills:\n";
        vector<string> headers = {"SkillID", "SkillName", "Description", "Efficiency"};
        vector<int> widths = {12, 25, 80, 20};
        printHeader(headers, widths); // Print the header

        for (const auto &skill : this->currentMember->skills)
        {
            string skillID = skill->getSkillID();
            string skillName = skill->getSkillName();
            string description = skill->getDescription();
            string efficiency = skill->getSkillEfficiency();
            printRow({skillID, skillName, description, efficiency}, widths);
        }
        printFooter(widths); // Print the footer
    }
}

void TimeBankSystem::printListingTableMember()
{
    // print all listings on the market, make sure the current member is not the supporter of the listing, and they are eligible to view the listing
    cout << "Here are available listings on the market:\n";
    if (this->skillListingList.size() == 0)
    {
        cout << "N/A" << std::endl;
    }
    else
    {
        for (SkillListing &listing : this->skillListingList)
        {
            if (listing.supporterName != this->currentMember->getUsername() && listing.listingState == 0 && listing.isEligibleToView(*currentMember))
            {
                printSkillListingTable(listing);
                cout << std::endl;
            }
        }
    }

    char choice;
    do
    {
        cout << "Do you want to book a listing? (Y/N): ";
        cin >> choice;

    } while (choice != 'Y' & choice != 'y' & choice != 'N' & choice != 'n');
    fflush(stdin); // Clear input buffer
    if (choice == 'Y' || choice == 'y')
    {
        if (promptAddRequest())
        {
            addRequestFromPrompt();
        }
        else
        {
            listingMenu();
        }
    }
    else if (choice == 'N' || choice == 'n')
    {
        listingMenu();
    }
}

void TimeBankSystem::printSkillListingTable(SkillListing &listing)
{
    // print a single listing
    int leftColumnWidth = 40;
    int rightColumnWidth = 85;
    RegularMember supporter = findMemberByUsername(listing.supporterName);
    Skill skill = findSkillByID(listing.skillID);
    string city = (supporter.city == 24) ? "Hanoi" : "Saigon";
    int secs = listing.workingTimeSlot.durationInSeconds();
    string distance = (supporter.calculateDistance(*currentMember) > 10000) ? "~" : std::to_string(supporter.calculateDistance(*currentMember));
    string minHostRatingScore = (listing.minHostRatingScore == -1) ? "Any" : std::to_string(listing.minHostRatingScore);
    string listingStatus = (listing.listingState == 0) ? "Available" : (listing.listingState == 1) ? "Hidden"
                                                                   : (listing.listingState == 2)   ? "Booked"
                                                                   : (listing.listingState == 3)   ? "Ongoing"
                                                                                                   : "Completed";
    // Draw the top line of the table
    drawTableLine(leftColumnWidth + rightColumnWidth + 3);
    const std::string colorCode = "\e[1;93m";      // Yellow color code
    const std::string colorCode2 = "\e[38;5;213m"; // Pink color code
    const std::string colorReset = "\033[0m";      // Reset color code
    int colorCodeLength = colorCode.length() + colorReset.length();
    int colorCodeLength2 = colorCode2.length() + colorReset.length();

    // Draw the header row
    drawRow("Supporter Info", "\e[1;93mListing ID: " + listing.listingID + "\033[0m" + " - Total Credits Cost: " + std::to_string(listing.calculateTotalCreds()), leftColumnWidth, rightColumnWidth + colorCodeLength);
    drawTableLine(leftColumnWidth + rightColumnWidth + 3); // Draw line after header

    // Draw rows of the table
    drawRow("username: " + listing.getSupporterName(), "Skill perform:", leftColumnWidth, rightColumnWidth);
    drawRow("full name: " + supporter.fullName, "+ Name: " + skill.skillName, leftColumnWidth, rightColumnWidth);
    drawRow("phone number: " + supporter.phoneNumber, "+ Description: " + skill.description, leftColumnWidth, rightColumnWidth);
    drawRow("email: " + supporter.email, "+ Efficiency: " + skill.skillEfficiency, leftColumnWidth, rightColumnWidth);
    drawRow("home address: " + supporter.homeAddress, "Start Date: " + listing.workingTimeSlot.getStartDate().getFormattedTimestamp(), leftColumnWidth, rightColumnWidth);
    drawRow("city: " + city, "End Date: " + listing.workingTimeSlot.getEndDate().getFormattedTimestamp(), leftColumnWidth, rightColumnWidth);
    drawRow("hostRatingScore: " + std::to_string(supporter.getHostRatingScore()), listing.workingTimeSlot.convertSecToDuration(secs), leftColumnWidth, rightColumnWidth);
    drawRow("skillRatingScore: " + std::to_string(supporter.getSkillRatingScore()), "Status: " + listingStatus, leftColumnWidth, rightColumnWidth);
    drawRow("supporterRatingScore: " + std::to_string(supporter.getSupporterRatingScore()), "Minimum hostRatingScore required: " + minHostRatingScore, leftColumnWidth, rightColumnWidth);
    drawRow("", "Distance from you: \e[38;5;213m" + distance + " kilometers\033[0m", leftColumnWidth, rightColumnWidth + colorCodeLength2);

    drawTableLine(leftColumnWidth + rightColumnWidth + 3); // Draw the bottom line of the table

    // Print comments
    for (Review &review : this->reviewList)
    {
        if (review.getReviewee() == supporter.getUsername())
        {
            drawRow2("\e[1m\e[38;5;217m" + review.getReviewID() + +"\e[0m"
                                                                   ": " +
                         review.getReviewer() + " posted on " + review.timestamp.getFormattedTimestamp(),
                     "", rightColumnWidth, leftColumnWidth);
            drawRow2("Skill: " + findSkillByID(findListingByID(review.listingID).skillID).skillName, "", rightColumnWidth, leftColumnWidth);
            if (review.reviewID[1] == 'H')
            {
                drawRow2("hostRatingScore: " + std::to_string(review.hostRating), "", rightColumnWidth, leftColumnWidth);
            }
            else if (review.reviewID[1] == 'S')
            {
                drawRow2("skillRatingScore: " + std::to_string(review.skillRating), "", rightColumnWidth, leftColumnWidth);
                drawRow2("supporterRatingScore: " + std::to_string(review.supporterRating), "", rightColumnWidth, leftColumnWidth);
            }
            drawRow2("Comments: " + review.comments, "", leftColumnWidth, rightColumnWidth);
            // drawRow2("", "", rightColumnWidth, leftColumnWidth);
        }
    }
    drawTableLine(leftColumnWidth + rightColumnWidth + 3);
}

void TimeBankSystem::printListingNoReviews(SkillListing &listing)
{
    // print a single listing
    int leftColumnWidth = 40;
    int rightColumnWidth = 85;
    RegularMember supporter = findMemberByUsername(listing.supporterName);
    Skill skill = findSkillByID(listing.skillID);
    string city = (supporter.city == 24) ? "Hanoi" : "Saigon";
    int secs = listing.workingTimeSlot.durationInSeconds();
    // double distance = supporter.calculateDistance(*currentMember);
    string minHostRatingScore = (listing.minHostRatingScore == -1) ? "Any" : std::to_string(listing.minHostRatingScore);
    string listingStatus = (listing.listingState == 0) ? "Available" : (listing.listingState == 1) ? "Hidden"
                                                                   : (listing.listingState == 2)   ? "Booked"
                                                                   : (listing.listingState == 3)   ? "Ongoing"
                                                                                                   : "Completed";
    // Draw the top line of the table
    drawTableLine(leftColumnWidth + rightColumnWidth + 3);

    // Draw the header row
    drawRow(" Supporter Info", " Listing ID: " + listing.listingID + " - Total Credits Cost: " + std::to_string(listing.calculateTotalCreds()), leftColumnWidth, rightColumnWidth);

    // Draw line after header
    drawTableLine(leftColumnWidth + rightColumnWidth + 3);

    // Draw rows of the table
    drawRow("username: " + listing.getSupporterName(), "Skill perform:", leftColumnWidth, rightColumnWidth);
    drawRow("full name: " + supporter.fullName, "+ Name: " + skill.skillName, leftColumnWidth, rightColumnWidth);
    drawRow("phone number: " + supporter.phoneNumber, "+ Description: " + skill.description, leftColumnWidth, rightColumnWidth);
    drawRow("email: " + supporter.email, "+ Efficiency: " + skill.skillEfficiency, leftColumnWidth, rightColumnWidth);
    drawRow("home address: " + supporter.homeAddress, "Start Date: " + listing.workingTimeSlot.getStartDate().getFormattedTimestamp(), leftColumnWidth, rightColumnWidth);
    drawRow("city: " + city, "End Date: " + listing.workingTimeSlot.getEndDate().getFormattedTimestamp(), leftColumnWidth, rightColumnWidth);
    drawRow("hostRatingScore: " + std::to_string(supporter.getHostRatingScore()), listing.workingTimeSlot.convertSecToDuration(secs), leftColumnWidth, rightColumnWidth);
    drawRow("skillRatingScore: " + std::to_string(supporter.getSkillRatingScore()), "Status: " + listingStatus, leftColumnWidth, rightColumnWidth);
    drawRow("supporterRatingScore: " + std::to_string(supporter.getSupporterRatingScore()), "Minimum hostRatingScore required: " + minHostRatingScore, leftColumnWidth, rightColumnWidth);
    // drawRow("", "Distance from you: " + std::to_string(distance) + " kilometers", leftColumnWidth, rightColumnWidth);

    // Draw the bottom line of the table
    drawTableLine(leftColumnWidth + rightColumnWidth + 3);
}

void TimeBankSystem::printMemberTable(int mode)
{
    // Mode 1 print for admin, mode 2 for guests
    if (mode == 1)
    {
        for (RegularMember &mem : this->memberList)
        {
            mem.showRestrictedMemberInfo();
        }
        adminMenu();
    }
    else if (mode == 2)
    {
        for (RegularMember &mem : this->memberList)
        {
            mem.showRestrictedMemberInfo();
        }
        guestMenu();
    }
}

void TimeBankSystem::printListingTable(int mode)
{
    // Admin mode can view comments and all modes
    if (mode == 1)
    {
        for (SkillListing &listing : this->skillListingList)
        {
            printSkillListingTable(listing);
        }
        adminMenu();
    }
    else if (mode == 2) // Guests mode cannot view comments, and only see the available ones
    {
        for (SkillListing &listing : this->skillListingList)
        {
            if (listing.listingState == 0)
            {
                printListingNoReviews(listing);
            }
        }
        guestMenu();
    }
}

void TimeBankSystem::loadData()
{
    FileHandler fileHandler;
    this->memberList = fileHandler.loadUsers("./databases/users.csv");
    this->admin = fileHandler.loadAdmin("./databases/admin.csv");
    this->skillList = fileHandler.loadSkills("./databases/skills.csv");
    this->skillListingList = fileHandler.loadListings("./databases/listings.csv");
    this->requestList = fileHandler.loadRequests("./databases/requests.csv");
    this->reviewList = fileHandler.loadReviews("./databases/reviews.csv");
}

void TimeBankSystem::saveData()
{
    FileHandler fileHandler;
    fileHandler.saveUsers("./databases/users.csv", this->memberList);
    fileHandler.saveAdmin("./databases/admin.csv", this->admin);
    fileHandler.saveSkills("./databases/skills.csv", this->skillList);
    fileHandler.saveListings("./databases/listings.csv", this->skillListingList);
    fileHandler.saveRequests("./databases/requests.csv", this->requestList);
    fileHandler.saveReviews("./databases/reviews.csv", this->reviewList);
}

void TimeBankSystem::extractMemberData()
{

    // Clear the current member's vectors first
    (this->currentMember)->skills.clear();
    (this->currentMember)->skillListings.clear();
    (this->currentMember)->sentreceivedRequests.clear();
    (this->currentMember)->sentreceivedReviews.clear();
    (this->currentMember)->blockedMembers.clear();
    (this->currentMember)->receivedHostReviews.clear();
    (this->currentMember)->receivedSupporterReviews.clear();
    (this->currentMember)->timeTable.clear();

    // Extract data from skillList, skillListingList, requestList, reviewList to current user's skillListings, requests, reviews vectors of pointers
    /*skill*/
    for (Skill &skill : this->skillList)
    {
        if (skill.getOwnerName() == (this->currentMember)->getUsername())
        {
            (this->currentMember)->skills.push_back(&skill);
        }
    }

    /*skillListing*/
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.getSupporterName() == (this->currentMember)->getUsername())
        {
            (this->currentMember)->skillListings.push_back(&listing);
        }
    }

    /*request*/
    for (Request &request : this->requestList)
    {
        if (request.getRequesterName() == (this->currentMember)->getUsername()) // If the current member is the host
        {
            (this->currentMember)->sentreceivedRequests.push_back(&request); // sentRequest
        }
        else if (request.getReceiverName() == (this->currentMember)->getUsername()) // If the current member is the supporter
        {
            (this->currentMember)->sentreceivedRequests.push_back(&request); // receivedRequest
        }
    }

    /*review*/
    for (Review &review : this->reviewList)
    {
        if (review.getReviewer() == (this->currentMember)->getUsername())
        {
            (this->currentMember)->sentreceivedReviews.push_back(&review); // sentReview
        }
        else if (review.getReviewee() == (this->currentMember)->getUsername())
        {
            (this->currentMember)->sentreceivedReviews.push_back(&review); // receivedReview
        }
    }

    /*blockList*/
    std::fstream blockFile("./databases/blocklist.csv", std::ios::in);
    std::string line;
    std::string blocker, blockedMemberUsername;

    // Skip the first line
    std::getline(blockFile, line);

    while (std::getline(blockFile, line))
    {
        std::stringstream ss(line);
        std::getline(ss, blocker, ',');               // Read the blocker username
        std::getline(ss, blockedMemberUsername, ','); // Read the blocked member username

        if (blocker == (this->currentMember)->getUsername())
        {
            // You don't need to read blockedMemberUsername again here.
            // Instead, you can directly add it to the vector.
            RegularMember *blockedMember = &findMemberByUsername(blockedMemberUsername);

            if (blockedMember != nullptr)
            {
                (this->currentMember)->blockedMembers.push_back(blockedMember);
            }
            else
            {
                cout << "Error populating blocked members list!\n";
            }
        }
    }
    // Get the current member's timetable, check 2 and 3 state of the listing of that user and push back the time slot to the timetable
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.getSupporterName() == (this->currentMember)->getUsername() || listing.getHostName() == (this->currentMember)->getUsername())
        {
            if (listing.getListingState() == 2 || listing.getListingState() == 3)
            {
                (this->currentMember)->timeTable.push_back(&(listing.workingTimeSlot));
            }
        }
    }

    // Automatically update the pending request state to rejected when when the supporter timetable conflicts with the requested listing time slot.
    for (Request &request : this->requestList)
    {
        if (request.getRequestStatus() == "Pending" && request.receiverName == (this->currentMember)->getUsername())
        {

            for (Period *slot : this->currentMember->timeTable)
            {
                if (slot->isOverlappedWith(findListingByID(request.getListingID()).getWorkingTimeSlot()))
                {
                    request.setRequestStatus("Rejected");
                }
            }
        }
    }
}

void TimeBankSystem::automaticallyUpdate()
{
    // Automatically update the available listing state to hidden when the start date is passed
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.getListingState() == 0 && listing.getWorkingTimeSlot().getStartDate().isBeforeStartDate(DateTime()))
        {
            listing.setListingState(1);
        }
    }
    // Automatically update the available listing state to hidden when the the supporter time slot is not available
    // Loop through the supporter's skill listings, check for booked and ongoing ones
    // If the working timeslot of any of those listings overlaps with the currently available listing's working time slot, hide it
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.getListingState() == 0)
        {
            for (SkillListing &listing2 : this->skillListingList)
            {
                if (listing2.getListingState() == 2 || listing2.getListingState() == 3)
                {
                    if (listing.getSupporterName() == listing2.getSupporterName())
                    {
                        if (listing.getWorkingTimeSlot().isOverlappedWith(listing2.getWorkingTimeSlot()))
                        {
                            listing.setListingState(1);
                        }
                    }
                }
            }
        }
    }
    // Automatically update the booked listing state to ongoing when the start date is passed
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.getListingState() == 2 && listing.getWorkingTimeSlot().getStartDate().isBeforeStartDate(DateTime()))
        {
            listing.setListingState(3);
        }
    }
    // Automatically update the ongoing listing state to completed when the end date is passed
    for (SkillListing &listing : this->skillListingList)
    {
        if (listing.getListingState() == 3 && listing.getWorkingTimeSlot().getEndDate().isBeforeStartDate(DateTime()))
        {
            listing.setListingState(4);
            // Automatically increment the supporter's credit points when the listing is completed
            float creds = listing.calculateTotalCreds();
            // cout << "Supporter earned " << creds << " credits for completing this listing!\n"; // Debugging purpose
            findMemberByUsername(listing.getSupporterName()).creditPoints += listing.calculateTotalCreds();
            // Automatically decrement the host's credit points when the listing is completed
            findMemberByUsername(listing.getHostName()).creditPoints -= listing.calculateTotalCreds();
        }
    }

    // Automatically update the pending request state to rejected when the start date is passed
    for (Request &request : this->requestList)
    {
        if (request.getRequestStatus() == "Pending" && findListingByID(request.getListingID()).getWorkingTimeSlot().getStartDate().isBeforeStartDate(DateTime()))
        {
            request.setRequestStatus("Rejected");
        }
    }
    // Automatically update the pending request state to rejected when the listingID is hidden
    for (Request &request : this->requestList)
    {
        if (request.getRequestStatus() == "Pending" && findListingByID(request.getListingID()).getListingState() == 1)
        {
            request.setRequestStatus("Rejected");
        }
    }
    // Automatically update the pending request state to rejected when the listingID is booked by another host
    for (Request &request : this->requestList)
    {
        if (request.getRequestStatus() == "Pending" && (findListingByID(request.getListingID()).getListingState() == 2 || findListingByID(request.getListingID()).getListingState() == 3))
        {
            request.setRequestStatus("Rejected");
        }
    }
    // Automatically update the pending request state to rejected when one member blocks another member or vice versa
    for (Request &request : this->requestList)
    {
        if (request.getRequestStatus() == "Pending")
        {
            if (findMemberByUsername(request.getRequesterName()).isBlockedBy(request.getReceiverName()) || findMemberByUsername(request.getReceiverName()).isBlockedBy(request.getRequesterName()))
            {
                request.setRequestStatus("Rejected");
            }
        }
    }
}

void TimeBankSystem::updateRatings()
{
    for (RegularMember &mem : this->memberList)
    {
        this->currentMember = &mem;
        extractMemberData();
        mem.hostRatingScore = mem.getHostRatingScore();
        mem.skillRatingScore = mem.getSkillRatingScore();
        mem.supporterRatingScore = mem.getSupporterRatingScore();
        this->currentMember = nullptr; // Reset the current member pointer
    }
}

void TimeBankSystem::clearData()
{
    this->memberList.clear();
    this->skillList.clear();
    this->skillListingList.clear();
    this->requestList.clear();
    this->reviewList.clear();
}