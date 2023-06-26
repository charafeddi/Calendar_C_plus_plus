#include "Calendar.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>


Calendar::Calendar():currentDate() {
	time_t t = time(0);
    struct tm* now = localtime(&t);
    currentDate.SetDate(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
}

void Calendar::Run() {
    char choice;
    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "---------------------------\n";
        std::cout << "N: Next month\n";
        std::cout << "P: Previous month\n";
        std::cout << "C: Input year and month\n";
        std::cout << "A: Add an event\n";
        std::cout << "L: List all events\n";
        std::cout << "D: Delete an event\n";
        std::cout << "S: Save events to a file\n";
        std::cout << "R: Load events from a file\n";
        std::cout << "Q: Quit\n";
        std::cout << "---------------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (toupper(choice)) {
            case 'N':
                NextMonth();
                break;
            case 'P':
                PreviousMonth();
                break;
            case 'C':
                InputYearAndMonth();
                break;
            case 'A':
                CreateEvent();
                break;
            case 'L':
                ListEvents();
                break;
            case 'D':
                DeleteEvent();
                break;
            case 'S':
                SaveEvents();
                break;
            case 'R':
                LoadEvents();
                break;
            case 'Q':
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (toupper(choice) != 'Q');
}

std::string Calendar::GetMonthName(int month) {
    static const std::string monthNames[] = {"January", "February", "March", "April", "May", "June", "July",
                                             "August", "September", "October", "November", "December"};
    return monthNames[month - 1];
}

int Calendar::GetTotalDaysInMonth(int year, int month) {
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int totalDays = daysInMonth[month - 1];

    if (month == 2 && IsLeapYear(year)) {
        totalDays++;
    }

    return totalDays;
}

bool Calendar::IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Calendar::GetWeekday(int year, int month, int day) {
    int y, c, m;
    if (month == 1 || month == 2) {
        y = (year - 1) % 100;
        c = (year - 1) / 100;
        m = month + 12;
    } else {
        y = year % 100;
        c = year / 100;
        m = month;
    }
    int weekday = ((y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10) % 7 + 7) % 7;
    return weekday;
}

void Calendar::Draw() const {
    std::cout << std::setw(21) << GetMonthName(currentDate.GetMonth()) << " " << currentDate.GetYear() << "\n";
    std::cout << "*******************************\n";
    std::cout << "SU MO TU WE TH FR SA\n";

    int year = currentDate.GetYear();
    int month = currentDate.GetMonth();
    int totalDays = GetTotalDaysInMonth(year, month);
    int firstWeekday = GetWeekday(year, month, 1);

    int day = 1;
    int weekday = firstWeekday;

    std::cout << std::setw(3 * weekday) << "";
    while (day <= totalDays) {
        std::cout << std::setw(3) << day;
        day++;
        weekday++;

        if (weekday == 7) {
            weekday = 0;
            std::cout << "\n";
        }
    }

    if (weekday != 0) {
        std::cout << "\n";
    }

    std::cout << std::endl;
}

void Calendar::NextMonth() {
    currentDate.NextMonth();
    Draw();
}

void Calendar::PreviousMonth() {
    currentDate.PreviousMonth();
    Draw();
}

void Calendar::InputYearAndMonth() {
    int year, month;
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter month: ";
    std::cin >> month;

    currentDate.SetDate(year, month, 1);
    Draw();
}

void Calendar::CreateEvent() {
    int year, month, day;
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter month: ";
    std::cin >> month;
    std::cout << "Enter day: ";
    std::cin >> day;

    Date date(year, month, day);

    std::cin.ignore();
    std::string description;
    std::cout << "Enter event description: ";
    std::getline(std::cin, description);

    Event event(date, description);
    events.push_back(event);

    std::cout << "Event added successfully." << std::endl;
}

void Calendar::ListEvents() const {
    if (events.empty()) {
        std::cout << "No events found." << std::endl;
    } else {
        std::cout << "Event List:" << std::endl;
        for (int i = 0; i < events.size(); i++) {
            std::cout << "[" << i + 1 << "] ";
            events[i].PrintEvent();
        }
    }
}

void Calendar::DeleteEvent() {
    int eventId;
    std::cout << "Enter event ID to delete: ";
    std::cin >> eventId;

    if (eventId < 1 || eventId > events.size()) {
        std::cout << "Invalid event ID. Please try again." << std::endl;
    } else {
        events.erase(events.begin() + eventId - 1);
        std::cout << "Event deleted successfully." << std::endl;
    }
}

void Calendar::SaveEvents() {
    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin.ignore();
    std::getline(std::cin, fileName);

    std::ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& event : events) {
            file << event.GetDate().GetYear() << " "
                 << event.GetDate().GetMonth() << " "
                 << event.GetDate().GetDay() << " "
                 << event.GetDescription() << "\n";
        }
        file.close();
        std::cout << "Events saved to file successfully." << std::endl;
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}

void Calendar::LoadEvents() {
    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin.ignore();
    std::getline(std::cin, fileName);

    std::ifstream file(fileName);
    if (file.is_open()) {
        events.clear();
        int year, month, day;
        std::string description;

        while (file >> year >> month >> day) {
            file.ignore();
            std::getline(file, description);
            Date date(year, month, day);
            Event event(date, description);
            events.push_back(event);
        }

        file.close();
        std::cout << "Events loaded from file successfully." << std::endl;
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}
