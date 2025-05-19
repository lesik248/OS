#include "thread_utils.h"
#include <iostream>
#include <windows.h>

volatile size_t minIndex = 0;
volatile size_t maxIndex = 0;
volatile element_t averageValue = 0;

DWORD WINAPI min_max(LPVOID vectorPtr) {
    storage_t& numbers = *(storage_t*)vectorPtr;

    for (size_t i = 1; i < numbers.size(); ++i) {
        Sleep(7);
        if (numbers[i] < numbers[minIndex]) minIndex = i;
        Sleep(7);
        if (numbers[i] > numbers[maxIndex]) maxIndex = i;
        Sleep(7);
    }

    std::cout << "Min element: " << numbers[minIndex] << std::endl;
    std::cout << "Max element: " << numbers[maxIndex] << std::endl;

    return 0;
}

DWORD WINAPI average(LPVOID vectorPtr) {
    storage_t& numbers = *(storage_t*)vectorPtr;

    averageValue = 0;
    for (size_t i = 0; i < numbers.size(); ++i) {
        averageValue += numbers[i];
        Sleep(12);
    }
    averageValue /= numbers.size();

    std::cout << "Average value: " << averageValue << std::endl;

    return 0;
}
