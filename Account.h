#ifndef NEAMTU_TRANSAZIONI_ACCOUNT_H
#define NEAMTU_TRANSAZIONI_ACCOUNT_H


#include <string>
#include <vector>
#include "Transaction.h"

class Account {
public:
    Account(std::string  username, std::string  password);

    bool loadTransactions();
    bool saveTransactions() const;
    double calcBalance();
    bool addTransaction(Transaction::Type type, double amount, const std::string& description);
    const std::vector<Transaction> searchTransactionsByDesc(const std::string& desc);
    const std::vector<std::string> viewTransactions();
    int getNumTransactions();

    const std::string &getUsername() const;
    void setUsername(const std::string &username);
    const std::string &getPassword() const;
    void setPassword(const std::string &password);
    const std::vector<Transaction> &getTransactions() const;

private:
    std::string username;
    std::string password;
    std::vector<Transaction> transactions;
};


#endif //NEAMTU_TRANSAZIONI_ACCOUNT_H