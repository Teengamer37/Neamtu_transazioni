#include "gtest/gtest.h"

#include "../Account.h"


class AccountSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        a = new Account("john", "pswd");
        a->addTransaction(Transaction::DEPOSIT, 100, "deposit 100");
        a->addTransaction(Transaction::WITHDRAWAL, 50, "withdrawal 50", {2025, 10, 16});
    }

    Account* a = nullptr;  // XXX C++11 standard initialization
};


TEST_F(AccountSuite, TestAddTransaction) {
    //50-200 = numero negativo: non dovrebbe far nulla
    ASSERT_FALSE(a->addTransaction(Transaction::WITHDRAWAL, 200, "withdrawal from 50 account balance!"));
    //amount negativo: non dovrebbe far nulla
    ASSERT_FALSE(a->addTransaction(Transaction::DEPOSIT, -350, "negative deposit!"));
    //data nel passato: non dovrebbe far nulla
    ASSERT_FALSE(a->addTransaction(Transaction::DEPOSIT, 50, "old-timer transaction", {2022, 10, 1}));
    //data non conforme: non dovrebbe far nulla
    ASSERT_FALSE(a->addTransaction(Transaction::DEPOSIT, 50, "bizarre date", {2012, 18, 50}));
    //test addTransaction(Transaction t) (dovrebbe dare errore per data nel passato)
    ASSERT_FALSE(a->addTransaction(Transaction(Transaction::DEPOSIT, 20, "transaction in transaction", {2024, 11, 30})));
}

TEST_F(AccountSuite, TestLoadTransactions) {
    //carico 2 transazioni da file (sincronizzato con la repo)
    Account b("john", "pswd");
    b.loadTransactions();
    ASSERT_EQ(b.getNumTransactions(), 2);
    ASSERT_EQ(b.getTransactions().size(), 2);
}

TEST_F(AccountSuite, TestAccountBalance) {
    //elimino tutte le transazioni
    a->clearTransactions();
    ASSERT_EQ(a->getNumTransactions(), 0);
    ASSERT_EQ(a->calcBalance(), 0);
    //riaggiungo le transazioni - bilancio = 50
    a->addTransaction(Transaction::DEPOSIT, 100, "deposit 100");
    a->addTransaction(Transaction::WITHDRAWAL, 50, "withdrawal 50");
    ASSERT_EQ(a->calcBalance(), 50);
}

TEST_F(AccountSuite, TestCreditTransfer) {
    //creo nuovo account
    Account b("jim", "1234");
    b.addTransaction(Transaction::DEPOSIT, 100, "deposit 100");
    ASSERT_EQ(b.getNumTransactions(), 1);
    //errore: bilancio < 70
    ASSERT_FALSE(a->makeCreditTransfer(b, 70));
    //errore: valore negativo
    ASSERT_FALSE(a->makeCreditTransfer(b, -50));
    //errore: data "nel passato"
    ASSERT_FALSE(a->makeCreditTransfer(b, -50, {2022, 1, 1}));
    //errore: data non conforme
    ASSERT_FALSE(a->makeCreditTransfer(b, -50, {200, 1, 49}));
    //errore: stesso account
    ASSERT_FALSE(b.makeCreditTransfer(b, 20));
    a->makeCreditTransfer(b, 20);
    ASSERT_EQ(a->getNumTransactions(), 3);
    ASSERT_EQ(b.getNumTransactions(), 2);
    ASSERT_EQ(a->calcBalance(), 30);
    ASSERT_EQ(b.calcBalance(), 120);
}

TEST_F(AccountSuite, TestSearchTransactionsByDesc) {
    ASSERT_EQ(a->searchTransactionsByDesc("withdrawal").size(), 1);
    ASSERT_EQ(a->searchTransactionsByDesc("clap").size(), 0);
    ASSERT_EQ(a->searchTransactionsByDesc("0").size(), 2);
}

TEST_F(AccountSuite, TestSearchTransactionsByType) {
    ASSERT_EQ(a->searchTransactionsByType(Transaction::DEPOSIT).size(), 1);
    ASSERT_EQ(a->searchTransactionsByType(Transaction::WITHDRAWAL).size(), 1);
}

TEST_F(AccountSuite, TestSearchTransactionsByDate) {
    ASSERT_EQ(a->searchTransactionsByDate(Date::getPresentDate()).size(), 1);
    ASSERT_EQ(a->searchTransactionsByDate({2025, 10, 16}).size(), 1);
    ASSERT_EQ(a->searchTransactionsByDate({2022, 11, 30}).size(), 0);
}

TEST_F(AccountSuite, TestFilterTransactionsByDateInterval) {
    //errore: start>end
    ASSERT_ANY_THROW(a->filterTransactionsByDateInterval({2024, 12, 31}, {2023, 12, 31}));

    ASSERT_EQ(a->filterTransactionsByDateInterval({2024, 12, 31}, {2025, 12, 31}).size(), 2);
    ASSERT_EQ(a->filterTransactionsByDateInterval({2024, 12, 31}, {2025, 1, 5}).size(), 0);
}

TEST_F(AccountSuite, TestViewTransactions) {
    ASSERT_EQ(a->viewTransactions().size(), 2);
    a->addTransaction(Transaction::DEPOSIT, 700, "salary yay");
    ASSERT_EQ(a->viewTransactions().size(), 3);
}

TEST_F(AccountSuite, TestViewTransactionsByDateOrder) {
    ASSERT_EQ(a->viewTransactionsByDateOrder().size(), 2);
    a->addTransaction(Transaction::DEPOSIT, 710, "salary yay", {2025, 10, 16});
    ASSERT_EQ(a->viewTransactions()[2], "2025/10/16 - Deposit - 710.00 Euro - salary yay");
}

TEST_F(AccountSuite, TestSearchLargestTransaction) {
    ASSERT_EQ(a->getLargestTransaction().getAmount(), 100);
    a->addTransaction(Transaction::DEPOSIT, 700, "salary yay");
    ASSERT_EQ(a->getLargestTransaction().getAmount(), 700);
}

TEST_F(AccountSuite, TestCancelTransaction) {
    ASSERT_TRUE(a->cancelTransaction(Transaction(Transaction::WITHDRAWAL, 50, "withdrawal 50", {2025, 10, 16})));
    ASSERT_FALSE(a->cancelTransaction(Transaction(Transaction::WITHDRAWAL, 50, "withdrawal 50", {2025, 10, 16})));
    ASSERT_FALSE(a->cancelTransaction(Transaction(Transaction::DEPOSIT, 710, "salary yay", {2025, 10, 16})));
}