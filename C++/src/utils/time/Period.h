#ifndef EEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_TIME_PERIOD_H
#define EEEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_TIME_PERIOD_H

#include "DateTime.h"

class Period
{
private:
    DateTime startDate;
    DateTime endDate;

public:
    // Constructor
    Period();
    Period(const DateTime &start, const DateTime &end);

    // Getters
    DateTime getStartDate() const { return startDate; }
    DateTime getEndDate() const { return endDate; }

    // Method to check if this period overlaps with another time period
    bool isOverlappedWith(const Period &other) const;

    // Method to calculate the duration of the period in seconds
    int durationInSeconds() const;

    // Method to compare two periods
    bool isSameAs(const Period &other) const;

    // Function to print the calendar of the current year
    static std::string printMonth(int n);
    static void printYearCalendar(const std::vector<Period *> &busyPeriods);

    // Convert seconds to duration format (e.g. 1d 2h 3m 4s)
    static std::string convertSecToDuration(long n);

    std::string getFormattedPeriod() const;

    friend class TimeBankSystem;
    friend class FileHandler;
    friend class SkillListing;
};

#endif // EEET2482_COSC2082_2023C_GROUP14_TIMEBANKAPP_SRC_UTILS_TIME_PERIOD_H