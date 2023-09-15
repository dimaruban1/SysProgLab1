cmake_minimum_required(VERSION 3.26)
project(SysProgLab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(SysProgLab1 main.c
        headerFiles/hashTable.h
        headerFiles/alphabet.h
        headerFiles/resultStruct.h)
