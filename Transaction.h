#ifndef NEAMTU_TRANSAZIONI_TRANSACTION_H
#define NEAMTU_TRANSAZIONI_TRANSACTION_H

#include <string>

class Transaction {
public:
    enum Type {DEPOSIT, WITHDRAWAL};

    Transaction();
    Transaction(Type type, double amount, std::string  description);

    std::string toString();

    Type getType() const;
    double getAmount() const;
    const std::string &getDescription() const;
    std::string typeToString();

private:
    Type type;
    double amount;
    std::string description;
};


#endif //NEAMTU_TRANSAZIONI_TRANSACTION_H