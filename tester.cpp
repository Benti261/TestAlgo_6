#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

struct TestCase {
    std::string name;
    std::string input;
    std::string expected;
};

std::string generateNumbers(int n, long long value) {
    if (n <= 0) return "";
    
    std::string result = std::to_string(value);
    std::string value_str = " " + std::to_string(value);
    
    result.reserve(n * (value_str.length() + 1));
    
    for (int i = 1; i < n; i++) {
        result += value_str;
    }
    return result;
}

std::string generateOnesWithSpaces(int n) {
    return generateNumbers(n, 1);
}

const int NUM_TESTS = 17;  
TestCase tests[NUM_TESTS] = {
    {"Test1", "5\n1 2 3 4 5", "9"},
    {"Test2", "5\n5 4 3 2 1", "9"},
    {"Test3", "4\n5 5 5 5", "20"},
    {"Test4", "1\n7", "7"},
    {"Test5", "2\n3 5", "6"},
    {"Test6", "6\n2 1 5 6 2 3", "10"},
    {"Test7", "7\n1 3 2 4 1 5 2", "7"},
    {"Test8", "8\n1 2 3 4 3 2 1 5", "10"},
    {"Test9", "4\n1000000000 1000000000 1000000000 1000000000", "4000000000"},
    {"Test10", "1\n10", "10"},
    {"Test11", "5\n1 2 3 4 100", "100"},
    {"Test12", "5\n100 4 3 2 1", "100"},
    {"Test13", "7\n1 2 3 4 3 2 1", "10"},
    {"Test14", "9\n1 2 3 4 4 4 3 2 1", "15"},
    {"Test15", "10\n1 3 2 5 4 3 6 2 1 4", "14"},
    {"Test16", "1000000\n" + generateNumbers(1000000, 1), "1000000"},
    {"Test17", "1000000\n" + generateNumbers(1000000, 1000000000), "1000000000000000"} 
};

std::string runProgram(const std::string& input) {
    std::string filename = "test_input.txt";
    std::ofstream file(filename);
    file << input;
    file.close();

    std::string command = "./main < " + filename;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "ERROR";

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    remove(filename.c_str());

    result.erase(result.find_last_not_of(" \n\r\t") + 1);
    return result;
}

int main() {
    std::cout << "Running tests for Histogram Max Area\n";
    std::cout << "====================================\n\n";

    int passed = 0;
    for (int i = 0; i < NUM_TESTS; i++) {
        const TestCase& test = tests[i];
        std::cout << test.name << ": ";
        std::string output = runProgram(test.input);

        if (output == test.expected) {
            std::cout << "✓ PASSED\n";
            passed++;
        } else {
            std::cout << "✗ FAILED\n";
            std::cout << "  Input: " << (test.input.length() > 100 ? test.input.substr(0, 100) + "..." : test.input) << "\n";
            std::cout << "  Expected: " << test.expected << "\n";
            std::cout << "  Got: " << output << "\n\n";
        }
    }

    std::cout << "\n====================================\n";
    std::cout << "Results: " << passed << "/" << NUM_TESTS << " passed\n";
    return 0;
}
