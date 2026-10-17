#include "LanguageModel.h"

#include <iostream>
#include <exception>

int main() {
    try {
        LanguageModel model(2);
        model.train("ababac");

        std::cout << "K-gram counts:\n";

        for (const auto& entry : model.getGramsCounts()) {
            std::cout << entry.first
                      << ": " << entry.second << '\n';
        }

        std::cout << "\nTransition counts:\n";

        for (const auto& entry : model.getTransitions()) {
            std::cout << entry.first << ": ";

            for (const auto& transition : entry.second) {
                std::cout << transition.first
                          << " = " << transition.second
                          << "  ";
            }

            std::cout << '\n';
        }

    } catch (const std::exception& e) {
        std::cerr << "slm: " << e.what() << '\n';
        return 1;
    }

    return 0;
}