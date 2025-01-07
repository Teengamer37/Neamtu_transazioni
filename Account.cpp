#include "Account.h"

#include <utility>
#include <fstream>
#include <algorithm>

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
    std::string typeStr, description, dateStr;
    double amount;
    while (file >> dateStr >> typeStr >> amount) {
        std::getline(file, description);

        //creo data di default (se mentre recupero la data dal file essa non è una vera data, inserisco la data di default)
        Date date(1980, 1, 1);
        std::vector<int> v(3);
        sscanf(dateStr.c_str(), "%d/%d/%d", &v[0], &v[1], &v[2]);
        //verifico se la data recuperata è corretta
        if (Date::checkDate(v[0], v[1], v[2])) date = Date(v[0], v[1], v[2]);

        Transaction::Type type = (typeStr == "Deposit") ? Transaction::DEPOSIT : Transaction::WITHDRAWAL;
        description = description.substr(1);
        transactions.emplace_back(type, amount, description, date);
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

    //immetto ad ogni riga la data, il tipo di transazione, la somma e la descrizione
    for (const auto& transaction : transactions) {
        file << transaction.getDateToString() << " " << (transaction.getType() == Transaction::DEPOSIT ? "Deposit" : "Withdrawal")
             << " " << transaction.getAmount() << " "  << transaction.getDescription() << "\n";
    }

    //chiudo il file
    file.close();
    return true;
}

//calcola il bilancio del conto corrente
double Account::calcBalance() const {
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
//l'attributo date è opzionale: se non viene inserito, viene messo in automatico la data odierna
bool Account::addTransaction(Transaction::Type type, double amount, const std::string& description, Date date) {
    //impedisco l'aggiunta se inserisco una somma di prelievo maggiore di quella che ho a disposizione...
    if (type == Transaction::WITHDRAWAL && calcBalance()-amount <= 0) return false;
    //...o se inserisco un valore <=0...
    if (amount <= 0) return false;
    //...o se la data non è conforme
    if (!date.checkDate()) return false;

    //aggiungo la transazione e la salvo nel file
    transactions.emplace_back(type, amount, description, date);
    saveTransactions();

    return true;
}

//aggiunge una transazione fornendo un oggetto Transaction
bool Account::addTransaction(const Transaction& t) {
    transactions.emplace_back(t);
    saveTransactions();

    return true;
}

//bonifico ordinario tra due conti correnti
bool Account::makeCreditTransfer(Account& destination, double amount, Date date) {
    //annullo l'operazione se la somma da trasferire è <=0...
    if (amount <= 0) return false;
    //...o se il mittente è anche il destinatario...
    if (this == &destination) return false;
    //...o se la somma da trasferire supera il bilancio del conto...
    if (calcBalance() < amount) return false;
    //...o se la data non è conforme
    if (!date.checkDate()) return false;

    //aggiungo prelievo al mittente e deposito al destinatario, salvando tutto nei loro file
    addTransaction(Transaction::WITHDRAWAL, amount, "Credit transfer to " + destination.username, date);
    saveTransactions();
    destination.addTransaction(Transaction::DEPOSIT, amount, "Credit transfer from " + username, date);
    destination.saveTransactions();
    return true;
}

//cerca le transazioni attraverso la descrizione
//(verrà evidenziata la transazione che conterrà una substring desc)
std::vector<Transaction> Account::searchTransactionsByDesc(const std::string& desc) const {
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

//cerca le transazioni attraverso la data della transazione
std::vector<Transaction> Account::searchTransactionsByDate(const Date& date) const {
    std::vector<Transaction> transactionsFound;

    //cerco tra le varie transazioni...
    for(const auto& transaction : transactions){
        //..se la data corrisponde...
        if(transaction.getDate()==date)
            //...aggiungo nel vector...
            transactionsFound.push_back(transaction);
    }

    //...e ritorno il vector
    return transactionsFound;
}

//trova tutte le transazioni comprese tra le due date
std::vector<Transaction> Account::filterTransactionsByDateInterval(const Date& start, const Date& end) const {
    //se data inizio non è minore strettamente di data fine, mi blocco
    //(se voglio cercare le transazioni di una sola data, uso searchTransactionsByDate)
    if(end<=start) {
        throw std::runtime_error("Start date is NOT > end date!");
    }

    std::vector<Transaction> transactionsFound;

    //cerco tra le varie transazioni...
    for(const auto& transaction : transactions){
        //...se la data della transazione rientra nell'intervallo...
        if(transaction.getDate() >= start && transaction.getDate() <= end)
            //...la aggiungo nel vector...
            transactionsFound.push_back(transaction);
    }

    //...e ritorno il vector
    return transactionsFound;
}

//ritorna un vector di stringhe con le varie descrizioni di tutte le transazioni
std::vector<std::string> Account::viewTransactions() const {
    std::vector<std::string> transactionVector;
    transactionVector.reserve(transactions.size());

    //inserisco nel vector tutti i toString generati dalle transazioni singole...
    for (auto transaction : transactions) {
        transactionVector.emplace_back(transaction.toString());
    }

    //...e ritorno il vector
    return transactionVector;
}

//ritorna un vector di stringhe con le varie transazioni in ordine cronologico (secondo la data)
std::vector<std::string> Account::viewTransactionsByDateOrder() const {
    std::vector<std::string> transactionVector;
    transactionVector.reserve(transactions.size());

    //salvo una copia delle transazioni in sortedTransactions e
    //ordino il vettore di transazioni con std::sort
    std::vector<Transaction> sortedTransactions = transactions;  // Copia delle transazioni
    std::sort(sortedTransactions.begin(), sortedTransactions.end(),[](const Transaction& t1, const Transaction& t2) {
                  return t1.getDate() < t2.getDate();  // Confronta le date
              });

    //inserisco nel vector tutti i toString generati dalle transazioni singole adesso ordinate...
    for (const auto& transaction : sortedTransactions) {
        transactionVector.emplace_back(transaction.toString());
    }

    //...e ritorno il vector
    return transactionVector;
}

//ritorna la dimensione del vector di transazioni
int Account::getNumTransactions() const {
    return transactions.size();
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
    Transaction t(Transaction::DEPOSIT, 0, "", Date(1980,1,1));
    //se non ho transazioni, finisco prima lanciando un errore
    if (transactions.empty()) {
        throw std::runtime_error("No transactions available");
    }

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

//cancella una specifica transazione che combaci tutti i dati (data, tipo, ammontare, descrizione)
bool Account::cancelTransaction(const Transaction& t) {
    //se non ho transazioni, finisco prima lanciando un errore
    if (transactions.empty()) {
        throw std::runtime_error("No transactions available");
    }

    //itero le transazioni...
    for (auto it = transactions.begin(); it != transactions.end(); it++) {
        //...fino a quando non trovo la transazione uguale a quella che sto cercando
        if (*it == t) {
            transactions.erase(it);
            return true;
        }
    }

    //se non trovo nulla, non cancello nulla
    return false;
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