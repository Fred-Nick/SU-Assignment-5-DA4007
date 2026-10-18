#include "LanguageModel.h"
#include "TextGenerator.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string normalizeText(const std::string& text) {
    std::string result;

    for (std::size_t i = 0; i < text.size();) {
        // UTF-8 curly apostrophes: ’ and ‘
        if (i + 2 < text.size() &&
            static_cast<unsigned char>(text[i]) == 0xE2 &&
            static_cast<unsigned char>(text[i + 1]) == 0x80 &&
            (static_cast<unsigned char>(text[i + 2]) == 0x98 ||
             static_cast<unsigned char>(text[i + 2]) == 0x99)) {
            result += '\'';
            i += 3;
        }
        // UTF-8 en dash and em dash
        else if (i + 2 < text.size() &&
                 static_cast<unsigned char>(text[i]) == 0xE2 &&
                 static_cast<unsigned char>(text[i + 1]) == 0x80 &&
                 (static_cast<unsigned char>(text[i + 2]) == 0x93 ||
                  static_cast<unsigned char>(text[i + 2]) == 0x94)) {
            result += '-';
            i += 3;
        }
        // Copy ordinary ASCII characters
        else {
            unsigned char c =
                static_cast<unsigned char>(text[i]);

            if (c < 128) {
                result += static_cast<char>(c);
            } else {
                // Skip unsupported UTF-8 bytes
                ++i;
                continue;
            }

            ++i;
        }
    }

    return result;
}


int main(int argc, char* argv[]) {
    try {
        int pos = 1;
        double alpha = 0.0;

        // Read optional -a alpha.
        if (pos < argc && std::string(argv[pos]) == "-a") {
            if (pos + 1 >= argc) {
                throw std::invalid_argument(
                    "option -a requires a non-negative number");
            }

            std::string value = argv[pos + 1];
            std::size_t used = 0;

            try {
                alpha = std::stod(value, &used);
            } catch (const std::exception&) {
                throw std::invalid_argument(
                    "option -a requires a non-negative number");
            }

            if (used != value.size() ||
                !std::isfinite(alpha) || alpha < 0.0) {
                throw std::invalid_argument(
                    "option -a requires a non-negative number");
            }

            pos += 2;
        } else if (pos < argc && argv[pos][0] == '-') {
            throw std::invalid_argument("unknown option");
        }

        if (argc - pos != 3) {
            throw std::invalid_argument(
                "usage: slm [-a alpha] k filename length");
        }

        // Parse k.
        std::string kText = argv[pos++];
        std::size_t used = 0;
        int k;

        try {
            k = std::stoi(kText, &used);
        } catch (const std::exception&) {
            throw std::invalid_argument(
                "k must be a positive integer");
        }

        if (used != kText.size() || k <= 0) {
            throw std::invalid_argument(
                "k must be a positive integer");
        }

        std::string filename = argv[pos++];

        // Parse requested output length.
        std::string lengthText = argv[pos++];
        used = 0;
        int length;

        try {
            length = std::stoi(lengthText, &used);
        } catch (const std::exception&) {
            throw std::invalid_argument(
                "output length must be an integer at least k");
        }

        if (used != lengthText.size() || length <= 0 || length < k) {
            throw std::invalid_argument(
                "output length must be a positive integer at least k");
        }

        // Read the training file.
        std::ifstream file(filename);

        if (!file) {
            throw std::runtime_error(
                "cannot open file '" + filename + "'");
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();

        // Train the model and generate text.
        LanguageModel model(k, alpha);
        std::string text = normalizeText(buffer.str());
        model.train(text);

        TextGenerator generator(model);
        std::cout << generator.generate(length) << '\n';

    } catch (const std::exception& e) {
        std::cerr << "slm: " << e.what() << '\n';
        return 1;
    }

    return 0;
}