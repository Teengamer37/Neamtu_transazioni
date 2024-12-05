#include "Account.h"

#include <utility>
#include <fstream>

Account::Account(std::string username, std::string password) :
                username(std::move(username)), password(std::move(password)) {}

bool Account::loadTransactions() {
    std::ifstream file(username + ".txt");

    //se il file è aperto, allora annullo l'operazione, visto che non posso accedere al file
    if (!file.is_open()) {
        return false;
    }

    //elimino le transazioni correnti dell'account (se ce ne sono) e scorro nel file salvando le transazioni
    transactions.clear();
    std::string typeStr, description;
    double amount;
    while (file >> typeStr >> amount) {
        std::getline(file, description);
        Transaction::Type type = (typeStr == "Deposit") ? Transaction::DEPOSIT : Transaction::WITHDRAWAL;
        description = description.substr(1);
        transactions.emplace_back(type, amount, description);
    }

    //chiudo il file
    file.close();
    return true;
}

bool Account::saveTransactions() const {
    std::ofstream file(username + ".txt");

    //se il file è aperto, allora termino l'operazione, visto che non posso accedere al file
    if (!file.is_open()) {
        return false;
    }

    //immetto ad ogni riga il tipo di transazione, la somma e la descrizione
    for (const auto& transaction : transactions) {
        file << (transaction.getType() == Transaction::DEPOSIT ? "Deposit" : "Withdrawal") << " "
             << transaction.getAmount() << " " << transaction.getDescription() << "\n";
    }

    //chiudo il file
    file.close();
    return true;
}

double Account::calcBalance() {
    double balance = 0.0;

    for (const auto& transaction : transactions) {
        //se è un DEPOSIT, allora viene aggiunta la somma al bilancio...
        if (transaction.getType() == Transaction::DEPOSIT) {
            balance += transaction.getAmount();
            //...al contrario, se è un WITHDRAWAL, si sottrae la somma dal bilancio
        } else {
            balance -= transaction.getAmount();
        }
    }

    return balance;
}

bool Account::addTransaction(Transaction::Type type, double amount, const std::string& description) {
    if (type == Transaction::WITHDRAWAL && calcBalance()-amount <= 0) return false;

    if (amount <= 0) return false;

    transactions.emplace_back(type, amount, description);

    return true;
}

const std::vector<Transaction> Account::searchTransactionsByDesc(const std::string& desc) {
    std::vector<Transaction> transactionsFound;

    for(auto transaction : transactions){
        if(transaction.getDescription().find(desc, 0) != std::string::npos)
            transactionsFound.push_back(transaction);
    }

    return transactionsFound;
}

const std::vector<std::string> Account::viewTransactions() {
    std::vector<std::string> transactionVector;
    transactionVector.reserve(transactions.size());

    for (auto transaction : transactions) {
        transactionVector.emplace_back(transaction.toString());
    }

    return transactionVector;
}

int Account::getNumTransactions() {
    return transactions.size();
}

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