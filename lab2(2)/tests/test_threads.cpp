#include "../main_program/thread_utils.h"
#include "catch.hpp"
#include <windows.h>
#include <vector>

TEST_CASE("min_max correctly identifies min and max indices") {
    storage_t numbers;
    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(8);
    numbers.push_back(1);
    numbers.push_back(9);
    numbers.push_back(2); // min = 1 (index 3), max = 9 (index 4)

    minIndex = 0;
    maxIndex = 0;

    DWORD threadId;
    HANDLE hThread = CreateThread(NULL, 0, min_max, (void*)&numbers, 0, &threadId);
    REQUIRE(hThread != NULL);

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    REQUIRE(numbers[minIndex] == 1);
    REQUIRE(numbers[maxIndex] == 9);
}

TEST_CASE("average computes correct average") {
    storage_t numbers;
    numbers.push_back(2);
    numbers.push_back(4);
    numbers.push_back(6);
    numbers.push_back(8); // average = 5

    averageValue = 0;

    DWORD threadId;
    HANDLE hThread = CreateThread(NULL, 0, average, (void*)&numbers, 0, &threadId);
    REQUIRE(hThread != NULL);

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    REQUIRE(averageValue == 5);
}
