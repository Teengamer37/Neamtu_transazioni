#ifndef NEAMTU_TRANSAZIONI_ACCOUNT_H
#define NEAMTU_TRANSAZIONI_ACCOUNT_H


#include <string>
#include <vector>
#include "Transaction.h"

class Account {
public:
    Account(const std::string& username, const std::string& password);

    bool loadTransactions();
    bool saveTransactions() const;
    bool addTransaction();
    const std::vector<Transaction> searchTransactions();

    const std::string &getUsername() const;
    void setUsername(const std::string &username);
    const std::string &getPassword() const;
    void setPassword(const std::string &password);
    const std::vector<Transaction> &getTransactions() const;
    void setTransactions(const std::vector<Transaction> &transactions);

private:
    std::string username;
    std::string password;
    std::vector<Transaction> transactions;
};


#endif //NEAMTU_TRANSAZIONI_ACCOUNT_H
