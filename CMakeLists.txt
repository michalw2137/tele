cmake_minimum_required(VERSION 3.17)

project(bledy_kody)

set(CMAKE_CXX_STANDARD 17)

add_executable(bledy_kody main.cpp source/Macierz.cpp include/Macierz.h source/Koder.cpp include/Koder.h source/Dekoder.cpp include/Dekoder.h source/ObslugaPlikow.cpp include/ObslugaPlikow.h)

