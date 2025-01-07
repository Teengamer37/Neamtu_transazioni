#include "gtest/gtest.h"

#include "../Transaction.h"

TEST(Transaction, Constructor) {
    Transaction t1(Transaction::DEPOSIT, 300, "first deposit");
    ASSERT_EQ(t1.getAmount(), 300);
    ASSERT_EQ(t1.getType(), Transaction::DEPOSIT);
    ASSERT_EQ(t1.typeToString(), "Deposit");
    ASSERT_EQ(t1.getDescription(), "first deposit");
    ASSERT_EQ(t1.getDate(), Date::getPresentDate());
    ASSERT_EQ(t1.getDateToString(), Date::getPresentDate().dateToString());

    Transaction t2(Transaction::WITHDRAWAL, 300, "first withdrawal");
    ASSERT_EQ(t2.getType(), Transaction::WITHDRAWAL);

    ASSERT_EQ(t1==t2, false);
}