// marker_utils.cpp
#include "marker_utils.h"
#include <cstdlib>
#include <Windows.h>

bool tryMarkRandomElement(int threadId, int& randomNumber, int* arr, int arraySize, CRITICAL_SECTION& cs) {
    randomNumber = rand() % arraySize;
    bool success = false;

    EnterCriticalSection(&cs);
    if (arr[randomNumber] == 0) {
        Sleep(5);
        arr[randomNumber] = threadId + 1;
        Sleep(5);
        success = true;
    }
    LeaveCriticalSection(&cs);

    return success;
}

void clearMarksOfThread(int threadId, int* arr, int arraySize, CRITICAL_SECTION& cs) {
    EnterCriticalSection(&cs);
    for (int i = 0; i < arraySize; i++) {
        if (arr[i] == threadId + 1) {
            arr[i] = 0;
        }
    }
    LeaveCriticalSection(&cs);
}
