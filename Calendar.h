
#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "Date.h"
#include "Event.h"
#include <vector>
#include <string>

class Calendar {
public:
	Calendar();
    void Run();

private:
    static std::string GetMonthName(int month);
    static int GetTotalDaysInMonth(int year, int month);
    static bool IsLeapYear(int year);
    static int GetWeekday(int year, int month, int day);

    void Draw() const;
    void NextMonth();
    void PreviousMonth();
    void InputYearAndMonth();
    void CreateEvent();
    void ListEvents() const;
    void DeleteEvent();
    void SaveEvents();
    void LoadEvents();

    Date currentDate;
    std::vector<Event> events;
};

#endif
