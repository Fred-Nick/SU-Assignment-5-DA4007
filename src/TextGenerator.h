#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include "LanguageModel.h"
#include <random>
#include <string>

class TextGenerator {
private:
    const LanguageModel& model_;
    std::mt19937 rng_;

public:
    explicit TextGenerator(const LanguageModel& model);
    std::string generate(int length);
};

#endif