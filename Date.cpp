#include "Date.h"
#include <ctime>

Date::Date(int year, int month, int day)
    : year(year), month(month), day(day) {
}

Date::Date(){
    time_t t = time(0);
    struct tm* now = localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

void Date::SetDate(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

void Date::NextMonth() {
    month++;
    if (month > 12) {
        month = 1;
        year++;
    }
}

void Date::PreviousMonth() {
    month--;
    if (month < 1) {
        month = 12;
        year--;
    }
}
