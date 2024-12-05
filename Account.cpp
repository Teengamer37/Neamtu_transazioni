#include "Account.h"

#include <utility>
#include <fstream>

//definizione costruttore
Account::Account(std::string username, std::string password) :
                username(std::move(username)), password(std::move(password)) {}

//carica le transazioni da un file [username].txt
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

//salva le transazioni nel file [username].txt
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

//calcola il bilancio del conto corrente
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

//aggiunge una transazione
bool Account::addTransaction(Transaction::Type type, double amount, const std::string& description) {
    //impedisco l'aggiunta se inserisco una somma di prelievo maggiore di quella che ho a disposizione...
    if (type == Transaction::WITHDRAWAL && calcBalance()-amount <= 0) return false;
    //...o se inserisco un valore <=0
    if (amount <= 0) return false;

    //aggiungo la transazione e la salvo
    transactions.emplace_back(type, amount, description);
    saveTransactions();

    return true;
}

//bonifico ordinario tra due conti correnti
bool Account::makeCreditTransfer(Account& destination, double amount) {
    //annullo l'operazione se la somma da trasferire è <=0...
    if (amount <= 0) return false;
    //...o se il mittente è anche il destinatario...
    if (this == &destination) return false;
    //...o se la somma da trasferire supera il bilancio del conto
    if (calcBalance() < amount) return false;

    //aggiungo prelievo al mittente e deposito al destinatario, salvando tutto nei loro file
    addTransaction(Transaction::WITHDRAWAL, amount, "Credit transfer to " + destination.username);
    saveTransactions();
    destination.addTransaction(Transaction::DEPOSIT, amount, "Credit transfer from " + username);
    destination.saveTransactions();
    return true;
}

//cerca le transazioni attraverso la descrizione
//(verrà evidenziata la transazione che conterrà una substring desc)
std::vector<Transaction> Account::searchTransactionsByDesc(const std::string& desc) {
    std::vector<Transaction> transactionsFound;

    //cerco tra le varie transazioni...
    for(const auto& transaction : transactions){
        if(transaction.getDescription().find(desc, 0) != std::string::npos)
            //...aggiungo nel vector...
            transactionsFound.push_back(transaction);
    }

    //...e ritorno il vector
    return transactionsFound;
}

//cerca le transazioni attraverso il tipo di transazione (deposito o prelievo)
std::vector<Transaction> Account::searchTransactionsByType(Transaction::Type type) const {
    std::vector<Transaction> transactionsFound;

    //cerco tra le varie transazioni...
    for(const auto& transaction : transactions){
        if(transaction.getType()==type)
            //...aggiungo nel vector...
            transactionsFound.push_back(transaction);
    }

    //...e ritorno il vector
    return transactionsFound;
}

//ritorna un vector di stringhe con le varie descrizioni di tutte le transazioni
std::vector<std::string> Account::viewTransactions() {
    std::vector<std::string> transactionVector;
    transactionVector.reserve(transactions.size());

    //inserisco nel vector tutti i toString generati dalle transazioni singole...
    for (auto transaction : transactions) {
        transactionVector.emplace_back(transaction.toString());
    }

    //...e ritorno il vector
    return transactionVector;
}

//calcola l'ammontare dei depositi
double Account::calculateTotalDeposits() const {
    double deposits = 0;

    //cerco tra le transazioni quali sono i depositi...
    for (const auto& transaction : transactions) {
        if (transaction.getType()==Transaction::DEPOSIT) {
            //...sommo il loro valore...
            deposits += transaction.getAmount();
        }
    }

    //...e ritorno la somma indietro
    return deposits;
}

//calcola l'ammontare dei prelievi
double Account::calculateTotalWithdrawals() const {
    double withdrawals = 0;

    //cerco tra le transazioni quali sono i prelievi...
    for (const auto& transaction : transactions) {
        if (transaction.getType()==Transaction::WITHDRAWAL) {
            //...sommo il loro valore...
            withdrawals += transaction.getAmount();
        }
    }

    //...e ritorno la somma indietro
    return withdrawals;
}

//ritorna la transazione con l'ammontare più grande (indifferente se esso è prelievo o deposito)
Transaction Account::getLargestTransaction() const {
    Transaction t;
    //se non ho transazioni, finisco prima ritornando un Transaction non inizializzato
    if (transactions.empty()) return t;

    double max = 0;

    //faccio pian piano la comparazione tra max e l'ammontare della transazione, aggiornando poi t e max
    for (const auto& transaction : transactions) {
        if (transaction.getAmount() >= max) {
            max = transaction.getAmount();
            t = transaction;
        }
    }

    return t;
}

//rimuove tutte le transazioni dell'account
void Account::clearTransactions() {
    transactions.clear();
}

//ritorna la dimensione del vector di transazioni
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