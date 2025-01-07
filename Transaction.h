#ifndef NEAMTU_TRANSAZIONI_TRANSACTION_H
#define NEAMTU_TRANSAZIONI_TRANSACTION_H

#include <string>
#include <vector>
#include "Date.h"

class Transaction {
public:
    enum Type {DEPOSIT, WITHDRAWAL};

    //costruttore
    Transaction(Type type, double amount, std::string description, const Date& date = Date::getPresentDate());

    //metodi
    std::string toString() const;
    std::string typeToString() const;
    std::string getDateToString() const;

    //getter
    Type getType() const;
    double getAmount() const;
    const std::string &getDescription() const;
    Date getDate() const;

    //override operatore
    bool operator==(const Transaction& other) const;

private:
    Type type;
    double amount;
    std::string description;
    Date date;
};


#endif //NEAMTU_TRANSAZIONI_TRANSACTION_H