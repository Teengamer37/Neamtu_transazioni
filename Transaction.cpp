#include "Transaction.h"

#include <utility>

Transaction::Transaction(Type type, double amount, std::string description) :
                        type(type), amount(amount), description(std::move(description)) {}

std::string Transaction::toString() {
    std::string transactionType = (type == Transaction::DEPOSIT ? "Deposit" : "Withdrawal");
    return transactionType + " - " + std::to_string(amount) + " Euro - " + description;
}

Transaction::Type Transaction::getType() const {
    return type;
}

void Transaction::setType(Transaction::Type type) {
    Transaction::type = type;
}

double Transaction::getAmount() const {
    return amount;
}

bool Transaction::setAmount(double amount) {
    if (amount <= 0) return false;

    Transaction::amount = amount;
    return true;
}

const std::string &Transaction::getDescription() const {
    return description;
}

void Transaction::setDescription(const std::string &description) {
    Transaction::description = description;
}