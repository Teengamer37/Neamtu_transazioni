#include "Transaction.h"

#include <utility>

Transaction::Transaction() {}

Transaction::Transaction(Type type, double amount, std::string description) :
                        type(type), amount(amount), description(std::move(description)) {}

std::string Transaction::toString() {
    std::string transactionType = (type == Transaction::DEPOSIT ? "Deposit" : "Withdrawal");
    return transactionType + " - " + std::to_string(amount) + " Euro - " + description;
}

Transaction::Type Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}

const std::string &Transaction::getDescription() const {
    return description;
}

std::string Transaction::typeToString(Transaction::Type type) {
    return (type == DEPOSIT) ? "Deposit" : "Withdrawal";
}