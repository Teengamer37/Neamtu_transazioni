#include "gtest/gtest.h"

#include "../Date.h"

TEST(DateTest, Constructor) {
    Date d5(2025, 9, 12);
    ASSERT_EQ(d5.getDay(), 12);
    ASSERT_EQ(d5.getMonth(), 9);
    ASSERT_EQ(d5.getYear(), 2025);

    Date d6 = d5;
    ASSERT_TRUE(d6==d5);
}

TEST(DateTest, TestCheckDate) {
    Date d7(2024,12,25);     //data normale
    Date d8(2024, 2, 29);    //data in anno bisestile
    Date d9(2023, 15, 41);   //data assurda
    Date d10(700, 15, 41);    //data <1980

    ASSERT_TRUE(d7.checkDate());
    ASSERT_TRUE(d8.checkDate());
    ASSERT_FALSE(d9.checkDate());
    ASSERT_FALSE(d10.checkDate());
}

TEST(DateTest, TestIsLeapYear) {
    ASSERT_TRUE(Date::isLeapYear(2020));
    ASSERT_TRUE(Date::isLeapYear(2016));
    ASSERT_TRUE(Date::isLeapYear(2000));
    ASSERT_FALSE(Date::isLeapYear(1900));
    ASSERT_FALSE(Date::isLeapYear(1951));
}