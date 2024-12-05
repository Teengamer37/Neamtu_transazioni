#include "gtest/gtest.h"

#include "../Account.h"

TEST(Account, Constructor) {
    Account a("john", "pwd");
    ASSERT_EQ(a.getUsername(), "john");
    ASSERT_EQ(a.getPassword(), "pwd");
    ASSERT_EQ(a.getNumTransactions(), 0);
}

TEST(Account, TestCalculateTotalDeposits) {
    Account a("user1", "pass1");
    a.addTransaction(Transaction::DEPOSIT, 100, "Deposit 1");
    a.addTransaction(Transaction::DEPOSIT, 50, "Deposit 2");
    ASSERT_EQ(a.calculateTotalDeposits(), 150);
}

TEST(AccountTest, TestCalculateTotalWithdrawals) {
    Account a("user2", "pass2");
    a.addTransaction(Transaction::DEPOSIT, 300, "Deposit 1");
    a.addTransaction(Transaction::WITHDRAWAL, 100, "Withdrawal 1");
    a.addTransaction(Transaction::WITHDRAWAL, 50, "Withdrawal 2");
    ASSERT_EQ(a.calculateTotalWithdrawals(), 150);
}

TEST(AccountTest, TestNumTransactions) {
    Account a("user3", "pass3");
    ASSERT_EQ(a.getNumTransactions(), 0);
    a.addTransaction(Transaction::DEPOSIT, 100, "Deposit 1");
    ASSERT_EQ(a.getNumTransactions(), 1);
}

TEST(AccountTest, TestGetTransactions) {
    Account a("user4", "pass4");
    ASSERT_EQ(a.getTransactions().size(), 0);
    a.addTransaction(Transaction::DEPOSIT, 344, "Deposit 1");
    ASSERT_EQ(a.getTransactions().size(), 1);
    a.addTransaction(Transaction::WITHDRAWAL, 120, "Withdrawal 1");
    ASSERT_EQ(a.getTransactions().size(), 2);
    a.addTransaction(Transaction::WITHDRAWAL, 51.5, "Withdrawal 2");
    ASSERT_EQ(a.getTransactions().size(), 3);
}

TEST(AccountTest, TestClearTransactions) {
    Account a("user5", "pass5");
    a.addTransaction(Transaction::DEPOSIT, 300, "Deposit 1");
    a.addTransaction(Transaction::WITHDRAWAL, 100, "Withdrawal 1");
    a.addTransaction(Transaction::WITHDRAWAL, 50, "Withdrawal 2");
    ASSERT_EQ(a.getNumTransactions(), 3);
    a.clearTransactions();
    ASSERT_EQ(a.getNumTransactions(), 0);
}