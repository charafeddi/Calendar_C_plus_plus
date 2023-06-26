
#ifndef _DATE_H
#define _DATE_H

class Date {
public:
    Date(int year, int month, int day);
	Date();
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    void SetDate(int year, int month, int day);
    void NextMonth();
    void PreviousMonth();

private:
    int year;
    int month;
    int day;
};

#endif
