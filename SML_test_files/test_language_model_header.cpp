#include "LanguageModel.h"
#include <iostream>

int main() {
    LanguageModel model(2);
    model.train("ababac");

    if (model.getK() != 2) {
        std::cout << "FAIL: Incorrect k\n";
        return 1;
    }

    if (model.getAlphabet().size() != 3) {
        std::cout << "FAIL: Incorrect alphabet\n";
        return 1;
    }

    if (model.getGramsCounts().empty()) {
        std::cout << "FAIL: No k-grams found\n";
        return 1;
    }

    std::cout << "PASS: LanguageModel.h interface works\n";
}