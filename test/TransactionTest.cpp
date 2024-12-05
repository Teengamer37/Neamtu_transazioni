#include "gtest/gtest.h"

#include "../Transaction.h"

TEST(Transaction, Constructor) {
    Transaction t(Transaction::DEPOSIT, 300, "first deposit");
    ASSERT_EQ(t.getAmount(), 300);
    ASSERT_EQ(t.getType(), Transaction::DEPOSIT);
    ASSERT_EQ(t.typeToString(), "Deposit");
    ASSERT_EQ(t.getDescription(), "first deposit");

    t = Transaction(Transaction::WITHDRAWAL, 300, "first withdrawal");
    ASSERT_EQ(t.getType(), Transaction::WITHDRAWAL);
}