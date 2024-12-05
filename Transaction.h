#ifndef NEAMTU_TRANSAZIONI_TRANSACTION_H
#define NEAMTU_TRANSAZIONI_TRANSACTION_H

#include <string>

class Transaction {
public:
    enum Type {DEPOSIT, WITHDRAWAL};

    //costruttori
    Transaction();
    Transaction(Type type, double amount, std::string  description);

    //metodi
    std::string toString();
    std::string typeToString();

    //getter/setter
    Type getType() const;
    double getAmount() const;
    const std::string &getDescription() const;

private:
    Type type;
    double amount;
    std::string description;
};


#endif //NEAMTU_TRANSAZIONI_TRANSACTION_H