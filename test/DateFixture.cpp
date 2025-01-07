#include "gtest/gtest.h"

#include "../Date.h"


class DateSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        d1 = new Date(2025, 1, 7);     //data normale
        d2 = new Date(2024,12,25);     //data normale
        d3 = new Date(2024, 2, 29);    //data in anno bisestile
        d4 = new Date(2023, 15, 41);   //data assurda
    }

    Date* d1 = nullptr;  // XXX C++11 standard initialization
    Date* d2 = nullptr;
    Date* d3 = nullptr;
    Date* d4 = nullptr;
};

TEST_F(DateSuite, TestCheckDate) {
    //primi 3 ok
    ASSERT_TRUE(d1->checkDate());
    ASSERT_TRUE(d2->checkDate());
    ASSERT_TRUE(d3->checkDate());
    //ultimo no
    ASSERT_FALSE(d4->checkDate());
}

TEST_F(DateSuite, TestDateToString) {
    ASSERT_EQ(d1->dateToString(), "2025/1/7");
    ASSERT_EQ(d2->dateToString(), "2024/12/25");
    ASSERT_EQ(d3->dateToString(), "2024/2/29");
    ASSERT_EQ(d4->dateToString(), "2023/15/41");
}

TEST_F(DateSuite, TestOperators) {
    //test operator==
    ASSERT_TRUE(*d1==*d1);
    ASSERT_FALSE(*d1==*d2);
    ASSERT_FALSE(*d4==*d4);   //false per data non valida
    //test operator!=
    ASSERT_FALSE(*d1!=*d1);
    ASSERT_TRUE(*d1!=*d2);
    ASSERT_FALSE(*d1!=*d4);   //false per data non valida
    //test operator>=
    ASSERT_TRUE(*d1>=*d1);
    ASSERT_TRUE(*d1>=*d2);
    ASSERT_FALSE(*d3>=*d2);
    ASSERT_FALSE(*d4>=*d4);   //false per data non valida
    //test operator<=
    ASSERT_TRUE(*d1<=*d1);
    ASSERT_FALSE(*d1<=*d2);
    ASSERT_TRUE(*d3<=*d2);
    ASSERT_FALSE(*d4<=*d4);    //false per data non valida
    //test operator<
    ASSERT_TRUE(*d2<*d1);
    ASSERT_FALSE(*d1<*d2);
}