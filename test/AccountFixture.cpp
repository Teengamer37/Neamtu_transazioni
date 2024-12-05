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
    ASSERT_FALSE(a->addTransaction(Transaction::WITHDRAWAL, 200, "withdrawal from 0 account balance!"));
    ASSERT_FALSE(a->addTransaction(Transaction::DEPOSIT, -350, "negative deposit!"));
}

TEST_F(AccountSuite, TestLoadTransactions) {
    a->loadTransactions();
    ASSERT_EQ(a->getNumTransactions(), 2);
    ASSERT_EQ(a->getTransactions().size(), 2);
}

TEST_F(AccountSuite, TestAccountBalance) {
    a->clearTransactions();
    ASSERT_EQ(a->getNumTransactions(), 0);
    ASSERT_EQ(a->calcBalance(), 0);
    a->addTransaction(Transaction::DEPOSIT, 100, "deposit 100");
    a->addTransaction(Transaction::WITHDRAWAL, 50, "withdrawal 50");
    ASSERT_EQ(a->calcBalance(), 50);
}

TEST_F(AccountSuite, TestCreditTransfer) {
    Account b("jim", "1234");
    ASSERT_EQ(b.getNumTransactions(), 0);
    ASSERT_FALSE(a->makeCreditTransfer(b, 70));
    ASSERT_FALSE(a->makeCreditTransfer(b, -50));
    ASSERT_FALSE(a->makeCreditTransfer(reinterpret_cast<Account &>(a), 70));
    a->makeCreditTransfer(b, 20);
    ASSERT_EQ(a->getNumTransactions(), 3);
    ASSERT_EQ(b.getNumTransactions(), 1);
    ASSERT_EQ(a->calcBalance(), 30);
    ASSERT_EQ(b.calcBalance(), 20);
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
}
