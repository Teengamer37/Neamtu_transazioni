cmake_minimum_required(VERSION 3.28)
project(Neamtu_transazioni)

set(CMAKE_CXX_STANDARD 17)

add_executable(Neamtu_transazioni main.cpp
        Transaction.cpp
        Transaction.h
        Account.cpp
        Account.h)
