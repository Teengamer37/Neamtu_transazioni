#ifndef NEAMTU_TRANSAZIONI_DATE_H
#define NEAMTU_TRANSAZIONI_DATE_H

#include <string>

class Date {
public:
    //costruttori
    Date(int year, int month, int day);
    Date(Date const &d);

    //metodi
    static bool checkDate(int t, int m, int d);
    bool checkDate() const;
    static bool isLeapYear(int year);
    std::string dateToString() const;
    static Date getPresentDate();

    //getter
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    //override operatori
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator<(const Date& other) const;

private:
    int day{}, month{}, year{};
};

#endif //NEAMTU_TRANSAZIONI_DATE_H