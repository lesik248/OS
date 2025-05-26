#include <Windows.h>
#include <iostream>

using namespace std;

int arraySize = 0;
int* arr = nullptr;
CRITICAL_SECTION cs;
HANDLE* handleThreads;
HANDLE* handleThreadsAreStarted;
HANDLE* handleThreadsAreStopped;
HANDLE* handleThreadsAreExited;
#include "marker_utils.h"

void printArray() {
    for (int i = 0; i < arraySize; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

DWORD WINAPI marker(LPVOID threadIndexPtr) {
    int threadId = (int)(size_t)threadIndexPtr;

    WaitForSingleObject(handleThreadsAreStarted[threadId], INFINITE);
    int markedCounter = 0;

    srand(threadId);

    while (true) {
        int randomNumber = -1;

        if (tryMarkRandomElement(threadId, randomNumber, arr, arraySize, cs)) {
            markedCounter++;
        } else {
            cout << "\tThread #" << threadId + 1 << " marked " << markedCounter << " elements\n";
            cout << "\tFailed to mark index: " << randomNumber << "\n\n";

            SetEvent(handleThreadsAreStopped[threadId]);
            ResetEvent(handleThreadsAreStarted[threadId]);

            HANDLE hPair[] = {
                handleThreadsAreStarted[threadId],
                handleThreadsAreExited[threadId]
            };

            DWORD waitResult = WaitForMultipleObjects(2, hPair, FALSE, INFINITE);
            if (waitResult == WAIT_OBJECT_0 + 1) {
                clearMarksOfThread(threadId, arr, arraySize, cs);
                ExitThread(0);
            } else {
                ResetEvent(handleThreadsAreStopped[threadId]);
                continue;
            }
        }
    }
}

void initResources(int amountOfThreads) {
    InitializeCriticalSection(&cs);
    handleThreads = new HANDLE[amountOfThreads];
    handleThreadsAreStarted = new HANDLE[amountOfThreads];
    handleThreadsAreStopped = new HANDLE[amountOfThreads];
    handleThreadsAreExited = new HANDLE[amountOfThreads];
}

void createThreads(int amountOfThreads) {
    for (int i = 0; i < amountOfThreads; i++) {
        handleThreads[i] = CreateThread(NULL, 0, marker, (LPVOID)(size_t)i, 0, NULL);
        handleThreadsAreStarted[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        handleThreadsAreStopped[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        handleThreadsAreExited[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }
}

void cleanup(int amountOfThreads) {
    for (int i = 0; i < amountOfThreads; i++) {
        CloseHandle(handleThreads[i]);
        CloseHandle(handleThreadsAreStarted[i]);
        CloseHandle(handleThreadsAreStopped[i]);
        CloseHandle(handleThreadsAreExited[i]);
    }
    delete[] handleThreads;
    delete[] handleThreadsAreStarted;
    delete[] handleThreadsAreStopped;
    delete[] handleThreadsAreExited;
    delete[] arr;
    DeleteCriticalSection(&cs);
}

int main() {
    int amountOfThreads = 0;

    cout << "Enter array size: ";
    cin >> arraySize;
    arr = new int[arraySize]();

    cout << "Enter thread count: ";
    cin >> amountOfThreads;

    initResources(amountOfThreads);
    createThreads(amountOfThreads);

    for (int i = 0; i < amountOfThreads; i++) {
        SetEvent(handleThreadsAreStarted[i]);
    }

    int completed = 0;
    bool* exited = new bool[amountOfThreads]();

    while (completed < amountOfThreads) {
        WaitForMultipleObjects(amountOfThreads, handleThreadsAreStopped, TRUE, INFINITE);

        cout << "Current array: ";
        printArray();

        int stopId;
        cout << "Enter thread number to stop (1-based): ";
        cin >> stopId;
        stopId--;

        if (!exited[stopId]) {
            exited[stopId] = true;
            completed++;
            SetEvent(handleThreadsAreExited[stopId]);
            WaitForSingleObject(handleThreads[stopId], INFINITE);
        }

        cout << "Array after exit: ";
        printArray();

        for (int i = 0; i < amountOfThreads; i++) {
            if (!exited[i]) {
                ResetEvent(handleThreadsAreStopped[i]);
                SetEvent(handleThreadsAreStarted[i]);
            }
        }
    }

    cleanup(amountOfThreads);
    delete[] exited;
    return 0;
}
