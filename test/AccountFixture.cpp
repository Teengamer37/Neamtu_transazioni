#include "gtest/gtest.h"

#include "../Account.h"


class AccountSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        a = new Account("john", "pswd");
        a->addTransaction(Transaction::DEPOSIT, 100, "deposit 100");
        a->addTransaction(Transaction::WITHDRAWAL, 50, "withdrawal 50");
    }

    Account* a = nullptr;  // XXX C++11 standard initialization
};


TEST_F(AccountSuite, TestAddTransaction) {
    //50-200 = numero negativo: non dovrebbe far nulla
    ASSERT_FALSE(a->addTransaction(Transaction::WITHDRAWAL, 200, "withdrawal from 50 account balance!"));
    //amount negativo: non dovrebbe far nulla
    ASSERT_FALSE(a->addTransaction(Transaction::DEPOSIT, -350, "negative deposit!"));
}

TEST_F(AccountSuite, TestLoadTransactions) {
    //carico 2 transazioni da file (sincronizzato con GitHub)
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

TEST_F(AccountSuite, TestViewTransactions) {
    ASSERT_EQ(a->viewTransactions().size(), 2);
    a->addTransaction(Transaction::DEPOSIT, 700, "salary yay");
    ASSERT_EQ(a->viewTransactions().size(), 3);
}

TEST_F(AccountSuite, TestSearchLargestTransaction) {
    ASSERT_EQ(a->getLargestTransaction().getAmount(), 100);
    a->addTransaction(Transaction::DEPOSIT, 700, "salary yay");
    ASSERT_EQ(a->getLargestTransaction().getAmount(), 700);
}
