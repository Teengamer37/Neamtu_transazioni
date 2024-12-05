#include "Transaction.h"

#include <utility>

Transaction::Transaction() {}

Transaction::Transaction(Type type, double amount, std::string description) :
                        type(type), amount(amount), description(std::move(description)) {}

//trasforma il contenuto della transazione in string per renderlo facilmente stampabile
std::string Transaction::toString() {
    std::string transactionType = (type == Transaction::DEPOSIT ? "Deposit" : "Withdrawal");
    return transactionType + " - " + std::to_string(amount) + " Euro - " + description;
}

//permette di determinare senza usare le parole-chiave dell'enum il tipo di transazione semplicemente in stringa
std::string Transaction::typeToString() {
    return (type == DEPOSIT) ? "Deposit" : "Withdrawal";
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