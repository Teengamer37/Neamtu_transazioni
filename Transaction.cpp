#include "Transaction.h"

Transaction::Type Transaction::getType() const {
    return type;
}

void Transaction::setType(Transaction::Type type) {
    Transaction::type = type;
}

double Transaction::getAmount() const {
    return amount;
}

void Transaction::setAmount(double amount) {
    Transaction::amount = amount;
}

const std::string &Transaction::getDescription() const {
    return description;
}

void Transaction::setDescription(const std::string &description) {
    Transaction::description = description;
}
