#ifndef _EVENT_H
#define _EVENT_H

#include "Date.h"
#include <string>

class Event {
public:
    Event(const Date& date, const std::string& description);

    const Date& GetDate() const;
    const std::string& GetDescription() const;
    void PrintEvent() const;

private:
    Date date;
    std::string description;
};

#endif 
