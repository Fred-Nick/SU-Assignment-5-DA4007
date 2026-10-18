
// This file tests whether the constructor rejects an invalid k-gram size 
// and if the input file is too short to contain k-grams followed by a character

#include "LanguageModel.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        LanguageModel model(0);
        std::cout << "FAIL: Invalid k accepted\n";
    } catch (const std::invalid_argument&) {
        std::cout << "PASS: Invalid k rejected\n";
    }

    try {
        LanguageModel model(2);
        model.train("ab");
        std::cout << "FAIL: Short text accepted\n";
    } catch (const std::runtime_error&) {
        std::cout << "PASS: Short text rejected\n";
    }
}