#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int passed = 0;
int failed = 0;

void runTest(const std::string& description,
             const std::string& command,
             bool shouldSucceed) {
    int result = std::system(command.c_str());

    // std::system returns zero when the command succeeds.
    bool succeeded = (result == 0);

    if (succeeded == shouldSucceed) {
        std::cout << "PASS: " << description << '\n';
        ++passed;
    } else {
        std::cout << "FAIL: " << description << '\n';
        ++failed;
    }
}

int main() {
    // Create ASCII training text.
    {
        std::ofstream file("test_main_input.txt");
        file << "ababac";
    }

    // Create UTF-8 training text containing curly apostrophe and dash.
    {
        std::ofstream file("test_main_utf8.txt");
        file << "Infant\xE2\x80\x99s flesh\xE2\x80\x94it's fine.";
    }

    // Valid input and smoothing.
    runTest("Valid arguments",
            "./slm 2 test_main_input.txt 5 >/dev/null 2>&1",
            true);

    runTest("Pseudocount smoothing",
            "./slm -a 0.01 2 test_main_input.txt 10 >/dev/null 2>&1",
            true);

    // Invalid arguments.
    runTest("Reject k = 0",
            "./slm 0 test_main_input.txt 5 >/dev/null 2>&1",
            false);

    runTest("Reject output length smaller than k",
            "./slm 3 test_main_input.txt 2 >/dev/null 2>&1",
            false);

    runTest("Reject missing training file",
            "./slm 2 nonexistent_test_file.txt 5 >/dev/null 2>&1",
            false);

    runTest("Reject unknown option",
            "./slm -x 2 test_main_input.txt 5 >/dev/null 2>&1",
            false);

    runTest("Reject negative pseudocount",
            "./slm -a -1 2 test_main_input.txt 5 >/dev/null 2>&1",
            false);

    runTest("Reject missing pseudocount value",
            "./slm -a >/dev/null 2>&1",
            false);

    // Training text too short: k = 3, text length = 3.
    {
        std::ofstream file("test_main_short.txt");
        file << "abc";
    }

    runTest("Reject training text without a followed k-gram",
            "./slm 3 test_main_short.txt 5 >/dev/null 2>&1",
            false);

    // Test UTF-8 normalization.
    runTest("Accept UTF-8 training text",
            "./slm 2 test_main_utf8.txt 10 > test_main_output.txt 2>/dev/null",
            true);

    // Check that generated output contains only ASCII bytes.
    runTest("Generated output contains only ASCII bytes",
            "LC_ALL=C grep -qP '[^\\x00-\\x7F]' test_main_output.txt",
            false);

    std::remove("test_main_input.txt");
    std::remove("test_main_utf8.txt");
    std::remove("test_main_short.txt");
    std::remove("test_main_output.txt");

    std::cout << "\nResults: " << passed
              << " passed, " << failed << " failed\n";

    return failed == 0 ? 0 : 1;
}