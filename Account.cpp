#include "Account.h"

const std::string &Account::getUsername() const {
    return username;
}

void Account::setUsername(const std::string &username) {
    Account::username = username;
}

const std::string &Account::getPassword() const {
    return password;
}

void Account::setPassword(const std::string &password) {
    Account::password = password;
}

const std::vector<Transaction> &Account::getTransactions() const {
    return transactions;
}

void Account::setTransactions(const std::vector<Transaction> &transactions) {
    Account::transactions = transactions;
}
