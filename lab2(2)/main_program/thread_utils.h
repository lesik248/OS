#pragma once
#include <vector>
#include <windows.h>

using element_t = int;
using storage_t = std::vector<element_t>;

extern volatile size_t minIndex;
extern volatile size_t maxIndex;
extern volatile element_t averageValue;

DWORD WINAPI min_max(LPVOID vectorPtr);
DWORD WINAPI average(LPVOID vectorPtr);
