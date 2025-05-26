#include "../src/marker_utils.h"
#include "catch.hpp"


TEST_CASE("tryMarkRandomElement eventually marks something") {
    int arraySize = 10;
    int* arr = new int[arraySize]();
    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);

    int threadId = 1;
    int markedIndex = -1;
    bool success = false;

    for (int i = 0; i < 100 && !success; ++i) {
        success = tryMarkRandomElement(threadId, markedIndex, arr, arraySize, cs);
    }

    REQUIRE(success == true);
    REQUIRE(markedIndex >= 0);
    REQUIRE(markedIndex < arraySize);
    REQUIRE(arr[markedIndex] == threadId + 1);

    DeleteCriticalSection(&cs);
    delete[] arr;
}


