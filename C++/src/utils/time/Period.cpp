/*
  RMIT University Vietnam
  Course: EEET2482/COSC2082 Advanced Programming Techniques
  Semester: 2023-3
  Assignment: Final Group Project
  Author: Trinh Nguyen Ha (s3981134)
  Compiler used: g++ (MinGW.org GCC-6.3.0-1) 6.3.0
  Created date: 24/12/2023
  Last modified: 07/01/2024
  Acknowledgement: https://hoven.in/cpp-projects/calendar-appointments.html
*/

#include <iostream>
#include <string>
#include <stdexcept>

#include "Period.h"
#include "DateTime.h"

// Default constructor
Period::Period() : startDate(DateTime())
{
    startDate.addTimePeriod(2, 0, 0, 0); // Add 2 days to current system time
    endDate = startDate;
    endDate.addTimePeriod(7, 0, 0, 0); // Then add 7 days to startDate for endDate
}

// Constructor with parameters
Period::Period(const DateTime &start, const DateTime &end) : startDate(start), endDate(end)
{
    if (startDate.toTimeT() > endDate.toTimeT())
    {
        throw std::invalid_argument("Start date must be before end date");
    }
}
// Method to check if this period overlaps with another
bool Period::isOverlappedWith(const Period &other) const
{
    return startDate.toTimeT() <= other.endDate.toTimeT() &&
           other.startDate.toTimeT() <= endDate.toTimeT();
}

// Method to calculate the duration of the period in seconds
int Period::durationInSeconds() const
{
    return static_cast<int>(endDate.toTimeT() - startDate.toTimeT());
}

// Method to compare two periods
bool Period::isSameAs(const Period &other) const
{
    return startDate.toTimeT() == other.startDate.toTimeT() &&
           endDate.toTimeT() == other.endDate.toTimeT();
}

std::string Period::convertSecToDuration(long n)
{
    int day = n / (24 * 3600); // an hour has 3600 seconds

    n = n % (24 * 3600); // get the modulus subtracted from a whole day
    int hour = n / 3600;

    n %= 3600; // get the modulus subtracted from a whole hour
    int minutes = n / 60;

    n %= 60; // get the modulus subtracted from a whole minute
    int seconds = n;

    return "Duration: " + std::to_string(day) + " day(s), " + std::to_string(hour) + " " + "hour(s), " + std::to_string(minutes) + " " + "min(s), and " + std::to_string(seconds) + " " + "sec(s).";
}

std::string Period::getFormattedPeriod() const
{
    return startDate.getFormattedTimestamp() + " - " + endDate.getFormattedTimestamp();
}

std::string Period::printMonth(int n)
{
    std::string month;
    switch (n)
    {
    case 1:
        month = "January";
        break;
    case 2:
        month = "February";
        break;
    case 3:
        month = "March";
        break;
    case 4:
        month = "April";
        break;
    case 5:
        month = "May";
        break;
    case 6:
        month = "June";
        break;
    case 7:
        month = "July";
        break;
    case 8:
        month = "August";
        break;
    case 9:
        month = "September";
        break;
    case 10:
        month = "October";
        break;
    case 11:
        month = "November";
        break;
    case 12:
        month = "December";
        break;
    }
    return month;
}

void Period::printYearCalendar(const std::vector<Period *> &busyPeriods)
{
    // Get the current year
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);
    int year = 1900 + localTime->tm_year;
    std::cout << "YEAR: "
              << "\033[1;33m" << std::setw(4) << year << "\033[0m" << std::endl;

    // Iterate over each month and print the calendar
    for (int month = 1; month <= 12; ++month)
    {
        // Print the month header
        std::cout << "\033[1m" << printMonth(month) << "\033[0m" << std::endl;
        // Print the days of the week header
        std::cout << "Su Mo Tu We Th Fr Sa" << std::endl;

        // Determine the first day of the month
        tm firstDayOfMonth = {};
        firstDayOfMonth.tm_year = year - 1900;
        firstDayOfMonth.tm_mon = month - 1;
        firstDayOfMonth.tm_mday = 1;
        mktime(&firstDayOfMonth);

        // Print leading spaces for the first day of the month
        for (int dayOfWeek = 0; dayOfWeek < firstDayOfMonth.tm_wday; ++dayOfWeek)
        {
            std::cout << "   ";
        }

        // Print each day of the month
        for (int day = 1; day <= DateTime::daysInMonth(month, year); ++day)
        {
            // Check if the day is in any busy period
            bool isBusy = false;
            for (const auto &period : busyPeriods)
            {
                // Logic to determine if 'day' is within 'period'
                if (period->startDate.getMonth() == month && period->startDate.getYear() == year)
                {
                    // If the month and year are the same, check if the day is within the period
                    if (period->startDate.getDay() <= day && day <= period->endDate.getDay())
                    {
                        isBusy = true;
                        break;
                    }
                }
            }
            // Change color if the day is busy
            if (isBusy)
            {
                std::cout << "\033[1;31m" << std::setw(2) << day << "\033[0m ";
            }
            else
            {
                std::cout << std::setw(2) << day << " ";
            }

            // Newline if the last day of the week
            if ((day + firstDayOfMonth.tm_wday) % 7 == 0 || day == DateTime::daysInMonth(month, year))
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
}