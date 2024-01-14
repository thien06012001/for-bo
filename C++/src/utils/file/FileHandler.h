#ifndef EEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_FILE_FILEHANDLER_H
#define EEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_FILE_FILEHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "../../models/user/User.h"
#include "../../models/user/Admin.h"
#include "../../models/user/RegularMember.h"
#include "../../models/skill/Skill.h"
#include "../../models/skill/SkillListing.h"
#include "../../models/skill/Request.h"
#include "../../models/skill/Review.h"
#include "../../utils/myUtils.h"

using std::cin;
using std::cout;
using std::string;

class FileHandler
{
public:
    FileHandler();
    std::vector<std::string> splitString(const std::string &input, char delimiter);
    RegularMember parseCSVLine(const std::string &csvLine);
    std::string convertToCSV(const RegularMember &member);

    // Function to load data from the CSV file into an Admin object
    Admin loadAdmin(const std::string &filename);
    // Function to save data from the Admin object to the CSV file
    void saveAdmin(const std::string &filename, const Admin &admin);

    // Function to load data from the CSV file into a vector<RegularMember>
    std::vector<RegularMember> loadUsers(const std::string &filename);
    // Function to save data from the vector<RegularMember> to the CSV file
    void saveUsers(const std::string &filename, const std::vector<RegularMember> &memberList);

    // Function to load data from the CSV file into a vector<Skill>
    std::vector<Skill> loadSkills(const std::string &filename);
    // Function to save data from the vector<Skill> to the CSV file
    void saveSkills(const std::string &filename, const std::vector<Skill> &skillList);

    // Function to load data from the CSV file into a vector<SkillListing>
    std::vector<SkillListing> loadListings(const std::string &filename);
    // Function to save data from the vector<SkillListing> to the CSV file
    void saveListings(const std::string &filename, const std::vector<SkillListing> &listingList);

    // Function to load data from the CSV file into a vector<Review>
    std::vector<Review> loadReviews(const std::string &filename);
    // Function to save data from the vector<Review> to the CSV file
    void saveReviews(const std::string &filename, const std::vector<Review> &reviewList);

    // Function to load data from the CSV file into a vector<Request>
    std::vector<Request> loadRequests(const std::string &filename);
    // Function to save data from the vector<Request> to the CSV file
    void saveRequests(const std::string &filename, const std::vector<Request> &requestList);
};

#endif // EEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_FILE_FILEHANDLER_H