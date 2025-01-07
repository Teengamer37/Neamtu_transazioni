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
    double calcBalance() const;
    bool addTransaction(Transaction::Type type, double amount, const std::string& description, Date date = Date::getPresentDate());
    bool addTransaction(const Transaction& t);
    bool makeCreditTransfer(Account& destination, double amount, Date date = Date::getPresentDate());
    std::vector<Transaction> searchTransactionsByDesc(const std::string& desc) const;
    std::vector<Transaction> searchTransactionsByType(Transaction::Type type) const;
    std::vector<Transaction> searchTransactionsByDate(const Date& date) const;
    std::vector<Transaction> filterTransactionsByDateInterval(const Date& start, const Date& end) const;
    std::vector<std::string> viewTransactions() const;
    std::vector<std::string> viewTransactionsByDateOrder() const;
    int getNumTransactions() const;
    double calculateTotalDeposits() const;
    double calculateTotalWithdrawals() const;
    Transaction getLargestTransaction() const;
    void clearTransactions();
    bool cancelTransaction(const Transaction& t);

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