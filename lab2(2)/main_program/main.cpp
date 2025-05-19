#include "thread_utils.h"
#include <iostream>
#include <windows.h>

int main() {
  size_t size;
  std::cout << "Enter array size: ";
  std::cin >> size;

  if (size <= 0) {
    std::cerr << "Array size must be greater than 0" << std::endl;
    return 1;
  }

  storage_t numbers(size);
  std::cout << "Enter array with " << size << " elements: ";
  for (element_t &elem : numbers) {
    std::cin >> elem;
  }

  DWORD IDThread;

  HANDLE hThreadMinMax = CreateThread(NULL, 0, min_max, (void *)&numbers, 0, &IDThread);
  if (hThreadMinMax == NULL) return GetLastError();

  std::cout << "Min-max thread with ID " << IDThread << " created" << std::endl;

  HANDLE hThreadAverage = CreateThread(NULL, 0, average, (void *)&numbers, 0, &IDThread);
  if (hThreadAverage == NULL) return GetLastError();

  std::cout << "Average thread with ID " << IDThread << " created" << std::endl;

  WaitForSingleObject(hThreadAverage, INFINITE);
  CloseHandle(hThreadAverage);

  WaitForSingleObject(hThreadMinMax, INFINITE);
  CloseHandle(hThreadMinMax);

  numbers[minIndex] = averageValue;
  numbers[maxIndex] = averageValue;

  for (int elem : numbers) std::cout << elem << " ";
  std::cout << std::endl;

  return 0;
}
