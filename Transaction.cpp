#include "Transaction.h"

#include <utility>

//costruttore
Transaction::Transaction(Type type, double amount, std::string description, const Date& date) :
                        type(type), amount(amount), description(std::move(description)), date(date) {}

//trasforma il contenuto della transazione in string per renderlo facilmente stampabile
std::string Transaction::toString() const {
    std::string transactionType = (type == Transaction::DEPOSIT ? "Deposit" : "Withdrawal");
    return date.dateToString() + " - " + transactionType + " - " + std::to_string(amount) + " Euro - " + description;
}

//permette di determinare senza usare le parole-chiave dell'enum il tipo di transazione semplicemente in stringa
std::string Transaction::typeToString() const {
    return (type == DEPOSIT) ? "Deposit" : "Withdrawal";
}

//ritorna la data della transazione in una stringa yyyy/mm/dd
std::string Transaction::getDateToString() const {
    return date.dateToString();
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

//ritorna direttamente l'oggetto Date
Date Transaction::getDate() const {
    return date;
}

//override di == per verificare se una transazione è identica all'altra
bool Transaction::operator==(const Transaction& other) const {
    if(type != other.type) return false;
    if(amount != other.amount) return false;
    if(description != other.description) return false;
    if(date != other.date) return false;
    return true;
}