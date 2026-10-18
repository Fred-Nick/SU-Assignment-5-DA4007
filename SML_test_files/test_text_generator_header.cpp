#include "LanguageModel.h"
#include "TextGenerator.h"
#include <iostream>
#include <string>

int main() {
    LanguageModel model(2);
    model.train("ababac");

    TextGenerator generator(model);
    std::string output = generator.generate(5);

    if (output.size() != 5) {
        std::cout << "FAIL: Incorrect output length\n";
        return 1;
    }

    std::cout << "PASS: TextGenerator.h interface works\n";
}

