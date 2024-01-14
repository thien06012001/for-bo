#ifndef EEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_TIME_DATETIME_H
#define EEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_TIME_DATETIME_H

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>

class DateTime
{
private:
    std::tm tm;

public:
    bool isValidFormat(const std::string &timestamp);
    bool isValidDate();
    static bool isLeapYear(int year);
    static int daysInMonth(int month, int year);

    // Default constructor sets to current system time
    DateTime();

    // Constructor that takes a timestamp string
    DateTime(const std::string &timestamp);

    // Getters for individual components
    int getDay() const { return tm.tm_mday; }
    int getMonth() const { return tm.tm_mon + 1; }    // tm_mon is 0-11
    int getYear() const { return tm.tm_year + 1900; } // tm_year is years since 1900
    int getHour() const { return tm.tm_hour; }
    int getMinute() const { return tm.tm_min; }
    int getSecond() const { return tm.tm_sec; }

    DateTime addTimePeriod(int days, int hours, int minutes, int seconds);
    DateTime calculateEndDate(int days, int hours, int minutes, int seconds);
    std::time_t toTimeT() const;

    bool isBeforeStartDate(const DateTime &other) const;
    bool isStartDate(const DateTime &other) const;

    std::string getFormattedTimestamp() const;

    friend class Period;
    friend class TimeBankSystem;
};
#endif // EEET2482_COSC2082_UTILS_TIME_DATE_HEEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_TIME_DATETIME_H
