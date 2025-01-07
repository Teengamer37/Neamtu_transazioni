#include <vector>
#include <ctime>
#include "Date.h"

//costruttori
Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}
Date::Date(const Date &d) = default;

//permette di verificare se l'anno è uno bisestile
bool Date::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//verifica se la combinazione anno-mese-giorno è una data valida (funzione static)
bool Date::checkDate(int y, int m, int d) {
    //non inserisco anni minori di 1980
    if (y<1980) return false;

    //vettore contenente i vari giorni per i rispettivi mesi
    //(metto apposta l'elemento in pos 0 = 0 affinché posso accedere al vettore direttamente tramite numero del mese)
    std::vector<int> daysInMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //se anno bisestile e il mese da analizzare è febbraio, modifico il numero di giorni di febbraio nel vettore
    if (m == 2 && isLeapYear(y)) daysInMonth[2] = 29;

    //controllo su mese e giorno
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > daysInMonth[m]) return false;

    return true;
}

//posso verificare anche la data di un oggetto Date (utile quando verifico se un oggetto Date in un file è corretto)
bool Date::checkDate() {
    return checkDate(year, month, day);
}

//unisce i 3 attributi giorno mese anno e mi restituisce una stringa in formato yyyy/mm/dd
std::string Date::dateToString() const {
    std::string dateStr = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
    return dateStr;
}

//restituisce un oggetto Date che contiene la data odierna
Date Date::getPresentDate() {
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;

    return {year, month, day};
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

//override operatore per controllare se 2 date sono uguali
bool Date::operator==(const Date &other) const {
    if (year == other.year && month == other.month && day == other.day) return true;
    return false;
}

//override operatore per controllare se 2 date sono diverse (chiamo operator== e inverto il risultato)
bool Date::operator!=(const Date &other) const {
    return !(*this==other);
}

//override operatore per controllare se data 1 >= data 2
bool Date::operator>=(const Date& other) const {
    if(year < other.year) return false;
    if(month < other.month) return false;
    if(day < other.day) return false;
    return true;
}

//override operatore per controllare se data 1 <= data 2
bool Date::operator<=(const Date& other) const {
    if(year > other.year) return false;
    if(month > other.month) return false;
    if(day > other.day) return false;
    return true;
}

//override operatore per controllare se data 1 < data 2
bool Date::operator<(const Date& other) const {
    return !(*this>=other);
}