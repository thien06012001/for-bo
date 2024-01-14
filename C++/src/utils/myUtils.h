#ifndef EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_MYUTILS_H
#define EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_MYUTILS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>


// Function to generate random ID numbers with 8 digits long
std::string generateRandomID();

// Functions to validate bank card number
bool isValidCard(std::string cardNumber);
std::string trimAndRemoveSpaces(std::string &str);
int sumEvenDigits(const std::string cardNumber);
int sumOfOddPlace(const std::string cardNumber);
int getDigit(const int number);

// Functions to validate user input when creating a new account
std::string getValidUsername();                   // username must be 6-17 characters long, only contains letters, numbers, underscores, and hyphens, no spaces
std::string getValidPassword();                   // password must be 8-17 characters long, no spaces
std::string getValidFullName();                   // name must be 2-50 characters long, only contains letters, spaces, and hyphens
std::string getValidEmail();                      // must contain @, no spaces
std::string getValidPhoneNumber();                // must be 10 digits long, only contains numbers, no spaces
std::string getValidAddress();                    // only contains letters, numbers, spaces, and hyphens, no commas
std::string getValidCardNumber();                 // use the isValidCard function above to validate card number
std::string getValidCity();                       // only Hanoi or Saigon
double getValidDouble(const std::string &prompt); // only numbers, no spaces
double getValidLatitude();                        // only numbers, no spaces
double getValidLongitude();                       // only numbers, no spaces

// Functions to validate user input when creating a new skill
std::string getValidStringInput(const std::string &prompt); // only letters, numbers, spaces, and hyphens, no commas

// Functions to validate user input when creating a new skill listing
float getValidFloat(const std::string &prompt);           // only numbers, no spaces
int getValidInt(const std::string &prompt);               // only numbers, no spaces
std::string getValidTimestamp(const std::string &prompt); // DD/MM/YYYY HH:MM:SS format, check if the date is valid, and make sure that single-digit dates, months, hours, minutes, and seconds are padded with 0

// Functions to draw table when printing info
void drawTableLine(int width);
void drawRow(const std::string &left, const std::string &right, int leftWidth, int rightWidth);
void drawRow2(const std::string &left, const std::string &right, int leftWidth, int rightWidth);

std::string roundUpToNDecimalPlaces(float number, int decimalPlaces);
std::vector<int> calculateWidths(const std::vector<std::string> &headers);
void printHeader(const std::vector<std::string> &headers, const std::vector<int> &widths);
void printLine(const std::vector<int> &widths, char c);
void printRow(const std::vector<std::string> &data, const std::vector<int> &widths);
void printFooter(const std::vector<int> &widths);

// Function to delete a line from a file
bool deleteLine(const std::string &filename, int lineNumber);

// Function to print the menu label
void printMenuLabel(const std::string &labelName);

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_MYUTILS_H