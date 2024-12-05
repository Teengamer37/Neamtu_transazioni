#ifndef NEAMTU_TRANSAZIONI_ACCOUNT_H
#define NEAMTU_TRANSAZIONI_ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class Account {
public:
    //costruttore
    Account(std::string username, std::string password);

    //metodi
    bool loadTransactions();
    bool saveTransactions() const;
    double calcBalance();
    bool addTransaction(Transaction::Type type, double amount, const std::string& description);
    bool makeCreditTransfer(Account& destination, double amount);
    std::vector<Transaction> searchTransactionsByDesc(const std::string& desc);
    std::vector<Transaction> searchTransactionsByType(Transaction::Type type) const;
    std::vector<std::string> viewTransactions();
    int getNumTransactions();
    double calculateTotalDeposits() const;
    double calculateTotalWithdrawals() const;
    Transaction getLargestTransaction() const;
    void clearTransactions();

    //getter/setter
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