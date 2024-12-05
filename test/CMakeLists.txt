cmake_minimum_required(VERSION 3.5)

set(CXX_STANDARD 11)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp
        TransactionTest.cpp
        AccountFixture.cpp
        AccountTest.cpp
)
add_executable(runAccountTransactionsTests ${TEST_SOURCE_FILES})
target_link_libraries(runAccountTransactionsTests gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)