#include "catch.hpp"
#include <windows.h>
#include <string>
#include <fstream>

// Forward declare functions if not in a header
void CreateSenderProcesses(const std::string& file_name, int number_of_senders, HANDLE* hEventStarted);

// Test dummy file creation
TEST_CASE("File can be created and opened for writing") {
    std::string file_name = "test_output.txt";
    std::fstream file(file_name.c_str(), std::ios::out);
    REQUIRE(file.is_open());
    file << "Test\n";
    file.close();

    std::ifstream check(file_name.c_str());
    std::string line;
    std::getline(check, line);
    REQUIRE(line == "Test");
    check.close();

    // Clean up
    remove(file_name.c_str());
}

// Test CreateSenderProcesses behavior for dummy setup
TEST_CASE("CreateSenderProcesses does not crash with dummy handles") {
    const int num_senders = 1;
    HANDLE dummyHandles[num_senders];

    // Just test that it doesn't crash — real CreateProcess won't work in test
    REQUIRE_NOTHROW(CreateSenderProcesses("testfile.txt", num_senders, dummyHandles));

}

// ==== Sender message formatting logic test ====
std::string formatMessage(const std::string& input) {
    char message[21];
    for (size_t i = 0; i < input.length() && i < 20; ++i) {
        message[i] = input[i];
    }
    for (size_t i = input.length(); i < 20; ++i) {
        message[i] = '\0';
    }
    message[20] = '\n';
    return std::string(message, 21);
}

TEST_CASE("Sender message formatting", "[sender]") {
    SECTION("Short message") {
        std::string msg = "hello";
        std::string formatted = formatMessage(msg);
        REQUIRE(formatted.substr(0, 5) == "hello");
        REQUIRE(formatted[20] == '\n');
    }

    SECTION("Exact 20 characters") {
        std::string msg = "abcdefghijklmnopqrst";
        std::string formatted = formatMessage(msg);
        REQUIRE(formatted.substr(0, 20) == msg);
        REQUIRE(formatted[20] == '\n');
    }

    SECTION("Longer than 20 characters") {
        std::string msg = "abcdefghijklmnopqrstuvwxy"; // 25 chars
        std::string formatted = formatMessage(msg.substr(0, 20));
        REQUIRE(formatted.length() == 21);
        REQUIRE(formatted[20] == '\n');
    }
}
