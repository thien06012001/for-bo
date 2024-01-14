/*
  RMIT University Vietnam
  Course: EEET2482/COSC2082 Advanced Programming Techniques
  Semester: 2023-3
  Assignment: Final Group Project
  Author: Trinh Nguyen Ha (s3981134)
  Compiler used: g++ (MinGW.org GCC-6.3.0-1) 6.3.0
  Created date: 22/12/2023
  Acknowledgement: https://stackoverflow.com/questions/1650715/is-there-a-standard-date-time-class-in-c
*/

#include <iostream>
#include <time.h>
#include <ctime>
#include "DateTime.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <regex>

using std::cin;
using std::cout;
using std::string;

bool DateTime::isLeapYear(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int DateTime::daysInMonth(int month, int year)
{
  if (month == 2)
  {
    return isLeapYear(year) ? 29 : 28;
  }
  else if (month == 4 || month == 6 || month == 9 || month == 11)
  {
    return 30;
  }
  else
  {
    return 31;
  }
}

DateTime DateTime::addTimePeriod(int days, int hours, int minutes, int seconds)
{
  tm.tm_mday += days;
  tm.tm_hour += hours;
  tm.tm_min += minutes;
  tm.tm_sec += seconds;

  // Handle overflow and normalize
  mktime(&tm);

  // Return DateTime object with normalized values
  return *this; // Assuming DateTime is a class with a suitable constructor
}

DateTime DateTime::calculateEndDate(int days, int hours, int minutes, int seconds)
{
  DateTime endDate = *this;
  endDate.addTimePeriod(days, hours, minutes, seconds);
  return endDate;
}

bool DateTime::isValidFormat(const std::string &timestamp)
{

  std::regex pattern("^\\d{2}/\\d{2}/\\d{4} \\d{2}:\\d{2}:\\d{2}$");
  if (!std::regex_match(timestamp, pattern))
  {
    return false;
  }
  // Format should be "dd/mm/yyyy hh:mm:ss"
  std::istringstream ss(timestamp);
  ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");
  return !ss.fail() && ss.eof();
}

bool DateTime::isValidDate()
{
  // Check if the parsed date is valid
  std::tm copy = tm;
  copy.tm_isdst = -1; // Not considering daylight saving time

  std::time_t tt = std::mktime(&copy);
  if (tt == -1)
  {
    return false; // mktime returns -1 for invalid date/time
  }

  // Ensure the time components are within valid ranges
  if (tm.tm_hour < 0 || tm.tm_hour > 23 ||
      tm.tm_min < 0 || tm.tm_min > 59 ||
      tm.tm_sec < 0 || tm.tm_sec > 59)
  {
    return false;
  }

  // Ensure that the normalized date matches the original date
  std::tm *ptm = std::localtime(&tt);
  return ptm && ptm->tm_mday == tm.tm_mday &&
         ptm->tm_mon == tm.tm_mon && ptm->tm_year == tm.tm_year;
}

DateTime::DateTime()
{
  std::time_t current_time = std::time(nullptr);
  tm = *std::localtime(&current_time);
}

// Constructor that takes a timestamp string
DateTime::DateTime(const std::string &timestamp)
{
  if (!isValidFormat(timestamp))
  {
    throw std::invalid_argument("Invalid date format");
  }
  else if (!isValidDate())
  {
    throw std::invalid_argument("Invalid date");
  }

  // Set initial values
  std::istringstream ss(timestamp);
  ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");
}

std::time_t DateTime::toTimeT() const
{
  return std::mktime(const_cast<std::tm *>(&tm));
}

std::string DateTime::getFormattedTimestamp() const
{
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d/%m/%Y %H:%M:%S");
  return oss.str();
}

bool DateTime::isBeforeStartDate(const DateTime &other) const
{
  return toTimeT() < other.toTimeT();
}

bool DateTime::isStartDate(const DateTime &other) const
{
  return toTimeT() == other.toTimeT();
}