#include "LanguageModel.h"
#include "TextGenerator.h"
#include <iostream>
#include <stdexcept>

int main() {
    LanguageModel model(3);
    model.train("ababac");
    TextGenerator generator(model);

    try {
        generator.generate(2);
        std::cout << "FAIL: Short output accepted\n";
    } catch (const std::invalid_argument&) {
        std::cout << "PASS: Short output rejected\n";
    }

    LanguageModel emptyModel(2);
    TextGenerator emptyGenerator(emptyModel);

    try {
        emptyGenerator.generate(5);
        std::cout << "FAIL: Empty model accepted\n";
    } catch (const std::runtime_error&) {
        std::cout << "PASS: Empty model rejected\n";
    }
}