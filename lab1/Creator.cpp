#include <iostream>
#include <fstream>
#include <cstring>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <filename> <number_of_records>\n";
        return 1;
    }

    std::ofstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    int count = std::stoi(argv[2]);
    for (int i = 0; i < count; ++i) {
        employee emp;
        std::cout << "Enter ID, name, hours: ";
        std::cin >> emp.num >> emp.name >> emp.hours;
        file.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    file.close();
    return 0;
}
