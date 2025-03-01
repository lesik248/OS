#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <cstring>

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

struct employee {
    int num;        // ID сотрудника
    char name[10];  // Имя
    double hours;   // Отработанные часы
};

#endif