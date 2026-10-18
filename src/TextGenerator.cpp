#include "TextGenerator.h"

#include <stdexcept>
#include <vector>

TextGenerator::TextGenerator(const LanguageModel& model)
    : model_(model), rng_(std::random_device{}()) {
}

std::string TextGenerator::generate(int length) {
    if (length < model_.getK()) {
        throw std::invalid_argument(
            "Output length must be at least k");
    }

    const auto& counts = model_.getGramsCounts();

    if (counts.empty()) {
        throw std::runtime_error("No k-grams available");
    }

    // Choose a starting k-gram based on frequency.
    std::vector<std::string> grams;
    std::vector<double> weights;

    for (const auto& entry : counts) {
        grams.push_back(entry.first);
        weights.push_back(entry.second);
    }

    std::discrete_distribution<std::size_t> startDist(
        weights.begin(), weights.end());

    std::string currentGram = grams[startDist(rng_)];
    std::string output = currentGram;

    while (static_cast<int>(output.size()) < length) {
        std::vector<char> characters;
        std::vector<double> probabilities;

        for (char c : model_.getAlphabet()) {
            double p =
                model_.getTransitionProbability(currentGram, c);

            if (p > 0.0) {
                characters.push_back(c);
                probabilities.push_back(p);
            }
        }

        if (characters.empty()) {
            break;
        }

        std::discrete_distribution<std::size_t> nextDist(
            probabilities.begin(), probabilities.end());

        char nextChar = characters[nextDist(rng_)];
        output += nextChar;

        currentGram = currentGram.substr(1) + nextChar;
    }

    return output;
}