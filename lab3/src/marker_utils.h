// marker_utils.h
#pragma once
#include <windows.h>

bool tryMarkRandomElement(int threadId, int& randomNumber, int* arr, int arraySize, CRITICAL_SECTION& cs);
void clearMarksOfThread(int threadId, int* arr, int arraySize, CRITICAL_SECTION& cs);
