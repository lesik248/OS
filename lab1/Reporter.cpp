
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: Reporter <input_binary> <output_text> <hourly_rate>\n";
        return 1;
    }

    std::ifstream binFile(argv[1], std::ios::binary);
    if (!binFile) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    std::ofstream txtFile(argv[2]);
    if (!txtFile) {
        std::cerr << "Error opening output file\n";
        return 1;
    }

    double rate = std::stod(argv[3]);


    employee emp;
    while (binFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        double salary = emp.hours * rate;
        txtFile << "ID: "<<emp.num << " Name: " << emp.name << " Work Hours: " << emp.hours << " Salary: " << salary << "\n";
    }


    binFile.close();
    txtFile.close();
    return 0;
}
