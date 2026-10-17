#include "LanguageModel.h"

#include <iomanip>
#include <iostream>
#include <exception>

int main() {
    try {
        LanguageModel model(2, 0.0);
        model.train("ababac");

        std::cout << std::fixed << std::setprecision(3);

        std::cout << "P(a | ab) = "
                  << model.getTransitionProbability("ab", 'a')
                  << '\n';

        std::cout << "P(b | ba) = "
                  << model.getTransitionProbability("ba", 'b')
                  << '\n';

        std::cout << "P(c | ba) = "
                  << model.getTransitionProbability("ba", 'c')
                  << '\n';

        std::cout << "P(a | ac) = "
                  << model.getTransitionProbability("ac", 'a')
                  << '\n';

    } catch (const std::exception& e) {
        std::cerr << "slm: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
