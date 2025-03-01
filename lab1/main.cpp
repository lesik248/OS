#include "employee.h"

int main() {
    std::string binFile, reportFile; // имена бинарного файла и файла с отчётом
    int numRecords;
    double hourlyRate;

    std::cout << "Enter binary file name: ";
    std::cin >> binFile;
    std::cout << "Enter number of records: ";
    std::cin >> numRecords;

    std::string creatorCmd = "Creator.exe " + binFile + " " + std::to_string(numRecords);
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)creatorCmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Error starting Creator\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Enter report file name: ";
    std::cin >> reportFile;
    std::cout << "Enter hourly rate: ";
    std::cin >> hourlyRate;

    std::string reporterCmd = "Reporter.exe " + binFile + " " + reportFile + " " + std::to_string(hourlyRate);

    if (!CreateProcess(NULL, (LPSTR)reporterCmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Error starting Reporter\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Report generated successfully.\n";

    // Вывод отчёта на консоль
    std::ifstream in(reportFile);
    if (!in) {
        std::cerr << "Cannot open report file!" << std::endl;
        return 1;
    }

    std::cout << "\nReport from file \"" << reportFile << "\":" << std::endl;
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << std::endl;
    }

    in.close();
    return 0;
}
