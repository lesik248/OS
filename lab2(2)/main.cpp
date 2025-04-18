#include <iostream>
#include <vector>

#include <windows.h>

// типы для хранения данных
using element_t = int;
using storage_t = std::vector<element_t>;

volatile size_t minIndex = 0;
volatile size_t maxIndex = 0;

DWORD WINAPI min_max(LPVOID vectorPtr) {
  storage_t &numbers = *(storage_t *)vectorPtr;

  // Сравниваем с 1, т.к. первый элемент уже всегда минимальный и максимальный
  for (size_t i = 1; i < numbers.size(); i++) {
    // сравнение в условии выхода из цикла
    Sleep(7);

    if (numbers[i] < numbers[minIndex]) {
      minIndex = i;
    }
    Sleep(7);

    if (numbers[i] > numbers[maxIndex]) {
      maxIndex = i;
    }
    Sleep(7);
  }

  std::cout << "Min element: " << numbers[minIndex] << std::endl;
  std::cout << "Max element: " << numbers[maxIndex] << std::endl;

  return 0;
}

volatile element_t averageValue = 0;

DWORD WINAPI average(LPVOID vectorPtr) {
  storage_t &numbers = *(storage_t *)vectorPtr;

  averageValue = 0;
  for (size_t i = 0; i < numbers.size(); i++) {
    averageValue += numbers[i];

    Sleep(12);
  }

  averageValue /= numbers.size();

  std::cout << "Average value: " << averageValue << std::endl;

  return 0;
}

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

  // используем ссылку, чтобы сразу записывать элементы в массив
  for (element_t &elem : numbers) {
    std::cin >> elem;
  }

  DWORD IDThread;

  HANDLE hThreadMinMax =
      CreateThread(NULL, 0, min_max, (void *)&numbers, 0, &IDThread);
  if (hThreadMinMax == NULL)
    return GetLastError();

  std::cout << "Min-max thread with ID " << IDThread << " created" << std::endl;

  HANDLE hThreadAverage =
      CreateThread(NULL, 0, average, (void *)&numbers, 0, &IDThread);
  if (hThreadAverage == NULL)
    return GetLastError();

  std::cout << "Average thread with ID " << IDThread << " created" << std::endl;

  // ждем пока поток закончит работу
  WaitForSingleObject(hThreadAverage, INFINITE);
  // закрываем дескриптор потока
  CloseHandle(hThreadAverage);

  // ждем пока поток закончит работу
  WaitForSingleObject(hThreadMinMax, INFINITE);
  // закрываем дескриптор потока
  CloseHandle(hThreadMinMax);

  numbers[minIndex] = averageValue;
  numbers[maxIndex] = averageValue;

  for (int elem : numbers) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  return 0;
}
