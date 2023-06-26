#include <iostream>
#include "Event.h"


Event::Event(const Date& date, const std::string& description)
    : date(date), description(description) {
}

const Date& Event::GetDate() const {
    return date;
}

const std::string& Event::GetDescription() const {
    return description;
}

void Event::PrintEvent() const {
    std::cout << date.GetYear() << "-" << date.GetMonth() << "-" << date.GetDay() << ": " << description << std::endl;
}
