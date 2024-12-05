#ifndef NEAMTU_TRANSAZIONI_TRANSACTION_H
#define NEAMTU_TRANSAZIONI_TRANSACTION_H


#include <string>

class Transaction {
public:
    enum Type {DEPOSIT, WITHDRAWAL};

    Transaction(Type type, double amount, const std::string& description);

    const std::string toString();

    Type getType() const;
    void setType(Type type);
    double getAmount() const;
    void setAmount(double amount);
    const std::string &getDescription() const;
    void setDescription(const std::string &description);

private:
    Type type;
    double amount;
    std::string description;
};


#endif //NEAMTU_TRANSAZIONI_TRANSACTION_H
